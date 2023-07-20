#pragma once

#include "base/concept.h"

namespace hyperkb {

class Relation : public Concept {
public:
  bool IsRelation() const { return true; }

protected:
};

using RelationPtr = std::shared_ptr<Relation>;

class Split : public Relation {};

}  // namespace hyperkb
