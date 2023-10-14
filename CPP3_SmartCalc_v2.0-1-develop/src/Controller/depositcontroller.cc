#include "depositcontroller.h"

void s21::DepositController::DepositCalculate(
    double deposit_amount, double deposit_term, double interest_rate,
    double tax_rate, double period, bool capitalization,
    s21::DepositData replenishments, s21::DepositData withdrawals,
    double* accrued_interest, double* tax_amount, double* deposit_end,
    double* deposit_total) {
  modelDeposit_.DepositCalculate(deposit_amount, deposit_term, interest_rate,
                                 tax_rate, period, capitalization,
                                 replenishments, withdrawals, accrued_interest,
                                 tax_amount, deposit_end, deposit_total);
}
