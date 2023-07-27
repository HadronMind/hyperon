#include "core/base/element.h"

namespace hyperkb {
namespace core {

HashVal Element::Hash() const {
  if (Element::INVALID_HASH != mHashedVal) return mHashedVal;
  mHashedVal = ComputeHash();
  return mHashedVal;
}
}  // namespace core
}  // namespace hyperkb