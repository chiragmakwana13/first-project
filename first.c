#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TOKEN_LENGTH 100

// DFA states
enum {
  START_STATE,
  IDENTIFIER_STATE,
  NUMBER_STATE,
  OPERATOR_STATE,
  WHITESPACE_STATE
};

// DFA transitions
int transitions[][5] = {
  //           a-z   0-9   +-*=/   space   other
  /* START */ { 1,    2,    3,      4,      -1   },
  /* IDEN */  { 1,    1,    5,      5,      -1   },
  /* NUM */   { 5,    2,    5,      5,      -1   },
  /* OP */    { 5,    5,    5,      5,      -1   },
  /* SPACE */ { 5,    5,    5,      4,      -1   },
};

// Token types
enum {
  IDENTIFIER_TOKEN,
  NUMBER_TOKEN,
  OPERATOR_TOKEN
};

// DFA function
int getTokenType(char* token) {
  int state = START_STATE;
  int length = strlen(token);

  for (int i = 0; i < length; i++) {
    char c = token[i];
    int input;

    if (c >= 'a' && c <= 'z') {
      input = 0;
    } else if (c >= '0' && c <= '9') {
      input = 1;
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
      input = 2;
    } else if (c == ' ' || c == '\t' || c == '\n') {
      input = 3;
    } else {
      input = 4;
    }

    state = transitions[state][input];

    if (state == -1) {
      return -1;
    }
  }

  if (state == IDENTIFIER_STATE) {
    return IDENTIFIER_TOKEN;
  } else if (state == NUMBER_STATE) {
    return NUMBER_TOKEN;
  } else if (state == OPERATOR_STATE) {
    return OPERATOR_TOKEN;
  } else {
    return -1;
  }
}

int main() {
  char input[MAX_TOKEN_LENGTH];
  char tokens[MAX_TOKEN_LENGTH][MAX_TOKEN_LENGTH];
  int token_count = 0;

  printf("Enter a string: ");
  fgets(input, MAX_TOKEN_LENGTH, stdin);

  char* token = strtok(input, " \t\n");

  while (token != NULL) {
    int token_type = getTokenType(token);

    if (token_type != -1) {
      strcpy(tokens[token_count], token);
      token_count++;
    }

    token = strtok(NULL, " \t\n");
  }

  printf("\nIdentified Tokens:\n");
  for (int i = 0; i < token_count; i++) {
    printf("%s\n", tokens[i]);
  }

  return 0;
}