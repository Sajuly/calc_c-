#include <gtest/gtest.h>

#include "parser.h"
#include "rpn_executor.h"
#include "token.h"

TEST(test1, tt_mul) {
  std::string str("2*4*5*(6)");
  double res = proverka(str);
  EXPECT_EQ(res, 240);
}

TEST(test2, tt_mul_sin) {
  std::string str("8*sin(6)");
  double res = proverka(str);
  EXPECT_NEAR(res, -2.23532398559, 6);
}

TEST(test3, tt_log) {
  std::string str("log(16)");
  double res = proverka(str);
  EXPECT_NEAR(res, 1.20411998266, 6);
}

TEST(test4, tt_pow) {
  std::string str("6^5-14*2");
  double res = proverka(str);
  EXPECT_EQ(res, 7748);
}

TEST(test5, tt_mod) {
  std::string str("6%4");
  double res = proverka(str);
  EXPECT_EQ(res, 2);
}

TEST(test6, tt_u_minus) {
  std::string str("-0");
  double res = proverka(str);
  EXPECT_EQ(res, 0);
}

TEST(test7, tt_nan) {
  std::string str("qwerty");
  double res = proverka(str);
  EXPECT_EQ(res, 1);  // err = 1
}

TEST(test8, tt_minus) {
  std::string str("3-(-3)");
  double res = proverka(str);
  EXPECT_EQ(res, 6);
}

TEST(test9, tt_U_plus) {
  std::string str("+10+10+5");
  double res = proverka(str);
  EXPECT_EQ(res, 25);
}

TEST(test10, tt_U_plus) {
  std::string str("15+75*1/3-42+3^3");
  double res = proverka(str);
  EXPECT_EQ(res, 25);
}

TEST(test11, tt_asin) {
  std::string str("asin(0.6)");
  double res = proverka(str);
  EXPECT_NEAR(res, 0.643501109, 6);
}

TEST(test12, tt_acos) {
  std::string str("acos(3*0.08)");
  double res = proverka(str);
  EXPECT_NEAR(res, 1.32843048, 6);
}

TEST(test13, tt_atan) {
  std::string str("atan(-0.4)");
  double res = proverka(str);
  EXPECT_NEAR(res, -0.3805064, 6);
}

TEST(test14, tt_tan) {
  std::string str("tan(-6)");
  double res = proverka(str);
  EXPECT_NEAR(res, 0.2910062, 6);
}

TEST(test15, tt_sqrt) {
  std::string str("sqrt(256.5)");
  double res = proverka(str);
  EXPECT_NEAR(res, 16.0156174, 6);
}

TEST(test16, tt_ln) {
  std::string str("ln(10)");
  double res = proverka(str);
  EXPECT_NEAR(res, 2.3025851, 6);
}

TEST(test17, tt_log) {
  std::string str("log(125)");
  double res = proverka(str);
  EXPECT_NEAR(res, 2.096910, 6);
}

TEST(test18, tt_bracket) {
  std::string str("()");
  double res = proverka(str);
  EXPECT_EQ(res, 0);
}

TEST(test19, tt_ln) {
  std::string str("2+2*2");
  double res = proverka(str);
  EXPECT_EQ(res, 6);
}

TEST(test20, tt_pl_mn) {
  std::string str("3-(+3)");
  double res = proverka(str);
  EXPECT_EQ(res, 0);
}

TEST(test21, tt_prior) {
  std::string str("1+2+3+4*5*6^7");
  double res = proverka(str);
  EXPECT_EQ(res, 5598726);
}

TEST(test22, tt_prior) {
  std::string str("123.456+2*3^4");
  double res = proverka(str);
  EXPECT_NEAR(res, 285.456, 6);
}

TEST(test23, tt_prior) {
  std::string str("(8+2*5)/(1+3*2-4)");
  double res = proverka(str);
  EXPECT_EQ(res, 6);
}

TEST(test24, tt_prior) {
  std::string str(
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))");
  double res = proverka(str);
  EXPECT_EQ(res, 10);
}

TEST(test25, tt_cos) {
  std::string str("cos(1*2)-1");
  double res = proverka(str);
  EXPECT_NEAR(res, -1.41614683655, 6);
}

TEST(test26, tt_cos_prior) {
  std::string str(
      "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1");
  double res = proverka(str);
  EXPECT_NEAR(res, -1.83907152908, 6);
}

TEST(test27, tt_mod) {
  std::string str("2.33%1");
  double res = proverka(str);
  EXPECT_NEAR(res, 0.33, 6);
}

TEST(test28, tt_sin_cos) {
  std::string str("sin(cos(5))");
  double res = proverka(str);
  EXPECT_NEAR(res, 0.27987335076, 6);
}

TEST(test29, tt_prior) {
  std::string str("3+4*2/(1-5)^2");
  double res = proverka(str);
  EXPECT_NEAR(res, 3.5, 6);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}