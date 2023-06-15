// Copyright 2023 The Summer Authors
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.

#ifndef TINY_STL_EXT_NEW_ALLOCATOR_H_
#define TINY_STL_EXT_NEW_ALLOCATOR_H_

#include <include/bits/c++config.h>
#include <include/bits/move.h>
#include <include/bits/functexcept.h>
#if __cplusplus >= 201103L
#include <include/std/type_traits.h>
#endif

namespace sun {

template <typename _Tp>
class new_allocator {
 public:
  typedef size_t      size_type;
  typedef ptrdiff_t   difference_type;
  typedef _Tp*        pointer;
  typedef const _Tp*  const_pointer;
  typedef _Tp&        reference;
  typedef const _Tp&  const_reference;
  typedef _Tp         value_type;

  template <typename _Tp1>
  struct rebind {
    typedef new_allocator<_Tp1> other;
  };

#if __cplusplus >= 201103L
  typedef sun::true_type propagate_on_container_move_assignment;
#endif

  new_allocator() noexcept {}

  new_allocator(const new_allocator&) noexcept {}

  template <typename _Tp1>
  new_allocator(const new_allocator<_Tp1>&) noexcept {}

  ~new_allocator() noexcept {}

  pointer
  addressof(reference __r) const noexcept {
    return sun::__addressof(__r);
  }

  const_pointer
  addressof(const_reference __r) const noexcept {
    return sun::__addressof(__r);
  }

  size_type
  max_size() const noexcept {
    return size_t(-1) / sizeof(_Tp);
  }

  pointer
  allocate(size_type __n, const void* = 0) {
    if (__n > this->max_size())
      sun::__throw_bad_alloc();
    return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
  }

  void
  deallocate(pointer __p, size_type) {
    ::operator delete(__p);
  }

#if __cplusplus >= 201103L
  template <typename _Up, typename... _Args>
  void
  construct(_Up* __p, _Args... __args) {
    ::new((void *)__p) _Up(sun::forward<_Args>(__args)...);
  }

  template <typename _Up>
  void
  destroy(_Up* __p) {
    __p->~_Up();
  }
#else
  void
  construct(pointer __p, const _Tp& __val) {
    ::new((void *)__p) _Tp(__val);
  }

  void
  destroy(pointer __p) {
    __p->~_Tp();
  }
#endif
};

}  // namespace sun

#endif  // TINY_STL_EXT_NEW_ALLOCATOR_H_
