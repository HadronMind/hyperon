#include "core/base/entity.h"

#include "core/base/relation.h"

namespace hyperkb {
namespace core {

bool Entity::BindRelation(const RelationPtr& relation) {
  std::string sname = relation->SemName();
  if (mBoundRelations.find(sname) != mBoundRelations.end()) {
    return false;
  }
  mBoundRelations[sname] = relation;
  return true;
}

bool Entity::UnbindRelation(const std::string& sname) {
  if (mBoundRelations.find(sname) != mBoundRelations.end()) {
    mBoundRelations.erase(sname);
    return true;
  }
  return false;
}
}  // namespace core
}  // namespace hyperkb