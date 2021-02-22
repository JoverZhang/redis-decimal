#include <iostream>
#include "../src/module.cc"
#include "./test_utils.cc"
#include "../src/decimal_utils.h"

#define D2 RedisDecimal<2>
#define D6 RedisDecimal<6>
#define D9 RedisDecimal<9>

using namespace std;
using namespace dec;

void testIgnoreCaseEquals() {
  CHECK(ignoreCaseEquals("1", "1"));
  CHECK(ignoreCaseEquals("22\0", "22\0"));
  CHECK(ignoreCaseEquals("333\n123", "333\n123"));
  CHECK(ignoreCaseEquals("333\0\n", "333\0"));
  CHECK(!ignoreCaseEquals("333\n", "333\0"));
}

void testRedisDecimal() {
  {
    D2 x("10"), y("20");
    x += y;
    CHECK_EQ("30.00", toString(x).data());
  }
  {
    D2 x("10"), y("20");
    x -= y;
    CHECK_EQ("-10.00", toString(x).data());
  }
  {
    D2 x("10"), y("20");
    x *= y;
    CHECK_EQ("200.00", toString(x).data());
  }
  {
    D2 x("10"), y("20");
    x /= y;
    CHECK_EQ("0.50", toString(x).data());
  }

  CHECK_EQ("4.444400", toString(D6("2.2222") * D6("2")).data());
  CHECK_EQ("-2.222200", toString(D6("2.2222") * D6("-1")).data());

  CHECK_EQ("1.111100", toString(D6("2.2222") / D6("2")).data());
  CHECK_EQ("3.333333", toString(D6("10") / D6("3")).data()); // actual is 3.333...
  CHECK_EQ("6.666667", toString(D6("20") / D6("3")).data()); // actual is 6.666...

  // Test for 7 digit
  {
    D9 x("0");
    for (int i = 0; i < 10'000'000; ++i) {
      x += D9("1") / D9("10000000");
    }
    CHECK_EQ("1.000000000", toString(x).data());

    for (int i = 0; i < 10'000'000; ++i) {
      x -= D9("1") * D9("0.0000001");
    }
    CHECK_EQ("0.000000000", toString(x).data());
  }
  {
    D9 x("0");
    for (int i = 0; i < 10'000'000; ++i) {
      x += D9("1");
    }
    CHECK_EQ("10000000.000000000", toString(x).data());

    for (int i = 0; i < 10'000'000; ++i) {
      x -= D9("1");
    }
    CHECK_EQ("0.000000000", toString(x).data());
  }
}

void testDecimalUtils() {
  {
    CHECK_EQ("30.000000", DecimalUtils::add("10", "20", 6).data());
    CHECK_EQ("-10.000000", DecimalUtils::sub("10", "20", 6).data());
    CHECK_EQ("200.000000", DecimalUtils::mul("10", "20", 6).data());
    CHECK_EQ("0.500000", DecimalUtils::div("10", "20", 6).data());
  }
  {
    // Multiple
    CHECK_EQ("4.444400", DecimalUtils::mul("2.2222", "2", 6).data());
    CHECK_EQ("-2.222200", DecimalUtils::mul("2.2222", "-1", 6).data());

    // Division
    CHECK_EQ("1.111100", DecimalUtils::div("2.2222", "2", 6).data());
    CHECK_EQ("1.1111", DecimalUtils::div("2.2222", "2", 4).data());
    CHECK_EQ("1.11", DecimalUtils::div("2.2222", "2", 2).data());
    CHECK_EQ("1", DecimalUtils::div("2.2222", "2", 0).data());
    CHECK_EQ("0.333333", DecimalUtils::div("1", "3", 6).data());
    CHECK_EQ("0.666666", DecimalUtils::div("2", "3", 6).data());
    CHECK_EQ("33.333333", DecimalUtils::div("100", "3", 6).data());
    CHECK_EQ("66.666666", DecimalUtils::div("200", "3", 6).data());
  }
  {
    // Test for 6 digit
    {
      string x = "0";
      for (int i = 0; i < 1'000'000; ++i) {
        x = DecimalUtils::add(x, DecimalUtils::div("1", "1000000", 6), 6);
      }
      CHECK_EQ("1.000000", x.data());

      for (int i = 0; i < 1'000'000; ++i) {
        x = DecimalUtils::sub(x, DecimalUtils::mul("1", "0.000001", 6), 6);
      }
      CHECK_EQ("0.000000", x.data());
    }
  }
}

int main() {
  testIgnoreCaseEquals();
  testRedisDecimal();
  testDecimalUtils();
  return 0;
}
