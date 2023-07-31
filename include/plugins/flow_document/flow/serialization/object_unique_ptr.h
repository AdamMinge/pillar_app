#ifndef FLOW_DOCUMENT_OBJECT_UNIQUE_PTR_H
#define FLOW_DOCUMENT_OBJECT_UNIQUE_PTR_H

/* ---------------------------------- Standard ------------------------------ */
#include <memory>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/pointer_cast/unique_ptr_cast.h>
#include <utils/serializer/archive_property.h>
#include <utils/serializer/serializable.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/concept.h"
#include "flow_document/export.h"
#include "flow_document/flow/factory/object_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------ DeserializeByObjectFactory ---------------------- */

template <IsObject TYPE>
struct DeserializeByObjectFactory {
  [[nodiscard]] std::unique_ptr<TYPE> operator()(
      utils::IArchive& archive) const {
    auto object_class = QString{};
    archive >> utils::ArchiveProperty("class", object_class);

    auto& manager = egnite::PluginManager::getInstance();
    auto factories = manager.getObjects<ObjectFactory>();

    auto object_factory = static_cast<ObjectFactory*>(nullptr);
    for (auto factory : factories) {
      if (object_class == factory->getObjectClassName()) {
        object_factory = factory;
        break;
      }
    }

    return utils::cast_unique_ptr<TYPE>(object_factory->createObject());
  }
};

/* ------------------------ DeserializeByDefaultFactory --------------------- */

template <IsObject TYPE>
struct DeserializeByDefaultFactory {
  [[nodiscard]] std::unique_ptr<TYPE> operator()(
      utils::IArchive& archive) const {
    return std::make_unique<TYPE>();
  }
};

/* ------------------------------ ObjectUniquePtr --------------------------- */

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY =
                             DeserializeByObjectFactory>
class ObjectUniquePtr : public utils::Serializable {
 public:
  ObjectUniquePtr();
  ObjectUniquePtr(std::unique_ptr<TYPE> ptr);
  explicit ObjectUniquePtr(TYPE* ptr);

  ~ObjectUniquePtr();

  ObjectUniquePtr(const ObjectUniquePtr&) = delete;
  ObjectUniquePtr& operator=(const ObjectUniquePtr&) = delete;

  ObjectUniquePtr(ObjectUniquePtr&& other) noexcept;
  ObjectUniquePtr& operator=(ObjectUniquePtr&& other) noexcept;

  [[nodiscard]] TYPE* get() const;
  [[nodiscard]] TYPE* operator->() const;
  [[nodiscard]] TYPE& operator*() const;

  operator bool() const;
  operator std::unique_ptr<TYPE>();

  void reset();
  void reset(TYPE* ptr);

  void serialize(utils::OArchive& archive) const override;
  void deserialize(utils::IArchive& archive) override;

 private:
  DESERIALIZATION_STRATEGY<TYPE> m_deserialization_strategy;
  std::unique_ptr<TYPE> m_ptr;
};

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::ObjectUniquePtr() = default;

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::ObjectUniquePtr(
    std::unique_ptr<TYPE> ptr)
    : m_ptr(std::move(ptr)) {}

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::ObjectUniquePtr(TYPE* ptr)
    : m_ptr(ptr) {}

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::~ObjectUniquePtr() {
  reset();
}

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::ObjectUniquePtr(
    ObjectUniquePtr&& other) noexcept
    : m_ptr(std::move(other.m_ptr)) {
  other.m_ptr = nullptr;
}

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>&
ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::operator=(
    ObjectUniquePtr&& other) noexcept {
  if (this != &other) {
    reset();
    m_ptr = std::move(other.m_ptr);
    other.m_ptr = nullptr;
  }
  return *this;
}

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
TYPE* ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::get() const {
  return m_ptr.get();
}

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
TYPE* ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::operator->() const {
  return m_ptr.get();
}

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
TYPE& ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::operator*() const {
  return *m_ptr;
}

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::operator bool() const {
  return m_ptr != nullptr;
}

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
ObjectUniquePtr<TYPE,
                DESERIALIZATION_STRATEGY>::operator std::unique_ptr<TYPE>() {
  return std::unique_ptr<TYPE>(m_ptr.release());
}

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
void ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::reset() {
  m_ptr.reset();
}

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
void ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::reset(TYPE* ptr) {
  m_ptr.reset(ptr);
}

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
void ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::serialize(
    utils::OArchive& archive) const {
  auto object_class = m_ptr->getClassName();
  archive << utils::ArchiveProperty("class", object_class);
  m_ptr->serialize(archive);
}

template <IsObject TYPE, template <typename> class DESERIALIZATION_STRATEGY>
void ObjectUniquePtr<TYPE, DESERIALIZATION_STRATEGY>::deserialize(
    utils::IArchive& archive) {
  m_ptr = m_deserialization_strategy(archive);
  m_ptr->deserialize(archive);
}

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECT_UNIQUE_PTR_H