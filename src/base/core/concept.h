#pragma once

#include <limits>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>

#include "base/core/concept_repr.h"
#include "base/core/element.h"
#include "base/core/lineage.h"

namespace hyperkb {
namespace base {

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
class Concept : public Element, public UnionSplitLineage {
  friend class Category;

public:
  Concept() = delete;
  explicit Concept(const std::string& sname);
  Concept(const std::string& sname, const ConceptPtr& parent);
  Concept(const std::string& sname, const CategoryPtr& category);
  Concept(const std::string& sname, const ContextPtr& context);
  Concept(const std::string& sname, const ConceptPtr& parent,
          const CategoryPtr& category, const ContextPtr& context);

  /*override*/ inline std::string SemName() const { return sname; }

  inline bool IsEntity() const { return false; }
  inline bool IsRelation() const { return false; }
  inline bool IsRole() const { return false; }
  inline bool IsContext() const { return false; }

  CategoryPtr GetCategory() const;
  ContextPtr GetContext() const;

  /**
   * @brief Check the object is instantized from Concept subtype.
   * @return boolean
   */
  template <typename T>
  inline typename std::enable_if_t<std::is_base_of<Concept, T>::value, bool>
  IsInstanceOf() const {
    return std::dynamic_pointer_cast<T>(*this) != nullptr;
  }

  uint32_t ReprCount() const;
  uint32_t ReprCount(const ConceptRepr::REPR_MODAL modal) const;

  /**
   * @brief Add new presentation to this concept. This operation always succeeds
   * if a valid modal is given.
   * @param repr
   * @param modal
   */
  void AddRepr(const ConceptReprPtr& repr, const ConceptRepr::REPR_MODAL modal);
  std::list<ConceptReprPtr> GetRepr(const ConceptRepr::REPR_MODAL modal) const;

  // Concept in string is denoted by curly braces.
  virtual std::string ToString() const;

protected:
  explicit Concept(const Concept&) {}
  explicit Concept(Concept&&) {}

protected:
  // Semantic name
  std::string sname;

  // A concept must belong to a category, as specified or the default.
  std::weak_ptr<Category> mCategory;

  // An element would have an empty (default) or single related context when
  // user provides. A context link would be created when more than one contexts
  // are related to the element.
  std::weak_ptr<Context> mContext;

private:
  // TODO: support general properties

  // stored representations
  std::map<ConceptRepr::REPR_MODAL, std::list<ConceptReprPtr>> mReprMap;
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

}  // namespace base
}  // namespace hyperkb