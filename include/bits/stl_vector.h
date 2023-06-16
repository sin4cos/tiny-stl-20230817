// Copyright 2023 The Summer Authors
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.

#ifndef TINY_STL_BITS_STL_VECTOR_H_
#define TINY_STL_BITS_STL_VECTOR_H_

#include <include/bits/stl_iterator_base_types.h>
#include <include/bits/stl_iterator_base_funcs.h>
#include <include/bits/allocator.h>

namespace sun {

template <typename _Tp, typename _Alloc>
struct _Vector_base {

  struct _Vector_impl : public _Tp_alloc_type {
    pointer _M_start;
    pointer _M_finish;
    pointer _M_end_of_storage;

    _Vector_impl()
     : _Tp_alloc_type(), _M_start(0), _M_finish(0), _M_end_of_storage(0) {}

    _Vector_impl(_Tp_alloc_type const& __a)
     : _Tp_alloc_type(__a), _M_start(0), _M_finish(0), _M_end_of_storage(0) {}

#if __cplusplus >= 201103L
    _Vector_impl(_Tp_alloc_type&& __a)
     : _Tp_alloc_type(sun::move(__a)),
       _M_start(0), _M_finish(0), _M_end_of_storage(0) {}
#endif

    void _M_swap_data(_Vector_impl& __x) {
      sun::swap(_M_start, __x._M_start);
      sun::swap(_M_finish, __x._M_finish);
      sun::swap(_M_end_of_storage, __x._M_end_of_storage);
    }
  };  // struct _Vector_impl

  // TODO
};

}  // namespace sun

#endif // TINY_STL_BITS_STL_VECTOR_H_

