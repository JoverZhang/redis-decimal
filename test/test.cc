#include <iostream>
#include "../src/module.cc"
#include "./test_utils.cc"

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


int main() {
  testIgnoreCaseEquals();
  testRedisDecimal();
  return 0;
}
