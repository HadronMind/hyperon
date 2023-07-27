#include "core/base/relation.h"

#include "core/base/entity.h"

namespace hyperkb {
  namespace core {

bool Relation::HasEntity(const std::string& sname) const {
  return mEntities.find(sname) != mEntities.end();
}

bool Relation::AddEntity(const EntityPtr& entity) {
  if (mEntities.find(sname) == mEntities.end()) {
    mEntities[entity->SemName()] = entity;
    entity->BindRelation(shared_from_base<Relation>());
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
  auto it = mEntities.find(sname);
  if (it != mEntities.end()) {
    it->second->UnbindRelation(this->SemName());
    mEntities.erase(it);
    return true;
  }
  return false;
}

}  // namespace hyperkb
}