#include "base/concept.h"

#include <fmt/core.h>

namespace hyperkb {

void Concept::AddRepr(const ConceptReprPtr& repr,
                      const ConceptRepr::REPR_MODAL modal) {
  auto repr_vec = repr_map[modal];
  repr_vec.push_back(repr);
}

std::list<ConceptReprPtr> Concept::GetRepr(
    const ConceptRepr::REPR_MODAL modal) const {
  auto found = repr_map.find(modal);
  if (found != repr_map.end()) {
    return found->second;
  }
  return std::list<ConceptReprPtr>{};
}

uint32_t Concept::ReprCount() const {
  uint32_t s = 0;
  for (auto it = repr_map.begin(); it != repr_map.end(); it++) {
    s += it->second.size();
  }
  return s;
}

uint32_t Concept::ReprCount(const ConceptRepr::REPR_MODAL modal) const {
  return GetRepr(modal).size();
}

std::string Concept::ToString() const { return fmt::format("\\{{}\\}", iname); }

}  // namespace hyperkb
