#include <string>
#include "../deps/redismodule/redismodule.h"
#include "./redis_decimal.h"
#include "./decimal_utils.h"

#define RC_RETURN(rst) \
  RedisModule_ReplyWithString(ctx, rst); \
  return REDISMODULE_OK;


bool ignoreCaseEquals(const std::string str, const std::string expect) {
  return std::equal(str.begin(), str.end(), expect.begin(), [](char c1, char c2) {
    return tolower(c1) == tolower(c2);
  });
}

bool redisIgnoreCaseEquals(RedisModuleString *str, const char *expect) {
  return ignoreCaseEquals(std::string(RedisModule_StringPtrLen(str, NULL)), std::string(expect));
}

int validate_precision(int prec) {
  return prec < 0 || MAX_PREC < prec;
}

int BigDecimal_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  if (argc < 4 || argc > 5) {
    return RedisModule_WrongArity(ctx);
  }
  RedisModule_AutoMemory(ctx);

  RedisModuleString *x = argv[2], *y = argv[3];
  RedisDecimalUtils rdUtils(ctx);

  // Set precision
  long long int prec;
  if (argc == 5) {
    if (RedisModule_StringToLongLong(argv[4], &prec) || validate_precision(prec)) {
      return RedisModule_WrongArity(ctx);
    }
  } else {
    prec = MAX_PREC;
  }

  // Addition
  if (redisIgnoreCaseEquals(argv[1], "ADD")) {
    RC_RETURN(rdUtils.add(x, y, prec))
  }
  // Subtraction
  if (redisIgnoreCaseEquals(argv[1], "SUB")) {
    RC_RETURN(rdUtils.sub(x, y, prec))
  }
  // Multiplication
  if (redisIgnoreCaseEquals(argv[1], "MUL")) {
    RC_RETURN(rdUtils.mul(x, y, prec))
  }
  // Division
  if (redisIgnoreCaseEquals(argv[1], "DIV")) {
    // TODO: optimize here
    // Check by zero
    RedisDecimal<MAX_PREC> check_by_zero(y);
    if (check_by_zero.getUnbiased() == 0) {
      return RedisModule_WrongArity(ctx);
    }
    RC_RETURN(rdUtils.div(x, y, prec))
  }

  return RedisModule_WrongArity(ctx);
}

#ifdef __cplusplus
extern "C" {
#endif

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  if (RedisModule_Init(ctx, "RedisDecimal", 1, REDISMODULE_APIVER_1) == REDISMODULE_ERR)
    return REDISMODULE_ERR;

  if (RedisModule_CreateCommand(ctx, "decimal", BigDecimal_RedisCommand, "readonly random fast", 0, 0, 0) ==
      REDISMODULE_ERR)
    return REDISMODULE_ERR;

  return REDISMODULE_OK;
}

#ifdef __cplusplus
}
#endif
