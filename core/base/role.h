#pragma once

#include <memory>

#include "core/base/concept.h"

namespace hyperkb {
namespace core {

class Role;
using RolePtr = std::shared_ptr<Role>;

class Role : public Concept {
public:
  /* override */ inline bool IsRole() const { return true; }
};

}  // namespace core
}  // namespace hyperkb