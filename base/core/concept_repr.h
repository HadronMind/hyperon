#pragma once

#include <fmt/core.h>

#include <map>
#include <memory>
#include <string>

namespace hyperkb {

namespace base {
/**
 * @brief Multimodal represention of concepts / knowledge.
 */
class ConceptRepr {
public:
  /**
   * Representation modal signature
   */
  enum REPR_MODAL {
    MODAL_NATLANG,  // Raw string desc
    MODAL_IMAGE,
    MODAL_SOUND,
    MODAL_VECTOR,
    MODAL_PROLOG_E,  // Prolog eval
    MODAL_GUILE_E,   // Guile eval
  };

  inline REPR_MODAL GetModal() const { return mModal; }

  virtual std::string ToString() const = 0;

protected:
  ConceptRepr() = default;
  explicit ConceptRepr(const ConceptRepr&){};
  explicit ConceptRepr(ConceptRepr&&){};

  ConceptRepr& operator=(const ConceptRepr&) { return *this; };
  ConceptRepr& operator=(ConceptRepr&&) { return *this; }

  REPR_MODAL mModal;
};

using ConceptReprPtr = std::shared_ptr<ConceptRepr>;

template <typename T>
static inline typename std::enable_if_t<std::is_base_of<ConceptRepr, T>::value,
                                        std::shared_ptr<T>>
cast_from_ConceptRepr(const ConceptReprPtr& obj) {
  return std::dynamic_pointer_cast<T>(obj);
}

template <typename T>
static inline typename std::enable_if_t<std::is_base_of<ConceptRepr, T>::value,
                                        ConceptReprPtr>
cast_to_ConceptRepr(const std::shared_ptr<const T>& obj) {
  return std::dynamic_pointer_cast<ConceptRepr>(
      std::const_pointer_cast<T>(obj));
}

/**
 * @brief Natural language representation.
 */
class ConceptReprNL : ConceptRepr {
public:
  enum MODAL_NATLANG_TYPE { ENGLISH, CHINESE };

  ConceptReprNL(const std::string& desc, const MODAL_NATLANG_TYPE lang_type,
                const std::string encoding = "utf-8")
      : mLangType(lang_type), mEncoding(encoding), mLangDesc(desc) {
    this->mModal = MODAL_NATLANG;
  }

  inline std::string& GetRepr() { return mLangDesc; }

  std::string ToString() { return mLangDesc; }

protected:
  MODAL_NATLANG_TYPE mLangType;
  std::string mEncoding;
  std::string mLangDesc;
};

class ConceptReprImage : ConceptRepr {
public:
  ConceptReprImage() { this->mModal = MODAL_IMAGE; }
};

class ConceptReprGuile : ConceptRepr {
public:
  ConceptReprGuile() { this->mModal = MODAL_GUILE_E; }
};

}  // namespace base
}  // namespace hyperkb
