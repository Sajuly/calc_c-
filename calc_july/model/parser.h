#include <list>
#include <string>

#include "token.h"

#ifndef PARSER_H
#define PARSER_H

#define MAX_LEXEMA_LENGTH 255

s21::Token get_token(std::string token_string, s21::Token prev);

std::list<s21::Token> parse_source(std::string source);

bool check_parse_errors(std::list<s21::Token> parsed_list);

#endif  // PARSER_H
