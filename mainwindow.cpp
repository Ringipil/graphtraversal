#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QGraphicsTextItem>
#include <QRectF>
#include <QtWidgets>
#include <utility>

//Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool isDirected = ui->graphTypeComboBox->currentText() == "Directed";
    graph = new Graph(isDirected);

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

    // Connect the graph type combo box to update the graph type

    connect(ui->graphTypeComboBox, &QComboBox::currentTextChanged, this, &MainWindow::onGraphTypeChanged);


    // Initialize visualization timer
    bfsVisualizationTimer = new QTimer(this);
    connect(bfsVisualizationTimer, &QTimer::timeout, this, &MainWindow::visualizeNextBFSStep);

    dfsVisualizationTimer = new QTimer(this);
    connect(dfsVisualizationTimer, &QTimer::timeout, this, &MainWindow::visualizeNextDFSStep);


}

// Slot to handle graph type change
void MainWindow::onGraphTypeChanged(const QString& text) {
    bool isDirected = (text == "Directed");
    graph = new Graph(isDirected); // Recreate the graph with the new directed status
    onResetGraph(); // Optionally reset the graph to clear existing edges/vertices
}
//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// New function to add a vertex to the scene
void MainWindow::onAddVertex() {
    bool ok;
    int vertexId = ui->vertexInput->text().toInt(&ok);
    if (!ok || vertexId < 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid positive integer for the vertex ID.");
        return;
    }
    graph->addVertex(vertexId); // addVertex now has a void return type
    updateVisualization(); // Update visualization to reflect the new vertex

}

// New function to add an edge to the scene
void MainWindow::onAddEdge() {
    QString edgeText = ui->edgeInput->text();
    QStringList vertices = edgeText.split(',');

    if (vertices.size() != 2) {
        QMessageBox::warning(this, "Input Error", "Please enter the edge in format src,dest.");
        return;
    }

    bool okU, okV;
    int u = vertices.at(0).toInt(&okU);
    int v = vertices.at(1).toInt(&okV);

    if (!okU || !okV || u < 0 || v < 0) {
        QMessageBox::warning(this, "Input Error", "Please enter valid positive integers for the vertex IDs.");
        return;
    }

    // Check if both vertices exist
    if (!graph->vertexExists(u) || !graph->vertexExists(v)) {
        QMessageBox::warning(this, "Vertex Error", "One or both vertices do not exist.");
        return;
    }

    graph->addEdge(u, v); // Add the edge to the graph
    updateVisualization(); // Update the visualization to reflect the new edge
}

//New function to run BFS
void MainWindow::onRunBFS() {
    bool ok;
    int startNode = QInputDialog::getInt(this, tr("Start Node for BFS"),
                                         tr("Enter start node:"), 1, 0, 100, 1, &ok);
    if (!ok || !graph->vertexExists(startNode)) {
        QMessageBox::warning(this, "BFS Error", "Invalid start node.");
        return;
    }

    stepsList->clear();
    colors.clear(); // Clear colors map before starting BFS

    bfsSteps.clear(); // Clear previous steps

    auto stepCallback = [this](int node, const string& colorStr) {
        QColor color = (colorStr == "gray") ? Qt::gray : (colorStr == "black" ? Qt::black : Qt::white);
        bfsSteps.append([this, node, color, colorStr]() {
            // This lambda will be called later to update the visualization
            colors[node] = color; // Update the color for the current node
            updateVisualization(); // Call updateVisualization with the updated colors map
            stepsList->addItem("Node " + QString::number(node) + ": " + QString::fromStdString(colorStr));
        });
    };

    graph->bfs(startNode, stepCallback);
    bfsVisualizationTimer->start(2000); // Start timer, adjust delay as needed
}

// New function to visualize next BFS step
void MainWindow::visualizeNextBFSStep() {
    if (!bfsSteps.isEmpty()) {
        auto step = bfsSteps.takeFirst(); // Get the next step
        step(); // Execute the step
    } else {
        bfsVisualizationTimer->stop(); // Stop the timer if no more steps
        QMessageBox::information(this, "BFS Complete", "BFS traversal has completed.");
    }
}

