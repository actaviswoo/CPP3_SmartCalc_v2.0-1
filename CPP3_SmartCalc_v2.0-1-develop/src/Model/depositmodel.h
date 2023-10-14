#ifndef SRC_MODEL_DEPOSITMODEL_H
#define SRC_MODEL_DEPOSITMODEL_H

#include <array>
#include <cmath>
#include <iostream>
#include <vector>

namespace s21 {

struct DepositData {
  std::vector<int> period;
  std::vector<int> day;
  std::vector<double> deposit_amount;
};

class ModelDeposit {
 public:
  ModelDeposit(){};
  ~ModelDeposit(){};
  void DepositCalculate(double deposit_amount, double deposit_term,
                        double interest_rate, double tax_rate, double period,
                        bool capitalization, DepositData replenishments,
                        DepositData withdrawals, double* accrued_interest,
                        double* tax_amount, double* deposit_end,
                        double* deposit_total);

 private:
  void DataCalculate(DepositData data, double deposit_term,
                     double* total_deposit_amount, int i, double* dated,
                     int flag);
  int PaymentParse(int period);
  int TempParse(int period, int deposit_term);
};

}  // namespace s21

#endif  // SRC_MODEL_DEPOSITMODEL_H
