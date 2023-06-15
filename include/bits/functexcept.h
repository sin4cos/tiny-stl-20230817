// Copyright 2023 The Summer Authors
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.

#ifndef TINY_STL_BITS_FUNCTEXCEPT_H_
#define TINY_STL_BITS_FUNCTEXCEPT_H_

namespace sun {

void
__throw_bad_alloc(void) { abort(); }

}  // namespace sun

#endif  // TINY_STL_BITS_FUNCTEXCEPT_H_