// New function to run DFS
void MainWindow::onRunDFS() {
    bool ok;
    int startNode = QInputDialog::getInt(this, tr("Start Node for DFS"),
                                         tr("Enter start node:"), 1, 0, 100, 1, &ok);
    if (!ok || !graph->vertexExists(startNode)) {
        QMessageBox::warning(this, "DFS Error", "Invalid start node.");
        return;
    }

    stepsList->clear();
    colors.clear();
    dfsSteps.clear();

    // Define the callback function
    auto stepCallback = [this](int node, const std::string& colorStr, const std::string& additionalInfo) {
        QColor color;
        if (colorStr == "gray") {
            color = Qt::gray;
        } else if (colorStr == "black") {
            color = Qt::black;
        }

        dfsSteps.append([this, node, color, colorStr, additionalInfo]() {
            colors[node] = color;
            updateVisualization();
            stepsList->addItem("Node " + QString::number(node) + ": " + QString::fromStdString(colorStr + " (" + additionalInfo + ")"));
        });
    };

    // Pass the callback to the DFS algorithm
    graph->dfs(startNode, stepCallback);
    dfsVisualizationTimer->start(2000); // Start the timer for visualization
}

// New function to visualize next DFS step
void MainWindow::visualizeNextDFSStep() {
    if (!dfsSteps.isEmpty()) {
        auto step = dfsSteps.takeFirst(); // Get the next step
        step(); // Execute the step
    } else {
        dfsVisualizationTimer->stop(); // Stop the timer if no more steps
        QMessageBox::information(this, "DFS Complete", "DFS traversal has completed.");

    }
}

// New function to reset the graph
void MainWindow::onResetGraph() {
    graph->resetGraph();
    colors.clear();
    updateVisualization();
    stepsList->clear();
    // Optionally, update the UI or visualization to reflect the reset graph
    QMessageBox::information(this, "Graph Reset", "Graph has been reset.");
}

// New function to update the visualization
void MainWindow::updateVisualization() {
    scene->clear();
    int N = graph->getAllAdjacencyLists().size();
    if (N == 0) return;
    QRectF rect = scene->sceneRect();
    QPointF center = rect.center();
    double radius = qMin(rect.width(), rect.height()) / 2;
    std::unordered_map<int, QPointF> vertexPositions;
    double angleIncrement = 2 * M_PI / N;

    // Calculate positions for each vertex
    for (const auto& pair : graph->getAllAdjacencyLists()) {
        int i = std::distance(graph->getAllAdjacencyLists().begin(), graph->getAllAdjacencyLists().find(pair.first));
        double theta = i * angleIncrement;
        double x = center.x() + radius * cos(theta);
        double y = center.y() + radius * sin(theta);
        vertexPositions[pair.first] = QPointF(x, y);
    }

    // Draw vertices
    for (const auto& pair : vertexPositions) {
        QColor vertexColor = (colors.find(pair.first) != colors.end()) ? colors.at(pair.first) : Qt::white;
        scene->addEllipse(pair.second.x() - 20, pair.second.y() - 20, 40, 40, QPen(), QBrush(vertexColor));

        // Determine text color based on vertex color
        QColor textColor = (vertexColor == Qt::gray || vertexColor == Qt::black) ? Qt::white : Qt::black;

        auto text = scene->addText(QString::number(pair.first));
        text->setDefaultTextColor(textColor); // Set the text color
        text->setPos(pair.second.x() - 10, pair.second.y() - 10);
    }

    // Draw edges
    for (const auto& pair : graph->getAllAdjacencyLists()) {
        for (int neighbor : pair.second) {
            QPointF start = vertexPositions[pair.first];
            QPointF end = vertexPositions[neighbor];

            // Calculate unit vector from start to end
            QPointF direction = end - start;
            QPointF unitVector = direction / QLineF(start, end).length();

            // Offset start and end points by vertex radius
            double vertexRadius = 20.0; // Assuming vertex circle radius
            start += unitVector * vertexRadius;
            end -= unitVector * vertexRadius;

            // Draw the line
            QGraphicsLineItem *lineItem = scene->addLine(QLineF(start, end), QPen(Qt::darkRed));

            if (graph->isDirected()) {
                drawArrow(QLineF(start, end)); // Draw arrowhead at the end of the line
            }
        }
    }

    QRectF fixedSceneRect = QRectF(0, 0, 300, 300);
    scene->setSceneRect(fixedSceneRect);
}

// New function to draw an arrowhead at the end of a line
void MainWindow::drawArrow(const QLineF& line) {
    QPen pen(Qt::darkRed, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    pen.setWidth(5);

    double angle = std::atan2(-line.dy(), line.dx());
    QPointF arrowP1 = line.p2() - QPointF(std::sin(angle + M_PI / 3) * 10, std::cos(angle + M_PI / 3) * 10);
    QPointF arrowP2 = line.p2() - QPointF(std::sin(angle + M_PI - M_PI / 3) * 10, std::cos(angle + M_PI - M_PI / 3) * 10);

    QPolygonF arrowHead;
    arrowHead.clear();
    arrowHead << line.p2() << arrowP1 << arrowP2;
    scene->addPolygon(arrowHead, pen, QBrush(Qt::darkRed));
}
