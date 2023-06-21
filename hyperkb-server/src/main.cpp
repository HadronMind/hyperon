#include "hyperkdb-server.h"
#include <vector>
#include <string>

int main() {
    hyperkdb_server();
    
    std::vector<std::string> vec;
    vec.push_back("test_package");

    hyperkdb_server_print_vector(vec);
}
