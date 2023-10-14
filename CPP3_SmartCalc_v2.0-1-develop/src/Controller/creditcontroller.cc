#include "creditcontroller.h"

void s21::CreditController::CreditCalculate(double total_credit_amount,
                                            int term, double interest_rate,
                                            int type, double* monthly_payment,
                                            double* overpayment_on_credit,
                                            double* total_payment,
                                            double* diff_monthly_payment_max,
                                            double* diff_monthly_payment_min) {
  modelCredit_.CreditCalculate(total_credit_amount, term, interest_rate, type,
                               monthly_payment, overpayment_on_credit,
                               total_payment, diff_monthly_payment_max,
                               diff_monthly_payment_min);
}
