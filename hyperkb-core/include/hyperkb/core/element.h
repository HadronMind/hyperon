#ifndef HYPERKB_CORE_ELEMENT_H
#define HYPERKB_CORE_ELEMENT_H

#include <limits>
#include <memory>
#include <string>

namespace hyperkb {

class Element;
using ElementPtr = std::shared_ptr<Element>;
class Node;
using NodePtr = std::shared_ptr<Node>;
class Link;
using LinkPtr = std::shared_ptr<Link>;
using HashVal = uint64_t;
using Arity = uint64_t;
using ElementType = uint32_t;

// Structural model: hypergraph element-node-link
class Element {
public:
  static const HashVal INVALID_HASH = std::numeric_limits<size_t>::max();
  static const ElementType INVALID_TYPE = 0x0;

  Element() = default;
  virtual ~Element() = default;

  virtual std::string to_string() const = 0;
  virtual bool is_node() const { return false; }
  virtual bool is_link() const { return false; }
  virtual bool is_entity() const { return false; }
  virtual bool is_relation() const { return false; }
  virtual bool is_role() const { return false; }
  virtual bool is_context() const { return false; }

  inline std::string& get_uuid(bool local = false) {
    return local ? this->local_uuid : this->uuid;
  }

  inline HashVal get_hash() const {
    if (Element::INVALID_HASH != _hash_value) return _hash_value;
    _hash_value = compute_hash();
    return _hash_value;
  }

  // The arity represents the number of incoming N-ary-wires for Node, and
  // the number of all N-ary-wires elements for Link.
  virtual Arity get_arity() const { return 0; }

  // Object equality
  virtual bool operator==(const Element&) const = 0;
  bool operator!=(const Element& other) const { return not operator==(other); }
  virtual bool operator<(const Element&) const = 0;

protected:
  std::string uuid;  // global identifier
  std::string local_uuid;

  Element() = default;

  // Copy constructor
  explicit Element(const Element& other) {}
  // Move constructor
  explicit Element(Element&& other) {}

  // Copy assignment
  Element& operator=(const Element&) { return *this; };
  // Move assignment
  Element& operator=(Element&&) noexcept { return *this; };

  mutable HashVal _hash_value{Element::INVALID_HASH};
  virtual ElementType get_element_type() { return INVALID_TYPE; }
  virtual HashVal compute_hash() const = 0;
};

/**
 * Create ElementPtr of specific subclass using appropriate constructor.
 */
template <typename T, typename... Args>
static inline typename std::enable_if<std::is_base_of<Element, T>::value,
                                      std::shared_ptr<T>>::type
create_element(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

/**
 * Cast ElementPtr to the specific Element subclass.
 */
template <typename T>
static inline typename std::enable_if<std::is_base_of<Element, T>::value,
                                      std::shared_ptr<T>>::type
cast_from_element(const ElementPtr& element) {
  return std::dynamic_pointer_cast<T>(element);
}

/**
 * Cast specific Element subclass to ElementPtr.
 */
template <typename T>
static inline typename std::enable_if<std::is_base_of<Element, T>::value,
                                      ElementPtr>::type
cast_to_element(const std::shared_ptr<const T>& element) {
  return std::dynamic_pointer_cast<Element>(
      std::const_pointer_cast<T>(element));
}

// Basic element
class Node : public Element {
public:
  bool is_node() const { return true; }
};

// A link may contains multiple nodes or other links
class Link : public Element {
  bool is_link() const { return true; }
};

}  // namespace hyperkb

#endif