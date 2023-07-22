#include "base/lineagable.h"

#include <algorithm>

namespace hyperkb {

bool Lineagable::HasParent(const ElementPtr& parent) const {
  return HasParent(parent->GlobalId());
}

bool Lineagable::HasChild(const ElementPtr& child) const {
  return HasChild(child->GlobalId());
}

bool Lineagable::RemoveParent(const ElementPtr& parent) {
  return RemoveParent(parent->GlobalId());
}

bool Lineagable::RemoveChild(const ElementPtr& child) {
  return RemoveChild(child->GlobalId());
}

bool UnionSplitLineagable::HasParent(const std::string& parent) const {
  return mParentsMap.find(parent) != mParentsMap.end();
}

bool UnionSplitLineagable::HasChild(const std::string& child) const {
  return mChildrenMap.find(child) != mChildrenMap.end();
}

bool UnionSplitLineagable::AddParent(const ElementPtr& parent) {
  return mParentsMap
      .insert(std::pair<std::string, ElementPtr>(parent->GlobalId(), parent))
      .second;
}

bool UnionSplitLineagable::AddChild(const ElementPtr& child) {
  return mChildrenMap
      .insert(std::pair<std::string, ElementPtr>(child->GlobalId(), child))
      .second;
}

bool UnionSplitLineagable::RemoveParent(const std::string& parent) {
  if (parent.empty()) return false;

  auto it = mUnions.begin();
  while (it != mUnions.end()) {
    auto found = it->find(parent);
    if (found != it->end()) {
      if (it->size() == 1) {
        it = mUnions.erase(it);
      } else {
        it->erase(found);
      }
    } else {
      ++it;
    }
  }

  if (auto it = mParentsMap.find(parent); it != mParentsMap.end()) {
    mParentsMap.erase(it);
    return true;
  }
  return false;
}

bool UnionSplitLineagable::RemoveChild(const std::string& child) {
  if (child.empty()) return false;

  auto it = mSplits.begin();
  while (it != mSplits.end()) {
    auto found = it->find(child);
    if (found != it->end()) {
      if (it->size() == 1) {
        it = mSplits.erase(it);
      } else {
        it->erase(found);
      }
    } else {
      ++it;
    }
  }

  if (auto it = mChildrenMap.find(child); it != mChildrenMap.end()) {
    mChildrenMap.erase(it);
    return true;
  }
  return false;
}

bool UnionSplitLineagable::AddParentsUnion(
    const std::list<ElementPtr>& parents) {
  for_each(parents.begin(), parents.end(),
           [this](const ElementPtr& ele) { this->AddParent(ele); });
  bool found = HasUnionedParents(parents);
  if (!found) {
    std::set<std::string> newUnion;
    for (auto it = parents.begin(); it != parents.end(); ++it) {
      newUnion.insert((*it)->GlobalId());
    }
    mUnions.push_back(newUnion);
    found = true;
  }
  return found;
}

bool UnionSplitLineagable::AddChildrenSplit(
    const std::list<ElementPtr>& children) {
  for_each(children.begin(), children.end(),
           [this](const ElementPtr& ele) { this->AddChild(ele); });
  bool found = HasSplitChildren(children);
  if (!found) {
    std::set<std::string> newSplit;
    for (auto it = children.begin(); it != children.end(); ++it) {
      newSplit.insert((*it)->GlobalId());
    }
    mSplits.push_back(newSplit);
    found = true;
  }
  return found;
}

bool UnionSplitLineagable::HasUnionedParents(
    const std::list<ElementPtr>& parents) const {
  bool found = false;
  for (auto it = mUnions.begin(); it != mUnions.end(); ++it) {
    found = all_of(parents.begin(), parents.end(), [it](const ElementPtr& ele) {
      return it->find(ele->GlobalId()) != it->end();
    });
    if (found) {
      break;
    }
  }
  return found;
}

bool UnionSplitLineagable::HasSplitChildren(
    const std::list<ElementPtr>& children) const {
  bool found = false;
  for (auto it = mSplits.begin(); it != mSplits.end(); ++it) {
    found =
        all_of(children.begin(), children.end(), [it](const ElementPtr& ele) {
          return it->find(ele->GlobalId()) != it->end();
        });
    if (found) {
      break;
    }
  }
  return found;
}

bool UnionSplitLineagable::DismissParentsUnion(
    const std::list<ElementPtr>& parents) {
  bool ret = false;
  auto it = mUnions.begin();
  while (it != mUnions.end()) {
    bool all_found =
        all_of(parents.begin(), parents.end(), [it](const ElementPtr& ele) {
          return it->find(ele->GlobalId()) != it->end();
        });
    if (all_found) {
      it = mUnions.erase(it);
      ret = true;
    } else {
      ++it;
    }
  }
  return ret;
}

bool UnionSplitLineagable::DismissChildrenSplit(
    const std::list<ElementPtr>& children) {
  bool ret = false;
  auto it = mSplits.begin();
  while (it != mSplits.end()) {
    bool all_found =
        all_of(children.begin(), children.end(), [it](const ElementPtr& e) {
          return it->find(e->GlobalId()) != it->end();
        });
    if (all_found) {
      it = mSplits.erase(it);
      ret = true;
    } else {
      ++it;
    }
  }
  return ret;
}

}  // namespace hyperkb
