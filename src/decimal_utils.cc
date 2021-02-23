#include "./decimal_utils.h"

#define DECIMAL(PREC) dec::decimal<PREC, dec::round_down_round_policy>
#define DECIMAL_D DECIMAL(MAX_PREC)

#define RESULT(n, prec) \
  switch (prec) {  \
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


string DecimalUtils::add(const string &a, const string &b, int precision) {
  DECIMAL_D x(a), y(b);
  x += y;
  RESULT(x, precision)
}

string DecimalUtils::sub(const string &a, const string &b, int precision) {
  DECIMAL_D x(a), y(b);
  x -= y;
  RESULT(x, precision)
}

string DecimalUtils::mul(const string &a, const string &b, int precision) {
  DECIMAL_D x(a), y(b);
  x *= y;
  RESULT(x, precision)
}

string DecimalUtils::div(const string &a, const string &b, int precision) {
  DECIMAL_D x(a), y(b);
  x /= y;
  RESULT(x, precision)
}


RedisModuleString *
RedisDecimalUtils::add(const RedisModuleString *a, const RedisModuleString *b, int precision) {
  string rst = DecimalUtils::add(RedisModule_StringPtrLen(a, NULL), RedisModule_StringPtrLen(b, NULL), precision);
  return RedisModule_CreateString(this->_ctx, rst.data(), rst.length());
}

RedisModuleString *
RedisDecimalUtils::sub(const RedisModuleString *a, const RedisModuleString *b, int precision) {
  string rst = DecimalUtils::sub(RedisModule_StringPtrLen(a, NULL), RedisModule_StringPtrLen(b, NULL), precision);
  return RedisModule_CreateString(this->_ctx, rst.data(), rst.length());
}

RedisModuleString *
RedisDecimalUtils::mul(const RedisModuleString *a, const RedisModuleString *b, int precision) {
  string rst = DecimalUtils::mul(RedisModule_StringPtrLen(a, NULL), RedisModule_StringPtrLen(b, NULL), precision);
  return RedisModule_CreateString(this->_ctx, rst.data(), rst.length());
}

RedisModuleString *
RedisDecimalUtils::div(const RedisModuleString *a, const RedisModuleString *b, int precision) {
  string rst = DecimalUtils::div(RedisModule_StringPtrLen(a, NULL), RedisModule_StringPtrLen(b, NULL), precision);
  return RedisModule_CreateString(this->_ctx, rst.data(), rst.length());
}
