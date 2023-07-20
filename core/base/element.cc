#include "base/element.h"

namespace hyperkb {
HashVal Element::Hash() const {
  if (Element::INVALID_HASH != mHashedVal) return mHashedVal;
  mHashedVal = ComputeHash();
  return mHashedVal;
}
}  // namespace hyperkb