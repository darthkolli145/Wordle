#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wordle_lib.h"

int main(void) {
  printf("\n**** tests for free_vocabulary ****\n");
  char **expected_vocabulary;
  expected_vocabulary = calloc(20, sizeof(char *));
  int i = 0;
  expected_vocabulary[i++] = strdup("moody");
  expected_vocabulary[i++] = strdup("sheep");
  expected_vocabulary[i++] = strdup("hippy");
  expected_vocabulary[i++] = strdup("sleet");
  expected_vocabulary[i++] = strdup("oxide");
  expected_vocabulary[i++] = strdup("flour");
