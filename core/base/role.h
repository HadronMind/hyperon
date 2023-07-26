#pragma once

#include <memory>

#include "base/concept.h"

namespace hyperkb {

class Concept;
class Role;
using RolePtr = std::shared_ptr<Role>;

class Role : public Concept {
public:
  bool IsRole() const { return true; }
};

}  // namespace hyperkb