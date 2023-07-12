#include "lineagable.h"

namespace hyperkb {

std::string UnionSplitLineagable::GetElementKeyStr(const ElementPtr& ele) {
  return ele->GlobalId();
}

bool UnionSplitLineagable::AddParent(const ElementPtr& parent) {
  std::string pkey = GetElementKeyStr(parent);
  auto res =
      mParentsMap.insert(std::pair<std::string, ElementPtr>(pkey, parent));
  return res.second;
}

bool UnionSplitLineagable::AddChild(const ElementPtr& child) {
  std::string pkey = GetElementKeyStr(child);
  auto res =
      mChildrenMap.insert(std::pair<std::string, ElementPtr>(pkey, child));
  return res.second;
}

bool UnionSplitLineagable::RemoveParent(const std::string& parent) {
  auto it = mParentsMap.find(parent);
  if (it != mParentsMap.end()) {
    mParentsMap.erase(it);
    return true;
  }
  return false;
}

bool UnionSplitLineagable::RemoveChild(const std::string& child) {
  auto it = mChildrenMap.find(child);
  if (it != mChildrenMap.end()) {
    mChildrenMap.erase(it);
    return true;
  }
  return false;
}

bool UnionSplitLineagable::AddParentsUnion(const ElementPtr& parents...) {return false;}

bool UnionSplitLineagable::AddChildrenSplit(const ElementPtr& children...) {return false;}

}  // namespace hyperkb