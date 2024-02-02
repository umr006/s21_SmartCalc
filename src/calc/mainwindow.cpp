#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#ifdef __cplusplus
extern "C"
{
#endif
#include "s21.h"
#ifdef __cplusplus
}
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    credit.show();
}


void MainWindow::on_pushButton_1_clicked()
{
    ui->label->setText(ui->label->text() + "1");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->setText(ui->label->text() + "2");
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->label->setText(ui->label->text() + "3");
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->label->setText(ui->label->text() + "4");
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->label->setText(ui->label->text() + "5");
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->label->setText(ui->label->text() + "6");
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->label->setText(ui->label->text() + "7");
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->label->setText(ui->label->text() + "8");
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->label->setText(ui->label->text() + "9");
}


void MainWindow::on_pushButton_dot_clicked()
{
    if(oper)
        ui->label->setText(ui->label->text() + ".");
    oper = 0;
}


void MainWindow::on_pushButton_plus_clicked()
{
    ui->label->setText(ui->label->text() + "+");
    oper = 1;
}


void MainWindow::on_pushButton_minus_clicked()
{
    ui->label->setText(ui->label->text() + "-");
    oper = 1;
}


void MainWindow::on_pushButton_mul_clicked()
{
    ui->label->setText(ui->label->text() + "*");
    oper = 1;
}


void MainWindow::on_pushButton_div_clicked()
{
    ui->label->setText(ui->label->text() + "/");
    oper = 1;
}


void MainWindow::on_pushButton_eq_clicked()
{
    if(ui->label->text() == "") {
        QMessageBox::information(this, "Ошибка", "Строка ввода пустай");
    } else {
        double result = 0, x = 0;
        QString qt_str = ui->label->text();
        QByteArray byte_str = qt_str.toUtf8();
        char *str = byte_str.data();
        if (input_check(str) == 1  /*|| input_check(str) == 1*/) {
            QMessageBox::information(this, "Ошибка", "Неверный ввод");
        } else {
            if (ui->label->text().contains('x')) {
                QString qt_x = ui->lineEdit->text();
                x = qt_x.toDouble();

                calc_proc(str, x, &result);
                QString new_label;
                new_label = QString::number(result, 'g', 8);
                ui->label->setText(new_label);
            } else {
                calc_proc(str, x, &result);
                QString new_label;
                new_label = QString::number(result, 'g', 8);
                ui->label->setText(new_label);
            }
        }
    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->label->setText("");
    oper = 1;
}


void MainWindow::on_pushButton_eq_2_clicked()
{
    QString currentText = ui->label->text();

    if (!currentText.isEmpty()) {
        currentText.chop(1);
        ui->label->setText(currentText);
        oper = 1;
    }
}

void MainWindow::on_pushButton_mod_clicked()
{
    ui->label->setText(ui->label->text() + "mod");
    oper = 1;
    
}


void MainWindow::on_pushButton_open_clicked()
{
    ui->label->setText(ui->label->text() + "(");
    oper = 1;
}


void MainWindow::on_pushButton_close_clicked()
{
    ui->label->setText(ui->label->text() + ")");
    oper = 1;
}


void MainWindow::on_pushButton_pow_clicked()
{
    ui->label->setText(ui->label->text() + "^");
    oper = 1;
}


void MainWindow::on_pushButton_sin_clicked()
{
    ui->label->setText(ui->label->text() + "sin(");
    oper = 1;
}


void MainWindow::on_pushButton_cos_clicked()
{
    ui->label->setText(ui->label->text() + "cos(");
    oper = 1;
}


void MainWindow::on_pushButton_tan_clicked()
{
    ui->label->setText(ui->label->text() + "tan(");
    oper = 1;
}


void MainWindow::on_pushButton_asin_clicked()
{
    ui->label->setText(ui->label->text() + "asin(");
    oper = 1;
}


void MainWindow::on_pushButton_acos_clicked()
{
    ui->label->setText(ui->label->text() + "acos(");
    oper = 1;
}


void MainWindow::on_pushButton_atan_clicked()
{
    ui->label->setText(ui->label->text() + "atan(");
    oper = 1;
}


void MainWindow::on_pushButton_log_clicked()
{
    ui->label->setText(ui->label->text() + "log(");
    oper = 1;
}


void MainWindow::on_pushButton_ln_clicked()
{
    ui->label->setText(ui->label->text() + "ln(");
    oper = 1;
}


void MainWindow::on_pushButton_sqrt_clicked()
{
    ui->label->setText(ui->label->text() + "sqrt(");
    oper = 1;
}


void MainWindow::on_pushButton_pow_2_clicked()
{
    ui->label->setText(ui->label->text() + "x");
    oper = 1;
}


void MainWindow::on_pushButton_graph_clicked()
{
    graph.show();

}


void MainWindow::on_pushButton_0_clicked()
{
    ui->label->setText(ui->label->text() + "0");
}

