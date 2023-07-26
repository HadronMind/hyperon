#pragma once

#include <limits>
#include <memory>
#include <string>

namespace {
// An OP way of enable_shared_from_base.
// Refers to https:// stackoverflow.com/a/32172486
template <class Base>
class enable_shared_from_base : public std::enable_shared_from_this<Base> {
protected:
  template <class Derived>
  std::shared_ptr<Derived> shared_from_base() {
    return std::static_pointer_cast<Derived>(shared_from_this());
  }
};
}  // namespace

namespace hyperkb {

class Element;
using ElementPtr = std::shared_ptr<Element>;

using ElementType = uint32_t;
using HashVal = uint64_t;
using ArityType = uint64_t;
using MarkerType = uint64_t;

/**
 * @brief Element is the root class of everything in the KB.
 */
class Element : public enable_shared_from_base<Element> {
public:
  static const HashVal INVALID_HASH = std::numeric_limits<size_t>::max();
  static const ElementType INVALID_TYPE = 0x0;

  Element() = default;
  virtual ~Element() = default;

  // Global and local identifier
  inline std::string GlobalId() const { return mIdentifier; }
  inline std::string LocalId() const { return mLocalIdentifier; }

  // Globally unique semantic name, as the same as identifier by default.
  virtual inline std::string SemName() const { return mIdentifier; }

  // Hashed value
  virtual HashVal Hash() const;

  // The arity represents the number of incoming N-ary-wires for Node, and
  // the number of all N-ary-wires elements for Link.
  virtual ArityType Arity() const { return 0; }

  // Object equality
  virtual bool operator==(const Element&) const = 0;
  virtual bool operator<(const Element&) const = 0;
  bool operator!=(const Element& other) const { return not operator==(other); }

  // Plain string representation of element
  virtual std::string ToString() const = 0;

  // Subclass indicator
  virtual bool IsConcept() const { return false; }

protected:
  // global and local identifier, reserved
  std::string mIdentifier;
  std::string mLocalIdentifier;

  // bit-wise markers, reserved
  MarkerType markers;

  explicit Element(const Element& other) {}
  explicit Element(Element&& other) {}

  Element& operator=(const Element&) { return *this; };
  Element& operator=(Element&&) noexcept { return *this; };

  mutable HashVal mHashedVal{Element::INVALID_HASH};
  virtual ElementType GetElementType() { return INVALID_TYPE; }
  virtual HashVal ComputeHash() const = 0;
};

/**
 * Create ElementPtr of specific subclass using appropriate constructor.
 */
template <typename T, typename... Args>
static inline typename std::enable_if_t<std::is_base_of<Element, T>::value,
                                        std::shared_ptr<T>>
create_element(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

/**
 * Cast ElementPtr to the specific Element subclass.
 */
template <typename T>
static inline typename std::enable_if_t<std::is_base_of<Element, T>::value,
                                        std::shared_ptr<T>>
cast_from_element(const ElementPtr& element) {
  return std::dynamic_pointer_cast<T>(element);
}

/**
 * Cast specific Element subclass to ElementPtr.
 */
template <typename T>
static inline
    typename std::enable_if_t<std::is_base_of<Element, T>::value, ElementPtr>
    cast_to_element(const std::shared_ptr<const T>& element) {
  return std::dynamic_pointer_cast<Element>(
      std::const_pointer_cast<T>(element));
}

}  // namespace hyperkb
