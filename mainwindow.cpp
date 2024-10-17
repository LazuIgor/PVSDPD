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
    date_time_start_ = ui->dateTimeEdit->dateTime();
    date_time_finish_ = ui->dateTimeEdit_2->dateTime();

    connect(ui->importDataAction, &QAction::triggered, this, [=](){
        Fileparser parser;
        parser.parse(QFileDialog::getOpenFileName(this, "", "", "*.txt"), date_time_start_, date_time_finish_);
        auto data = parser.data_container();

        for(int i = 0; i < data.length(); i++)
        {
            if(data[i].length() == 0)
            {
                QMessageBox::critical(this, "Ошибка", "Для заданного диапазона дат нет значений");
                break;
            }
            QVector<double> x;
            for(int j = 0; j < data[i].length(); j++)
            {
                x.push_back(j);
            }

            ui->mainPlot->addGraph();
            ui->mainPlot->graph(i)->setData(x, data[i]);
            ui->mainPlot->rescaleAxes();
            ui->mainPlot->replot();
        }
        ui->mainPlot->replot();
    });

    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [=](){
        date_time_start_ = ui->dateTimeEdit->dateTime();
    });

    connect(ui->dateTimeEdit_2, &QDateTimeEdit::dateTimeChanged, this, [=](){
        date_time_finish_ = ui->dateTimeEdit_2->dateTime();
    });

}

MainWindow::~MainWindow()
{
    logger.log(LogLevel::LOG_INFO, "End work with program");
    delete ui;
}
