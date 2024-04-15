#include <gtest/gtest.h>

#include <cmath>

#include "../backend/s21_smartcalc_controller.h"


using namespace s21;
TEST(SmartCalcTest, AdditionTests) {
  S21SmartCalc calculator1("2 + 3", 0);
  EXPECT_DOUBLE_EQ(calculator1.Evaluate(), 2 + 3);

  S21SmartCalc calculator2("+7+5+100000000000+142.4142412", 0);
  EXPECT_DOUBLE_EQ(calculator2.Evaluate(), +7 + 5 + 100000000000 + 142.4142412);

  S21SmartCalc calculator3("(2+3)+(5+7)", 0);
  EXPECT_DOUBLE_EQ(calculator3.Evaluate(), (2 + 3) + (5 + 7));

  S21SmartCalc calculator4("2 + 2", 0);
  EXPECT_DOUBLE_EQ(calculator4.Evaluate(), 2 + 2);
}

TEST(SmartCalcTest, SubtractionTest) {
  S21SmartCalc calculator1("2 - 3", 0);
  EXPECT_DOUBLE_EQ(calculator1.Evaluate(), 2 - 3);

  S21SmartCalc calculator2("-0-5-(100000000000-142.4142412)", 0);
  EXPECT_DOUBLE_EQ(calculator2.Evaluate(),
                   -0 - 5 - (100000000000 - 142.4142412));

  S21SmartCalc calculator3("(2-3)-(5-7)", 0);
  EXPECT_DOUBLE_EQ(calculator3.Evaluate(), (2 - 3) - (5 - 7));

  S21SmartCalc calculator4("5 - 3", 0);
  EXPECT_DOUBLE_EQ(calculator4.Evaluate(), 5 - 3);
}

TEST(SmartCalcTest, MultiplicationTest) {
  S21SmartCalc calculator1("2 * 3", 0);
  EXPECT_DOUBLE_EQ(calculator1.Evaluate(), 2 * 3);

  S21SmartCalc calculator2("-1*(5*(0.00004*142.4142412))", 0);
  EXPECT_DOUBLE_EQ(calculator2.Evaluate(), -1 * (5 * (0.00004 * 142.4142412)));

  S21SmartCalc calculator3("(2*3)*(5*7)", 0);
  EXPECT_DOUBLE_EQ(calculator3.Evaluate(), (2 * 3) * (5 * 7));

  S21SmartCalc calculator4("4 * 2", 0);
  EXPECT_DOUBLE_EQ(calculator4.Evaluate(), 4 * 2);
}

TEST(SmartCalcTest, DivisionTest) {
  S21SmartCalc calculator1("2 / 3", 0);
  EXPECT_DOUBLE_EQ(calculator1.Evaluate(), 2.0 / 3);

  S21SmartCalc calculator2("-1.0/5/0.5/142.4142412", 0);
  EXPECT_DOUBLE_EQ(calculator2.Evaluate(), -1.0 / 5 / 0.5 / 142.4142412);

  S21SmartCalc calculator3("(6/7) * (7/6)", 0);
  EXPECT_DOUBLE_EQ(calculator3.Evaluate(), (6.0 / 7) * (7.0 / 6));

  S21SmartCalc calculator4("8 / 4", 0);
  EXPECT_DOUBLE_EQ(calculator4.Evaluate(), 8 / 4);
}

TEST(SmartCalcTest, PowerTest) {
  S21SmartCalc calculator1("2 ^ 3", 0);
  EXPECT_DOUBLE_EQ(calculator1.Evaluate(), pow(2, 3));

  S21SmartCalc calculator2("7 ^ (-8)", 0);
  EXPECT_DOUBLE_EQ(calculator2.Evaluate(), pow(7, -8));

  S21SmartCalc calculator3("2^2^2^2", 0);
  EXPECT_DOUBLE_EQ(calculator3.Evaluate(), 65536);

  S21SmartCalc calculator4("2 ^ 3", 0);
  EXPECT_DOUBLE_EQ(calculator4.Evaluate(), 8);
}

TEST(SmartCalcTest, CosTest) {
  for (double i = -10; i < 10; i += 0.1) {
    S21SmartCalc calculator("cos(x)", i);
    EXPECT_NEAR(calculator.Evaluate(), cos(i), 1e-7);
  }
}

TEST(SmartCalcTest, SinTest) {
  for (double i = -10; i < 10; i += 0.1) {
    S21SmartCalc calculator("sin(x)", i);
    EXPECT_NEAR(calculator.Evaluate(), sin(i), 1e-7);
  }
}

TEST(SmartCalcTest, TanTest) {
  for (double i = -10; i < 10; i += 0.1) {
    S21SmartCalc calculator("tan(x)", i);
    EXPECT_NEAR(calculator.Evaluate(), tan(i), 1e-7);
  }
}

