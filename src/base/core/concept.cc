#include "base/core/concept.h"

#include <fmt/core.h>

#include "base/core/category.h"
#include "base/core/context.h"

namespace hyperkb {
namespace base {

Concept::Concept(const std::string& sname) : sname(sname) {}

Concept::Concept(const std::string& sname, const ConceptPtr& parent)
    : sname(sname) {
  AddParent(parent);
}

Concept::Concept(const std::string& sname, const CategoryPtr& category)
    : sname(sname), mCategory(category) {}

Concept::Concept(const std::string& sname, const ConceptPtr& parent,
                 const CategoryPtr& category, const ContextPtr& context)
    : sname(sname), mCategory(category), mContext(context) {
  AddParent(parent);
};

CategoryPtr Concept::GetCategory() const {
  if (!mCategory.expired()) {
    return mCategory.lock();
  }
  return CategoryPtr();
}

ContextPtr Concept::GetContext() const {
  if (!mContext.expired()) {
    return mContext.lock();
  }
  return ContextPtr();
}

void Concept::AddRepr(const ConceptReprPtr& repr,
                      const ConceptRepr::REPR_MODAL modal) {
  auto repr_vec = mReprMap[modal];
  repr_vec.push_back(repr);
}

std::list<ConceptReprPtr> Concept::GetRepr(
    const ConceptRepr::REPR_MODAL modal) const {
  auto found = mReprMap.find(modal);
  if (found != mReprMap.end()) {
    return found->second;
  }
  return std::list<ConceptReprPtr>{};
}

uint32_t Concept::ReprCount() const {
  uint32_t s = 0;
  for (auto it = mReprMap.begin(); it != mReprMap.end(); it++) {
    s += it->second.size();
  }
  return s;
}

uint32_t Concept::ReprCount(const ConceptRepr::REPR_MODAL modal) const {
  return GetRepr(modal).size();
}

std::string Concept::ToString() const { return fmt::format("\\{{}\\}", sname); }

}  // namespace base
}  // namespace hyperkb
