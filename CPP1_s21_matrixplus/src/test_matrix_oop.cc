#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

extern const char* err_msgs[];

void init_matrix(S21Matrix* matrix, double num) {
  for (int i = 0; i < matrix->getRows(); i++) {
    for (int j = 0; j < matrix->getCols(); j++) {
      matrix->getMatrix()[i][j] = num;
    }
  }
}

TEST(EqMatrix1, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  ASSERT_TRUE(matrix_a.EqMatrix(matrix_b));
}
TEST(EqMatrix2, True) {
  S21Matrix matrix_a(13, 3);
  S21Matrix matrix_b(13, 3);
  ASSERT_TRUE(matrix_a == matrix_b);
}
TEST(EqMatrix3, True) {
  S21Matrix matrix_a(3, 3);
  init_matrix(&matrix_a, 7);
  S21Matrix matrix_b(3, 3);
  init_matrix(&matrix_b, 7);
  ASSERT_TRUE(matrix_a.EqMatrix(matrix_b));
}
TEST(EqMatrix4, True) {
  S21Matrix matrix_a(3, 3);
  init_matrix(&matrix_a, 7.007);
  S21Matrix matrix_b(3, 3);
  init_matrix(&matrix_b, 7.007);
  ASSERT_TRUE(matrix_a == matrix_b);
}
TEST(EqMatrix1, False) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(2, 2);
  ASSERT_FALSE(matrix_a == matrix_b);
}
TEST(EqMatrix2, False) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 2);
  ASSERT_FALSE(matrix_a.EqMatrix(matrix_b));
}
TEST(EqMatrix3, False) {
  S21Matrix matrix_a(3, 3);
  init_matrix(&matrix_a, 7.007);
  S21Matrix matrix_b(3, 3);
  init_matrix(&matrix_b, 7.006);
  ASSERT_FALSE(matrix_a == matrix_b);
}
TEST(EqMatrix4, False) {
  S21Matrix matrix_a(8, 8);
  init_matrix(&matrix_a, 1.00007);
  S21Matrix matrix_b(8, 8);
  init_matrix(&matrix_b, 1.00006);
  ASSERT_FALSE(matrix_a.EqMatrix(matrix_b));
}
TEST(SumMatrix1, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 1.00001;
  matrix_a(1, 0) = -9000;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -1;
  matrix_b(0, 1) = -1.00001;
  matrix_b(1, 0) = 9000;
  matrix_b(1, 1) = 0;
  result(0, 0) = 0;
  result(0, 1) = 0;
  result(1, 0) = 0;
  result(1, 1) = 0;
  matrix_a.SumMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}
TEST(SumMatrix2, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  S21Matrix result(3, 3);
  matrix_a(0, 0) = 12;
  matrix_a(0, 1) = -75.5;
  matrix_a(0, 2) = 199;
  matrix_a(1, 0) = 2.22222;
  matrix_a(1, 1) = 0;
  matrix_a(1, 2) = -444444;
  matrix_a(2, 0) = 1;
  matrix_a(2, 1) = 2;
  matrix_a(2, 2) = 3;
  matrix_b(0, 0) = -12;
  matrix_b(0, 1) = 75.5;
  matrix_b(0, 2) = -199;
  matrix_b(1, 0) = 2.22222;
  matrix_b(1, 1) = 3000;
  matrix_b(1, 2) = -444444;
  matrix_b(2, 0) = 2.22222;
  matrix_b(2, 1) = -34.42435;
  matrix_b(2, 2) = 444444;
  result(0, 0) = 0;
  result(0, 1) = 0;
  result(0, 2) = 0;
  result(1, 0) = 4.44444;
  result(1, 1) = 3000;
  result(1, 2) = -888888;
  result(2, 0) = 3.22222;
  result(2, 1) = -32.42435;
  result(2, 2) = 444447;
  ASSERT_TRUE((matrix_a + matrix_b) == result);
}
TEST(SumMatrix1, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 1.2345678;
  matrix_a(0, 1) = 0;
  matrix_b(0, 0) = 32552;
  matrix_b(0, 1) = -532532;
  matrix_b(1, 0) = 4124.543523;
  matrix_b(1, 1) = -2;

  EXPECT_THROW(matrix_a.SumMatrix(matrix_b), std::out_of_range);
}
TEST(SumMatrix2, False) {
  S21Matrix matrix_a(2, 3);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 1.2345678;
  matrix_a(0, 1) = 0;
  matrix_a(0, 2) = 11110;
  matrix_b(0, 0) = 32552;
  matrix_b(0, 1) = -532532;
  matrix_b(1, 0) = 4124.543523;
  matrix_b(1, 1) = -2;
  EXPECT_THROW(matrix_a + matrix_b, std::out_of_range);
}
TEST(SubMatrix1, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  init_matrix(&matrix_a, 7);
  init_matrix(&matrix_b, -7);
  init_matrix(&result, 14);
  matrix_a.SubMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}