TEST(SmartCalcTest, AcosTest) {
  for (double i = -1; i < 1; i += 0.1) {
    S21SmartCalc calculator("acos(x)", i);
    EXPECT_NEAR(calculator.Evaluate(), acos(i), 1e-7);
  }
}

TEST(SmartCalcTest, AsinTest) {
  for (double i = -1; i < 1; i += 0.1) {
    S21SmartCalc calculator("asin(x)", i);
    EXPECT_NEAR(calculator.Evaluate(), asin(i), 1e-7);
  }
}

TEST(SmartCalcTest, AtanTest) {
  for (double i = -10; i < 10; i += 0.1) {
    S21SmartCalc calculator("atan(x)", i);
    EXPECT_NEAR(calculator.Evaluate(), atan(i), 1e-7);
  }
}

TEST(SmartCalcTest, SqrtTest) {
  for (double i = 0; i < 10; i += 0.1) {
    S21SmartCalc calculator("sqrt(x)", i);
    EXPECT_NEAR(calculator.Evaluate(), sqrt(i), 1e-7);
  }
}

TEST(SmartCalcTest, LnTest) {
  for (double i = 0.1; i < 10; i += 0.1) {
    S21SmartCalc calculator("-ln(x)", i);
    EXPECT_NEAR(calculator.Evaluate(), -log(i), 1e-7);
  }
}

TEST(SmartCalcTest, LogTest) {
  for (double i = 0.1; i < 10; i += 0.1) {
    S21SmartCalc calculator("log(x)", i);
    EXPECT_NEAR(calculator.Evaluate(), log10(i), 1e-7);
  }
}

TEST(SmartCalcTest, ModTest) {
  for (int i = -10; i < 10 && i != 0; i++) {
    S21SmartCalc calculator("10 mod x", i);
    EXPECT_NEAR(calculator.Evaluate(), 10 % i, 1e-7);
  }
}

TEST(SmartCalcTest, ComplexTest1) {
  for (double i = 0; i < 10; i += 0.1) {
    S21SmartCalc calculator("(sin(x))^2 + (cos(x))^2", i);
    EXPECT_NEAR(calculator.Evaluate(), pow(sin(i), 2) + pow(cos(i), 2), 1e-7);
  }

  for (double i = 0; i < 10; i += 0.1) {
    S21SmartCalc calculator("sin(x) + (sqrt(4^2))^3 - 3^x", i);
    EXPECT_NEAR(calculator.Evaluate(), sin(i) + pow(sqrt(16), 3) - pow(3, i),
                1e-7);
  }
}

TEST(SmartCalcTest, ComplexTest2) {
  for (double i = 0.1; i < 10; i += 0.1) {
    S21SmartCalc calculator("((2 + tan(x)) * ln(x) / sqrt(x)) ^ 2", i);
    EXPECT_NEAR(calculator.Evaluate(),
                pow((((2 + tan(i)) * log(i)) / sqrt(i)), 2), 1e-7);
  }

  for (double i = 0; i < 10; i += 0.1) {
    S21SmartCalc calculator("(2^2^2^2 - sqrt(5)/asin(0.5) - x)^(-1*log(2))", i);
    EXPECT_NEAR(calculator.Evaluate(),
                pow((65536 - sqrt(5) / asin(0.5) - i), (-1 * log10(2))), 1e-7);
  }
}

TEST(SmartCalcTest, ComplexTest3) {
  S21SmartCalc calculator1(
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2",
      0);
  EXPECT_DOUBLE_EQ(calculator1.Evaluate(), 2192);

  S21SmartCalc calculator2("ln(2*(2^(atan(sqrt(10/(acos(0.0000001)))))))", 0);
  EXPECT_DOUBLE_EQ(calculator2.Evaluate(), 1.5203874212153758);

  S21SmartCalc calculator3("tan(1.5 * ln(3) - cos(0.7 + sqrt(25 / asin(0.5))))",
                           0);
  EXPECT_DOUBLE_EQ(calculator3.Evaluate(), 6.0218701361445346);

  S21SmartCalc calculator4(
      "1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 "
      "/ (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / "
      "(1 / (1 / (1 / (1 / 2))))))))))))))))))))))))))))))))",
      0);
  EXPECT_DOUBLE_EQ(calculator4.Evaluate(), 0.5);

  S21SmartCalc calculator5("sqrt(2^(cos(1.2) - sin(0.8)) * tan(3.6 / sqrt(9)))",
                           0);
  EXPECT_DOUBLE_EQ(calculator5.Evaluate(), 1.4181289045281718);
}

