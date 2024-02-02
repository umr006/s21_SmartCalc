#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

namespace Ui {
class Credit;
}

class Credit : public QDialog
{
    Q_OBJECT

public:
    explicit Credit(QWidget *parent = nullptr);
    ~Credit();

private slots:

    void on_calc_clicked();

    void on_check_ann_stateChanged(int arg1);

    void on_check_diff_stateChanged(int arg1);

private:
    Ui::Credit *ui;
    int ann = 0, diff = 0;
};

#endif // CREDIT_H
