#include "depositmodel.h"

void s21::ModelDeposit::DepositCalculate(
    double deposit_amount, double deposit_term, double interest_rate,
    double tax_rate, double period, bool capitalization,
    DepositData replenishments, DepositData withdrawals,
    double* accrued_interest, double* tax_amount, double* deposit_end,
    double* deposit_total) {
  double total_deposit_amount = deposit_amount;
  int payment = PaymentParse(period);
  double interest = 0.0;
  interest_rate = (interest_rate / 365) / 100;
  double replenishments_deposit_amount = 0.0;
  double withdrawals_deposit_amount = 0.0;
  for (int i = 1; i <= deposit_term; i++) {
    if (capitalization) {
      interest += total_deposit_amount * interest_rate;
      if (i % payment == 0 && payment) {
        total_deposit_amount += interest;
        interest = 0.0;
      }
    } else {
      interest += total_deposit_amount * interest_rate;
    }
    DataCalculate(replenishments, deposit_term, &total_deposit_amount, i,
                  &replenishments_deposit_amount, 1);
    DataCalculate(withdrawals, deposit_term, &total_deposit_amount, i,
                  &withdrawals_deposit_amount, -1);
  }
  if (capitalization) {
    *accrued_interest = total_deposit_amount - deposit_amount;
    *accrued_interest -= replenishments_deposit_amount;
    *accrued_interest += withdrawals_deposit_amount;
  } else {
    *accrued_interest = interest;
  }
  *tax_amount =
      (*accrued_interest - 7.5 / 100 * 1000000) > 0
          ? (*accrued_interest - 7.5 / 100 * 1000000) * (tax_rate / 100)
          : 0;
  *deposit_end = *accrued_interest - *tax_amount;
  *deposit_total = total_deposit_amount;
}

void s21::ModelDeposit::DataCalculate(DepositData data, double deposit_term,
                                      double* total_deposit_amount, int i,
                                      double* dated, int flag) {
  for (size_t j = 0; j < data.day.size(); j++) {
    int temp = TempParse(data.period[j], deposit_term);
    if (i % temp == 0 && temp && i >= data.day[j]) {
      *total_deposit_amount =
          *total_deposit_amount + (flag * data.deposit_amount[j]);
      *dated += data.deposit_amount[j];
    }
  }
}

int s21::ModelDeposit::PaymentParse(int period) {
  if (period == 1)
    return 1;
  else if (period == 2)
    return 7;
  else if (period == 3)
    return 30;
  else if (period == 4)
    return 91;
  else if (period == 5)
    return 183;
  else if (period == 6)
    return 365;
  return 0;
}

int s21::ModelDeposit::TempParse(int period, int deposit_term) {
  if (period == 1)
    return deposit_term;
  else if (period == 2)
    return 30;
  else if (period == 3)
    return 60;
  else if (period == 4)
    return 91;
  else if (period == 5)
    return 183;
  else if (period == 6)
    return 365;
  return 0;
}
