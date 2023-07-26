#include "base/entity.h"

#include "base/relation.h"

namespace hyperkb {

bool Entity::BindRelation(const RelationPtr& relation) {
  std::string sname = relation->SemName();
  if (mConnectedRelations.find(sname) != mConnectedRelations.end()) {
    return false;
  }
  mConnectedRelations[sname] = relation;
}

bool Entity::UnbindRelation(const std::string& sname) {
  if (mConnectedRelations.find(sname) != mConnectedRelations.end()) {
    mConnectedRelations.erase(sname);
    return true;
  }
  return false;
}
}  // namespace hyperkb