#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QRect>

class QLabel;

class Breakout : public QWidget
{
    Q_OBJECT

public:
    Breakout(QWidget *parent = nullptr);
    ~Breakout();

    //bool QRect::intersects(const QRect &rectangle) const;

protected:
    static const int MOVE_SPEED = 15;

    /// 공의 이동 ///
    int timerId;
    int xDir, yDir;
    void timerEvent(QTimerEvent *);
    void moveObjects();

    /// 패들 충돌 처리 ///
    void checkCollision();

protected slots:
    void keyPressEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent *e);

    ///// 공의 이동 ////
//    void timerEvent(QTimerEvent *);
//    void moveObjects();

private:
    static const int NO_OF_BRICKS = 30;

    QLabel *ball;
    QLabel *paddle;
    QLabel *bricks[NO_OF_BRICKS];



};
#endif // BREAKOUT_H
