#pragma once

#include "base/relation.h"

namespace hyperkb {

class Link;
using LinkPtr = std::shared_ptr<Link>;

class Link : public Relation {};

}  // namespace hyperkb
