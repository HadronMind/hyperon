#pragma once

#include <memory>

#include "base/core/concept.h"

namespace hyperkb {
namespace base {

class Role;
using RolePtr = std::shared_ptr<Role>;

class Role : public Concept {
public:
  /* override */ inline bool IsRole() const { return true; }
};

}  // namespace base
}  // namespace hyperkb