#include "parser.h"

#include <iostream>
#include <list>
#include <stack>
#include <string>

#include "token.h"

s21::Token get_token(std::string token_string, s21::Token prev) {
  s21::Token result_token;

  if (token_string.size() == 1) {
    switch (token_string[0]) {
      case '(':
        result_token.token_type = TT_OPEN_BRACKET;
        break;
      case ')':
        result_token.token_type = TT_CLOSE_BRACKET;
        break;
      case '+':
        result_token.token_type = TT_PLUS;
        if (prev.token_type == TT_OPEN_BRACKET) {
          result_token.token_type = TT_U_PLUS;
        }
        break;
      case '-':
        result_token.token_type = TT_MINUS;
        if (prev.token_type == TT_OPEN_BRACKET) {
          result_token.token_type = TT_U_MINUS;
        }
        break;
      case '*':
        result_token.token_type = TT_MUL;
        break;
      case '/':
        result_token.token_type = TT_DIV;
        break;
      case 'x':
        result_token.token_type = TT_X;
        break;
      case '^':
        result_token.token_type = TT_POW;
        break;
      case '%':
        result_token.token_type = TT_MOD;
        break;
      default:
        break;
    }
  } else {
    if (token_string == "sin") {
      result_token.token_type = TT_SIN;
    } else if (token_string == "cos") {
      result_token.token_type = TT_COS;
    } else if (token_string == "tan") {
      result_token.token_type = TT_TAN;
    } else if (token_string == "asin") {
      result_token.token_type = TT_ASIN;
    } else if (token_string == "sqrt") {
      result_token.token_type = TT_SQRT;
    } else if (token_string == "ln") {
      result_token.token_type = TT_LN;
    } else if (token_string == "acos") {
      result_token.token_type = TT_ACOS;
    } else if (token_string == "atan") {
      result_token.token_type = TT_ATAN;
    } else if (token_string == "log") {
      result_token.token_type = TT_LOG;
    }
  }

  if (result_token.token_type == TT_UNKNOWN) {
    size_t endptr;
    try {
      setlocale(LC_NUMERIC, "C");  // влияетна символ десятичной точки
      double dig = std::stod(token_string, &endptr);  // строку в дубль

      if (endptr == token_string.size()) {
        result_token.token_type = TT_DIGIT;
        result_token.value = dig;
      } else {
        result_token.token_type = TT_UNKNOWN;
      }
    } catch (...) {
      result_token.token_type = TT_UNKNOWN;
    }
  }

  result_token.str = token_string;  // for debug

  return result_token;
}

std::list<s21::Token> parse_source(std::string source) {
  std::list<s21::Token> result;

  std::string lexema;  // текущая лексема
  std::string val;
  s21::Token prev;

  for (auto i : source) {
    switch (i) {
      case '(':
      case ')':
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
      case '%':
        if (lexema.size() != 0) {
          prev = get_token(lexema, prev);
          result.push_back(prev);
        }
        lexema = "";

        val = i;
        prev = get_token(val, prev);
        result.push_back(prev);
        break;
      case ' ':  // пропустим пробелы
        break;
      default:
        lexema.push_back(i);
    }
  }

  if (lexema.size() != 0) {
    result.push_back(get_token(lexema, prev));
  }

  return result;
}

bool check_parse_errors(std::list<s21::Token> parsed_list) {
  bool code = 0;
  for (s21::Token tt : parsed_list) {
    if (tt.token_type == TT_UNKNOWN) {
      std::cout << "Unknown lexema: " << tt.str << std::endl;
      code = 1;
    }
  }
  return code;
}
