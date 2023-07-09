#pragma once

#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>

#include "element.h"

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
  virtual bool has_parent(const std::string& parent) = 0;
  bool has_parent(const ElementPtr& parent) {
    return has_parent(_element_key_string(parent));
  };

  /**
   * @brief Check whether the lineage contains specific child.
   *
   * @param child Element string key or pointer.
   * @return true
   * @return false
   */
  virtual bool has_child(const std::string& child) = 0;
  bool has_child(const ElementPtr& child) {
    return has_child(_element_key_string(child));
  };

  /**
   * @brief Add a parent to the lineage.
   *
   * @param parent Element pointer.
   * @return true if the parent is not existed and added successfully.
   * @return false if the parent already existing.
   */
  virtual bool add_parent(const ElementPtr& parent) = 0;

  /**
   * @brief Add a child to the lineage.
   *
   * @param child Element pointer.
   * @return true if the child is not existed and added successfully.
   * @return false if the child already existing.
   */
  virtual bool add_child(const ElementPtr& child) = 0;

  /**
   * @brief Remove specific parent from the lineage.
   *
   * @param parent Element string key or pointer.
   * @return true if the parent is removed successfully.
   * @return false if the parent is absent.
   */
  virtual bool remove_parent(const std::string& parent) = 0;
  bool remove_parent(const ElementPtr& parent) {
    return remove_parent(_element_key_string(parent));
  }

  /**
   * @brief Remove specific child from the lineage.
   *
   * @param child Element string key or pointer.
   * @return true if the child is removed successfully.
   * @return false if the child is absent.
   */
  virtual bool remove_child(const std::string& child) = 0;
  bool remove_child(const ElementPtr& child) {
    return remove_child(_element_key_string(child));
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
  virtual std::string _element_key_string(const ElementPtr& ele) = 0;
};

/**
 * @brief A kind of lineage with parent unions and children splits.
 */
class UnionSplitLineagable : public Lineagable {
  inline bool has_parent(const std::string& parent) {
    return mParentsMap.find(parent) != mParentsMap.end();
  }

  inline bool has_child(const std::string& child) {
    return mChildrenMap.find(child) != mChildrenMap.end();
  }

  inline bool add_parent(const ElementPtr& parent) {
    std::string pkey = _element_key_string(parent);
    auto res =
        mParentsMap.insert(std::pair<std::string, ElementPtr>(pkey, parent));
    return res.second;
  }

  inline bool add_child(const ElementPtr& child) {
    std::string pkey = _element_key_string(child);
    auto res =
        mChildrenMap.insert(std::pair<std::string, ElementPtr>(pkey, child));
    return res.second;
  }

  inline bool remove_parent(const std::string& parent) {
    auto it = mParentsMap.find(parent);
    if (it != mParentsMap.end()) {
      mParentsMap.erase(it);
      return true;
    }
    return false;
  }

  inline bool remove_child(const std::string& child) {
    auto it = mChildrenMap.find(child);
    if (it != mChildrenMap.end()) {
      mChildrenMap.erase(it);
      return true;
    }
    return false;
  }

  /**
   * @brief Add the given parents into a union or ensure they are alreay in a
   * union.
   * @param parents A list of element pointers.
   * @return true The given parents are added into a union.
   * @return false The given parents are alreayd in a union.
   */
  bool add_parents_union(const ElementPtr& parents...);

  /**
   * @brief Add the given children into a split or ensure they are alreay in a
   * split.
   * @param children A list of element pointers.
   * @return true The given children are added into a split.
   * @return false The given children are alreayd in a split.
   */
  bool add_children_split(const ElementPtr& children...);

  /**
   * @brief Check whether the given parents are in a union or not.
   * @param parents A list of element pointers.
   * @return true The given parents are in a union.
   * @return false They are not fully in a union.
   */
  bool has_unioned_parents(const ElementPtr& parents...);

  /**
   * @brief Check whether the given children are in a split or not.
   * @param children A list of element pointers.
   * @return true The given children are in a split.
   * @return false They are not fully in a split.
   */
  bool has_split_children(const ElementPtr& children...);

  /**
   * @brief Eliminate the union bound between given parents.
   * @param parents A list of element pointers.
   * @return true The parents are present in a union and dismissed successfully.
   * @return false They are not fully present or dismissed failed.
   */
  bool dismiss_parents_union(const ElementPtr& parents...);

  /**
   * @brief Eliminate the split bound between given children.
   * @param children A list of element pointers.
   * @return true The children are present in a split and dismissed
   * successfully.
   * @return false They are not fully present or dismissed failed.
   */
  bool dismiss_children_split(const ElementPtr& children...);

protected:
  // Use global UUID as the default element key string.
  inline std::string _element_key_string(const ElementPtr& ele) {
    return ele->global_id();
  }

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