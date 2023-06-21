#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define HYPERKDB_CORE_EXPORT __declspec(dllexport)
#else
  #define HYPERKDB_CORE_EXPORT
#endif

HYPERKDB_CORE_EXPORT void hyperkdb_core();
HYPERKDB_CORE_EXPORT void hyperkdb_core_print_vector(const std::vector<std::string> &strings);
