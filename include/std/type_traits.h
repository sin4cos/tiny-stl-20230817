#ifndef STD_TYPE_TRAITS_H
#define STD_TYPE_TRAITS_H

#include <include/bits/c++config.h>

namespace sun {

template <typename _Tp, _Tp __v>
struct integral_constant {
  static constexpr _Tp                value = __v;
  typedef _Tp                         value_type;
  typedef integral_constant<_Tp, __v> type;
  constexpr operator value_type() { return value; }
};

template <typename _Tp, _Tp __v>
constexpr _Tp integral_constant<_Tp, __v>::value;

typedef integral_constant<bool, true> true_type;

typedef integral_constant<bool, false> false_type;


/* 类型相关*/

template <typename, typename>
struct is_same : public false_type {};

template <typename _Tp>
struct is_same<_Tp, _Tp> : public true_type {};

}  // namespace sun

#endif  // STD_TYPE_TRAITS_H