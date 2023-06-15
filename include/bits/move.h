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

}  // namespace sun
#endif  // __cplusplus >= 201103L

#endif  // TINY_STL_BITS_MOVE_H_
