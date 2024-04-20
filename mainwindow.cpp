#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      plotTime(0.0)
{
    ui->setupUi(this);

    device = new Device(this);
    checked_power = false;
    checked_connectPC = false;
    checked_headsetContact = false;


    series = new QLineSeries();
    chart = new QChart();
    chartView = new QChartView(chart);

    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("EEG Signal Plot");


    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->signalPlotFrame);
    chartView->setFixedSize(910, 350);

    axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    axisX->setRange(0, 6);

    axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    axisY->setRange(-15,15);

    // site combo bbox
    for (int i = 1; i <= EEG_SITES; ++i) {
        ui->sitePlotComboBox->addItem(QString("Site %1").arg(i));
    }


    // Connect First site in combobox's signal to plot
    connect(device->sites[0], &EEGSite::signalGenerated, this, &MainWindow::plotEEGSignal);


    connect(ui->sitePlotComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateSiteToPlot);

    ui->menu->setDisabled(true);
    ui->menuView->setDisabled(true);
    ui->timeAndDateView->setDisabled(true);
    ui->sessionLogsView->setDisabled(true);
    ui->newSessionView->setDisabled(true);
    ui->ComputerView->setDisabled(true);

    // Connections
    //connect(ui->generateSignal, &QPushButton::clicked, this, &MainWindow::on_generateSignal_clicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearGraph);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_power_clicked()
{

    //checked default state: false
    if (checked_power) {
        power_off();
    }
    else {
        if (ui->battery->value() > 0)
        {
            //enable menu and buttons that should be on when turned on
            ui->menuView->setEnabled(true);
            ui->timeAndDateView->setDisabled(true);
            ui->sessionLogsView->setDisabled(true);
            ui->newSessionView->setDisabled(true);
            ui->menu->setEnabled(true);
            checked_power = true;
            std::cout << "checked power is now true" << std::endl;
        }
    }
}

void MainWindow::power_off()    //ONLY turns everything off
{
        //disable menu and buttons that should be off when turning device off
        ui->menuView->setDisabled(true);
        ui->timeAndDateView->setDisabled(true);
        ui->sessionLogsView->setDisabled(true);
        ui->newSessionView->setDisabled(true);
        ui->menu->setDisabled(true);
        ui->sessionBar->setValue(0);
        ui->sessionTimer->setNum(29);
        device->stopSesh();
        checked_power = false;
        std::cout << "checked power is now false" << std::endl;
}


void MainWindow::on_menu_clicked()
{
    //return to menu device view
    ui->menuView->setEnabled(true);
    ui->timeAndDateView->setDisabled(true);
    ui->sessionLogsView->setDisabled(true);
    ui->newSessionView->setDisabled(true);
}


void MainWindow::on_newSession_clicked()
{
    //switch to new session device view
    ui->newSessionView->setEnabled(true);
    ui->menuView->setDisabled(true);
    ui->timeAndDateView->setDisabled(true);
    ui->sessionLogsView->setDisabled(true);

    if (!device->hasContact) {
        ui->play->setDisabled(true);
        //instruct user to get headset and connect. Allow user to press start once connection is logged
        std::cout << "connect your headset to start" << std::endl;
    }
}


void MainWindow::on_sessionLogs_clicked()
{
    QVector<QString> logList = device->readSessionHistory();
    QStringList dateList;
    for (const QString& element : logList) {
        QStringList parts = element.split(';');
        if (parts.size() > 0) {
            QString date = parts.at(0).trimmed();
            dateList.append(date);
        }
    }
    //switch to session logs device view
    ui->sessionLogsView->setEnabled(true);
    ui->menuView->setDisabled(true);
    ui->timeAndDateView->setDisabled(true);
    ui->newSessionView->setDisabled(true);

    //display logs, allow scrolling through the logs
    ui->sessionsLogWidget->blockSignals(true);
    ui->sessionsLogWidget->clear();
    ui->sessionsLogWidget->blockSignals(false);
    ui->sessionsLogWidget->addItems(dateList);
}


void MainWindow::on_setTimeAndDate_clicked()
{
    //switch to time and date device view
    ui->timeAndDateView->setEnabled(true);
    ui->menuView->setDisabled(true);
    ui->sessionLogsView->setDisabled(true);
    ui->newSessionView->setDisabled(true);
}


void MainWindow::on_play_clicked()
{
    //default state: pause (not checked)
    if (!device->getIsSeshPaused()) {
        //TODO: pause session UI
        device->pauseSesh(); // set button ready to play when next clicked
        std::cout << "play\nchecked play is now false" << std::endl;
    }
    else {
        ui->menu->setDisabled(true);
        device->playSesh();    // set button ready to pause when next clicked
        std::cout << "checked play is now true" << std::endl;
    }
}


