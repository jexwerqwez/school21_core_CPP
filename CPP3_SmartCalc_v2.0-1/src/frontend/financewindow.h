#ifndef CPP3_S21_SMARTCALC_V2_0_FRONTEND_FINANCEWINDOW_H_
#define CPP3_S21_SMARTCALC_V2_0_FRONTEND_FINANCEWINDOW_H_

#include <QMainWindow>

#include "../backend/s21_smartcalc_controller.h"

namespace s21 {
class FinanceWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit FinanceWindow(QWidget *parent = nullptr,
                         S21SmartCalcController *controller = nullptr)
      : QMainWindow(parent), controller_(controller) {}

  virtual ~FinanceWindow() {}

 protected:
  S21SmartCalcController *controller_;
  QString inputed_pr_ = "";
  QString inputed_sum_ = "";
  QString inputed_time_ = "";
  bool pr_is_active_ = 0;
  bool sum_is_active_ = 0;
  bool time_is_active_ = 0;

  virtual void DigitsNumbers() = 0;
  virtual void Signes() = 0;
  virtual void Parameters() = 0;
  virtual void CalcFunctions() = 0;
  virtual void UpdateInputDisplay() = 0;
  virtual void closeEvent(QCloseEvent *event) = 0;
};
}  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V2_0_FRONTEND_FINANCEWINDOW_H_
