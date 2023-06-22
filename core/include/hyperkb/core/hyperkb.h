#pragma once

#include <map>
#include <string>
#include <vector>

#include "hyperkb/core/concept.h"
#include "hyperkb/core/element.h"

#ifdef _WIN32
#define HYPERKDB_CORE_EXPORT __declspec(dllexport)
#else
#define HYPERKDB_CORE_EXPORT
#endif

namespace hyperkb {

CategoryPtr cur_ns;
std::map<std::string, CategoryPtr> allns_map;

std::vector<CategoryPtr>& list_namespaces();
CategoryPtr& use_namespace(const std::string& ns_name,
                           const std::vector<CategoryPtr>& include = {});

}  // namespace hyperkb
