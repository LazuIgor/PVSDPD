#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileparser.h"
#include "realiselogger.cpp"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    logger.log(LogLevel::LOG_INFO, "Start work with program");
    ui->setupUi(this);

    connect(ui->importDataAction, &QAction::triggered, this, [=](){
        Fileparser parser;
        parser.parse(QFileDialog::getOpenFileName(this, "", "", "*.txt"));
        auto data = parser.data_container();

        for(int i = 0; i < data.length(); i++)
        {
            QVector<double> x;
            for(int j = 0; j < data[i].length(); j++)
            {
                x.push_back(j);
            }
            QCPGraph graph = QCPGraph(ui->mainPlot->xAxis, ui->mainPlot->yAxis);
            graph.addData(x, data[i]);
            //graphs_.push_back(graph);

            ui->mainPlot->addGraph(graph.keyAxis(), graph.valueAxis());
        }
        ui->mainPlot->replot();


    });
}

MainWindow::~MainWindow()
{
    logger.log(LogLevel::LOG_INFO, "End work with program");
    delete ui;
}
