#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_activated(int index);

    void on_comboBox_2_activated(int index);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_comboBox_4_activated(int index);

    void on_doubleSpinBox_5_valueChanged(double arg1);

    void on_doubleSpinBox_6_valueChanged(double arg1);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_doubleSpinBox_4_valueChanged(double arg1);

    void on_doubleSpinBox_7_valueChanged(double arg1);

    void on_doubleSpinBox_8_valueChanged(double arg1);


    void on_comboBox_5_currentIndexChanged(int index);

    void on_doubleSpinBox_9_valueChanged(double arg1);


    void on_doubleSpinBox_10_valueChanged(double arg1);





    void on_doubleSpinBox_11_valueChanged(double arg1);

    void on_doubleSpinBox_12_valueChanged(double arg1);

    void on_doubleSpinBox_17_valueChanged(double arg1);

    void on_doubleSpinBox_18_valueChanged(double arg1);

    void on_doubleSpinBox_19_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
