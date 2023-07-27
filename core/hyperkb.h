#pragma once

#include "base/category.h"
#include "base/category_manager.h"
#include "base/concept.h"
#include "base/concept_repr.h"
#include "base/context.h"
#include "base/element.h"

#ifdef _WIN32
#define HYPERKDB_CORE_EXPORT __declspec(dllexport)
#else
#define HYPERKDB_CORE_EXPORT
#endif
