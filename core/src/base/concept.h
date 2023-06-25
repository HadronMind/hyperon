#pragma once

#include <fmt/core.h>

#include <limits>
#include <map>
#include <memory>
#include <string>

#include "category_manager.h"
#include "concept_repr.h"

namespace hyperkb {

class Concept;
using ConceptPtr = std::shared_ptr<Concept>;
class Entity;
using EntityPtr = std::shared_ptr<Entity>;
class Relation;
using RelationPtr = std::shared_ptr<Relation>;
class Role;
using RolePtr = std::shared_ptr<Role>;
class Context;
using ContextPtr = std::shared_ptr<Context>;
class Indv;
using IndvPtr = std::shared_ptr<Indv>;
class Link;
using LinkPtr = std::shared_ptr<Link>;

/**
 * @brief Base class to represent a general concept.
 *
 * We formulate an Entity-Relation model, as well as two supplementary
 * concepts of Role and Context to construct the whole picture.
 */
class Concept : public Element {
  friend class Category;

public:
  Concept(const std::string& inner_name, const CategoryPtr& category)
      : iname(inner_name), mCategory(category){};

  Concept(const std::string& inner_name, const CategoryPtr& category,
          const ElementPtr& parent_element, const ContextPtr& context)
      : iname(inner_name),
        mCategory(category),
        mParent(parent_element),
        mContext(context){};

  inline std::string inner_name() { return iname; }
  inline std::weak_ptr<Category>& category() { return mCategory; }
  inline ElementPtr& parent() { return mParent; }
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
  std::vector<ConceptReprPtr> get_repr(const ConceptRepr::repr_modal modal) {
    auto found = repr_map.find(modal);
    if (found != repr_map.end()) {
      return found->second;
    }
    return std::vector<ConceptReprPtr>{};
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

protected:
  explicit Concept(const Concept&) {}
  explicit Concept(Concept&&) {}

private:
  std::string iname;
  std::weak_ptr<Category> mCategory;
  ElementPtr mParent;
  ContextPtr mContext;
  uint32_t mMember;

  // stored representations
  std::map<ConceptRepr::repr_modal, std::vector<ConceptReprPtr>> repr_map;
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

class Entity : public Concept {
public:
  Entity() = default;

  bool is_entity() const { return true; }
};

class Relation : public Concept {
public:
  bool is_relation() const { return true; }
};

class Indv : public Entity {};

class Link : public Relation {};

class Role : public Concept {
public:
  bool is_role() const { return true; }
};

class Context : public Concept {};

}  // namespace hyperkb
