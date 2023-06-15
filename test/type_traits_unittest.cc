#include <gtest/gtest.h>
#include <include/std/type_traits.h>

TEST(TypeTraitsTest, IntegralConstantTest) {
  typedef sun::integral_constant<int, 2> two_t;
  typedef sun::integral_constant<int, 4> four_t;

  static_assert(not sun::is_same<two_t, four_t>::value,
                "two_t and four_t are equal");
  static_assert(two_t::value * 2 == four_t::value, "2*2 != 4");
}

TEST(TypeTraitsTest, IsSameTest) {
  static_assert(sun::is_same<float, int32_t>::value == false,
                "float type is not same as int32_t type");

  static_assert(sun::is_same<int, int>::value == true,
                "int type is same as int type");
  static_assert(sun::is_same<int, unsigned int>::value == false,
                "int type is not same as unsigned int type");
  static_assert(sun::is_same<int, signed int>::value == true,
                "int type is not same as signed int type");

  static_assert(sun::is_same<int, const int>::value == false,
                "const-qualified type T is not same as non-const T");
  static_assert(sun::is_same<int, volatile int>::value == false,
                "volatile-qualified type T is not same as non-volatile T");
  static_assert(sun::is_same<const int, volatile int>::value == false,
                "volatile-qualified type T is not same as const-qualified T");
}

TEST(TypeTraitsTest, RemoveReferenceTest) {
  static_assert(sun::is_same<int, sun::remove_reference<int&>::type>::value,
                "");
  static_assert(sun::is_same<int, sun::remove_reference<int&&>::type>::value,
                "");
  static_assert(not sun::is_same<int, int&>::value, "");
  static_assert(not sun::is_same<int, int&&>::value, "");
  static_assert(
      sun::is_same<const int, sun::remove_reference<const int&>::type>::value,
      "");
}

TEST(TypeTraitsTest, IsLvalueReferenceTest) {
  static_assert(not sun::is_lvalue_reference<int>::value, "");
  static_assert(sun::is_lvalue_reference<int&>::value, "");
  static_assert(not sun::is_lvalue_reference<int&&>::value, "");
}

TEST(TypeTraitsTest, IsRvalueReferenceTest) {
  static_assert(not sun::is_rvalue_reference<int>::value, "");
  static_assert(not sun::is_rvalue_reference<int&>::value, "");
  static_assert(sun::is_rvalue_reference<int&&>::value, "");
}
