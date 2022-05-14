#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "littlecomputer.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LC = nullptr;
    ui->splitter->setStretchFactor(0,7);
    ui->splitter->setStretchFactor(1,2);
    ui->plainTextEdit_console->setStyleSheet("QPlainTextEdit {background-color: black; color: white;}");
    setCentralWidget(ui->splitter);
//    QScrollBar *sb = ui->plainTextEdit_console->verticalScrollBar();
//    sb->setValue(sb->maximum());
}

MainWindow::~MainWindow()
{
    delete ui;

    if(LC != nullptr)
        delete LC;
}



void MainWindow::onPrintConsole(QString str)
{
    ui->plainTextEdit_console->insertPlainText(str);
}

void MainWindow::onClearConsole()
{
    ui->plainTextEdit_console->setPlainText("");
}


void MainWindow::on_actionRun_triggered()
{
    if(LC != nullptr)
    {
        LC->terminate();    // close thread forcefully
        LC->wait();         // wait for closing
        delete LC;          // clear memory
    }

    LC = new LittleComputer(ui->plainTextEdit_code->toPlainText());
    QObject::connect(LC, SIGNAL(printConsol(QString)), this, SLOT(onPrintConsole(QString)));
    QObject::connect(LC, SIGNAL(clearConsol()), this, SLOT(onClearConsole()));
    LC->start();
}


//void MainWindow::on_actionHello_world_triggered()
//{
//    QString hello("#Hello World Example\n"
//                  "PRINT \"Hello\"\n"
//                  "PRINT SPACE\n"
//                  "PRINT \"world!\"");

//    ui->plainTextEdit_code->setPlainText(hello);
//}


//void MainWindow::on_actionTimer_triggered()
//{
//    QString timerCode("#Timer Example\n"
//                      "_timerLoop_\n"
//                      "SLEEP\n"
//                      "CLEAR\n"
//                      "ADD A 1\n"
//                      "PRINT A\n"
//                      "JMP _timerLoop_");

//    ui->plainTextEdit_code->setPlainText(timerCode);

//}


void MainWindow::on_actionAbort_triggered()
{
    if( LC != nullptr)
    {
        LC->terminate();    // close thread forcefully
        LC->wait();         // wait for closing
        delete LC;          // clear memory
        LC = nullptr;
    }

}



