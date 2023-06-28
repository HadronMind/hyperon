#pragma once

#include "concept.h"

namespace hyperkb {

class Relation : public Concept {
public:
  bool is_relation() const { return true; }

protected:
};

using RelationPtr = std::shared_ptr<Relation>;

class Split : public Relation {};

}  // namespace hyperkb
