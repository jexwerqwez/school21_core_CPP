#ifndef CPP3_S21_SMARTCALC_V2_0_FRONTEND_CREDITWINDOW_H_
#define CPP3_S21_SMARTCALC_V2_0_FRONTEND_CREDITWINDOW_H_

#include <QDebug>
#include <QMainWindow>

#include "financewindow.h"
#include "resultdialog.h"

namespace s21 {
QT_BEGIN_NAMESPACE
namespace Ui {
class CreditWindow;
}
QT_END_NAMESPACE

class CreditWindow : public FinanceWindow {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = nullptr,
                        S21SmartCalcController *controller = nullptr);
  ~CreditWindow() override;

  struct DiffPaymentInfo {
    double total_diff_payment = 0;
    QVector<double> monthly_payments;
    QString payment_details;
  };

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
  void OnPushButtonEqClicked();
  void CalcAnnuity();
  void CalcDifferentiated();
  void closeEvent(QCloseEvent *event) override;

 private:
  Ui::CreditWindow *ui_;
  DiffPaymentInfo diff_payment_info_;
  void UpdateActiveParameter(QString &activeParam, const QString &button_text);
};
}  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V2_0_FRONTEND_CREDITWINDOW_H_
