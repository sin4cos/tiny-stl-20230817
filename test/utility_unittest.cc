#include <gtest/gtest.h>
#include <include/bits/move.h>


void foo(int& n) {
  printf("lvalue overload, n:%d\n", n);
}

void foo(int&& n) {
  printf("rvalue overload, n:%d\n", n);
}

template <typename T>
void wrapper(T&& arg) {
  foo(sun::forward<T>(arg));
}

TEST(UtilityTest, ForwardTest) {
  int i = 10;
  wrapper(i);
  wrapper(20);
}
