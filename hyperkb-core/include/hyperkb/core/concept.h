#ifndef HYPERKB_CORE_CONCEPT_H
#define HYPERKB_CORE_CONCEPT_H

#include <limits>
#include <map>
#include <memory>
#include <string>

#include "hyperkb/core/element.h"

namespace hyperkb {

class Concept;
using ConceptPtr = std::shared_ptr<Concept>;
class Entity;
using EntityPtr = std::shared_ptr<Entity>;
class Relation;
using RelationPtr = std::shared_ptr<Relation>;
class Role;
using RolePtr = std::shared_ptr<Role>;
class Context;
using ContextPtr = std::shared_ptr<Context>;

// Conceptual model: entity-releation
class Concept {
public:
  std::string iname;
  ElementPtr parent;
  std::string english;
  std::string chinese;
  uint32_t members;
  ContextPtr context;
};

/**
 * Create ConceptPtr of specific subclass using appropriate constructor.
 */
template <typename T, typename... Args>
static inline typename std::enable_if<std::is_base_of<Concept, T>::value,
                                      std::shared_ptr<T>>::type
create_concept(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

/**
 * Cast ConceptPtr to the specific Concept subclass.
 */
template <typename T>
static inline typename std::enable_if<std::is_base_of<Concept, T>::value,
                                      std::shared_ptr<T>>::type
cast_from_concept(const ConceptPtr& concept) {
  return std::dynamic_pointer_cast<T>(concept);
}

/**
 * Cast specific Concept subclass to ConceptPtr.
 */
template <typename T>
static inline typename std::enable_if<std::is_base_of<Concept, T>::value,
                                      ConceptPtr>::type
cast_to_concept(const std::shared_ptr<const T>& concept) {
  return std::dynamic_pointer_cast<Concept>(
      std::const_pointer_cast<T>(concept));
}

class Entity : public Concept, Node {
public:
  Entity(const Concept&) = delete;
  Entity(const Node&) = delete;
};

class Relation : public Concept, Link {
public:
};

class Role : public Concept, Node {};

class Namespace {
public:
  uint64_t elements;
};

class Context : public Concept, Node {};

}  // namespace hyperkb
#endif