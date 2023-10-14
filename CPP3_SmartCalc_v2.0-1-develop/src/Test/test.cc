#include <gtest/gtest.h>

#include "../Controller/calculatorcontroller.h"
#include "../Controller/creditcontroller.h"
#include "../Controller/depositcontroller.h"

void test_validator(std::string s, double result) {
  s21::CalculatorController a;
  double res = 0;
  if (a.Validator(s)) {
    res = 1;
  }
  ASSERT_EQ(res, result);
}

void test_calculate(std::string s, double result) {
  s21::CalculatorController a;
  double res = 0;
  if (a.Validator(s)) {
    a.Input(s, 0);
    res = a.Calculate();
  }
  EXPECT_FLOAT_EQ(res, result);
}

TEST(Calculator, Calculate) {
  test_calculate("1 + 2", 3);
  test_calculate("1 + (-2)", -1);
  test_calculate("1 - 2", -1);
  test_calculate("2 * 2", 4);
  test_calculate("2 / 4", 0.5);
  test_calculate("4 / 2", 2);
  test_calculate("2 ^ 2", 4);
  test_calculate("3 ^ 3 ^ 3", 7.6255975e+12);
  test_calculate("4 mod 2", 0);
  test_calculate("5 mod 2", 1);
  test_calculate("2 + 3 * 2", 8);
  test_calculate("(2 + 3) * 2", 10);
  test_calculate("sin(1)", 0.84147096);
  test_calculate("cos(1)", 0.54030228);
  test_calculate("tan(1)", 1.5574077);
  test_calculate("asin(1)", 1.5707964);
  test_calculate("acos(0.5)", 1.0471976);
  test_calculate("atan(1)", 0.78539819);
  test_calculate("ln(2)", 0.69314718);
  test_calculate("log(2)", 0.30103001);
  test_calculate("acos(-0.5)+asin(-0.5)+atan(0.1)*cos(30)*sin(20)*tan(45)",
                 1.5935309);
  test_calculate("(4^acos(2/4)/tan(2*2)/5^acos(2/4)/tan(tan(tan(2*2))))",
                 -0.58934796);
  test_calculate("asin(1)*(asin(1)-(-cos(0))^2*(3))+13/3", 2.0883455);
  test_calculate("acos(0.5)*13/3", 4.5378561);
  test_calculate("atan(0.5)*(atan(0.5)-(-cos(0))^2*(3))+13/3", 3.1573596);
  test_calculate("ln(2)*(ln(2)-(-cos(0))^2*(3))+13/3", 2.7343447);
  test_calculate("log(2)*(log(2)-(-cos(0))^2*(3))+13/3", 3.5208623);
}

TEST(Calculator, Validator) {
  test_validator("1 + 2", 1);
  test_validator("1 + 2", 1);
  test_validator("10-20*(-10)", 1);
  test_validator("-(o(i(a(10.01)*n(2))/10m(2))^q(5)", 0);
  test_validator("mod+9(()))", 0);
  test_validator("md(+9(()))", 0);
  test_validator("-(o(i(a(10.01)*n(2))/10md+(2))^q(5)", 0);
  test_validator(")(s(x)", 0);
  test_validator(".+m)", 0);
  test_validator("*10", 0);
  test_validator("/10", 0);
  test_validator("mod10", 0);
  test_validator("^10", 0);
  test_validator("log(log(10))", 1);
  test_validator("sin(sin(-10))", 1);
  test_validator("cos(-cos(10))", 1);
  test_validator("-cos(cos(10))", 1);
  test_validator("-cos(-cos(10))", 1);
  test_validator("tan(--tan(10)+tan(10))", 0);
  test_validator("log(mod10)", 0);
  test_validator("sin(0.3)", 1);
  test_validator("cos(cos(10)))", 0);
  test_validator("cos(cos(10*))", 0);
  test_validator("cos(-cos(*10))", 0);
  test_validator("tan(--tan(10)+tan(10))", 0);
  test_validator("log(ln(50))", 1);
  test_validator("log(1mod10)", 1);
  test_validator("sin(-12*cos(32))", 1);
  test_validator("acos(-acos(10))", 1);
  test_validator("-acos(*acos(10))", 0);
  test_validator("ln(*ln(2))*5", 0);
  test_validator("ln(ln(2))", 1);
  test_validator("-log(1mod10)", 1);
  test_validator("-sin(-12*cos(32))", 1);
  test_validator("-acos(-acos(10))", 1);
  test_validator("acos(*acos(10))", 0);
  test_validator("-ln(*ln(2))*5", 0);
  test_validator("-ln(-ln(2))", 1);
  test_validator("ln(ln(x))", 1);
  test_validator("ln(*ln(x))*x", 0);
  test_validator("-acos(*acos(x))", 0);
  test_validator("acos(-acos(x))", 1);
  test_validator("sin(-x*cos(x))", 1);
  test_validator("log(50mod14)", 1);
  test_validator("1+1-1+ln(234)modln(log(12))", 1);
  test_validator("log(log(10))", 1);
  test_validator("(421+3.2)-32*cos(32)/3^4", 1);
  test_validator("cos(xmodx)", 1);
  test_validator("1modcos(3)", 1);
  test_validator("-cos(3)^4", 1);
  test_validator("1^0", 1);
}

TEST(CreditModel, Credit1) {
  s21::CreditController a;
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 1;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  a.CreditCalculate(total_credit_amount, term, interest_rate, type,
                    &monthly_payment, &overpayment_on_credit, &total_payment,
                    &diff_monthly_payment_max, &diff_monthly_payment_min);
  double real_result = 9036.34;
  EXPECT_FLOAT_EQ(monthly_payment, real_result);
}

