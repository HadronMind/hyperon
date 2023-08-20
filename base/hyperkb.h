#pragma once

#include "base/core/category.h"
#include "base/core/category_manager.h"
#include "base/core/concept.h"
#include "base/core/concept_repr.h"
#include "base/core/context.h"
#include "base/core/element.h"

#ifdef _WIN32
#define HYPERKDB_CORE_EXPORT __declspec(dllexport)
#else
#define HYPERKDB_CORE_EXPORT
#endif
