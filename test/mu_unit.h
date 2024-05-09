#ifndef MU_UNIT
#define MU_UNIT

#include <stdio.h>

#define mu_assert(message, test)                                               \
  do {                                                                         \
    if (!(test))                                                               \
      return message;                                                          \
  } while (0)

#define mu_run_test(test)                                                      \
  do {                                                                         \
    char *message = test();                                                    \
    tests_summary++;                                                           \
    if (message) {                                                             \
      tests_failed++;                                                          \
      printf("%s\n", message);                                                 \
    } else {                                                                   \
      tests_access++;                                                          \
    }                                                                          \
  } while (0)

extern int tests_access;
extern int tests_failed;
extern int tests_summary;

#endif // MU_UNIT