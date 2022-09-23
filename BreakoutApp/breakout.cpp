#include <QLabel>
#include <QApplication>

#include "breakout.h"

#define WIDTH   50
#define HEIGHT  12
#define SCR_WIDTH   300
#define SCR_HEIGHT  400

Breakout::Breakout(QWidget *parent)
    : QWidget(parent), xDir(1), yDir(-1)
{
    this->setStyleSheet("QWidget { background-color:gainsboro;}");
    ball = new QLabel(this);
    ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);
    ball->setStyleSheet("QLabel { background-color:black; border-radius: 5px;}");

    paddle = new QLabel(this);
    paddle->setGeometry(SCR_WIDTH*0.7,SCR_HEIGHT*0.9, WIDTH, HEIGHT);
    paddle->setStyleSheet("QLabel { background-color:lightskyblue; border:0.5px groove blue;}");

    QVector<QString> colorSheet;
    colorSheet << "moccasin" << "tan" << "darkseagreen" << "darkolivegreen" << "teal";

    for (int y=0,i=0;y<5;y++)
        for (int x=0; x<6 ; x++,i++)
        {
            bricks[i] = new QLabel(this);
            bricks[i]->setStyleSheet("QLabel {background-color: " + colorSheet[y] + "; border-bottom:0.5px groove black;"
                                                                                    "border-right:0.5px groove black;}");
            bricks[i]->setGeometry(x*WIDTH,y*HEIGHT+30,WIDTH,HEIGHT);
        }

    resize(SCR_WIDTH,SCR_HEIGHT);

    setMouseTracking(true);

    timerId = startTimer(10);
}

void Breakout::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Left:
    {
        int x = paddle->x();
        if (x > 0)
        {
            paddle->move(paddle->x()-MOVE_SPEED, paddle->y());
            if (paddle->x() < 0)
                paddle->move(0, paddle->y());
        }
    }
        break;
    case Qt::Key_Right:
    {
        if (paddle->x() + WIDTH < SCR_WIDTH)
        {
            paddle->move(paddle->x()+MOVE_SPEED, paddle->y());
            if (paddle->x() > SCR_WIDTH - WIDTH)
                paddle->move(SCR_WIDTH-WIDTH, paddle->y());
        }
    }
        break;
    case Qt::Key_Escape:
        qApp->exit();
        break;
    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->pos().x();
    x = (x<0)?0:(x+WIDTH>width())?width()-WIDTH:x;
    paddle->move(x,paddle->y());
}

void Breakout::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    moveObjects();
    checkCollision();
}

void Breakout::moveObjects()
{
    ball->move(ball->x() + xDir, ball->y() + yDir); // xDir +1 // yDir -1

    if ((ball->x() <= 0) || (ball->x()+10 >= SCR_WIDTH)) { xDir *= -1;}

    if (ball->y() <= 0 ) yDir=1;
}

void Breakout::checkCollision()
{
    if (ball->geometry().bottom() > height())   // 공이 아래로 가면 게임 종료
    {
        killTimer(timerId);
        qDebug("Game lost");
    }

    // 남은 블록이 없으면 게임 종료
    int j = 0;
    for (int i = 0; i<NO_OF_BRICKS; i++)
        if (bricks[i]->isHidden()) j++;

    if (j==NO_OF_BRICKS)
    {
        killTimer(timerId);
        qDebug("Victory");
    }

    // 사용자(패들)와 충돌을 처리
    if ((ball->geometry()).intersects(paddle->geometry()))
    {
        int paddleLPos = paddle->geometry().left();
        int ballLPos = ball->geometry().left();

        int first = paddleLPos + 10;
        int second = paddleLPos + 20;
        int third = paddleLPos + 30;
        int fourth = paddleLPos + 40;

        // 패들의 맞은 부분에 따랏 공의 반사되는 방향 조정
        if (ballLPos < first) xDir = -1; yDir = -1;
        if (ballLPos >= first && ballLPos < second) xDir = -1; yDir *= -1;
        if (ballLPos >= second && ballLPos < third) xDir = 0; yDir = -1;
        if (ballLPos >= third && ballLPos < fourth) xDir = 1; yDir *= -1;
        if (ballLPos > fourth) xDir = 1; yDir = -1;
    }

    // 블록의 충돌을 처리
    for (int i=0;i<NO_OF_BRICKS;i++)
    {
        if ((ball->geometry()).intersects(bricks[i]->geometry()))
        {
            int ballLeft = ball->geometry().left();
            int ballHeight = ball->geometry().height();
            int ballWidth = ball->geometry().width();
            int ballTop = ball->geometry().top();

            // 현재 블록의 위치를 계산
            QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft - 1,ballTop);
            QPoint pointTop(ballLeft, ballTop -1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);
            if (!bricks[i]->isHidden()) // 공과 블록의 충돌 검사
            {
                if(bricks[i]->geometry().contains(pointRight)) xDir = -1;
                else if(bricks[i]->geometry().contains(pointLeft)) xDir = 1;

                if(bricks[i]->geometry().contains(pointTop)) yDir = 1;
                else if(bricks[i]->geometry().contains(pointBottom)) yDir = -1;

                bricks[i]->setHidden(true);
            }
        }
    }
}

Breakout::~Breakout()
{
    delete ball;
    delete paddle;

    for(int i = 0; i < NO_OF_BRICKS; i++){
        delete bricks[i];
    }
}

