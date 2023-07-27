#include "core/base/lineage.h"

#include <algorithm>

namespace hyperkb {
  namespace core {

bool UnionSplitLineage::HasParent(const std::string& parent) const {
  return mParentsMap.find(parent) != mParentsMap.end();
}

bool UnionSplitLineage::HasChild(const std::string& child) const {
  return mChildrenMap.find(child) != mChildrenMap.end();
}

bool UnionSplitLineage::AddParent(const ElementPtr& parent) {
  return mParentsMap
      .insert(std::pair<std::string, ElementPtr>(parent->SemName(), parent))
      .second;
}

bool UnionSplitLineage::AddChild(const ElementPtr& child) {
  return mChildrenMap
      .insert(std::pair<std::string, ElementPtr>(child->SemName(), child))
      .second;
}

bool UnionSplitLineage::RemoveParent(const std::string& parent) {
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

bool UnionSplitLineage::RemoveChild(const std::string& child) {
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

bool UnionSplitLineage::AddParentsUnion(const std::list<ElementPtr>& parents) {
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

bool UnionSplitLineage::AddChildrenSplit(
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

bool UnionSplitLineage::HasUnionedParents(
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

bool UnionSplitLineage::HasSplitChildren(
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

bool UnionSplitLineage::DismissParentsUnion(
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

bool UnionSplitLineage::DismissChildrenSplit(
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
}
