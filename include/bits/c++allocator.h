// Copyright 2023 The Summer Authors
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.

#ifndef TINY_STL_BITS_CXXALLOCATOR_H_
#define TINY_STL_BITS_CXXALLOCATOR_H_

#include <include/ext/new_allocator.h>

#if __cplusplus >= 201103L
namespace sun {
template <typename _Tp>
using __allocator_base = sun::new_allocator<_Tp>;
}
#else
#define __allocator_base sun::new_allocator
#endif

#endif  // TINY_STL_BITS_CXXALLOCATOR_H_