TEST(SmartCalcTest, ComplexTest4) {
  S21SmartCalc calculator1("acos(0.7 / atan(0.3)) + asin(sin(0.4) * cos(0.5))",
                           0);
  EXPECT_TRUE(std::isnan(calculator1.Evaluate()));

  S21SmartCalc calculator2("cos(2.5 + sin(1.2 * tan(0.8 / sqrt(9))))", 0);
  EXPECT_DOUBLE_EQ(calculator2.Evaluate(), -0.94935339061349433);

  S21SmartCalc calculator3(
      "log(10000) - cos(sin(tan(0.4 + 3.2^2)) * asin(0.5))", 0);
  EXPECT_DOUBLE_EQ(calculator3.Evaluate(), 3.0256924506975276);

  S21SmartCalc calculator4(
      "1 / (1 + 1 / (2 + 1 / (3 + 1 / (4 + 1 / (5 + 1 / (6 + 1 / (7 + 1 / (8 + "
      "1 / (9 + 1 / (10 + 1 / (11 + 1 / (12 + 1 / (13 + 1 / (14 + 1 / (15 + 1 "
      "/ (16 + 1 / (17 + 1 / (18 + 1 / (19 + 1 / (20 + 1 / (21 + 1 / (22 + 1 / "
      "(23 + 1 / (24 + 1 / (25 + 1 / (26 + 1 / (27 + 1 / (28 + 1 / (29 + 1 / "
      "(30 + 1 / (31 + 1 / (32 + 1 / 33))))))))))))))))))))))))))))))))",
      0);
  EXPECT_DOUBLE_EQ(calculator4.Evaluate(), 0.69777465796400795);

  S21SmartCalc calculator5(
      "cos(2.5 + sin(1.2 * tan(0.8 / sqrt(9))) * 3^(ln(2)))", 0);
  EXPECT_DOUBLE_EQ(calculator5.Evaluate(), -0.99885315255329443);
}

TEST(SmartCalcTest, ComplexTest5) {
  S21SmartCalc calculator1("sin(cos(tan(acos(asin(atan(atan(acos(1))))))))", 0);
  EXPECT_DOUBLE_EQ(calculator1.Evaluate(), -0.28061055348533886);

  S21SmartCalc calculator2(
      "(sin(1) + cos(1)) * (tan(1) / (acos(1) - asin(1))) + (atan(1)^2)", 0);
  EXPECT_DOUBLE_EQ(calculator2.Evaluate(), -0.75314554164716108);

  S21SmartCalc calculator3(
      "sqrt((sin(1) + cos(1)) * (tan(1) / (acos(1) - asin(1))) + (atan(1)^2))",
      0);
  EXPECT_TRUE(std::isnan(calculator3.Evaluate()));

  S21SmartCalc calculator4("ln(2^(sin(3.14) + cos(1.57)) - sqrt(4))", 0);
  EXPECT_TRUE(std::isnan(calculator4.Evaluate()));

  S21SmartCalc calculator5(
      "log(2^(sin(1.5) + cos(2.5)) / (tan(0.7) + ln(1.2)))", 0);
  EXPECT_DOUBLE_EQ(calculator5.Evaluate(), 0.048549088779287458);
}

TEST(SmartCalcTest, ComplexTest6) {
  S21SmartCalc calculator1("1.0 / 1000000000000000000000000000000000.0", 0);
  EXPECT_DOUBLE_EQ(calculator1.Evaluate(), 1.0000000000000001e-33);

  S21SmartCalc calculator2(
      "acos(-0.5)+asin(-0.5)+atan(0.1)*cos(30)*sin(20)*tan(45)", 0);
  EXPECT_DOUBLE_EQ(calculator2.Evaluate(), 1.5935309268233344);

  S21SmartCalc calculator3("log(sin(1 / 2999999))", 0);
  EXPECT_NEAR(calculator3.Evaluate(), -6.47712, 0.00001);
  S21SmartCalc calculator4("cos(2^(tan(3.14) - sin(1.57)) * sqrt(16))", 0);
  EXPECT_DOUBLE_EQ(calculator4.Evaluate(), -0.41413970498991637);

  S21SmartCalc calculator5(
      "2 + (3 - (4 * (5 / (6 + (7 - (8 * (9 / (10 ^ 2))))))))", 0);
  EXPECT_DOUBLE_EQ(calculator5.Evaluate(), 3.3713355048859937);
}

