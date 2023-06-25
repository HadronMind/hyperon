#pragma once

#include <fmt/core.h>

#include <map>
#include <memory>
#include <string>

namespace hyperkb {

/**
 * @brief Multimodal represention of concepts / knowledge.
 */
class ConceptRepr {
public:
  /**
   * Representation modal signature
   */
  enum repr_modal {
    modal_natlang,  // Raw string desc
    modal_image,
    modal_sound,
    modal_vector,
    modal_prolog_e,  // Prolog eval
    modal_guile_e,   // Guile eval
  };

  inline repr_modal get_modal() { return m_modal; }

  virtual std::string to_string() = 0;

protected:
  ConceptRepr() = default;
  explicit ConceptRepr(const ConceptRepr&){};
  explicit ConceptRepr(ConceptRepr&&){};

  ConceptRepr& operator=(const ConceptRepr&) { return *this; };
  ConceptRepr& operator=(ConceptRepr&&) { return *this; }

  repr_modal m_modal;
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
  enum modal_natlang_type { english, chinese };

  ConceptReprNL(const std::string& desc, const modal_natlang_type lang_type,
                const std::string encoding = "utf-8")
      : mLangType(lang_type), mEncoding(encoding), mLangDesc(desc) {
    this->m_modal = modal_natlang;
  }

  inline std::string& get_repr() { return mLangDesc; }

  std::string to_string() { return mLangDesc; }

protected:
  modal_natlang_type mLangType;
  std::string mEncoding;
  std::string mLangDesc;
};

class ConceptReprImage : ConceptRepr {
public:
  ConceptReprImage() { this->m_modal = modal_image; }
};

class ConceptReprGuile : ConceptRepr {
public:
  ConceptReprGuile() { this->m_modal = modal_guile_e; }
};

}  // namespace hyperkb
