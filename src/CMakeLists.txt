include_directories(${PROJECT_SOURCE_DIR}/deps/redismodule)
include_directories(${PROJECT_SOURCE_DIR}/deps/rmutil)

set(headers
    ../deps/redismodule/redismodule.h
    ../deps/decimal_for_cpp/decimal.h)

add_library(decimal SHARED
            module.cc
            redis_decimal.h
            decimal_utils.h
            ${headers})
