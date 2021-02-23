![GitHub](https://img.shields.io/github/v/release/joverzhang/redis-decimal?include_prereleases)
[![Docker Cloud Build Status](https://img.shields.io/docker/cloud/build/ttmo/redis-decimal?logo=docker)](https://hub.docker.com/repository/docker/ttmo/redis-decimal)
![GitHub](https://img.shields.io/github/license/JoverZhang/redis-decimal)

# RedisDecimal: Floating-Point Number based on 10 for Redis

# Quick Start Guide

## 1. Building and Loading

To build **RedisDecimal**, ensure you have `cmake` and `make`, and afterwards run the following command.

```shell
cmake .
make
```

If the build is successful, you'll have a shared library called `libdecimal.so` in the `lib` directory.

To load the library, pass its path to the `--loadmodule` directive when starting `redis-server`:

```shell
$ redis-server --loadmodule ./lib/libdecimal.so
```

## 2. Use RedisDecimal with `redis-cli`

```shell
# redis-cli
127.0.0.1:6379>
```

And run the following command:

```shell
127.0.0.1:6379> DECIMAL ADD 10 20
"30.000000000"
127.0.0.1:6379> DECIMAL SUB 10 20
"-10.000000000"
127.0.0.1:6379> DECIMAL MUL 10 20
"200.000000000"
127.0.0.1:6379> DECIMAL DIV 10 20
"0.500000000"
```

# Extensions

## Test for RedisDecimal

To build **RedisDecimal**, and run the **unit testing**.

```shell
cmake .
make
./.tests/tests
```
