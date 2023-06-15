// Copyright 2023 The Summer Authors
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.

#ifndef TINY_STL_BITS_ALLOCATOR_H_
#define TINY_STL_BITS_ALLOCATOR_H_

#include <include/bits/c++allocator.h>
#include <include/bits/memoryfwd.h>
#if __cplusplus >= 201103L
#include <include/std/type_traits.h>
#endif

namespace sun {

template <>
class allocator<void> {
 public:
  typedef size_t        size_type;
  typedef ptrdiff_t     difference_type;
  typedef void*         pointer;
  typedef const void*   const_pointer;
  typedef void          value_type;

  template <typename _Tp1>
  struct rebind {
    typedef allocator<_Tp1> other;
  };

#if __cplusplus >= 201103L
  typedef true_type propagate_on_container_move_assignment;
#endif
};


template <typename _Tp>
class allocator : public __allocator_base<_Tp> {
 public:
  typedef size_t        size_type;
  typedef ptrdiff_t     difference_type;
  typedef _Tp*          pointer;
  typedef const _Tp*    const_pointer;
  typedef _Tp&          reference;
  typedef const _Tp&    const_reference;
  typedef _Tp           value_type;

  template <typename _Tp1>
  struct rebind {
    typedef allocator<_Tp1> other;
  };

#if __cplusplus >= 201103L
  typedef true_type propagate_on_container_move_assignment;
#endif

  allocator() throw() {}

  allocator(const allocator& __a) throw()
   : __allocator_base<_Tp>(__a) {}
 
  template <typename _Tp1>
  allocator(const allocator<_Tp1>&) throw() {}

  ~allocator() throw() {}
  
  // Inherit everything else.
};

template <typename _T1, typename _T2>
inline bool
operator==(const allocator<_T1>&, const allocator<_T2>&) {
  return true;
}

template <typename _Tp>
inline bool
operator==(const allocator<_Tp>&, const allocator<_Tp>&) {
  return true;
}

template <typename _T1, typename _T2>
inline bool
operator!=(const allocator<_T1>&, const allocator<_T2>&) {
  return false;
}

template <typename _Tp>
inline bool
operator!=(const allocator<_Tp>&, const allocator<_Tp>&) {
  return false;
}

}  // namespace sun

#endif  // TINY_STL_BITS_ALLOCATOR_H_

