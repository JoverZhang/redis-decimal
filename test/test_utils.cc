#include <cstdio>
#include <cstdlib>
#include <cstring>

static inline void check_helper(const char *file, int line, const char *source, bool condition) {
  if (!condition) {
    printf("%s:%d:\n CHECK(%s) failed\n", file, line, source);
    abort();
  }
}

static inline void check_equals_helper(const char *file, int line,
                                       const char *expected_source, const char *expected,
                                       const char *value_source, const char *value) {
  if ((expected == NULL && value != NULL) ||
      (expected != NULL && value == NULL)) {
    abort();
  }

  if ((expected != NULL && value != NULL && strcmp(expected, value) != 0)) {
    printf("%s:%d:\n CHECK_EQ(%s, %s) failed\n"
           "#  Expected: %s\n"
           "#  Found:    %s\n",
           file, line, expected_source, value_source, expected, value);
    abort();
  }
}

#define CHECK(condition) check_helper(__FILE__, __LINE__, #condition, condition)
#define CHECK_EQ(expect, actual) check_equals_helper(__FILE__, __LINE__, #expect, expect, #actual, actual)
