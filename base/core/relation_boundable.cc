#include "base/core/relation_boundable.h"

#include "base/core/relation.h"

namespace hyperkb {
namespace base {

bool SimpleRelationBoundable::BindRelation(const RelationPtr& relation) {
  std::string sname = relation->SemName();
  if (mBoundRelations.find(sname) != mBoundRelations.end()) {
    return false;
  }
  mBoundRelations[sname] = relation;
  return true;
}

bool SimpleRelationBoundable::UnbindRelation(const std::string& sname) {
  if (mBoundRelations.find(sname) != mBoundRelations.end()) {
    mBoundRelations.erase(sname);
    return true;
  }
  return false;
}
}  // namespace base
}  // namespace hyperkb