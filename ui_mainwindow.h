/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QLineEdit *vertexInput;
    QPushButton *bfsButton;
    QComboBox *graphTypeComboBox;
    QPushButton *addEdgeButton;
    QLineEdit *edgeInput;
    QPushButton *addVertexButton;
    QGraphicsView *graphicsView;
    QListWidget *stepsListWidget;
    QPushButton *dfsButton;
    QPushButton *resetGraphButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1085, 630);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        vertexInput = new QLineEdit(centralwidget);
        vertexInput->setObjectName("vertexInput");

        gridLayout_2->addWidget(vertexInput, 1, 0, 1, 1);

        bfsButton = new QPushButton(centralwidget);
        bfsButton->setObjectName("bfsButton");

        gridLayout_2->addWidget(bfsButton, 4, 0, 1, 1);

        graphTypeComboBox = new QComboBox(centralwidget);
        graphTypeComboBox->addItem(QString());
        graphTypeComboBox->addItem(QString());
        graphTypeComboBox->setObjectName("graphTypeComboBox");

        gridLayout_2->addWidget(graphTypeComboBox, 4, 1, 1, 1);

        addEdgeButton = new QPushButton(centralwidget);
        addEdgeButton->setObjectName("addEdgeButton");

        gridLayout_2->addWidget(addEdgeButton, 3, 1, 1, 1);

        edgeInput = new QLineEdit(centralwidget);
        edgeInput->setObjectName("edgeInput");

        gridLayout_2->addWidget(edgeInput, 3, 0, 1, 1);

        addVertexButton = new QPushButton(centralwidget);
        addVertexButton->setObjectName("addVertexButton");

        gridLayout_2->addWidget(addVertexButton, 1, 1, 1, 1);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");

        gridLayout_2->addWidget(graphicsView, 9, 0, 1, 1);

        stepsListWidget = new QListWidget(centralwidget);
        stepsListWidget->setObjectName("stepsListWidget");

        gridLayout_2->addWidget(stepsListWidget, 9, 1, 1, 1);

        dfsButton = new QPushButton(centralwidget);
        dfsButton->setObjectName("dfsButton");

        gridLayout_2->addWidget(dfsButton, 5, 0, 1, 1);

        resetGraphButton = new QPushButton(centralwidget);
        resetGraphButton->setObjectName("resetGraphButton");

        gridLayout_2->addWidget(resetGraphButton, 5, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1085, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        vertexInput->setText(QCoreApplication::translate("MainWindow", "Vertex ID", nullptr));
        bfsButton->setText(QCoreApplication::translate("MainWindow", "Run BFS", nullptr));
        graphTypeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Directed", nullptr));
        graphTypeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Unidirected", nullptr));

        addEdgeButton->setText(QCoreApplication::translate("MainWindow", "Add Edge", nullptr));
        edgeInput->setText(QCoreApplication::translate("MainWindow", "Edge (src,dest)", nullptr));
        addVertexButton->setText(QCoreApplication::translate("MainWindow", "Add Vertex", nullptr));
        dfsButton->setText(QCoreApplication::translate("MainWindow", "Run DFS", nullptr));
        resetGraphButton->setText(QCoreApplication::translate("MainWindow", "Reset Graph", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
