#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace hyperkb {
namespace common {

template <typename T>
class IJsonizable {
public:
  // Deserialize string to specific type
  virtual T& from_jsonstr(const std::string& jsonstr) = 0;

  // Serialize specific type to string
  virtual std::string& to_jsonstr() = 0;

  // Deserialize json to c++ class
  virtual T& from_json(const nlohmann::json& json) = 0;

  // Serialize c++ class to json
  virtual nlohmann::json& to_json() = 0;
};
}  // namespace common
}  // namespace hyperkb
