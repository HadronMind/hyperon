#pragma once

#include "hyperkb/core/category_manager.h"
#include "hyperkb/core/concept.h"
#include "hyperkb/core/element.h"

#ifdef _WIN32
#define HYPERKDB_CORE_EXPORT __declspec(dllexport)
#else
#define HYPERKDB_CORE_EXPORT
#endif