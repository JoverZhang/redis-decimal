#ifndef DECIMAL_MODULE_DECIMAL_UTILS_H
#define DECIMAL_MODULE_DECIMAL_UTILS_H

#include <string>
#include "../deps/redismodule/redismodule.h"
#include "../deps/decimal_for_cpp/decimal.h"

using std::string;
using dec::decimal;

const int DEFAULT_PREC = 6;

#define DECIMAL(PREC) dec::decimal<PREC, dec::round_down_round_policy>

#define DECIMAL_D DECIMAL(DEFAULT_PREC)

#define RESULT(n, prec) \
switch (prec) {         \
  case 0: \
    return toString(DECIMAL(0)(n.getUnbiased(), n.getPrecFactor())); \
  case 1: \
    return toString(DECIMAL(1)(n.getUnbiased(), n.getPrecFactor())); \
  case 2: \
    return toString(DECIMAL(2)(n.getUnbiased(), n.getPrecFactor())); \
  case 3: \
    return toString(DECIMAL(3)(n.getUnbiased(), n.getPrecFactor())); \
  case 4: \
    return toString(DECIMAL(4)(n.getUnbiased(), n.getPrecFactor())); \
  case 5: \
    return toString(DECIMAL(5)(n.getUnbiased(), n.getPrecFactor())); \
  case 6: \
    return toString(DECIMAL(6)(n.getUnbiased(), n.getPrecFactor())); \
} \
throw std::logic_error("Precision other than 0-6 is not supported.");


class DecimalUtils {
 public:
  static string add(const string &a, const string &b) {
    return add(a, b, DEFAULT_PREC);
  }

  static string add(const string &a, const string &b, int precision) {
    DECIMAL_D x(a), y(b);
    x += y;
    RESULT(x, precision)
  }

  static string sub(const string &a, const string &b) {
    return sub(a, b, DEFAULT_PREC);
  }

  static string sub(const string &a, const string &b, int precision) {
    DECIMAL_D x(a), y(b);
    x -= y;
    RESULT(x, precision)
  }

  static string mul(const string &a, const string &b) {
    return mul(a, b, DEFAULT_PREC);
  }

  static string mul(const string &a, const string &b, int precision) {
    DECIMAL_D x(a), y(b);
    x *= y;
    RESULT(x, precision)
  }

  static string div(const string &a, const string &b) {
    return div(a, b, DEFAULT_PREC);
  }

  static string div(const string &a, const string &b, int precision) {
    DECIMAL_D x(a), y(b);
    x /= y;
    RESULT(x, precision)
  }
};


#endif //DECIMAL_MODULE_DECIMAL_UTILS_H
