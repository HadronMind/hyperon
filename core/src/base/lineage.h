#pragma once

#include <map>
#include <memory>

namespace hyperkb {

class ConceptPtr;

class Lineage {
  class Union {};
  class Split {};
  std::map<std::string, ConceptPtr> mParentsMap;
  std::map<std::string, ConceptPtr> mChildrenMap;
};

using LineagePtr = std::shared_ptr<Lineage>;
}  // namespace hyperkb
