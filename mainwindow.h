#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "graph.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addEdgeButton_clicked(); // Slot for adding edge button click
    void on_bfsButton_clicked(); // Slot for BFS button click

private:
    Ui::MainWindow *ui;
    Graph graph;
    QGraphicsScene *scene;

    void visualizeGraph(); // Method to visualize the graph
};

#endif // MAINWINDOW_H
