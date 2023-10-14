#ifndef SRC_CONTROLLER_DEPOSITCONTROLLER_H
#define SRC_CONTROLLER_DEPOSITCONTROLLER_H

#include "../Model/depositmodel.h"

namespace s21 {

class DepositController {
 public:
  DepositController(){};
  ~DepositController(){};
  void DepositCalculate(double deposit_amount, double deposit_term,
                        double interest_rate, double tax_rate, double period,
                        bool capitalization, s21::DepositData replenishments,
                        s21::DepositData withdrawals, double* accrued_interest,
                        double* tax_amount, double* deposit_end,
                        double* deposit_total);

 private:
  s21::ModelDeposit modelDeposit_;
};

}  // namespace s21

#endif  // SRC_CONTROLLER_DEPOSITCONTROLLER_H
