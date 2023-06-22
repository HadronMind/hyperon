#pragma once

#include <limits>
#include <map>
#include <memory>
#include <string>

#include "hyperkb/core/category.h"

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
class Indv;
using IndvPtr = std::shared_ptr<Indv>;
class Link;
using LinkPtr = std::shared_ptr<Link>;

/**
 * @brief Base class to represent a general concept.
 *
 * We formulate an Entity-Relation model, as well as two supplementary
 * concepts of Role and Context to construct the whole picture.
 */
class Concept : public Element {
  friend class Category;

public:
  std::string iname;
  std::weak_ptr<Category> ns;
  ElementPtr parent;
  ContextPtr context;
  uint32_t members;
  std::string english;
  std::string chinese;

protected:
  /**
   * @brief Check the object is instantized from Concept subtype.
   *
   * @return boolean
   */
  template <typename T>
  inline typename std::enable_if_t<std::is_base_of<Concept, T>::value, bool>
  is_instance_of() {
    return std::dynamic_pointer_cast<T>(*this) != nullptr;
  }
};

/**
 * Create ConceptPtr of specific subclass using appropriate constructor.
 */
template <typename T, typename... Args>
static inline typename std::enable_if_t<std::is_base_of<Concept, T>::value,
                                        std::shared_ptr<T>>
create_concept(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

/**
 * Cast ConceptPtr to the specific Concept subclass.
 */
template <typename T>
static inline typename std::enable_if_t<std::is_base_of<Concept, T>::value,
                                        std::shared_ptr<T>>
cast_from_concept(const ConceptPtr& concept) {
  return std::dynamic_pointer_cast<T>(concept);
}

/**
 * Cast specific Concept subclass to ConceptPtr.
 */
template <typename T>
static inline
    typename std::enable_if_t<std::is_base_of<Concept, T>::value, ConceptPtr>
    cast_to_concept(const std::shared_ptr<const T>& concept) {
  return std::dynamic_pointer_cast<Concept>(
      std::const_pointer_cast<T>(concept));
}

class Entity : public Concept {
public:
  Entity() = default;

  bool is_entity() const { return true; }

protected:
  explicit Entity(const Concept&){};
};

class Relation : public Concept {
public:
  bool is_relation() const { return true; }
};

class Indv : public Entity {};

class Link : public Relation {};

class Role : public Concept {
public:
  bool is_role() const { return true; }
};

class Context : public Concept {};

}  // namespace hyperkb
