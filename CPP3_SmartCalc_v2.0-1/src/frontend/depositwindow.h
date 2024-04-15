#ifndef CPP3_S21_SMARTCALC_V2_0_FRONTEND_DEPOSITWINDOW_H_
#define CPP3_S21_SMARTCALC_V2_0_FRONTEND_DEPOSITWINDOW_H_

#include <QDebug>
#include <QMainWindow>

#include "financewindow.h"
#include "resultdialog.h"

namespace s21 {
QT_BEGIN_NAMESPACE
namespace Ui {
class DepositWindow;
}
QT_END_NAMESPACE

class DepositWindow : public FinanceWindow {
  Q_OBJECT
 public:
  explicit DepositWindow(QWidget *parent = nullptr,
                         S21SmartCalcController *controller = nullptr);
  ~DepositWindow();

 public slots:
  void DisplayResult(const QString &result);

 protected slots:
  void DigitsNumbers() override;
  void Signes() override;
  void Parameters() override;
  void CalcFunctions() override;
  void UpdateInputDisplay() override;

 signals:
  void CalculateExpression(const QString &expression);
  void WindowClosed();

 private slots:
  void CalcAll(bool capitalization);
  void closeEvent(QCloseEvent *event);
  void OnPushButtonEqClicked();

 private:
  Ui::DepositWindow *ui_;
  QString inputed_minus_ = "";
  QString inputed_plus_ = "";
  QString inputed_nalog_ = "";
  QString inputed_period = "";

  bool minus_is_active_ = false;
  bool plus_is_active_ = false;
  bool nalog_is_active_ = false;
  bool period_is_active_ = false;

  double SumOfList(const QString &list);
  void UpdateActiveParameter(QString &activeParam, const QString &button_text);
};
}  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V2_0_FRONTEND_DEPOSITWINDOW_H_
