#pragma

#include <memory>

namespace hyperkb {
namespace common {

class inheritable_esft_base
    : public std::enable_shared_from_this<inheritable_esft_base> {
public:
  virtual ~inheritable_esft_base() {}
};

template <class T>
class inheritable_esft : virtual public inheritable_esft_base {
public:
  std::shared_ptr<T> shared_from_this() {
    return std::dynamic_pointer_cast<T>(
        inheritable_esft_base::shared_from_this());
  }

  // Utility method to easily downcast.
  template <class Derived>
  std::shared_ptr<Derived> shared_from_base() {
    return std::dynamic_pointer_cast<Derived>(
        inheritable_esft_base::shared_from_this());
  }
};

}  // namespace common
}  // namespace hyperkb