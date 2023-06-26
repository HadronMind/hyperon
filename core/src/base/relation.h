#pragma once

#include "concept.h"

namespace hyperkb {

class Relation;
using RelationPtr = std::shared_ptr<Relation>;
class Link;
using LinkPtr = std::shared_ptr<Link>;

class Relation : public Concept {
public:
  bool is_relation() const { return true; }

protected:
};

class Split : public Relation {};

class Link : public Relation {};

}  // namespace hyperkb
