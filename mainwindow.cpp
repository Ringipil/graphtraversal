#include "mainwindow.h"
#include "ui_MainWindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , graph(false) // Initialize graph as undirected by default
    , scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addEdgeButton_clicked() {
    QString edgeInput = ui->edgeInput->text();
    QStringList nodes = edgeInput.split(",");
    if (nodes.size() == 2) {
        int u = nodes[0].toInt();
        int v = nodes[1].toInt();
        graph.addEdge(u, v);
        visualizeGraph();
    }
}

void MainWindow::visualizeGraph() {
    scene->clear();

    // Placeholder for graph visualization
    // This would involve drawing nodes and edges using QGraphicsItems
    for (const auto& pair : graph.getAllAdjacencyLists()) {
        int node = pair.first;
        for (int neighbor : pair.second) {
            // Draw nodes and edges in the scene
            scene->addEllipse(node * 20, neighbor * 20, 5, 5); // Example: simple circles for nodes
            scene->addLine(node * 20, node * 20, neighbor * 20, neighbor * 20); // Example: simple lines for edges
        }
    }
}

void MainWindow::on_bfsButton_clicked() {
    // Example start node for BFS
    int startNode = 1;

    auto stepCallback = [this](int node, const string& color) {
        // Visualization logic for each step
        // Update node color in the scene based on 'color'
        // This is a placeholder example:
        cout << "Node " << node << " is now " << color << endl;
    };

    graph.bfs(startNode, stepCallback);
}
