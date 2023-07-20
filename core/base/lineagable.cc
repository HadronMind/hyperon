#include "base/lineagable.h"

namespace hyperkb {

bool Lineagable::HasParent(const ElementPtr& parent) const {
  return HasParent(GetElementKeyStr(parent));
}

bool Lineagable::HasChild(const ElementPtr& child) const {
  return HasChild(GetElementKeyStr(child));
}

bool Lineagable::RemoveParent(const ElementPtr& parent) {
  return RemoveParent(GetElementKeyStr(parent));
}

bool Lineagable::RemoveChild(const ElementPtr& child) {
  return RemoveChild(GetElementKeyStr(child));
}

bool UnionSplitLineagable::HasParent(const std::string& parent) const {
  return mParentsMap.find(parent) != mParentsMap.end();
}

bool UnionSplitLineagable::HasChild(const std::string& child) const {
  return mChildrenMap.find(child) != mChildrenMap.end();
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

bool UnionSplitLineagable::AddParentsUnion(const ElementPtr& parents...) {
  return false;
}

bool UnionSplitLineagable::AddChildrenSplit(const ElementPtr& children...) {
  return false;
}

std::string UnionSplitLineagable::GetElementKeyStr(const ElementPtr& ele) {
  return ele->GlobalId();
}

}  // namespace hyperkb