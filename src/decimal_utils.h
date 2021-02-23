#ifndef DECIMAL_MODULE_DECIMAL_UTILS_H
#define DECIMAL_MODULE_DECIMAL_UTILS_H

#include <string>
#include "../deps/redismodule/redismodule.h"
#include "../deps/decimal_for_cpp/decimal.h"

using std::string;
using dec::decimal;

const int MAX_PREC = 6;


class DecimalUtils {
 public:
  static string add(const string &a, const string &b, int precision = MAX_PREC);

  static string sub(const string &a, const string &b, int precision = MAX_PREC);

  static string mul(const string &a, const string &b, int precision = MAX_PREC);

  static string div(const string &a, const string &b, int precision = MAX_PREC);
};


class RedisDecimalUtils {
 public:
  explicit RedisDecimalUtils(RedisModuleCtx *ctx) : _ctx(ctx) {};

  RedisModuleString *add(const RedisModuleString *a, const RedisModuleString *b, int precision = MAX_PREC);

  RedisModuleString *sub(const RedisModuleString *a, const RedisModuleString *b, int precision = MAX_PREC);

  RedisModuleString *mul(const RedisModuleString *a, const RedisModuleString *b, int precision = MAX_PREC);

  RedisModuleString *div(const RedisModuleString *a, const RedisModuleString *b, int precision = MAX_PREC);

 private:
  RedisModuleCtx *_ctx;
};

#endif //DECIMAL_MODULE_DECIMAL_UTILS_H
