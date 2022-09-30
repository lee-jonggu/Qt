#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientManager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ClientManager *clientManager = new ClientManager(this);
    ui->tabWidget->addTab(clientManager,"&Client Info");
}

MainWindow::~MainWindow()
{
    delete ui;
}

