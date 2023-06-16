// Copyright 2023 The Summer Authors
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.

#ifndef TINY_STL_STD_TYPE_TRAITS_H_
#define TINY_STL_STD_TYPE_TRAITS_H_

#include <include/bits/c++config.h>

namespace sun {

template <typename _Tp, _Tp __v>
struct integral_constant {
  static constexpr _Tp value = __v;
  typedef _Tp value_type;
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


// Const-volatile modifications.
// - remove_const: 移除 const 限定
// - remove_volatile: 移除 volatile 限定
// - remove_cv: 移除 const 和 volatile 限定
// - add_const: 添加 const 限定
// - add_volatile: 添加 volatile 限定
// - add_cv: 添加 const 和 volatile 限定

template <typename _Tp>
struct remove_const {
  typedef _Tp type;
};

template <typename _Tp>
struct remove_const<_Tp const> {
  typedef _Tp type;
};

template <typename _Tp>
struct remove_volatile {
  typedef _Tp type;
};

template <typename _Tp>
struct remove_volatile<_Tp volatile> {
  typedef _Tp type;
};

template <typename _Tp>
struct remove_cv {
  typedef
    typename remove_const<typename remove_volatile<_Tp>::type>::type type;
};

template <typename _Tp>
struct add_const {
  typedef _Tp const type;
};

template <typename _Tp>
struct add_volatile {
  typedef _Tp volatile type;
};

template <typename _Tp>
struct add_cv {
  typedef
    typename add_const<typename add_volatile<_Tp>::type>::type type;
};


// Reference transformations.
// - remove_reference: 移除引用属性
// - is_lvalue_reference: 是否为左值引用
// - is_rvalue_reference: 是否为右值引用

template <typename _Tp>
struct remove_reference {
  typedef _Tp type;
};

template <typename _Tp>
struct remove_reference<_Tp&> {
  typedef _Tp type;
};

template <typename _Tp>
struct remove_reference<_Tp&&> {
  typedef _Tp type;
};

template <typename>
struct is_lvalue_reference : public false_type {};

template <typename _Tp>
struct is_lvalue_reference<_Tp&> : public true_type {};

template <typename>
struct is_rvalue_reference : public false_type {};

template <typename _Tp>
struct is_rvalue_reference<_Tp&&> : public true_type {};

struct __sfinae_types {
  typedef char __one;
  typedef struct {
    char __arr[2];
  } __two;
};

// 使用 SFINAE 技术去探测给定类型 _Tp 是否有一个公有的类型成员 _NTYPE
#define HAS_NESTED_TYPE(_NTYPE)                                               \
template <typename _Tp>                                                       \
class __has_##_NTYPE##_helper : __sfinae_types {                              \
  template <typename _Up>                                                     \
  struct _Wrap_type {};                                                       \
                                                                              \
  template <typename _Up>                                                     \
  static __one __test(_Wrap_type<typename _Up::_NTYPE>*);                     \
                                                                              \
  template <typename _Up>                                                     \
  static __two __test(...);                                                   \
                                                                              \
 public:                                                                      \
  static constexpr bool value = sizeof(__test<_Tp>(0)) == 1;                  \
};                                                                            \
                                                                              \
template <typename _Tp>                                                       \
struct __has_##_NTYPE                                                         \
    : integral_constant<                                                      \
          bool, __has_##_NTYPE##_helper<typename remove_cv<_Tp>::type>::value>\
 {};



}  // namespace sun

#endif  // TINY_STL_STD_TYPE_TRAITS_H_
