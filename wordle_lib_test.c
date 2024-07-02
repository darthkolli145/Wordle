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

bool these_words_present(char **vocabulary, size_t num_words,
                         char **expected_vocabulary,
                         size_t expected_num_words) {
  for (size_t i = 0; i < expected_num_words; i++) {
    printf("vocabulary: %s\n", vocabulary[i]);
  }
  for (size_t i = 0; i < expected_num_words; i++) {
    if (!word_in_vocabulary(expected_vocabulary[i], vocabulary, num_words)) {
      printf("FAILURE: expected to find word %s\n", expected_vocabulary[i]);
      return false;
    }
  }
  printf("SUCCESS: all expected words present\n");
  return true;
}

void check_score_guess(char *secret, char *guess, char *expected) {
  printf("secret: %s, guess: %s, expected result: %s\n", secret, guess,
         expected);

  char result[7];
  score_guess(secret, guess, result);

  printf("score: %s\n", result);

  bool success = strings_equal_newline(expected, result);
  printf("%s: got %s\n", success ? "SUCCESS" : "FAILURE", result);
}

int main(void) {
  printf("\n**** tests for valid_guess ****\n");
  char **vocabulary = calloc(10, sizeof(char *));
  vocabulary[0] = strdup("moody");
  vocabulary[1] = strdup("sheep");
  vocabulary[2] = strdup("hippy");
  vocabulary[3] = strdup("sleet");
  vocabulary[4] = strdup("oxide");
  vocabulary[5] = strdup("flour");
  vocabulary[6] = strdup("copse");
  vocabulary[7] = strdup("nobly");
  vocabulary[8] = strdup("fraud");
  vocabulary[9] = strdup("geese");

should_be_exactly_equal("moody in vocabulary", true,
                          valid_guess("moody", vocabulary, 10));
  should_be_exactly_equal("sleet in vocabulary", true,
                          valid_guess("sleet", vocabulary, 10));
  should_be_exactly_equal("irate not in vocabulary", false,
                          valid_guess("irate", vocabulary, 10));
  should_be_exactly_equal("raise not in vocabulary", false,
                          valid_guess("raise", vocabulary, 10));

  should_be_exactly_equal("ggggg not in vocabulary", false,
                          valid_guess("ggggg", vocabulary, 10));
  should_be_exactly_equal("jazzy not in vocabulary", false,
                          valid_guess("jazzy", vocabulary, 10));
  should_be_exactly_equal("oxide in vocabulary", true,
                          valid_guess("oxide", vocabulary, 10));
  should_be_exactly_equal("geese in vocabulary", true,
                          valid_guess("geese", vocabulary, 10));
  free_vocabulary(vocabulary, 10);
