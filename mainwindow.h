#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QListWidget>
#include <unordered_map>
#include <QColor>
#include "graph.h"
#include <QTimer>
#include <QLine>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddVertex();
    void onAddEdge();
    void onRunBFS();
    void onRunDFS();
    void onResetGraph();

    void onGraphTypeChanged(const QString& text);

private:
    Ui::MainWindow *ui;
    Graph* graph;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QListWidget* stepsList;
    std::unordered_map<int, QColor> colors;
    QTimer* bfsVisualizationTimer;
    QTimer* dfsVisualizationTimer;
    QList<std::function<void()>> bfsSteps;
    QList<std::function<void()>> dfsSteps;


    void updateVisualization();
    void visualizeNextBFSStep();
    void visualizeNextDFSStep();
    void drawArrow(const QLineF& line);

    void addVertexToScene(int vertexId, const QPointF& position, const QColor& vertexColor);
    void addEdgeToScene(int u, int v, const QPointF& posU, const QPointF& posV);

    void classifyAndDisplayEdges();

};

#endif
