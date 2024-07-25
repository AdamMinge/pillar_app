#ifndef FLOW_DOCUMENT_OBJECT_UNIQUE_PTR_H
#define FLOW_DOCUMENT_OBJECT_UNIQUE_PTR_H

/* ---------------------------------- Standard ------------------------------ */
#include <memory>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_manager.h>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/pointer/unique_ptr_cast.h>
#include <qtils/serializer/archive_property.h>
#include <qtils/serializer/serializable.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/concept.h"
#include "flow/document/export.h"
#include "flow/document/flow/factory/object_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ------------------------- SerializeByObjectFactory ----------------------- */

template <IsObject TYPE>
struct SerializeByObjectFactory {
  void serialize(qtils::OArchive& archive, TYPE* object) const {
    auto object_class = object->getClassName();
    archive << qtils::ArchiveProperty("class", object_class);
  }

  [[nodiscard]] std::unique_ptr<TYPE> deserialize(
      qtils::IArchive& archive) const {
    auto object_class = QString{};
    archive >> qtils::ArchiveProperty("class", object_class);

    auto& manager = pillar::PluginManager::getInstance();
    auto factories = manager.getObjects<ObjectFactory>();

    auto object_factory = static_cast<ObjectFactory*>(nullptr);
    for (auto factory : factories) {
      if (object_class == factory->getObjectClassName()) {
        object_factory = factory;
        break;
      }
    }

    return qtils::cast_unique_ptr<TYPE>(object_factory->createObject());
  }
};

/* ------------------------ SerializeByDefaultFactory ----------------------- */

template <IsObject TYPE>
struct SerializeByDefaultFactory {
  void serialize(qtils::OArchive& archive, TYPE* object) const {}
  [[nodiscard]] std::unique_ptr<TYPE> deserialize(
      qtils::IArchive& archive) const {
    return std::make_unique<TYPE>();
  }
};

/* ------------------------------ ObjectUniquePtr --------------------------- */

template <IsObject TYPE, template <typename> class STRATEGY>
class ObjectUniquePtr : public qtils::Serializable,
                        public qtils::Deserializable {
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

  void serialize(qtils::OArchive& archive) const override;
  void deserialize(qtils::IArchive& archive) override;

 private:
  STRATEGY<TYPE> m_strategy;
  std::unique_ptr<TYPE> m_ptr;
};

template <IsObject TYPE, template <typename> class STRATEGY>
ObjectUniquePtr<TYPE, STRATEGY>::ObjectUniquePtr() = default;

template <IsObject TYPE, template <typename> class STRATEGY>
ObjectUniquePtr<TYPE, STRATEGY>::ObjectUniquePtr(std::unique_ptr<TYPE> ptr)
    : m_ptr(std::move(ptr)) {}

template <IsObject TYPE, template <typename> class STRATEGY>
ObjectUniquePtr<TYPE, STRATEGY>::ObjectUniquePtr(TYPE* ptr) : m_ptr(ptr) {}

template <IsObject TYPE, template <typename> class STRATEGY>
ObjectUniquePtr<TYPE, STRATEGY>::~ObjectUniquePtr() {
  reset();
}

template <IsObject TYPE, template <typename> class STRATEGY>
ObjectUniquePtr<TYPE, STRATEGY>::ObjectUniquePtr(
    ObjectUniquePtr&& other) noexcept
    : m_ptr(std::move(other.m_ptr)) {
  other.m_ptr = nullptr;
}

template <IsObject TYPE, template <typename> class STRATEGY>
ObjectUniquePtr<TYPE, STRATEGY>& ObjectUniquePtr<TYPE, STRATEGY>::operator=(
    ObjectUniquePtr&& other) noexcept {
  if (this != &other) {
    reset();
    m_ptr = std::move(other.m_ptr);
    other.m_ptr = nullptr;
  }
  return *this;
}

template <IsObject TYPE, template <typename> class STRATEGY>
TYPE* ObjectUniquePtr<TYPE, STRATEGY>::get() const {
  return m_ptr.get();
}

template <IsObject TYPE, template <typename> class STRATEGY>
TYPE* ObjectUniquePtr<TYPE, STRATEGY>::operator->() const {
  return m_ptr.get();
}

template <IsObject TYPE, template <typename> class STRATEGY>
TYPE& ObjectUniquePtr<TYPE, STRATEGY>::operator*() const {
  return *m_ptr;
}

template <IsObject TYPE, template <typename> class STRATEGY>
ObjectUniquePtr<TYPE, STRATEGY>::operator bool() const {
  return m_ptr != nullptr;
}

template <IsObject TYPE, template <typename> class STRATEGY>
ObjectUniquePtr<TYPE, STRATEGY>::operator std::unique_ptr<TYPE>() {
  return std::unique_ptr<TYPE>(m_ptr.release());
}

template <IsObject TYPE, template <typename> class STRATEGY>
void ObjectUniquePtr<TYPE, STRATEGY>::reset() {
  m_ptr.reset();
}

template <IsObject TYPE, template <typename> class STRATEGY>
void ObjectUniquePtr<TYPE, STRATEGY>::reset(TYPE* ptr) {
  m_ptr.reset(ptr);
}

template <IsObject TYPE, template <typename> class STRATEGY>
void ObjectUniquePtr<TYPE, STRATEGY>::serialize(
    qtils::OArchive& archive) const {
  m_strategy.serialize(archive, m_ptr.get());
  m_ptr->serialize(archive);
}

template <IsObject TYPE, template <typename> class STRATEGY>
void ObjectUniquePtr<TYPE, STRATEGY>::deserialize(qtils::IArchive& archive) {
  m_ptr = m_strategy.deserialize(archive);
  m_ptr->deserialize(archive);
}

/* ----------------------------------- Qtils -------------------------------- */

template <typename TYPE>
using DynamicObjectUniquePtr = ObjectUniquePtr<TYPE, SerializeByObjectFactory>;

template <typename TYPE>
using StaticObjectUniquePtr = ObjectUniquePtr<TYPE, SerializeByDefaultFactory>;

}  // namespace flow

#endif  // FLOW_DOCUMENT_OBJECT_UNIQUE_PTR_H