TEST(SubMatrix2, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  init_matrix(&matrix_a, 7);
  init_matrix(&matrix_b, -7);
  init_matrix(&result, 14);
  ASSERT_TRUE((matrix_a - matrix_b) == result);
}
TEST(SubMatrix1, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);
  EXPECT_THROW(matrix_a.SubMatrix(matrix_b), std::out_of_range);
}
TEST(SubMatrix2, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);
  EXPECT_THROW((matrix_a - matrix_b), std::out_of_range);
}
TEST(MulNumber1, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  init_matrix(&matrix_a, 8);
  init_matrix(&result, 80);
  matrix_a.MulNumber(10);
  ASSERT_TRUE(matrix_a == result);
}
TEST(MulNumber2, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  init_matrix(&matrix_a, 8);
  init_matrix(&result, 80);
  ASSERT_TRUE((matrix_a * 10) == result);
}
TEST(MulNumber3, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  init_matrix(&matrix_a, 8);
  init_matrix(&result, -4);
  ASSERT_TRUE((matrix_a * -0.5) == result);
}
TEST(MulNumber4, True) {
  S21Matrix matrix_a(4, 5);
  S21Matrix result(4, 5);
  init_matrix(&matrix_a, 8);
  init_matrix(&result, 80);
  ASSERT_TRUE((10 * matrix_a) == result);
}
TEST(MulNumber5, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  init_matrix(&matrix_a, 8);
  init_matrix(&result, -4);
  ASSERT_TRUE((-0.5 * matrix_a) == result);
}
TEST(MulMatrix1, True) {
  S21Matrix matrix_a(2, 4);
  S21Matrix matrix_b(4, 2);
  S21Matrix result(2, 2);
  init_matrix(&matrix_a, 0.00005);
  init_matrix(&matrix_b, -123);
  result(0, 0) = -0.0246;
  result(0, 1) = -0.0246;
  result(1, 0) = -0.0246;
  result(1, 1) = -0.0246;
  matrix_a.MulMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}