void MainWindow::on_stop_clicked()
{
    device->stopSesh();
    //TODO: stop session, erase all current session info.
    ui->menuView->setEnabled(true);
    ui->timeAndDateView->setDisabled(true);
    ui->sessionLogsView->setDisabled(true);
    ui->newSessionView->setDisabled(true);
    ui->menu->setEnabled(true);
    std::cout << "session stopped" << std::endl;
}


void MainWindow::on_submitTime_clicked()
{
    //TODO: get info from qtimedate widget, set
    device->setTime(ui->dateTimeEdit->dateTime());
}


void MainWindow::on_connectPc_clicked()
{

    //default state: false (not connected to PC)
    if (checked_connectPC) {
        //disconnect from PC
        ui->ComputerView->setDisabled(true);
        ui->logList->blockSignals(true);
        ui->logList->clear();
        ui->logList->blockSignals(false);
        checked_connectPC = false;  // set button ready to disconnect when next clicked
        std::cout << "checked connect pc is now false\n ready to disconnect" << std::endl;
    }
    else {
        QVector<QString> logs = device->readSessionHistory();
        QStringList dateList;
        for (const QString& element : logs) {
            QStringList parts = element.split(';');
            if (parts.size() > 0) {
                QString date = parts.at(0).trimmed();
                dateList.append(date);
            }
        }
        //connect to PC
        ui->ComputerView->setEnabled(true);

        //dummy list of log dates and times
        ui->logList->blockSignals(true);
        ui->logList->clear();
        ui->logList->blockSignals(false);
        ui->logList->addItems(dateList);   //add list to dropdown

        checked_connectPC = true;   // set button ready to connect when next clicked
        std::cout << "checked connect pc is now true \n ready to connect" << std::endl;
    }
}


void MainWindow::on_maxBattery_clicked()
{
    ui->battery->setValue(100); //set UI battery level
    device->setBattery(100);    //set battery value
}


void MainWindow::on_lowBattery_clicked()
{
    ui->battery->setValue(39);  //set UI battery level
    device->setBattery(39); //set battery value
}


void MainWindow::on_noBattery_clicked()
{
    ui->battery->setValue(0);   //set UI battery level
    device->setBattery(0);  //set battery value
}

void MainWindow::updateBattery(int batteryLevel)    //would be called from Device class to update battery value
{
    ui->battery->setValue(batteryLevel);   //set UI battery level
}


void MainWindow::on_contact_clicked()
{
    if (checked_headsetContact) {
        // Stop signal generation and is no longer in contact
        device->stopContact();

        //set red and blue indicators
        //background-color: rgb(x, y, z);

        checked_headsetContact = false;  // set button ready to connect when next clicked
        std::cout << "checked headset contact is now false\n ready to disconnect" << std::endl;
    }
    else {
        // clear the signal plot first
        clearGraph();

        //set red and blue indicators
        //background-color: rgb(x, y, z);

        // Calling generate signal function in EEGHeadset to test
        device->initiateContact();
        if (ui->newSessionView->isEnabled()) {
            // enable play button
            ui->play->setEnabled(true);
        }
        checked_headsetContact = true; // set button ready to disconnect when next clicked
        std::cout << "checked headset contact is now true\n ready to connect" << std::endl;
    }

}


void MainWindow::on_set_clicked()
{
    ui->battery->setValue(ui->percentage->value());
    device->setBattery(ui->percentage->value());
}


void MainWindow::update_session_timer(int time) {
    ui->sessionTimer->setText(QString::number(MAX_DUR - time));
    ui->sessionBar->setValue(static_cast<int>(time * 100 / MAX_DUR));
}

void MainWindow::plotEEGSignal(double value)
{
    series->append(plotTime, value);

    qreal sampleRate = SAMPLING_RATE;
    plotTime += 1.0 / sampleRate;

    axisX->setRange(0, plotTime);
}

void MainWindow::updateSiteToPlot(int index)
{
    if (index >= 0 && index < device->sites.size())
    {
        currSite = device->sites[index];

        // reset time when switching sites
        plotTime = 0.0;

        connect(currSite, &EEGSite::signalGenerated, this, &MainWindow::plotEEGSignal);
        series->clear();
    }
}

void MainWindow::clearGraph()
{
    // reset time
    plotTime = 0.0;

    series->clear();
}


void MainWindow::on_logList_currentIndexChanged(int index)
{
    QVector<QString> logList = device->readSessionHistory();
    QStringList list = QStringList::fromVector(logList);

    QStringList parts = logList[index].split(';');
    QString date = parts.at(0).trimmed();
    QString beforeBaseline = parts.at(1).trimmed();
    QString afterBaseline = parts.at(2).trimmed();

    QString displayText = "Date + time: "+ date + "\nBaseline before treatment: " + beforeBaseline + "\nBaseline after treatment: " + afterBaseline;

    ui->logView->setText(displayText);
}

void MainWindow::session_ended() {
    ui->menu->setEnabled(true);
    on_menu_clicked();
}
