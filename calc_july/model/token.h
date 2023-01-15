#ifndef TOKEN_H
#define TOKEN_H

#include <string>

// TT = Token Type
#define TT_END 0
#define TT_DIGIT 1
#define TT_PLUS 2
#define TT_MINUS 3
#define TT_MUL 4
#define TT_DIV 5
#define TT_OPEN_BRACKET 6
#define TT_CLOSE_BRACKET 7
#define TT_SIN 8
#define TT_COS 9
#define TT_TAN 10
#define TT_ASIN 11
#define TT_SQRT 12
#define TT_LN 13
#define TT_X 14
#define TT_ACOS 15
#define TT_ATAN 16
#define TT_LOG 17
#define TT_POW 18
#define TT_MOD 19
#define TT_U_MINUS 20
#define TT_U_PLUS 21
#define TT_UNKNOWN 22

namespace s21 {
class Token {
 public:
  int token_type;
  double value;
  std::string str;

  Token() {
    token_type = TT_UNKNOWN;
    value = 0;
  }

  ~Token(){};

};  // class Token
}  // namespace s21

#endif  // TOKEN_H
