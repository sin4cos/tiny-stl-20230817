// Copyright 2023 The Summer Authors
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.

#ifndef TINY_STL_BITS_MOVE_H_
#define TINY_STL_BITS_MOVE_H_

namespace sun {

template <typename _Tp>
inline _Tp* __addressof(_Tp& __r) noexcept {
  return reinterpret_cast<_Tp*>(
      &const_cast<char&>(reinterpret_cast<const volatile char&>(__r)));
}

}  // namespace sun


#if __cplusplus >= 201103L
#include <include/std/type_traits.h>
namespace sun {

template <typename _Tp>
constexpr _Tp&&
forward(typename sun::remove_reference<_Tp>::type& __t) noexcept {
  return static_cast<_Tp&&>(__t);
}

template <typename _Tp>
constexpr _Tp&&
forward(typename sun::remove_reference<_Tp>::type&& __t) noexcept {
  static_assert(not sun::is_lvalue_reference<_Tp>::value, "template argument"
                "substituting _Tp is an lvalue reference type");
  return static_cast<_Tp&&>(__t);
}

template <typename _Tp>
constexpr typename sun::remove_reference<_Tp>::type&&
move(_Tp&& __t) noexcept {
  return static_cast<typename sun::remove_reference<_Tp>::type&&>(__t);
}


}  // namespace sun

#define SUN_MOVE(__val) sun::move(__val)
#define SUN_FORWARD(_Tp, __val) sun::forward<_Tp>(__val)
#else
#define SUN_MOVE(__val) (__val)
#define SUN_FORWARD(_Tp, __val) (__val)
#endif  // __cplusplus >= 201103L


namespace sun {

template <typename _Tp>
inline void
swap(_Tp& __a, _Tp& __b) {
  _Tp __tmp = SUN_MOVE(__a);
  __a = SUN_MOVE(__b);
  __b = SUN_MOVE(__tmp);
}

template <typename _Tp, size_t _Nm>
inline void
swap(_Tp (&__a)[_Nm], _Tp (&__b)[_Nm]) {
  for (size_t __n = 0; __n < _Nm; ++__n)
    swap(__a[__n], __b[__n]);
}

}  // namespace sun

#endif  // TINY_STL_BITS_MOVE_H_
