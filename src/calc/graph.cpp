#include "graph.h"
#include "ui_graph.h"
#include <QMessageBox>

#ifdef __cplusplus
extern "C"
{
#endif
#include "s21.h"
#ifdef __cplusplus
}
#endif

Graph::Graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
}

Graph::~Graph()
{
    delete ui;
}

void Graph::check() {
    int flag = 1;

    QString qt_str = ui->lineEdit_5->text();
    QByteArray byte_str = qt_str.toUtf8();
    char *str = byte_str.data();

    if (qt_str == "" || input_check(str) == 1) {
        flag = 0;
        QMessageBox::information(this, "Ошибка", "Ошибка ввода");
    } else {
        str_graph = str;
    }


    QString x1 = ui->lineEdit->text();
    QByteArray byte_x1 = x1.toUtf8();
    char *str_x1 = byte_x1.data();

    if (x1 == "" || !graph_input(str_x1)) {
        flag = 0;
        QMessageBox::information(this, "Ошибка", "Область определения X1 введена неверно");
    } else {
        xBegin = x1.toDouble();
    }

    QString x2 = ui->lineEdit_2->text();
    QByteArray byte_x2 = x2.toUtf8();
    char *str_x2 = byte_x2.data();

    if (x2 == "" || !graph_input(str_x2)) {
        flag = 0;
        QMessageBox::information(this, "Ошибка", "Область определения X2 введена неверно");
    } else {
        xEnd = x2.toDouble();
    }

    QString y1 = ui->lineEdit_4->text();
    QByteArray byte_y1 = y1.toUtf8();
    char *str_y1 = byte_y1.data();

    if (y1 == "" || !graph_input(str_y1)) {
        flag = 0;
        QMessageBox::information(this, "Ошибка", "Область определения Y1 введена неверно");
    } else {
        yBegin = y1.toDouble();
    }

    QString y2 = ui->lineEdit_3->text();
    QByteArray byte_y2 = y2.toUtf8();
    char *str_y2 = byte_y2.data();

    if (y2 == "" || !graph_input(str_y2)) {
        flag = 0;
        QMessageBox::information(this, "Ошибка", "Область определения Y2 введена неверно");
    } else {
        yEnd = y2.toDouble();
    }

    if (xBegin > 1000000 || xEnd > 1000000) {
        flag = 0;
        QMessageBox::information(this, "Ошибка", "Слишком высокое значение для области определения");
    }

    if (yBegin > 1000000 || yEnd > 1000000) {
        flag = 0;
        QMessageBox::information(this, "Ошибка", "Слишком высокое значение для области определения");
    }

    if (xBegin > xEnd) {
        flag = 0;
        QMessageBox::information(this, "Ошибка", "Начала области определения не может быть больше чем конец области определения");
    }

    if (yBegin > yEnd) {
        flag = 0;
        QMessageBox::information(this, "Ошибка", "Начала области определения не может быть больше чем конец области определения");
    }
    if (flag) print();
}

void Graph::print() {
    ui->widget->clearGraphs();
    double res = 0;
    h = 0.1;
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);

    for (X = xBegin; X <= xEnd; X += h) {
        x.push_back(X);
        calc_proc(str_graph, X, &res);
        if(res > yEnd) {
            y.push_back(qQNaN());
        } else {
            y.push_back(res);
        }
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    x.clear();
    y.clear();
}

void Graph::on_pushButton_clicked()
{


    check();


}

