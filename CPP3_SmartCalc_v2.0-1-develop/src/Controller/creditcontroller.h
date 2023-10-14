#ifndef SRC_CONTROLLER_CREDITCONTROLLER_H
#define SRC_CONTROLLER_CREDITCONTROLLER_H

#include "../Model/creditmodel.h"

namespace s21 {

class CreditController {
 public:
  CreditController(){};
  ~CreditController(){};

  void CreditCalculate(double total_credit_amount, int term,
                       double interest_rate, int type, double* monthly_payment,
                       double* overpayment_on_credit, double* total_payment,
                       double* diff_monthly_payment_max,
                       double* diff_monthly_payment_min);

 private:
  s21::ModelCredit modelCredit_;
};

}  // namespace s21

#endif  // SRC_CONTROLLER_CREDITCONTROLLER_H
