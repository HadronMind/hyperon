#pragma once

#include "base/concept.h"

namespace hyperkb {

class Entity;
using EntityPtr = std::shared_ptr<Entity>;
class Indv;
using IndvPtr = std::shared_ptr<Indv>;
class Relation;

class Entity : public Concept {
public:
  Entity() = delete;
  ~Entity() = default;

  /* override */ inline bool IsEntity() const { return true; }

protected:
};

class Intersection : public Entity {};

class Indv : public Entity {};

}  // namespace hyperkb
