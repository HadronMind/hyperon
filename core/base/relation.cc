#include "base/relation.h"

#include "base/entity.h"

namespace hyperkb {

bool Relation::HasEntity(const std::string& sname) const {
  return mEntities.find(sname) != mEntities.end();
}

bool Relation::AddEntity(const EntityPtr& entity) {
  if (mEntities.find(sname) == mEntities.end()) {
    mEntities[entity->SemName()] = entity;
    return true;
  }
  return false;
}

EntityPtr Relation::operator[](const std::string& sname) {
  if (mEntities.find(sname) != mEntities.end()) {
    return mEntities[sname];
  }
  return std::shared_ptr<Entity>();
}

bool Relation::GetEntity(const std::string& sname, EntityPtr& entity) {
  if (mEntities.find(sname) != mEntities.end()) {
    entity = mEntities[sname];
    return true;
  }
  return false;
}

bool Relation::EraseEntity(const std::string& sname) {
  if (mEntities.find(sname) != mEntities.end()) {
    mEntities.erase(sname);
    return true;
  }
  return false;
}

}  // namespace hyperkb