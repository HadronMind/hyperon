#include "base/core/relation.h"

#include "base/core/concept.h"
#include "base/core/entity.h"

namespace hyperkb {
namespace base {

bool Relation::HasEntity(const std::string& sname) const {
  auto it = mContainedConcepts.find(sname);
  if (it != mContainedConcepts.end() && it->second->IsEntity()) {
    return true;
  }
  return false;
}

bool Relation::HasRelation(const std::string& sname) const {
  auto it = mContainedConcepts.find(sname);
  if (it != mContainedConcepts.end() && it->second->IsRelation()) {
    return true;
  }
  return false;
}

bool Relation::HasEntityOrRelation(const std::string& sname) const {
  return mContainedConcepts.find(sname) != mContainedConcepts.end();
}

bool Relation::AddEntity(const EntityPtr& entity) {
  if (mContainedConcepts.find(sname) == mContainedConcepts.end()) {
    mContainedConcepts[entity->SemName()] = entity;
    entity->BindRelation(shared_from_base<Relation>());
    return true;
  }
  return false;
}

bool Relation::AddRelation(const RelationPtr& relation) {
  if (mContainedConcepts.find(sname) == mContainedConcepts.end()) {
    mContainedConcepts[relation->SemName()] = relation;
    relation->BindRelation(shared_from_base<Relation>());
    return true;
  }
  return false;
}

bool Relation::GetEntity(const std::string& sname, EntityPtr& entity) {
  if (mContainedConcepts.find(sname) != mContainedConcepts.end()) {
    entity = std::dynamic_pointer_cast<Entity>(mContainedConcepts[sname]);
    return true;
  }
  return false;
}

bool Relation::GetRelation(const std::string& sname, RelationPtr& relation) {
  if (mContainedConcepts.find(sname) != mContainedConcepts.end()) {
    relation = std::dynamic_pointer_cast<Relation>(mContainedConcepts[sname]);
    return true;
  }
  return false;
}

bool Relation::EraseEntityOrRelation(const std::string& sname) {
  auto it = mContainedConcepts.find(sname);
  if (it != mContainedConcepts.end()) {
    if (std::dynamic_pointer_cast<Entity>(it->second)) {
      std::dynamic_pointer_cast<Entity>(it->second)
          ->UnbindRelation(this->SemName());
    } else if (std::dynamic_pointer_cast<Relation>(it->second)) {
      std::dynamic_pointer_cast<Relation>(it->second)
          ->UnbindRelation(this->SemName());
    } else {
      return false;
    }
    mContainedConcepts.erase(it);
    return true;
  }
  return false;
}

ConceptPtr Relation::operator[](const std::string& sname) {
  if (mContainedConcepts.find(sname) != mContainedConcepts.end()) {
    return mContainedConcepts[sname];
  }
  return ConceptPtr();
}

}  // namespace base
}  // namespace hyperkb