#include "base/core/element.h"

namespace hyperon {
namespace base {

HashVal Element::Hash() const {
  if (Element::INVALID_HASH != mHashedVal) return mHashedVal;
  mHashedVal = ComputeHash();
  return mHashedVal;
}
}  // namespace core
}  // namespace hyperon