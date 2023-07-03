#pragma once

#include <fmt/core.h>

#include <limits>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>

#include "concept_repr.h"
#include "element.h"

namespace hyperkb {

class Concept;
using ConceptPtr = std::shared_ptr<Concept>;
class Context;
using ContextPtr = std::shared_ptr<Context>;
class Category;
using CategoryPtr = std::shared_ptr<Category>;

/**
 * @brief Base class to represent a general concept.
 *
 * We formulate an Entity-Relation model, as well as two supplementary
 * concepts of Role and Context to construct the whole picture.
 */
class Concept : public Element {
  friend class Category;

public:
  Concept(const std::string& iname, const CategoryPtr& category)
      : iname(iname), mCategory(category){};

  Concept(const std::string& iname, const CategoryPtr& category,
          const ElementPtr& parent_element, const ContextPtr& context)
      : iname(iname),
        mCategory(category),
        //     mParent(parent_element),
        mContext(context){};

  inline bool is_entity() const { return false; }
  inline bool is_relation() const { return false; }

  inline std::string inner_name() { return iname; }
  inline std::weak_ptr<Category>& category() { return mCategory; }
  // inline ElementPtr& parent() { return mParent; }
  inline ContextPtr& context() { return mContext; }

  /**
   * @brief Check the object is instantized from Concept subtype.
   *
   * @return boolean
   */
  template <typename T>
  inline typename std::enable_if_t<std::is_base_of<Concept, T>::value, bool>
  is_instance_of() {
    return std::dynamic_pointer_cast<T>(*this) != nullptr;
  }

  /**
   * @brief Add new presentation to this concept. This operation always succeeds
   * if a valid modal is given.
   * @param repr
   * @param modal
   */
  void add_repr(const ConceptReprPtr& repr,
                const ConceptRepr::repr_modal modal) {
    auto repr_vec = repr_map[modal];
    repr_vec.push_back(repr);
  }

  // TODO: add custom repr filter
  std::list<ConceptReprPtr> get_repr(const ConceptRepr::repr_modal modal) {
    auto found = repr_map.find(modal);
    if (found != repr_map.end()) {
      return found->second;
    }
    return std::list<ConceptReprPtr>{};
  }

  inline uint32_t repr_count() {
    uint32_t s = 0;
    for (auto it = repr_map.begin(); it != repr_map.end(); it++) {
      s += it->second.size();
    }
    return s;
  }

  inline uint32_t repr_count(const ConceptRepr::repr_modal modal) {
    return get_repr(modal).size();
  }

  // Concept in string is denoted by curly braces.
  std::string to_string() { return fmt::format("\\{{}\\}", iname); }

  // Lineage
  bool has_parent(const ConceptPtr& parent);
  bool has_parent(const std::string& parent);
  bool has_child(const ConceptPtr& child);
  bool has_child(const std::string& child);
  void add_parent(const ConceptPtr& parent);
  void add_parents(const ConceptPtr& parents...);
  void add_child(const ConceptPtr& child);
  void add_children(const ConceptPtr& children...);
  void remove_parent(const ConceptPtr& parent);
  void remove_parent(const std::string& parent);
  void remove_child(const ConceptPtr& child);
  void remove_child(const std::string& child);
  void add_parents_union(const ConceptPtr& parents...);
  void add_children_split(const ConceptPtr& children...);
  bool has_unioned_parents(const ConceptPtr& parents...);
  bool has_unioned_parents(const std::string& parents...);
  bool has_split_children(const ConceptPtr& children...);
  bool has_split_children(const std::string& children...);
  void dismiss_parents_union(const ConceptPtr& parents...);
  void dismiss_parents_union(const std::string& parents...);
  void dismiss_children_split(const ConceptPtr& children...);
  void dismiss_children_split(const std::string& children...);

protected:
  explicit Concept(const Concept&) {}
  explicit Concept(Concept&&) {}

private:
  std::string iname;
  std::weak_ptr<Category> mCategory;

  // An element would have an empty (default) or single related context when
  // user provides. A context link would be created when more than one contexts
  // are related to the element.
  ContextPtr mContext;

  // stored representations
  std::map<ConceptRepr::repr_modal, std::list<ConceptReprPtr>> repr_map;

  // Lineage: an embedded relation contains the conceptual hierarchy to reduce
  // the link numbers and avoid link iteration when reasoning.
  std::map<std::string, ConceptPtr> mParentsMap;
  std::map<std::string, ConceptPtr> mChildrenMap;
  // Parents group representing composites of a concept
  std::list<std::set<ConceptPtr>> mUnions;
  // Children group representing mutually exclusive relation
  std::list<std::set<ConceptPtr>> mSplits;

  // TODO: support general properties
};

/**
 * Create ConceptPtr of specific subclass using appropriate constructor.
 */
template <typename T, typename... Args>
static inline typename std::enable_if_t<std::is_base_of<Concept, T>::value,
                                        std::shared_ptr<T>>
create_concept(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

/**
 * Cast ConceptPtr to the specific Concept subclass.
 */
template <typename T>
static inline typename std::enable_if_t<std::is_base_of<Concept, T>::value,
                                        std::shared_ptr<T>>
cast_from_concept(const ConceptPtr& concept) {
  return std::dynamic_pointer_cast<T>(concept);
}

/**
 * Cast specific Concept subclass to ConceptPtr.
 */
template <typename T>
static inline
    typename std::enable_if_t<std::is_base_of<Concept, T>::value, ConceptPtr>
    cast_to_concept(const std::shared_ptr<const T>& concept) {
  return std::dynamic_pointer_cast<Concept>(
      std::const_pointer_cast<T>(concept));
}

}  // namespace hyperkb