TEST(MulMatrix2, True) {
  S21Matrix matrix_a(2, 4);
  S21Matrix matrix_b(4, 2);
  S21Matrix result(2, 2);
  init_matrix(&matrix_a, 0.00005);
  init_matrix(&matrix_b, -123);
  result(0, 0) = -0.0246;
  result(0, 1) = -0.0246;
  result(1, 0) = -0.0246;
  result(1, 1) = -0.0246;
  ASSERT_TRUE((matrix_a * matrix_b) == result);
}
TEST(MulMatrix1, False) {
  S21Matrix matrix_a(2, 4);
  S21Matrix matrix_b(2, 4);
  EXPECT_THROW(matrix_a.MulMatrix(matrix_b), std::out_of_range);
}
TEST(MulMatrix2, False) {
  S21Matrix matrix_a(2, 4);
  S21Matrix matrix_b(2, 4);
  EXPECT_THROW((matrix_a * matrix_b), std::out_of_range);
}
TEST(OperatorParentheses, True) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  ASSERT_EQ(matrix_a(0, 1), 2);
}
TEST(OperatorParentheses1, False) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  ASSERT_NE(matrix_a(0, 1), 10);
}
TEST(OperatorParentheses2, False) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  EXPECT_THROW(matrix_a(3, 3), std::out_of_range);
}
TEST(ConstOperatorParentheses, True) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  const S21Matrix const_matrix_a = matrix_a;
  ASSERT_EQ(const_matrix_a(0, 1), 2);
}
TEST(ConstOperatorParentheses1, False) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  const S21Matrix const_matrix_a = matrix_a;
  ASSERT_NE(const_matrix_a(0, 1), 10);
}
TEST(ConstOperatorParentheses2, False) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  const S21Matrix const_matrix_a = matrix_a;
  EXPECT_THROW(const_matrix_a(3, 3), std::out_of_range);
}
TEST(OperatorPlus, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;
  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;
  ASSERT_TRUE((matrix_a + matrix_b) == result);
}
TEST(OperatorMinus, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;

  ASSERT_TRUE((matrix_a - matrix_b) == result);
}
TEST(OperatorMultiplyMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;
  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;
  ASSERT_TRUE((matrix_a * matrix_b) == result);
}
TEST(OperatorMultiplyNumber, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;
  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  ASSERT_TRUE((matrix_a * 10) == result);
}
TEST(OperatorMultiplyNum, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;
  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;
  ASSERT_TRUE((10 * matrix_a) == result);
}
TEST(OperatorEqMatrix, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(1, 3);
  matrix_a = matrix_b;
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(OperatorSumMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;
  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;

  ASSERT_TRUE((matrix_a += matrix_b) == result);
}
TEST(OperatorSumMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW((matrix_a += matrix_b), std::out_of_range);
}

TEST(OperatorSubMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;
  ASSERT_TRUE((matrix_a -= matrix_b) == result);
}
TEST(OperatorSubMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  EXPECT_THROW(matrix_a -= matrix_b, std::out_of_range);
}
TEST(OperatorMulNumber, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;
  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;
  ASSERT_TRUE((matrix_a *= 10) == result);
}
TEST(OperatorMulMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;
  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  ASSERT_TRUE((matrix_a *= matrix_b) == result);
}
TEST(OperatorMulMatrix, False) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;
  EXPECT_THROW(matrix_a *= matrix_b, std::out_of_range);
}
TEST(Transpose, True) {
  S21Matrix matrix_a(4, 3);
  S21Matrix result(3, 4);
  matrix_a(0, 0) = 7;
  matrix_a(0, 1) = -98;
  matrix_a(0, 2) = 0.5;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 5.4;
  matrix_a(1, 2) = 32;
  matrix_a(2, 0) = 3.12;
  matrix_a(2, 1) = 2323;
  matrix_a(2, 2) = 23;
  matrix_a(3, 0) = -78;
  matrix_a(3, 1) = 476.4;
  matrix_a(3, 2) = 21;
  result(0, 0) = 7;
  result(0, 1) = 0;
  result(0, 2) = 3.12;
  result(0, 3) = -78;
  result(1, 0) = -98;
  result(1, 1) = 5.4;
  result(1, 2) = 2323;
  result(1, 3) = 476.4;
  result(2, 0) = 0.5;
  result(2, 1) = 32;
  result(2, 2) = 23;
  result(2, 3) = 21;
  S21Matrix res = matrix_a.Transpose();
  ASSERT_TRUE(res == result);
}
TEST(Determinant, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 4.444;
  matrix_a(0, 2) = -51;
  matrix_a(1, 0) = 9;
  matrix_a(1, 1) = 0;
  matrix_a(1, 2) = 9;
  matrix_a(2, 0) = 0;
  matrix_a(2, 1) = -11;
  matrix_a(2, 2) = 532.532;
  double expected_det = -16151.149872;
  double epsilon = 1e-7;
  ASSERT_NEAR(matrix_a.Determinant(), expected_det, epsilon);
}
TEST(Determinant, False) {
  S21Matrix matrix_a(3, 2);
  EXPECT_THROW(matrix_a.Determinant(), std::out_of_range);
}
TEST(CalcComplements, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 4.444;
  matrix_a(0, 2) = -51;
  matrix_a(1, 0) = 9;
  matrix_a(1, 1) = 0;
  matrix_a(1, 2) = 9;
  matrix_a(2, 0) = 0;
  matrix_a(2, 1) = -11;
  matrix_a(2, 2) = 532.532;
  S21Matrix matrix_b(3, 3);
  matrix_b = matrix_a.CalcComplements();
  S21Matrix result(3, 3);
  result(0, 0) = 99;
  result(0, 1) = -4792.788;
  result(0, 2) = -99;
  result(1, 0) = -1805.572208;
  result(1, 1) = 532.532;
  result(1, 2) = 11;
  result(2, 0) = 39.996;
  result(2, 1) = -468;
  result(2, 2) = -39.996;
  double epsilon = 1e-7;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_NEAR(matrix_b.getMatrix()[i][j], result.getMatrix()[i][j],
                  epsilon);
    }
  }
}
TEST(CalcComplements, False) {
  S21Matrix matrix_a(3, 2);
  EXPECT_THROW(matrix_a.CalcComplements(), std::out_of_range);
}
TEST(Inverse, False) {
  S21Matrix matrix_a(4, 3);
  S21Matrix result(3, 4);
  matrix_a(0, 0) = 7;
  matrix_a(0, 1) = -98;
  matrix_a(0, 2) = 0.5;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 5.4;
  matrix_a(1, 2) = 32;
  matrix_a(2, 0) = 3.12;
  matrix_a(2, 1) = 2323;
  matrix_a(2, 2) = 23;
  matrix_a(3, 0) = -78;
  matrix_a(3, 1) = 476.4;
  matrix_a(3, 2) = 21;
  EXPECT_THROW(matrix_a.InverseMatrix(), std::out_of_range);
}
TEST(Inverse, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 3);
  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;
  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;
  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;
  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;
  ASSERT_TRUE(matrix_a.InverseMatrix().EqMatrix(result));
  S21Matrix matrix_b(3, 3);
  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(0, 2) = 3;
  matrix_b(1, 0) = 4;
  matrix_b(1, 1) = 5;
  matrix_b(1, 2) = 6;
  matrix_b(2, 0) = 7;
  matrix_b(2, 1) = 8;
  matrix_b(2, 2) = 9;
  EXPECT_THROW(matrix_b.InverseMatrix(), std::out_of_range);
}
TEST(Get, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;
  ASSERT_EQ(matrix_a.getRows(), 3);
  ASSERT_EQ(matrix_a.getCols(), 3);
}
TEST(Set, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 2);
  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;
  result(0, 0) = 2;
  result(0, 1) = 5;
  result(1, 0) = 6;
  result(1, 1) = 3;
  result(2, 0) = 5;
  result(2, 1) = -2;
  matrix_a.setCols(2);
  ASSERT_TRUE(matrix_a == result);
  S21Matrix matrix_b(3, 3);
  S21Matrix result_b(2, 3);
  matrix_b(0, 0) = 2;
  matrix_b(0, 1) = 5;
  matrix_b(0, 2) = 7;
  matrix_b(1, 0) = 6;
  matrix_b(1, 1) = 3;
  matrix_b(1, 2) = 4;
  matrix_b(2, 0) = 5;
  matrix_b(2, 1) = -2;
  matrix_b(2, 2) = -3;
  result_b(0, 0) = 2;
  result_b(0, 1) = 5;
  result_b(0, 2) = 7;
  result_b(1, 0) = 6;
  result_b(1, 1) = 3;
  result_b(1, 2) = 4;
  matrix_b.setRows(2);
  ASSERT_TRUE(matrix_b == result_b);
}
TEST(setCols, False) {
  S21Matrix matrix_a(3, 3);
  init_matrix(&matrix_a, 5);
  EXPECT_THROW(matrix_a.setCols(-2), std::invalid_argument);
}
TEST(setRows, False) {
  S21Matrix matrix_a(3, 3);
  init_matrix(&matrix_a, 5);
  EXPECT_THROW(matrix_a.setRows(-2), std::invalid_argument);
}
TEST(Create1, False) {
  EXPECT_THROW(
      {
        try {
          S21Matrix matrix_a(-3, 3);
        } catch (const std::out_of_range& e) {
          throw;
        }
      },
      std::out_of_range);
}
TEST(Create2, False) {
  EXPECT_THROW(
      {
        try {
          S21Matrix matrix_a(3, 0);
        } catch (const std::out_of_range& e) {
          throw;
        }
      },
      std::out_of_range);
}
TEST(Copy, True) {
  S21Matrix matrix_a(3, 3);
  init_matrix(&matrix_a, -6);
  S21Matrix matrix_b(matrix_a);
  ASSERT_TRUE(matrix_b == matrix_b);
}
TEST(Move, True) {
  S21Matrix matrix_a(3, 3);
  init_matrix(&matrix_a, 1);
  S21Matrix matrix_b(matrix_a);
  S21Matrix matrix_c = std::move(matrix_a);
  ASSERT_TRUE(matrix_b == matrix_c);
  ASSERT_EQ(matrix_a.getRows(), 0);
  ASSERT_EQ(matrix_a.getCols(), 0);
  ASSERT_EQ(matrix_a.getMatrix(), nullptr);
}
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
