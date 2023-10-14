#include "creditmodel.h"

void s21::ModelCredit::CreditCalculate(double total_credit_amount, int term,
                                       double interest_rate, int type,
                                       double* monthly_payment,
                                       double* overpayment_on_credit,
                                       double* total_payment,
                                       double* diff_monthly_payment_max,
                                       double* diff_monthly_payment_min) {
  interest_rate = interest_rate / 100;
  *monthly_payment = 0;
  *overpayment_on_credit = 0;
  *total_payment = 0;
  *diff_monthly_payment_max = 0;
  *diff_monthly_payment_min = 0;
  if (type == 1) {
    *monthly_payment =
        total_credit_amount *
        (((interest_rate) / (12) * pow(1 + (interest_rate) / (12), term)) /
         (pow(1 + (interest_rate) / (12), term) - 1));
    *overpayment_on_credit = *monthly_payment * term - total_credit_amount;
    *total_payment = total_credit_amount + *overpayment_on_credit;
  } else {
    double principal_dept = total_credit_amount / term;
    double total_interest = 0;
    double loan_balance = total_credit_amount;
    double min_payment_per_month =
        principal_dept + (loan_balance * interest_rate / 12.0);
    double max_payment_per_month =
        total_credit_amount / term + (loan_balance * interest_rate / 12.0);
    for (int i = 0; i < term; i++) {
      double interest = loan_balance * interest_rate / 12.0;
      double payment = principal_dept + interest;
      total_interest += interest;
      loan_balance -= principal_dept;
      if (payment < min_payment_per_month) {
        min_payment_per_month = payment;
      }
      if (payment > max_payment_per_month) {
        max_payment_per_month = payment;
      }
    }
    *diff_monthly_payment_min = min_payment_per_month;
    *diff_monthly_payment_max = max_payment_per_month;
    *overpayment_on_credit = total_interest;
    *total_payment = total_credit_amount + total_interest;
  }
}