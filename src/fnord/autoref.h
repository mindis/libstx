/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _FNORD_BASE_AUTOREF_H
#define _FNORD_BASE_AUTOREF_H
#include <functional>
#include <memory>
#include <mutex>
#include <stdlib.h>
#include <atomic>
#include <fnord/stdtypes.h>

namespace fnord {

template <typename T>
class AutoRef {
public:
  using ValueType = T;

  AutoRef(std::nullptr_t);
  AutoRef(T* ref);

  AutoRef(const AutoRef<T>& other);
  AutoRef(AutoRef<T>&& other);

  ~AutoRef();
  AutoRef<T>& operator=(const AutoRef<T>& other);

  T& operator*() const;
  T* operator->() const;

  T* get() const;
  T* release();

  template <typename T_>
  AutoRef<T_> asInstanceOf() const;

protected:
  T* ref_;
};

class RefCounted {
public:
  RefCounted();
  virtual ~RefCounted() {}

  void incRef();
  bool decRef();
protected:
  mutable std::atomic<unsigned> refcount_;
};

template <typename T>
using RefPtr = AutoRef<T>;

template <typename T>
using RefPtrVector = Vector<AutoRef<T>>;

template <typename T>
AutoRef<T> mkRef(T* ptr);

} // namespace fnord

#include "autoref_impl.h"
#endif