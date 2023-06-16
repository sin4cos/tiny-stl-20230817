// Copyright 2023 The Summer Authors
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.

#ifndef TINY_STL_BITS_STL_ITERATOR_BASE_FUNCS_H_
#define TINY_STL_BITS_STL_ITERATOR_BASE_FUNCS_H_

namespace sun {

// @brief __distance 计算从迭代器__first至__last的跳数（距离）
// @param __first 指向第一个元素的迭代器
// @param __last 指向范围末尾的迭代器
// @return 跳数（距离）
//
// 这是针对所有输入类迭代器（输入迭代器、前向迭代器、双向迭代器、随机访问迭代器）的通用版本
template <typename _InputIterator>
inline typename iterator_traits<_InputIterator>::difference_type
__distance(_InputIterator __first, _InputIterator __last,
           input_iterator_tag)
{
  typename iterator_traits<_InputIterator>::difference_type __n = 0;
  while (__first != __last) {
    ++__first;
    ++__n;
  }
  return __n;
}

// @brief __distance 计算从迭代器__first至__last的跳数（距离）
// @param __first 指向第一个元素的迭代器
// @param __last 指向范围末尾的迭代器
// @return 跳数（距离）
//
// 这是针对随机访问迭代器的特化版本，提供更好的性能
template <typename _RandomAccessIterator>
inline typename iterator_traits<_RandomAccessIterator>::difference_type
__distance(_RandomAccessIterator __first, _RandomAccessIterator __last,
           random_access_iterator_tag)
{
  return __last - __first;
}

// @brief distance 计算从迭代器__first至__last的跳数（距离）
// @param __first 指向第一个元素的迭代器
// @param __last 指向范围末尾的迭代器
// @return 跳数（距离）
//
// 本函数只针对输入类迭代器（包括输入迭代器、前向迭代器、双向迭代器、随机访问迭代器）
template <typename _InputIterator>
inline typename iterator_traits<_InputIterator>::difference_type
distance(_InputIterator __first, _InputIterator __last) {
  return sun::__distance(__first, __last, sun::__iterator_category(__first));
}


// @brief __advance 增加给定的迭代器 Iter 以 n 个元素的步长（跳数）
// @param __i 要前进的迭代器
// @param __n 迭代器要前进的元素数量（步长）
//
// 这是针对所有输入类迭代器（输入迭代器、前向迭代器、双向迭代器、随机访问迭代器）的通用版本，
// 提供了前进的功能（不支持反向前进）
template <typename _InputIterator, typename _Distance>
inline void
__advance(_InputIterator& __i, _Distance __n, input_iterator_tag) {
  static_assert(__n >= 0, "invalid argument");
  while (__n--)
    ++__i;
}

// @brief __advance 增加给定的迭代器 Iter 以 n 个元素的步长（跳数）
// @param __i 要前进的迭代器
// @param __n 迭代器要前进的元素数量（步长）
//
// 这是针对双向迭代器的特化版本，提供了反向前进（即后退）的支持
template <typename _BidirectionalIterator, typename _Distance>
inline void
__advance(_BidirectionalIterator& __i, _Distance __n,
          bidirectional_iterator_tag) {
  if (__n > 0)
    while (__n--)
      ++__i;
  else
    while (__n++)
      --__i;
}

// @brief __advance 增加给定的迭代器 Iter 以 n 个元素的步长（跳数）
// @param __i 要前进的迭代器
// @param __n 迭代器要前进的元素数量（步长）
//
// 这是针对随机访问迭代器的特化版本，支持双向前进，并提供了更好的性能
template <typename _RandomAccessIterator, typename _Distance>
inline void
__advance(_RandomAccessIterator& __i, _Distance __n,
          random_access_iterator_tag) {
  __i += __n;
}

// @brief __advance 增加给定的迭代器 Iter 以 n 个元素的步长（跳数）
// @param __i 要前进的迭代器
// @param __n 迭代器要前进的元素数量（步长）
//
// 本函数只针对输入类迭代器（包括输入迭代器、前向迭代器、双向迭代器、随机访问迭代器）
template <typename _InputIterator, typename _Distance>
inline void
advance(_InputIterator& __i, _Distance __n) {
  typename iterator_traits<_InputIterator>::difference_type __d = __n;
  sun::__advance(__i, __d, sun::__iterator_category(__i));
}


#if __cplusplus >= 201103L

// @brief next 返回迭代器第 n 个后继 (since C++11)
// @param __x 一个迭代器（副本）
// @param __n Iter要前进的元素数量（步长）
// @return 前进 n 个元素（步长）的后继迭代器（副本）
template <typename _ForwardIterator>
inline _ForwardIterator
next(_ForwardIterator __x, 
    typename iterator_traits<_ForwardIterator>::difference_type __n = 1) {
  sun::advance(__x, __n);
  return __x;
}

// @brief prev 返回迭代器 Iter 第 n 个前驱 (since C++11)
// @param __x 一个迭代器（副本）
// @param __n Iter要后退的元素数量（步长）
// @return 后退 n 个元素（步长）的前驱迭代器（副本）
template <typename _BidirectionalIterator>
inline _BidirectionalIterator
prev(_BidirectionalIterator __x,
    typename iterator_traits<_BidirectionalIterator>::difference_type __n = 1) {
  sun::advance(__x, -__n);
  return __x;
}
#endif  // __cplusplus >= 201103L

}  // namespace

#endif // TINY_STL_BITS_STL_ITERATOR_BASE_FUNCS_H_

