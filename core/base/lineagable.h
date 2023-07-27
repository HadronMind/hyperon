#pragma once

#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>

#include "core/base/element.h"

namespace hyperkb {
namespace core {

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
  virtual bool HasParent(const ElementPtr& parent) const {
    return HasParent(parent->SemName());
  }

  /**
   * @brief Check whether the lineage contains specific child.
   *
   * @param child Element string key or pointer.
   * @return true
   * @return false
   */
  virtual bool HasChild(const std::string& child) const = 0;
  virtual bool HasChild(const ElementPtr& child) const {
    return HasChild(child->SemName());
  }

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
  virtual bool RemoveParent(const ElementPtr& parent) {
    return RemoveParent(parent->SemName());
  }

  /**
   * @brief Remove specific child from the lineage.
   *
   * @param child Element string key or pointer.
   * @return true if the child is removed successfully.
   * @return false if the child is absent.
   */
  virtual bool RemoveChild(const std::string& child) = 0;
  virtual bool RemoveChild(const ElementPtr& child) {
    return RemoveChild(child->SemName());
  }
};

}  // namespace core
}  // namespace hyperkb
