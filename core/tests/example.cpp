#include "hyperkdb/core/hyperkb.h"
#include <vector>
#include <string>

int main() {
    hyperkdb_core();
    
    std::vector<std::string> vec;
    vec.push_back("test_package");

    hyperkdb_core_print_vector(vec);
}
