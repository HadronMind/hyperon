#pragma once

#include <limits>
#include <map>
#include <memory>
#include <string>

#include "hyperkb/core/element.h"

namespace hyperkb {

class Concept;
using ConceptPtr = std::shared_ptr<Concept>;
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
class Category {
public:
  explicit Category(const std::string& name){};

  /**
   * @brief Get the number of enclosed/nested categories. (non-recursively)
   *
   * @return uint64_t The number of enclosed categories.
   */
  inline uint64_t enclosed_category_count() const { return subns_map.size(); }

  /**
   * @brief Check if containing a nested category. (non-recursively)
   *
   * @param ns Target category name
   * @return boolean
   */
  inline bool encloses_category(const std::string& ns) {
    return subns_map.find(ns) != subns_map.end();
  };

  /**
   * @brief Get the enclosed category object
   *
   * @param ns Target category name
   * @param result Found category pointer or nullptr
   */
  void get_enclosed_category(const std::string& ns, CategoryPtr& result) {
    auto cf = subns_map.find(ns);
    if (cf != subns_map.end()) {
      result = cf->second;
    } else {
      result = nullptr;
    }
  };

  /**
   * @brief The number of contained elements in the category, without enclosed
   * categories. The elements includ both concept and non-concept types.
   *
   * @return uint64_t
   */
  inline uint64_t element_count() const {
    return m_non_cnpt_ele_num + m_cnpt_ele_num;
  }

  /**
   * @brief Check if an elmenet is contained in the category (non-recursively).
   *
   * @param uuid Target element UUID
   * @return boolean
   */
  inline bool has_element(const std::string& uuid) {
    return cnpt_map.find(uuid) != cnpt_map.end() ||
           non_cnpt_map.find(uuid) != non_cnpt_map.end();
  };

  /**
   * @brief Get the element object
   *
   * @param uuid Target element UUID
   * @param result Element pointer or nullptr
   */
  void get_element(const std::string& uuid, ElementPtr& result) {
    auto cf = cnpt_map.find(uuid);
    if (cf != cnpt_map.end()) {
      result = std::dynamic_pointer_cast<Element>(cf->second);
    }
    auto ef = non_cnpt_map.find(uuid);
    if (ef != non_cnpt_map.end()) {
      result = ef->second;
    }
  };

  /**
   * @brief The number of Concept elements. We use template to control the
   * number of APIs in case that new concepts would be added in the future.
   *
   * * Get the number of concept: concept_count<T>(iname)
   * * Check existence: has_concept<T>(iname)
   * * Get concept: get_concept<T>(iname, result)
   */
  template <typename T>
  inline typename std::enable_if_t<std::is_base_of<Concept, T>::value, uint64_t>
  concept_count() const {
    if constexpr (std::is_same<T, class Concept>::value) return m_cnpt_ele_num;
    if constexpr (std::is_same<T, class Entity>::value) return m_entity_num;
    if constexpr (std::is_same<T, class Relation>::value) return m_relation_num;
    if constexpr (std::is_same<T, class Indv>::value) return m_indv_num;
    if constexpr (std::is_same<T, class Link>::value) return m_link_num;
    if constexpr (std::is_same<T, class Role>::value) return m_role_num;
    if constexpr (std::is_same<T, class Context>::value) return m_context_num;
    return 0;
  }

  /**
   * @brief Get the concept object
   *
   * @tparam T Subclass of Concept
   * @param iname Inner name of concept
   * @param result The subclass pointer or nullptr
   * @return std::enable_if_t<std::is_base_of<Concept, T>::value, bool>
   */
  template <typename T>
  inline typename std::enable_if_t<std::is_base_of<Concept, T>::value, bool>
  get_concept(const std::string& iname, std::shared_ptr<T>& result) {
    auto found = cnpt_map.find(iname);
    if (found == cnpt_map.end()) {
      result = nullptr;
      return false;
    }
    result = std::dynamic_pointer_cast<T>(found->second);
    return true;
  }

  /**
   * @brief Check the existence of specific concept (non-recursively)
   *
   * @tparam T A subclass of Concept
   * @param iname Inner name of concept
   * @return std::enable_if_t<std::is_base_of<Concept, T>::value, bool>
   */
  template <typename T>
  inline typename std::enable_if_t<std::is_base_of<Concept, T>::value, bool>
  has_concept(const std::string& iname) const {
    std::shared_ptr<T> csp;
    return get_concept<T>(iname, csp);
  }

protected:
  // Parent category, default nullptr
  CategoryPtr superior;
  // All enclosed categories, as map<ns_name, ptr>
  std::map<std::string, CategoryPtr> subns_map;

  // Currently the concept set is equivelent with element set.
  // non_cnpt_map reserved for future use.
  std::map<std::string, ConceptPtr> cnpt_map;
  std::map<std::string, ElementPtr> non_cnpt_map;

private:
  std::string m_name;
  uint64_t m_non_cnpt_ele_num;
  uint64_t m_cnpt_ele_num;
  uint64_t m_entity_num;
  uint64_t m_relation_num;
  uint64_t m_indv_num;
  uint64_t m_link_num;
  uint64_t m_role_num;
  uint64_t m_context_num;
};

}  // namespace hyperkb