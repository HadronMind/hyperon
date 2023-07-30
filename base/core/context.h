#pragma once

#include "base/core/concept.h"

namespace hyperkb {
namespace base {
class Context;
using ContextPtr = std::shared_ptr<Context>;

class Context : public Concept {
public:
  /* override */ inline bool IsContext() const { return true; }

private:
  std::map<std::string, ConceptPtr> mConcepts;
};

}  // namespace base
}  // namespace hyperkb
