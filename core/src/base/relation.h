#pragma once

#include "concept.h"

namespace hyperkb {

class Relation;
using RelationPtr = std::shared_ptr<Relation>;

class Relation : public Concept {
public:
  bool is_relation() const { return true; }

protected:
};

class Split : public Relation {};

}  // namespace hyperkb
