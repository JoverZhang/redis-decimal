#include <string>
#include "../deps/redismodule/redismodule.h"
#include "./redis_decimal.h"

#define PREC 9


bool ignoreCaseEquals(const std::string str, const std::string expect) {
  return std::equal(str.begin(), str.end(), expect.begin(), [](char c1, char c2) {
    return tolower(c1) == tolower(c2);
  });
}

bool redisIgnoreCaseEquals(RedisModuleString *str, const char *expect) {
  return ignoreCaseEquals(std::string(RedisModule_StringPtrLen(str, NULL)),
                          std::string(expect));
}

int BigDecimal_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
  if (argc < 3) {
    return RedisModule_WrongArity(ctx);
  }
  RedisDecimal<PREC> x(argv[2]), y(argv[3]);
  RedisModule_AutoMemory(ctx);

  if (redisIgnoreCaseEquals(argv[1], "ADD")) {
    x += y;
  } else if (redisIgnoreCaseEquals(argv[1], "SUB")) {
    x -= y;
  } else if (redisIgnoreCaseEquals(argv[1], "MUL")) {
    x *= y;
  } else if (redisIgnoreCaseEquals(argv[1], "DIV")) {
    x /= y;
  } else {
    return RedisModule_WrongArity(ctx);
  }

  RedisModule_ReplyWithString(ctx, x.toRedisString(ctx));
  return REDISMODULE_OK;
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
