#pragma once

#include <string>
#include <vector>

#ifdef _WIN32
#define HYPERKDB_SERVER_EXPORT __declspec(dllexport)
#else
#define HYPERKDB_SERVER_EXPORT
#endif

HYPERKDB_SERVER_EXPORT void hyperkdb_server();
HYPERKDB_SERVER_EXPORT void hyperkdb_server_print_vector(
    const std::vector<std::string> &strings);
