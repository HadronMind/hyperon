#pragma once

#include "concept/category_manager.h"
#include "concept/concept.h"
#include "concept/element.h"

#ifdef _WIN32
#define HYPERKDB_CORE_EXPORT __declspec(dllexport)
#else
#define HYPERKDB_CORE_EXPORT
#endif
