#pragma once
#include <string>
#include <vector>

#include "hyperkb/core/category.h"

namespace hyperkb {
/**
 * @brief Global status and indicators
 */
CategoryPtr cur_ns;
std::map<std::string, CategoryPtr> allns_map;

std::vector<CategoryPtr>& list_categories();
CategoryPtr& use_category(const std::string& category_name,
                          const std::vector<CategoryPtr>& include = {});
CategoryPtr& global_get_category(const std::string& category_name);

}  // namespace hyperkb
