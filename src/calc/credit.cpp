#include <QMessageBox>
#include "credit.h"
#include "ui_credit.h"


#ifdef __cplusplus
extern "C"
{
#endif
#include "s21.h"
#ifdef __cplusplus
}
#endif

Credit::Credit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Credit)
{
    ui->setupUi(this);
}

Credit::~Credit()
{
    delete ui;
}

void Credit::on_calc_clicked()
{
    ui->output_overpayment->setText("");
    ui->output_pay_month->setText("");
    ui->output_total_pay->setText("");

    double sum_credit, rate, month_payment, overpayment, total_payment;
    int month = 0;
    int flag = 1;


    QString qt_credit = ui->input_credit->text();
    QByteArray byte_credit = qt_credit.toUtf8();
    char *str_credit = byte_credit.data();
    if (qt_credit == "" || !check_posit(str_credit)) {
        flag = 0;
        QMessageBox::information(this, "Error", "Сумма введена некорректно");
    } else {
        sum_credit = qt_credit.toDouble();
    }

    QString qt_period = ui->input_period->text();
    QByteArray byte_period = qt_period.toUtf8();
    char *str_period = byte_period.data();
    if (qt_period == "" || !check_posit_int(str_period)) {
        flag = 0;
        QMessageBox::information(this, "Error", "Период введен некорректно");
    } else {
        month = qt_period.toInt();
    }


    QString qt_rate = ui->input_rate->text();
    QByteArray byte_rate = qt_rate.toUtf8();
    char *str_rate = byte_rate.data();
    if (qt_rate == "" || !check_posit(str_rate)) {
        flag = 0;
        QMessageBox::information(this, "Error", "Процент введен некорректно");
    } else {
        rate = qt_rate.toDouble();
    }

    if ((ann && diff) || (!ann && !diff)) {
        flag = 0;
        QMessageBox::information(this, "Error", "Выберите один из типов кредита");
    } else if (ann && !diff) {
        annuity(sum_credit, rate, month, &month_payment, &overpayment, &total_payment);

    } else if (diff && !ann) {
        differentiated(sum_credit, rate, month, &month_payment, &overpayment, &total_payment);
    }

    if (flag) {
        QString out_overpayment = QString::number(overpayment, 'g', 10);
        QString out_month = QString::number(month_payment, 'g', 10);
        QString out_total = QString::number(total_payment, 'g', 10);

        ui->output_pay_month->setText(out_month);
        ui->output_overpayment->setText(out_overpayment);
        ui->output_total_pay->setText(out_total);
    }


//    annuity(sum_credit, rate, month, &month_payment, &overpayment, &total_payment);
//    QString out_overpayment = QString::number(overpayment, 'g', 10);
//    QString out_month = QString::number(month_payment, 'g', 10);
//    QString out_total = QString::number(total_payment, 'g', 10);

//    ui->output_pay_month->setText(out_month);
//    ui->output_overpayment->setText(out_overpayment);
//    ui->output_total_pay->setText(out_total);
}


void Credit::on_check_ann_stateChanged(int arg1)
{
    if (arg1) {
        ann = 1;
    } else {
        ann = 0;
    }
}


void Credit::on_check_diff_stateChanged(int arg1)
{
    if (arg1) {
        diff = 1;
    } else {
        diff = 0;
    }
}

