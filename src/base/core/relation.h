#pragma once

#include "base/core/concept.h"
#include "base/core/relation_boundable.h"

namespace hyperon {
namespace base {

class Entity;
using EntityPtr = std::shared_ptr<Entity>;
class Relation;
using RelationPtr = std::shared_ptr<Relation>;

/**
 * @brief In the Entity-Relation model, a relation defines a interconnection,
 * i.e. hyperedge, of multiple entities or other relations.
 */
class Relation : public Concept, public SimpleRelationBoundable {
public:
  /* override */ inline bool IsRelation() const { return true; }

  virtual bool HasEntity(const std::string& sname) const;
  virtual bool HasRelation(const std::string& sname) const;
  virtual bool HasEntityOrRelation(const std::string& sname) const;
  virtual bool AddEntity(const EntityPtr& entity);
  virtual bool AddRelation(const RelationPtr& relation);
  virtual bool GetEntity(const std::string& sname, EntityPtr& entity);
  virtual bool GetRelation(const std::string& sname, RelationPtr& relation);
  virtual bool EraseEntityOrRelation(const std::string& sname);

  ConceptPtr operator[](const std::string& sname);

protected:
  std::map<std::string, ConceptPtr> mContainedConcepts;
};

template <typename T, typename... Args>
static inline typename std::enable_if_t<std::is_base_of<Relation, T>::value,
                                        std::shared_ptr<T>>
create_relation(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
static inline typename std::enable_if_t<std::is_base_of<Relation, T>::value,
                                        std::shared_ptr<T>>
cast_from_relation(const RelationPtr& relation) {
  return std::dynamic_pointer_cast<T>(relation);
}

template <typename T>
static inline
    typename std::enable_if_t<std::is_base_of<Relation, T>::value, RelationPtr>
    cast_to_relation(const std::shared_ptr<const T>& subrel) {
  return std::dynamic_pointer_cast<Relation>(
      std::const_pointer_cast<T>(subrel));
}

}  // namespace base
}  // namespace hyperon