TEST(SmartCalcTest, ComplexTest7) {
  S21SmartCalc calculator1("asin(2^(sin(3.14) + cos(1.57)) / sqrt(4))", 0);
  EXPECT_DOUBLE_EQ(calculator1.Evaluate(), 0.52455587485994881);

  S21SmartCalc calculator2("atan(2^(tan(3.14) - sin(1.57)) + sqrt(16))", 0);
  EXPECT_DOUBLE_EQ(calculator2.Evaluate(), 1.3521014222272312);

  S21SmartCalc calculator3("acos(2.5 * (cos(1) - sin(0.5)) / (tan(1) + 1))", 0);
  EXPECT_DOUBLE_EQ(calculator3.Evaluate(), 1.5112509165719772);

  S21SmartCalc calculator4(
      "sin(cos(tan(1.5^2 - sqrt(16) / ln(10))) * acos(0.7))", 0);
  EXPECT_DOUBLE_EQ(calculator4.Evaluate(), 0.62302621558935645);

  S21SmartCalc calculator5(
      "1 + (2 - (3 * (4 / (5 + (6 - (7 * (8 / (9 ^ (10 + (11 - (12 * (13 / (14 "
      "+ (15 - (16 * (17 / (18 ^ 19)))))))))))))))))",
      0);
  EXPECT_DOUBLE_EQ(calculator5.Evaluate(), 1.9090909090909023);
}

TEST(SmartCalcTest, ComplexTest8) {
  S21SmartCalc calculator1(
      "1 + (2 - (3 * (4 / (5 + (6 - (7 * (8 / (9 ^ (10 + (11 - (12 * (13 / (14 "
      "+ (15 - (16 * (17 / (18 ^ (19 + (20 - (21 * (22 / (23 ^ "
      "24))))))))))))))))))))))",
      0);
  EXPECT_DOUBLE_EQ(calculator1.Evaluate(), 1.9090909090909023);

  S21SmartCalc calculator2(
      "2 ^ (3 ^ (4 ^ (5 ^ (6 ^ (7 ^ (8 ^ (9 ^ (10 ^ (11 ^ (12 ^ 13))))))))))",
      0);
  EXPECT_TRUE(std::isinf(calculator2.Evaluate()));

  S21SmartCalc calculator3(
      "sin(2) + (cos(3) - (tan(4) * (acos(5) + (asin(6) - (atan(7) * (cos(8) + "
      "(sin(9) ^ (tan(10) + (acos(11) - (asin(12) * (atan(13) / (cos(14) + "
      "(sin(15) - (tan(16) * (acos(17) / (sin(18) ^ (cos(19) + (tan(20) - "
      "(asin(21) * (atan(22) / (cos(23) + (sin(24) - (tan(25) * (acos(26) / "
      "(sin(27) ^ (cos(28) + (tan(29) - (asin(30) * (atan(31) / (cos(32) + "
      "(sin(33) - (tan(34) * (acos(35) / (sin(36) ^ (cos(37) + (tan(38) - "
      "(asin(39) * (atan(40) / (cos(41) + (sin(42) - (tan(43) * (acos(44) / "
      "(sin(45) ^ (cos(46) + (tan(47) - (asin(48) * (atan(49) / (cos(50) + "
      "(sin(51) - (tan(52) * (acos(53) / (sin(54) ^ (cos(55) + (tan(56) - "
      "(asin(57) * (atan(58) / (cos(59) + (sin(60) - (tan(61) * (acos(62) / "
      "(sin(63) ^ (cos(64) + (tan(65) - (asin(66) * (atan(67) / (cos(68) + "
      "(sin(69) - (tan(70) * (acos(71) / (sin(72) ^ (cos(73) + (tan(74) - "
      "(asin(75) * (atan(76) / (cos(77) + (sin(78) - (tan(79) * (acos(80) / "
      "(sin(81) ^ (cos(82) + (tan(83) - (asin(84) * (atan(85) / (cos(86) + "
      "(sin(87) - (tan(88) * (acos(89) / (sin(90) ^ (cos(91) + (tan(92) - "
      "(asin(93) * (atan(94) / (cos(95) + (sin(96) - (tan(97) * (acos(98) / "
      "(sin(99) ^ "
      "(cos(100))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))"
      ")))))))))))))))))))))))))))))))))))",
      0);
  EXPECT_TRUE(std::isnan(calculator3.Evaluate()));

  S21SmartCalc calculator4("x^x^x^x", 2);
  EXPECT_DOUBLE_EQ(calculator4.Evaluate(), 65536);

  S21SmartCalc calculator5("-5", 0);
  EXPECT_DOUBLE_EQ(calculator5.Evaluate(), -5);
}

TEST(SmartCalcTest, ComplexTest9) {
  S21SmartCalc calculator1("-x", 5);
  EXPECT_DOUBLE_EQ(calculator1.Evaluate(), -5);

  S21SmartCalc calculator2("-7 + 7 + 100", 0);
  EXPECT_DOUBLE_EQ(calculator2.Evaluate(), 100);

  S21SmartCalc calculator3("7 + (-7) + 100", 0);
  EXPECT_DOUBLE_EQ(calculator3.Evaluate(), 100);
}

// TEST(SmartCalcTest, ErrorTest9) {
//   S21SmartCalc calculator1("(11", 11);
//   EXPECT_DOUBLE_EQ(calculator1.Evaluate(), 11);
// }


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
