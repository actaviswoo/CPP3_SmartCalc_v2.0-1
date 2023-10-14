#ifndef SRC_MODEL_CREDITMODEL_H
#define SRC_MODEL_CREDITMODEL_H

#include <cmath>
#include <iostream>

namespace s21 {

class ModelCredit {
 public:
  ModelCredit(){};
  ~ModelCredit(){};

  void CreditCalculate(double total_credit_amount, int term,
                       double interest_rate, int type, double* monthly_payment,
                       double* overpayment_on_credit, double* total_payment,
                       double* diff_monthly_payment_max,
                       double* diff_monthly_payment_min);
};

}  // namespace s21

#endif  // SRC_MODEL_CREDITMODEL_H