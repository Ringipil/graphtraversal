#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //graph = new Graph(false);  // Assume false means undirected
    scene = new QGraphicsScene(this);
    view = ui->graphicsView;
    view->setScene(scene);
    stepsList = ui->stepsListWidget;

    // Connect buttons to slots
    connect(ui->addVertexButton, &QPushButton::clicked, this, &MainWindow::onAddVertex);
    connect(ui->addEdgeButton, &QPushButton::clicked, this, &MainWindow::onAddEdge);
    connect(ui->bfsButton, &QPushButton::clicked, this, &MainWindow::onRunBFS);
    connect(ui->dfsButton, &QPushButton::clicked, this, &MainWindow::onRunDFS);
    connect(ui->resetGraphButton, &QPushButton::clicked, this, &MainWindow::onResetGraph);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddVertex() {
    // Implementation for adding vertex
}

void MainWindow::onAddEdge() {
    // Implementation for adding edge
}

void MainWindow::onRunBFS() {
    // Implementation for running BFS
}

void MainWindow::onRunDFS() {
    // Implementation for running DFS
}

void MainWindow::onResetGraph() {
    // Implementation for resetting graph
}

void MainWindow::updateVisualization() {
    // Implementation for updating visualization
}

