#pragma once

#include "base/lineagable.h"

namespace hyperkb {

/**
 * @brief A kind of lineage with parent unions and children splits.
 */
class UnionSplitLineage : public Lineagable {
  /* override */ bool HasParent(const std::string& parent) const;
  /* override */ bool HasChild(const std::string& child) const;
  /* override */ bool AddParent(const ElementPtr& parent);
  /* override */ bool AddChild(const ElementPtr& child);
  /* override */ bool RemoveParent(const std::string& parent);
  /* override */ bool RemoveChild(const std::string& child);

  /**
   * @brief Add the given parents into a union or ensure they are already in a
   * union.
   * @param parents A list of element pointers.
   * @return true The given parents are added into a union.
   * @return false The given parents are alreayd in a union.
   */
  bool AddParentsUnion(const std::list<ElementPtr>& parents);

  /**
   * @brief Add the given children into a split or ensure they are already in a
   * split.
   * @param children A list of element pointers.
   * @return true The given children are added into a split.
   * @return false The given children are alreayd in a split.
   */
  bool AddChildrenSplit(const std::list<ElementPtr>& children);

  /**
   * @brief Check whether the given parents are in a union or not.
   * @param parents A list of element pointers.
   * @return true The given parents are in a union.
   * @return false They are not fully in a union.
   */
  bool HasUnionedParents(const std::list<ElementPtr>& parents) const;

  /**
   * @brief Check whether the given children are in a split or not.
   * @param children A list of element pointers.
   * @return true The given children are in a split.
   * @return false They are not fully in a split.
   */
  bool HasSplitChildren(const std::list<ElementPtr>& children) const;

  /**
   * @brief Eliminate the union bound between given parents. All unions
   * containing given parents are dismissed.
   * @param parents A list of element pointers.
   * @return true The parents are present in a union and dismissed successfully.
   * @return false They are not fully present or dismissed failed.
   */
  bool DismissParentsUnion(const std::list<ElementPtr>& parents);

  /**
   * @brief Eliminate the split bound between given children. All splits
   * containing given children are dismissed.
   * @param children A list of element pointers.
   * @return true The children are present in a split and dismissed
   * successfully.
   * @return false They are not fully present or dismissed failed.
   */
  bool DismissChildrenSplit(const std::list<ElementPtr>& children);

private:
  // All parents map for fast indexing
  std::unordered_map<std::string, ElementPtr> mParentsMap;
  // All children map for fast indexing
  std::unordered_map<std::string, ElementPtr> mChildrenMap;
  // Parents group representing composites of a concept
  std::list<std::set<std::string>> mUnions;
  // Children group representing mutually exclusive relation
  std::list<std::set<std::string>> mSplits;
};
}  // namespace hyperkb