#include <gtest/gtest.h>
#include <include/bits/allocator.h>

struct Foo {
 Foo() {
   printf("Foo Ctor\n");
 }

 ~Foo() {
   printf("Foo Dtor\n");
 }
};

TEST(MemoryTest, AllocatorTest) {
  sun::allocator<int> alloc;
  int* p = alloc.allocate(1);
  *p = 2023;
  ASSERT_EQ(*p, 2023);
  ASSERT_NE(*p, 2022);
  alloc.deallocate(p, 1);

  sun::allocator<Foo> foo_alloc;
  Foo* f = foo_alloc.allocate(1);
  foo_alloc.construct(f);
  foo_alloc.destroy(f);
  foo_alloc.deallocate(f, 1);

  ASSERT_EQ(alloc, foo_alloc);  // allocator是无状态的，所以本质上它们是相等的
}
