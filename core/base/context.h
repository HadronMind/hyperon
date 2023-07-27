#pragma once

#include "core/base/concept.h"

namespace hyperkb {
namespace core {
class Context;
using ContextPtr = std::shared_ptr<Context>;

class Context : public Concept {};

}  // namespace core
}  // namespace hyperkb
