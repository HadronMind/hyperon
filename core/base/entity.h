#pragma once

#include "base/concept.h"

namespace hyperkb {

class Entity;
using EntityPtr = std::shared_ptr<Entity>;
class Indv;
using IndvPtr = std::shared_ptr<Indv>;

class Entity : public Concept {
public:
  Entity() = delete;
  ~Entity() = default;

protected:
};

class Intersection : public Entity {};

class Indv : public Entity {};

}  // namespace hyperkb
