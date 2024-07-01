#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wordle_lib.h"

void should_be_exactly_equal(const char *message, int expected, int actual) {
  printf("%s\n", message);
  printf("%s: wanted %d, got %d\n",
         (expected == actual) ? "SUCCESS" : "FAILURE", expected, actual);
}

void ptr_should_be_equal(const char *message, void *expected, void *actual) {
  printf("%s\n", message);
  printf("%s: wanted %p, got %p\n",
         (expected == actual) ? "SUCCESS" : "FAILURE", expected, actual);
}

bool strings_equal_newline(char *expected, char *actual) {
  char *mycopy = strdup(actual);

  for (size_t i = 0; i < strlen(mycopy); i++) {
    if (mycopy[i] == '\n') {
      mycopy[i] = '\0';
    }
  }
  bool out = !strcmp(expected, mycopy);
  free(mycopy);
  return out;
}

bool word_in_vocabulary(char *word, char **vocabulary, size_t num_words) {
  for (size_t i = 0; i < num_words; i++) {
    if (strings_equal_newline(word, vocabulary[i])) {
      return true;
    }
  }
  return false;
}
