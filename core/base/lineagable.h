#pragma once

#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>

#include "base/element.h"

namespace hyperkb {

/**
 * @brief Lineage: an embedded relation contains the elements hierarchy to
 * reduce the link numbers and avoid link iteration when reasoning.
 */
class Lineagable {
public:
  /**
   * @brief Check whether the lineage contains specific parent.
   *
   * @param parent Element string key or pointer.
   * @return true
   * @return false
   */
  virtual bool HasParent(const std::string& parent) const = 0;
  bool HasParent(const ElementPtr& parent) const {
    return HasParent(GetElementKeyStr(parent));
  };

  /**
   * @brief Check whether the lineage contains specific child.
   *
   * @param child Element string key or pointer.
   * @return true
   * @return false
   */
  virtual bool HasChild(const std::string& child) const = 0;
  bool HasChild(const ElementPtr& child) const {
    return HasChild(GetElementKeyStr(child));
  };

  /**
   * @brief Add a parent to the lineage.
   *
   * @param parent Element pointer.
   * @return true if the parent is not existed and added successfully.
   * @return false if the parent already existing.
   */
  virtual bool AddParent(const ElementPtr& parent) = 0;

  /**
   * @brief Add a child to the lineage.
   *
   * @param child Element pointer.
   * @return true if the child is not existed and added successfully.
   * @return false if the child already existing.
   */
  virtual bool AddChild(const ElementPtr& child) = 0;

  /**
   * @brief Remove specific parent from the lineage.
   *
   * @param parent Element string key or pointer.
   * @return true if the parent is removed successfully.
   * @return false if the parent is absent.
   */
  virtual bool RemoveParent(const std::string& parent) = 0;
  bool RemoveParent(const ElementPtr& parent) {
    return RemoveParent(this->GetElementKeyStr(parent));
  }

  /**
   * @brief Remove specific child from the lineage.
   *
   * @param child Element string key or pointer.
   * @return true if the child is removed successfully.
   * @return false if the child is absent.
   */
  virtual bool RemoveChild(const std::string& child) = 0;
  bool RemoveChild(const ElementPtr& child) {
    return RemoveChild(this->GetElementKeyStr(child));
  };

protected:
  /**
   * @brief Inner helper func to customize element string key.
   *
   * @param ele Element pointer.
   * @return std::string
   *
   * TODO: optimize virtual func calls
   */
  virtual std::string GetElementKeyStr(const ElementPtr& ele) const = 0;
};

/**
 * @brief A kind of lineage with parent unions and children splits.
 */
class UnionSplitLineagable : public Lineagable {
  inline bool HasParent(const std::string& parent) const {
    return mParentsMap.find(parent) != mParentsMap.end();
  }

  inline bool HasChild(const std::string& child) const {
    return mChildrenMap.find(child) != mChildrenMap.end();
  }

  bool AddParent(const ElementPtr& parent);

  bool AddChild(const ElementPtr& child);

  bool RemoveParent(const std::string& parent);

  bool RemoveChild(const std::string& child);

  /**
   * @brief Add the given parents into a union or ensure they are alreay in a
   * union.
   * @param parents A list of element pointers.
   * @return true The given parents are added into a union.
   * @return false The given parents are alreayd in a union.
   */
  bool AddParentsUnion(const ElementPtr& parents...);

  /**
   * @brief Add the given children into a split or ensure they are alreay in a
   * split.
   * @param children A list of element pointers.
   * @return true The given children are added into a split.
   * @return false The given children are alreayd in a split.
   */
  bool AddChildrenSplit(const ElementPtr& children...);

  /**
   * @brief Check whether the given parents are in a union or not.
   * @param parents A list of element pointers.
   * @return true The given parents are in a union.
   * @return false They are not fully in a union.
   */
  bool HasUnionedParents(const ElementPtr& parents...);

  /**
   * @brief Check whether the given children are in a split or not.
   * @param children A list of element pointers.
   * @return true The given children are in a split.
   * @return false They are not fully in a split.
   */
  bool HasSplitChildren(const ElementPtr& children...);

  /**
   * @brief Eliminate the union bound between given parents.
   * @param parents A list of element pointers.
   * @return true The parents are present in a union and dismissed successfully.
   * @return false They are not fully present or dismissed failed.
   */
  bool DismissParentsUnion(const ElementPtr& parents...);

  /**
   * @brief Eliminate the split bound between given children.
   * @param children A list of element pointers.
   * @return true The children are present in a split and dismissed
   * successfully.
   * @return false They are not fully present or dismissed failed.
   */
  bool DismissChildrenSplit(const ElementPtr& children...);

protected:
  // Use global UUID as the default element key string.
  virtual std::string GetElementKeyStr(const ElementPtr& ele);

private:
  // All parents map for fast indexing
  std::unordered_map<std::string, ElementPtr> mParentsMap;
  // All children map for fast indexing
  std::unordered_map<std::string, ElementPtr> mChildrenMap;
  // Parents group representing composites of a concept
  std::list<std::set<ElementPtr>> mUnions;
  // Children group representing mutually exclusive relation
  std::list<std::set<ElementPtr>> mSplits;
};

}  // namespace hyperkb