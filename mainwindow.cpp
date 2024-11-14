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

    ui->statusLabel->setText("Нет данных для визуализации");

    ui->mainPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->mainPlot->setSelectionRectMode(QCP::srmNone);

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeFormat("yyyy-MM-dd hh:mm:ss");
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    ui->mainPlot->xAxis->setTicker(dateTimeTicker);

    ui->startDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->finishDateTimeEdit->setDateTime(QDateTime::currentDateTime());

    date_time_start_ = ui->startDateTimeEdit->dateTime();
    date_time_finish_ = ui->finishDateTimeEdit->dateTime();
    /*
    connect(ui->importDataAction, &QAction::triggered, this, [=](){
        Fileparser parser;
        parser.parse(QFileDialog::getOpenFileName(this, "", "", "*.txt"), date_time_start_, date_time_finish_);
        auto data = parser.data_container();
        for(int i = 0; i < ui->mainPlot->graphCount(); i++)
        {
            ui->mainPlot->removeGraph(ui->mainPlot->removeGraph(i));
        }
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
                x.push_back(parser.times[j].toMSecsSinceEpoch());
            }

            ui->mainPlot->addGraph();
            ui->mainPlot->graph(i)->setData(x, data[i]);
            ui->mainPlot->rescaleAxes();
            ui->mainPlot->replot();
        }
        ui->mainPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        ui->mainPlot->setSelectionRectMode(QCP::srmNone);
        ui->mainPlot->replot();
    });
*/

    connect(ui->startDateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [=](){
        date_time_start_ = ui->startDateTimeEdit->dateTime();
        checkDataFromDatabase();
    });

    connect(ui->finishDateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [=](){
        date_time_finish_ = ui->finishDateTimeEdit->dateTime();
        checkDataFromDatabase();
    });

    connect(ui->lineNumberSpinBox, &QSpinBox::valueChanged, this, [=](int ){
        checkDataFromDatabase();
    });

    QVector<QString> names {"Температура", "Вакуум", "Скорость вытягивателя", "Производительность мотора", "Давление", "Температура помещения"};
    for (int i = 0; i < 6; ++i)
    {
        QListWidgetItem *item = new QListWidgetItem(names[i]);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);
        ui->traceList->addItem(item);
    }

    connect(ui->traceList, &QListWidget::itemChanged, this, [=](QListWidgetItem *item){
        bool visible;
        item->checkState() == Qt::Checked ? visible = true : visible = false;
        int graphIndex = ui->traceList->indexFromItem(item).row();
        if(ui->mainPlot->graphCount() > graphIndex)
        {
            ui->mainPlot->graph(graphIndex)->setVisible(visible);
            ui->mainPlot->replot();
        }
        //checkDataFromDatabase();
    });
}

void MainWindow::checkDataFromDatabase()
{
    QString current_path = QDir().currentPath();

    QVector<QVector<double>> FinalData;
    QVector<double> x;
    for(int j = 0; j < 6; j++)
    {
        FinalData.push_back(QVector<double>());
    }

    QDirIterator it(current_path + "/database", QDirIterator::Subdirectories);
    QList<QString> files;
    while (it.hasNext())
    {
        QFile f(it.next());
        files.append(f.fileName());
    }
    int graphCount = ui->mainPlot->graphCount();

    for(int i = 0; i < graphCount; i++)
    {
        ui->mainPlot->removeGraph(ui->mainPlot->removeGraph(i));
    }
    for(int i = 0; i < files.length(); i++)
    {
        QString lineNumber = QString::number(ui->lineNumberSpinBox->value());
        if(files[i].contains("line_" + lineNumber + "_"))
        {
            Fileparser parser;
            parser.parse(files[i], ui->startDateTimeEdit->dateTime(), ui->finishDateTimeEdit->dateTime());
            auto data = parser.data_container();

            for(int j = 0; j < data.length(); j++)
            {
                if(data[j].length() == 0)
                {
                    break;
                }
                FinalData[j] += data[j];
            }
            if(parser.times.length() > 0)
            {
                for(int j = 0; j < data[0].length(); j++)
                {
                    x.push_back(parser.times[j].toSecsSinceEpoch());
                }
            }
        }
    }
    QString finalAlarm = "Нет данных для визуализации";
    QList<QString> alarmList;
    QList<QPen> pens = {QPen(Qt::red), QPen(Qt::blue), QPen(Qt::green), QPen(Qt::black), QPen(Qt::cyan), QPen(Qt::darkYellow)};
    for(int i = 0; i < FinalData.length(); i++)
    {
        if(FinalData[i].length() > 0)
        {
            finalAlarm = "";
            bool visibuilyty;
            ui->traceList->item(i)->checkState() == Qt::Checked ? visibuilyty = true : visibuilyty = false;
            ui->mainPlot->addGraph();
            ui->mainPlot->graph(i)->setData(x, FinalData[i]);
            ui->mainPlot->graph(i)->setVisible(visibuilyty);
            ui->mainPlot->graph(i)->setPen(pens[i]);

            if(visibuilyty == true)
            {
                QString alarm = isValidData(i, FinalData[i]);
                if(alarmList.contains(alarm) == false && alarm != "")
                {
                    alarmList.push_back(alarm);
                }
            }
            ui->mainPlot->rescaleAxes();
            ui->mainPlot->replot();
        }
        ui->mainPlot->replot();
    }
    for(QString alarm : alarmList)
    {
        finalAlarm += alarm + "\n";
    }
    if(finalAlarm == "")
    {
        finalAlarm = "Все показания в норме";
    }
    ui->statusLabel->setText(finalAlarm);
}

QString MainWindow::isValidData(int dataType, QVector<double> data)
{
    QString alarm = "";
    switch(dataType)
    {
    case 0:
        for(double value: data)
        {
            if(value > 230)
            {
                alarm = "Температура превышает допустимое значение, уменьшите её";
            }
        }
        break;
    case 1:
        for(double value: data)
        {
            if(value > 1000 || value < 0)
            {
                alarm = "Показания датчик вакуума неисправен, проверьте его";
            }
        }
        break;
    case 2:
        for(double value: data)
        {
            if(value < 0 || value > 400)
            {
                alarm = "Вытягиватели неисправны, проверьте их";
            }
        }
        break;
    case 3:
        for(double value: data)
        {
            if(value > 750)
            {
                alarm = "Показания вакуума превышают допустимое значение, понизьте вакуум";
            }
        }
        break;
    case 4:
        for(double value: data)
        {
            if(value > 100)
            {
                alarm = "Мотор работает на предельных мощностях, остановите линию";
            }
        }
        break;
    case 5:
        for(double value: data)
        {
            if(value > 75000)
            {
                alarm = "Показания вакуума превышают допустимое значение, понизьте вакуум";
            }
        }
        break;
    case 6:
        for(double value: data)
        {
            if(value < 35)
            {
                alarm = "Температура в помещении нижне нормы, проверьте теплоизоляцию помещения";
            }
        }
        break;
    }
    return alarm;
}

void MainWindow::setUserInfo(QString name, QString surname, QString position)
{
    logger.log(LogLevel::LOG_INFO, name.toStdString() + " " +
                                       surname.toStdString() + " " +
                                       position.toStdString() + " working with program");
}

MainWindow::~MainWindow()
{
    logger.log(LogLevel::LOG_INFO, "End work with program");
    delete ui;
}
