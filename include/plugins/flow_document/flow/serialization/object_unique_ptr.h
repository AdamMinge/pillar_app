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

template <IsObject TYPE>
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
  std::unique_ptr<TYPE> m_ptr;
};

template <IsObject TYPE>
ObjectUniquePtr<TYPE>::ObjectUniquePtr() = default;

template <IsObject TYPE>
ObjectUniquePtr<TYPE>::ObjectUniquePtr(std::unique_ptr<TYPE> ptr)
    : m_ptr(std::move(ptr)) {}

template <IsObject TYPE>
ObjectUniquePtr<TYPE>::ObjectUniquePtr(TYPE* ptr) : m_ptr(ptr) {}

template <IsObject TYPE>
ObjectUniquePtr<TYPE>::~ObjectUniquePtr() {
  reset();
}

template <IsObject TYPE>
ObjectUniquePtr<TYPE>::ObjectUniquePtr(ObjectUniquePtr&& other) noexcept
    : m_ptr(std::move(other.m_ptr)) {
  other.m_ptr = nullptr;
}

template <IsObject TYPE>
ObjectUniquePtr<TYPE>& ObjectUniquePtr<TYPE>::operator=(
    ObjectUniquePtr&& other) noexcept {
  if (this != &other) {
    reset();
    m_ptr = std::move(other.m_ptr);
    other.m_ptr = nullptr;
  }
  return *this;
}

template <IsObject TYPE>
TYPE* ObjectUniquePtr<TYPE>::get() const {
  return m_ptr.get();
}

template <IsObject TYPE>
TYPE* ObjectUniquePtr<TYPE>::operator->() const {
  return m_ptr.get();
}

template <IsObject TYPE>
TYPE& ObjectUniquePtr<TYPE>::operator*() const {
  return *m_ptr;
}

template <IsObject TYPE>
ObjectUniquePtr<TYPE>::operator bool() const {
  return m_ptr != nullptr;
}

template <IsObject TYPE>
ObjectUniquePtr<TYPE>::operator std::unique_ptr<TYPE>() {
  return std::unique_ptr<TYPE>(m_ptr.release());
}

template <IsObject TYPE>
void ObjectUniquePtr<TYPE>::reset() {
  m_ptr.reset();
}

template <IsObject TYPE>
void ObjectUniquePtr<TYPE>::reset(TYPE* ptr) {
  m_ptr.reset(ptr);
}

template <IsObject TYPE>
void ObjectUniquePtr<TYPE>::serialize(utils::OArchive& archive) const {
  auto object_class = m_ptr->getClassName();
  archive << utils::ArchiveProperty("class", object_class);
  m_ptr->serialize(archive);
}

template <IsObject TYPE>
void ObjectUniquePtr<TYPE>::deserialize(utils::IArchive& archive) {
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

  m_ptr = utils::cast_unique_ptr<TYPE>(object_factory->createObject());
  m_ptr->deserialize(archive);
}

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECT_UNIQUE_PTR_H