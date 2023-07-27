#include "core/base/category.h"

namespace hyperkb {

namespace core {

void Category::GetEnclosedCategory(const std::string& ns,
                                   CategoryPtr& result) const {
  auto cf = mSubnsMap.find(ns);
  if (cf != mSubnsMap.end()) {
    result = cf->second;
  } else {
    result = nullptr;
  }
};

void Category::GetElement(const std::string& uuid, ElementPtr& result) const {
  auto cf = mCnptMap.find(uuid);
  if (cf != mCnptMap.end()) {
    result = std::dynamic_pointer_cast<Element>(cf->second);
  }
  auto ef = mNonCnptMap.find(uuid);
  if (ef != mNonCnptMap.end()) {
    result = ef->second;
  }
};

template <typename T>
typename std::enable_if_t<std::is_base_of<Concept, T>::value, uint64_t>
Category::ConceptCount() const {
  if constexpr (std::is_same<T, class Concept>::value) return mConceptEleNum;
  if constexpr (std::is_same<T, class Entity>::value) return mEntityNum;
  if constexpr (std::is_same<T, class Relation>::value) return mRelationNum;
  if constexpr (std::is_same<T, class Indv>::value) return mIndvNum;
  if constexpr (std::is_same<T, class Link>::value) return mLinkNum;
  if constexpr (std::is_same<T, class Role>::value) return mRoleNum;
  if constexpr (std::is_same<T, class Context>::value) return mContextNum;
  return 0;
}

template <typename T>
typename std::enable_if_t<std::is_base_of<Concept, T>::value, bool>
Category::GetConcept(const std::string& iname,
                     std::shared_ptr<T>& result) const {
  auto found = mCnptMap.find(iname);
  if (found == mCnptMap.end()) {
    result = nullptr;
    return false;
  }
  result = std::dynamic_pointer_cast<T>(found->second);
  return true;
}

template <typename T>
typename std::enable_if_t<std::is_base_of<Concept, T>::value, bool>
Category::HasConcept(const std::string& iname) const {
  std::shared_ptr<T> csp;
  return GetConcept<T>(iname, csp);
}

}  // namespace core
}  // namespace hyperkb