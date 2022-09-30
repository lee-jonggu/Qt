#include "clientmanager.h"
#include "ui_clientmanager.h"

ClientManager::ClientManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientManager)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 300 << 660;
    ui->splitter->setSizes(sizes);
}

ClientManager::~ClientManager()
{
    delete ui;
}
