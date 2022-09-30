#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QMainWindow>

namespace Ui {
class ClientManager;
}

class ClientManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientManager(QWidget *parent = nullptr);
    ~ClientManager();

private:
    Ui::ClientManager *ui;
};

#endif // CLIENTMANAGER_H
