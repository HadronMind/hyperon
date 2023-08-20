#pragma once

#include <limits>
#include <map>
#include <memory>
#include <string>

#include "base/core/concept.h"
#include "common/memory/esft.h"

namespace hyperkb {
namespace base {

class Category;
using CategoryPtr = std::shared_ptr<Category>;

/**
 * @brief A category is a logical closure that includes a bunch of related
 * concepts. Each concept has its own category, as a one-to-one projection.
 * Categorys can contain enclosed/nested sub-categories, which represents the
 * inclusion nature of concept categories. For example, the category of
 * "Solid-state physics" should be placed as an enclosed category in the
 * category of "Physics theory". Concepts in the same category should be
 * consistent logically or theoretically.
 */
class Category : public common::inheritable_esft<Category> {
public:
  explicit Category(const std::string& name) : mName(name){};

  /**
   * @brief Get the number of enclosed/nested categories. (non-recursively)
   *
   * @return uint64_t The number of enclosed categories.
   */
  inline uint64_t EnclosedCategoryCount() const { return mSubnsMap.size(); }

  /**
   * @brief Check if containing a nested category. (non-recursively)
   *
   * @param ns Target category name
   * @return boolean
   */
  inline bool EnclosesCategory(const std::string& ns) {
    return mSubnsMap.find(ns) != mSubnsMap.end();
  };

  /**
   * @brief Get the enclosed category object
   *
   * @param ns Target category name
   * @param result Found category pointer or nullptr
   */
  void GetEnclosedCategory(const std::string& ns, CategoryPtr& result) const;

  /**
   * @brief The number of contained elements in the category, without enclosed
   * categories. The elements includ both concept and non-concept types.
   *
   * @return uint64_t
   */
  inline uint64_t ElementCount() const {
    return mNonConceptEleNum + mConceptEleNum;
  }

  /**
   * @brief Check if an elmenet is contained in the category (non-recursively).
   *
   * @param uuid Target element UUID
   * @return boolean
   */
  inline bool HasElement(const std::string& uuid) const {
    return mCnptMap.find(uuid) != mCnptMap.end() ||
           mNonCnptMap.find(uuid) != mNonCnptMap.end();
  };

  /**
   * @brief Get the element object
   *
   * @param uuid Target element UUID
   * @param result Element pointer or nullptr
   */
  void GetElement(const std::string& uuid,
                  std::shared_ptr<Element>& result) const;

  /**
   * @brief The number of Concept elements. We use template to control the
   * number of APIs in case that new concepts would be added in the future.
   *
   * * Get the number of concept: concept_count<T>(iname)
   * * Check existence: has_concept<T>(iname)
   * * Get concept: get_concept<T>(iname, result)
   */
  template <typename T>
  typename std::enable_if_t<std::is_base_of<Concept, T>::value, uint64_t>
  ConceptCount() const;

  /**
   * @brief Get the concept object
   *
   * @tparam T Subclass of Concept
   * @param iname Inner name of concept
   * @param result The subclass pointer or nullptr
   * @return std::enable_if_t<std::is_base_of<Concept, T>::value, bool>
   */
  template <typename T>
  typename std::enable_if_t<std::is_base_of<Concept, T>::value, bool>
  GetConcept(const std::string& iname, std::shared_ptr<T>& result) const;

  /**
   * @brief Check the existence of specific concept (non-recursively)
   *
   * @tparam T A subclass of Concept
   * @param iname Inner name of concept
   * @return std::enable_if_t<std::is_base_of<Concept, T>::value, bool>
   */
  template <typename T>
  typename std::enable_if_t<std::is_base_of<Concept, T>::value, bool>
  HasConcept(const std::string& iname) const;

protected:
  // Parent category, default nullptr
  CategoryPtr mSuperior;
  // All enclosed categories, as map<ns_name, ptr>
  std::map<std::string, CategoryPtr> mSubnsMap;

  // Currently the concept set is equivelent with element set.
  // mNonCnptMap reserved for future use.
  std::map<std::string, ConceptPtr> mCnptMap;
  std::map<std::string, std::shared_ptr<Element>> mNonCnptMap;

private:
  std::string mName;
  uint64_t mNonConceptEleNum;
  uint64_t mConceptEleNum;
  uint64_t mEntityNum;
  uint64_t mRelationNum;
  uint64_t mIndvNum;
  uint64_t mLinkNum;
  uint64_t mRoleNum;
  uint64_t mContextNum;
};

}  // namespace base
}  // namespace hyperkb
