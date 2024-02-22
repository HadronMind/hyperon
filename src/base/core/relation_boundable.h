#pragma once

#include <map>
#include <memory>
#include <string>

namespace hyperon {
namespace base {

class Relation;
using RelationPtr = std::shared_ptr<Relation>;

class RelationBoundable {
public:
  virtual bool BindRelation(const RelationPtr& relation) = 0;
  virtual bool UnbindRelation(const std::string& sname) = 0;
  virtual bool IsRelationBoundable() { return true; }
};

class SimpleRelationBoundable {
public:
  virtual bool BindRelation(const RelationPtr& relation);
  virtual bool UnbindRelation(const std::string& sname);

private:
  std::map<std::string, std::weak_ptr<Relation>> mBoundRelations;
};

}  // namespace base
}  // namespace hyperon