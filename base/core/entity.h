#pragma once

#include <map>

#include "base/core/concept.h"
#include "base/core/relation_boundable.h"

namespace hyperkb {
namespace base {

class Relation;
using RelationPtr = std::shared_ptr<Relation>;

class Entity : public Concept, public SimpleRelationBoundable {
public:
  /* override */ inline bool IsEntity() const { return true; }
};

template <typename T, typename... Args>
static inline typename std::enable_if_t<std::is_base_of<Entity, T>::value,
                                        std::shared_ptr<T>>
create_entity(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
static inline typename std::enable_if_t<std::is_base_of<Entity, T>::value,
                                        std::shared_ptr<T>>
cast_from_entity(const std::shared_ptr<Entity>& entity) {
  return std::dynamic_pointer_cast<T>(entity);
}

template <typename T>
static inline typename std::enable_if_t<std::is_base_of<Entity, T>::value,
                                        std::shared_ptr<Entity>>
cast_to_entity(const std::shared_ptr<const T>& subent) {
  return std::dynamic_pointer_cast<Entity>(std::const_pointer_cast<T>(subent));
}

}  // namespace base

}  // namespace hyperkb
