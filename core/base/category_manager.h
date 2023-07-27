#pragma once
#include <memory>
#include <string>
#include <vector>

namespace hyperkb {
namespace core {

class Category;
using CategoryPtr = std::shared_ptr<Category>;

/**
 * @brief Global status and indicators
 */
CategoryPtr cur_ns;
std::map<std::string, CategoryPtr> allns_map;

std::vector<CategoryPtr>& ListCategories();

CategoryPtr& UseCategory(const std::string& category_name,
                         const std::vector<CategoryPtr>& include = {});

CategoryPtr& GetGlobalCategory(const std::string& category_name);

}  // namespace core
}  // namespace hyperkb
