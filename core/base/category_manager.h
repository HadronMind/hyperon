#pragma once
#include <string>
#include <vector>

#include "base/category.h"

namespace hyperkb {
/**
 * @brief Global status and indicators
 */
CategoryPtr cur_ns;
std::map<std::string, CategoryPtr> allns_map;

std::vector<CategoryPtr>& ListCategories();

CategoryPtr& UseCategory(const std::string& category_name,
                         const std::vector<CategoryPtr>& include = {});

CategoryPtr& GetGlobalCategory(const std::string& category_name);

}  // namespace hyperkb
