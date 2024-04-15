#ifndef CPP3_S21_SMARTCALC_V2_0_FRONTEND_GRAPHWINDOW_H_
#define CPP3_S21_SMARTCALC_V2_0_FRONTEND_GRAPHWINDOW_H_

#include <QDialog>
#include <QVector>

#include "../backend/s21_smartcalc_controller.h"

namespace s21 {
QT_BEGIN_NAMESPACE
namespace Ui {
class GraphWindow;
}
QT_END_NAMESPACE

class GraphWindow : public QDialog {
  Q_OBJECT

 public:
  explicit GraphWindow(QWidget *parent = nullptr, QString expression = "",
                       S21SmartCalcController *controller = nullptr);
  ~GraphWindow();

 public slots:
  void onCalculationResultReceived(const QString &result);

 signals:
  void GraphWindowClosed();
  void requestExpressionEvaluation(const QString &expression, double x);

 private:
  Ui::GraphWindow *ui_;
  S21SmartCalcController *controller_;
  QString current_expression_;
  QVector<double> x_, y_;
  double x_begin_, x_end_, h_, current_x_;

  void calculateYValues(const QString &expression);
};
}  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V2_0_FRONTEND_GRAPHWINDOW_H_
