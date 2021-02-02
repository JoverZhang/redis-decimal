#ifndef DECIMAL_MODULE_REDIS_DECIMAL_H
#define DECIMAL_MODULE_REDIS_DECIMAL_H

#include <iostream>
#include "../deps/decimal_for_cpp/decimal.h"
#include "../deps/redismodule/redismodule.h"

template<int Prec>
class RedisDecimal : public dec::decimal<Prec> {
 public:
  explicit RedisDecimal(const char *value) : dec::decimal<Prec>(std::string(value)) {}

  explicit RedisDecimal(const RedisModuleString *value)
          : dec::decimal<Prec>(std::string(RedisModule_StringPtrLen(value, NULL))) {}

  RedisModuleString *toRedisString(RedisModuleCtx *ctx) const {
    std::string str = dec::toString(*this);
    return RedisModule_CreateString(ctx, str.data(), str.length());
  }

  // Interim
  RedisModuleString *interimToRedisString(RedisModuleCtx *ctx) const {
    std::string str = dec::toString(*this);
    return RedisModule_CreateString(ctx, str.data(), str.length() - 1);
  }

  const RedisDecimal operator+(const RedisDecimal &rhs) const {
    dec::decimal<Prec> result = static_cast<dec::decimal<Prec>>(*this) + static_cast<dec::decimal<Prec>>(rhs);
    return *static_cast<RedisDecimal<Prec> *>(&result);
  }

  const RedisDecimal operator-(const RedisDecimal &rhs) const {
    dec::decimal<Prec> result = static_cast<dec::decimal<Prec>>(*this) - static_cast<dec::decimal<Prec>>(rhs);
    return *static_cast<RedisDecimal<Prec> *>(&result);
  }

  const RedisDecimal operator*(const RedisDecimal &rhs) const {
    dec::decimal<Prec> result = static_cast<dec::decimal<Prec>>(*this) * static_cast<dec::decimal<Prec>>(rhs);
    return *static_cast<RedisDecimal<Prec> *>(&result);
  }

  const RedisDecimal operator/(const RedisDecimal &rhs) const {
    dec::decimal<Prec> result = static_cast<dec::decimal<Prec>>(*this) / static_cast<dec::decimal<Prec>>(rhs);
    return *static_cast<RedisDecimal<Prec> *>(&result);
  }
};

#endif //DECIMAL_MODULE_REDIS_DECIMAL_H
