#pragma once

#include "base/concept.h"

namespace hyperkb {

class Entity;

/**
 * @brief In the Entity-Relation model, a relation defines a interconnection,
 * i.e. hyperedge, of multiple entities.
 */
class Relation : public Concept {
public:
  /* override */ inline bool IsRelation() const { return true; }

protected:
private:
};

using RelationPtr = std::shared_ptr<Relation>;

class Split : public Relation {};

}  // namespace hyperkb
