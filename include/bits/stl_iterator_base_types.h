// Copyright 2023 The Summer Authors
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.

#ifndef TINY_STL_BITS_STL_ITERATOR_BASE_TYPES_H_
#define TINY_STL_BITS_STL_ITERATOR_BASE_TYPES_H_

#include <include/bits/c++config.h>
#if __cplusplus >= 201103L
#include <include/std/type_traits.h>
#endif

namespace sun {

struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag : public input_iterator_tag {};

struct bidirectional_iterator_tag : public forward_iterator_tag {};

struct random_access_iterator_tag : public bidirectional_iterator_tag {};


// @brief iterator 通用的迭代器类
//
// 这是一个空类，除了定义一些嵌套的类型外什么事都不做
template <typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
          typename _Pointer = _Tp*, typename _Reference = _Tp&>
struct iterator {
  // 定义嵌套类型
  typedef _Category       iterator_category;
  typedef _Tp             value_type;
  typedef _Distance       difference_type;
  typedef _Pointer        pointer;
  typedef _Reference      reference;
};


#if __cplusplus >= 201103L

HAS_NESTED_TYPE(iterator_category)

template <typename _Iterator,
          bool = __has_iterator_category<_Iterator>::value>
struct __iterator_traits {};

template <typename _Iterator>
struct __iterator_traits<_Iterator, true> {
  typedef typename _Iterator::iterator_category iterator_category;
  typedef typename _Iterator::value_type        value_type;
  typedef typename _Iterator::difference_type   difference_type;
  typedef typename _Iterator::pointer           pointer;
  typedef typename _Iterator::reference         reference;
};

// @brief 迭代器特征萃取类 - 通用版本
//
// 通用版本的特征萃取类只是简单地转发 _Iterator 定义的嵌套类型
// 针对 pointers 和 pointers-to-const 提供了语义更准确的特化版本
template <typename _Iterator>
struct iterator_traits : public __iterator_traits<_Iterator> {};

#else

// @brief 迭代器特征萃取类 - 通用版本
//
// 通用版本的特征萃取类只是简单地转发 _Iterator 定义的嵌套类型
// 针对 pointers 和 pointers-to-const 提供了语义更准确的特化版本
template <typename _Iterator>
struct iterator_traits {
  typedef typename _Iterator::iterator_category iterator_category;
  typedef typename _Iterator::value_type        value_type;
  typedef typename _Iterator::difference_type   difference_type;
  typedef typename _Iterator::pointer           pointer;
  typedef typename _Iterator::reference         reference;
};

#endif  // __cplusplus >= 201103L

// @brief 迭代器特征萃取类 - pointer 特化版本
template <typename _Tp>
struct iterator_traits<_Tp*> {
  typedef random_access_iterator_tag  iterator_category;
  typedef _Tp                         value_type;
  typedef ptrdiff_t                   difference_type;
  typedef _Tp*                        pointer;
  typedef _Tp&                        reference;
};

// @brief 迭代器特征萃取类 - const pointer 特化版本
template <typename _Tp>
struct iterator_traits<const _Tp*> {
  typedef random_access_iterator_tag  iterator_category;
  typedef _Tp                         value_type;
  typedef ptrdiff_t                   difference_type;
  typedef const _Tp*                  pointer;
  typedef const _Tp&                  reference;
};


template <typename _Iter>
inline typename iterator_traits<_Iter>::iterator_category
__iterator_category(const _Iter&) {
  return typename iterator_traits<_Iter>::iterator_category();
}

}  // namespace sun

#endif  // TINY_STL_BITS_STL_ITERATOR_BASE_TYPES_H_

