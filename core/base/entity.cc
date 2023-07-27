#include "core/base/entity.h"

#include "core/base/relation.h"

namespace hyperkb {
namespace core {

bool Entity::BindRelation(const RelationPtr& relation) {
  std::string sname = relation->SemName();
  if (mConnectedRelations.find(sname) != mConnectedRelations.end()) {
    return false;
  }
  mConnectedRelations[sname] = relation;
  return true;
}

bool Entity::UnbindRelation(const std::string& sname) {
  if (mConnectedRelations.find(sname) != mConnectedRelations.end()) {
    mConnectedRelations.erase(sname);
    return true;
  }
  return false;
}
}  // namespace core
}  // namespace hyperkb