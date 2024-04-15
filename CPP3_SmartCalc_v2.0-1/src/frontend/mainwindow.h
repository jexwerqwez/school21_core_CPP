#ifndef CPP3_S21_SMARTCALC_V2_0_FRONTEND_MAINWINDOW_H_
#define CPP3_S21_SMARTCALC_V2_0_FRONTEND_MAINWINDOW_H_

#include <QDebug>
#include <QMainWindow>
#include <QStack>
#include <QVector>
#include <cmath>
#include <iostream>

#include "../backend/s21_smartcalc_controller.h"
#include "creditwindow.h"
#include "depositwindow.h"
#include "graphwindow.h"

namespace s21 {
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(S21SmartCalcController *controller,
                      QWidget *parent = nullptr);
  ~MainWindow();

 public slots:
  void DisplayResult(const QString &result);
  void OnCreditWindowClosed();
  void OnDepositWindowClosed();

 signals:
  void CalculateExpression(const QString &expression);
  void SetXValue(double x);
  void PerformCalculationForGraph(const QString &expression, double x);
  void SendGraphCalculationResult(double y);

 private slots:
  void DigitsNumbers();
  void OnPushButtonDotClicked();
  void MathOperations();
  void UpdateInputDisplay();
  void OnPushButtonEqClicked();
  void Signes();
  void MathFunctions();
  void TrigOperations();
  void CalcFunctions();
  void OpenCreditWindow();
  void OpenDepositWindow();
  void OpenGraphWindow(QString &expression);
  void Unknown();
  bool CheckAroundUnknown();
  void ClearGraphInput();
  void connectButtons(const QStringList &buttons, const char *slot);

 private:
  Ui::MainWindow *ui;
  QString input_string_;
  CreditWindow *credit_window_ = nullptr;
  DepositWindow *deposit_window_ = nullptr;
  GraphWindow *graph_window_ = nullptr;
  S21SmartCalcController *controller_;
};
}  // namespace s21
#endif  // CPP3_S21_SMARTCALC_V2_0_FRONTEND_MAINWINDOW_H_
