#include <stdbool.h>
#include <tree_sitter/parser.h>

enum {
  STRING,
  LINE_BREAK
};

void *tree_sitter_shared_external_tokens_external_scanner_create() {
  return NULL;
}

void tree_sitter_shared_external_tokens_external_scanner_reset(void *payload) {
}

bool tree_sitter_shared_external_tokens_external_scanner_serialize(void *payload, TSExternalTokenState state) {
  return true;
}

void tree_sitter_shared_external_tokens_external_scanner_deserialize(void *payload, TSExternalTokenState state) {
}

bool tree_sitter_shared_external_tokens_external_scanner_scan(
  void *payload, TSLexer *lexer, const bool *whitelist) {

  // If a line-break is a valid lookahead token, only skip spaces.
  if (whitelist[LINE_BREAK]) {
    while (lexer->lookahead == ' ') {
      lexer->advance(lexer, true);
    }

    if (lexer->lookahead == '\n') {
      lexer->advance(lexer, false);
      lexer->result_symbol = LINE_BREAK;
      return true;
    }
  }

  // If a line-break is not a valid lookahead token, skip line breaks as well
  // as spaces.
  if (whitelist[STRING]) {
    while (lexer->lookahead == ' ' || lexer->lookahead == '\n') {
      lexer->advance(lexer, true);
    }

    if (lexer->lookahead == '\'') {
      lexer->advance(lexer, false);

      while (lexer->lookahead != '\'') {
        lexer->advance(lexer, false);
      }

      lexer->advance(lexer, false);
      lexer->result_symbol = STRING;
      return true;
    }
  }

  return false;
}

void tree_sitter_shared_external_tokens_external_scanner_destroy(void *payload) {
}