TEST(CreditModel, Credit2) {
  s21::CreditController a;
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 1;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  a.CreditCalculate(total_credit_amount, term, interest_rate, type,
                    &monthly_payment, &overpayment_on_credit, &total_payment,
                    &diff_monthly_payment_max, &diff_monthly_payment_min);
  double real_result = 16872.145;
  EXPECT_FLOAT_EQ(overpayment_on_credit, real_result);
}

TEST(CreditModel, Credit3) {
  s21::CreditController a;
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 1;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  a.CreditCalculate(total_credit_amount, term, interest_rate, type,
                    &monthly_payment, &overpayment_on_credit, &total_payment,
                    &diff_monthly_payment_max, &diff_monthly_payment_min);
  double real_result = 216872.16;
  EXPECT_FLOAT_EQ(total_payment, real_result);
}

TEST(CreditModel, Credit4) {
  s21::CreditController a;
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 2;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  a.CreditCalculate(total_credit_amount, term, interest_rate, type,
                    &monthly_payment, &overpayment_on_credit, &total_payment,
                    &diff_monthly_payment_max, &diff_monthly_payment_min);
  double real_result = 9650.00;
  EXPECT_FLOAT_EQ(diff_monthly_payment_max, real_result);
}

TEST(CreditModel, Credit5) {
  s21::CreditController a;
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 2;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  a.CreditCalculate(total_credit_amount, term, interest_rate, type,
                    &monthly_payment, &overpayment_on_credit, &total_payment,
                    &diff_monthly_payment_max, &diff_monthly_payment_min);
  double real_result = 8388.194444;
  EXPECT_FLOAT_EQ(diff_monthly_payment_min, real_result);
}

TEST(CreditModel, Credit6) {
  s21::CreditController a;
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 2;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  a.CreditCalculate(total_credit_amount, term, interest_rate, type,
                    &monthly_payment, &overpayment_on_credit, &total_payment,
                    &diff_monthly_payment_max, &diff_monthly_payment_min);
  double real_result = 16458.333333;
  EXPECT_FLOAT_EQ(overpayment_on_credit, real_result);
}

TEST(CreditModel, Credit7) {
  s21::CreditController a;
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 2;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  a.CreditCalculate(total_credit_amount, term, interest_rate, type,
                    &monthly_payment, &overpayment_on_credit, &total_payment,
                    &diff_monthly_payment_max, &diff_monthly_payment_min);
  double real_result = 216458.333333;
  EXPECT_FLOAT_EQ(total_payment, real_result);
}

TEST(DepositModel, Deposit1) {
  s21::DepositController a;
  double deposit_amount = 10000;
  double deposit_term = 365;
  double interest_rate = 10;
  double tax_rate = 13;
  double period = 3;
  bool capitalization = false;
  s21::DepositData replenishments;
  s21::DepositData withdrawals;
  double accrued_interest = 0;
  double tax_amount = 0;
  double deposit_end = 0;
  double deposit_total = 0;
  a.DepositCalculate(deposit_amount, deposit_term, interest_rate, tax_rate,
                     period, capitalization, replenishments, withdrawals,
                     &accrued_interest, &tax_amount, &deposit_end,
                     &deposit_total);
  EXPECT_FLOAT_EQ(accrued_interest, 1000);
  EXPECT_FLOAT_EQ(tax_amount, 0);
  EXPECT_FLOAT_EQ(deposit_end, 1000);
  EXPECT_FLOAT_EQ(deposit_total, 10000);
}

TEST(DepositModel, Deposit2) {
  s21::DepositController a;
  double deposit_amount = 10000;
  double deposit_term = 365;
  double interest_rate = 10;
  double tax_rate = 13;
  double period = 3;
  bool capitalization = true;
  s21::DepositData replenishments;
  s21::DepositData withdrawals;
  double accrued_interest = 0;
  double tax_amount = 0;
  double deposit_end = 0;
  double deposit_total = 0;
  a.DepositCalculate(deposit_amount, deposit_term, interest_rate, tax_rate,
                     period, capitalization, replenishments, withdrawals,
                     &accrued_interest, &tax_amount, &deposit_end,
                     &deposit_total);
  EXPECT_FLOAT_EQ(accrued_interest, 1032.1321);
  EXPECT_FLOAT_EQ(tax_amount, 0);
  EXPECT_FLOAT_EQ(deposit_end, 1032.1321);
  EXPECT_FLOAT_EQ(deposit_total, 11032.1321);
}

TEST(DepositModel, Deposit3) {
  s21::DepositController a;
  double deposit_amount = 1000000;
  double deposit_term = 365;
  double interest_rate = 20;
  double tax_rate = 30;
  double period = 1;
  bool capitalization = true;
  s21::DepositData replenishments;
  s21::DepositData withdrawals;
  double accrued_interest = 0;
  double tax_amount = 0;
  double deposit_end = 0;
  double deposit_total = 0;
  a.DepositCalculate(deposit_amount, deposit_term, interest_rate, tax_rate,
                     period, capitalization, replenishments, withdrawals,
                     &accrued_interest, &tax_amount, &deposit_end,
                     &deposit_total);
  EXPECT_FLOAT_EQ(accrued_interest, 221335.86);
  EXPECT_FLOAT_EQ(tax_amount, 43900.758);
  EXPECT_FLOAT_EQ(deposit_end, 177435.09);
  EXPECT_FLOAT_EQ(deposit_total, 1221335.9);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}