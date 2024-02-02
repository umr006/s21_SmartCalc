#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>

namespace Ui {
class Graph;
}

class Graph : public QDialog
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();
    void check();
    void print();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Graph *ui;

    double xBegin, xEnd, h, X, yBegin, yEnd;
    int N;

    QVector<double> x,y;

    char *str_graph;
};

#endif // GRAPH_H
