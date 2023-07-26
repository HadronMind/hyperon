#include "base/concept.h"

#include <fmt/core.h>

namespace hyperkb {

Concept::Concept(const std::string& sname, const CategoryPtr& category,
                 const ElementPtr& parent, const ContextPtr& context)
    : sname(sname), mCategory(category), mContext(context) {
  AddParent(parent);
};

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

}  // namespace hyperkb
