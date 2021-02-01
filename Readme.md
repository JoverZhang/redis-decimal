# RedisDecimal: Floating-Point Number based on 10 for Redis

# Quick Start Guide

## Building and Loading

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

# Extensions

## Test for RedisDecimal

To build **RedisDecimal**, and run the **unit testing**.

```shell
cmake .
make
./.test/test
```
