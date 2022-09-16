#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>

class QAction;

class QtEditor : public QMainWindow
{
    Q_OBJECT

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void printFile();

private:
    //QAction *makeAction(QString icon,QString name, QString shortCut, QString toolTip, QObject *recv, const char* slot);

    template <typename T>
    QAction* makeAction(QString icon, QString text, T shortCut,
                        QString toolTip, QObject* rect, const char* slot);

    template <typename T, typename Functor>
    QAction* makeAction(QString icon, QString text, T shortCut,
                        QString toolTip, Functor lambda);

    template <>
    QAction* makeAction(QString icon, QString text,
                                  const char* shortCut, QString toolTip,
                                  QObject* recv, const char* slot);
};
#endif // QTEDITOR_H
