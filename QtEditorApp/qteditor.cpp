#include "qteditor.h"
#include <QApplication>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QFontComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QStatusBar>

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{

    /////////////////////////////////////////// Status Bar ///////////////////////////////////////////
    QStatusBar *statusbar=statusBar();
    QLabel* statusLabel = new QLabel("Qt Editor",statusbar);
    statusLabel->setObjectName("StatusLabel");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started",15000);


    ////////////////////////////////////////// TextEdit, MenuBar //////////////////////////////////////////////

    QTextEdit *textedit = new QTextEdit(this);  // textEdit 객체 생성, 부모를 this로만 받으면 레이아웃이 안됨
    setCentralWidget(textedit);                 // 중앙영역위젯을 사용해야 화면 전체가 레이아웃 된다

                                                // 메뉴바를 여러 형식으로 만들 경우 인스턴스 생성 후 만드는게 좋다
//    QMenuBar *menubar = new QMenuBar(this);   // 클래스 인스턴스 생성 후
//    setMenuBar(menubar);                      // 클래스의 setMenuBar 메소드 호출해서 사용

                                                // 일반적으로는 한줄로 끝내는게 좋다
    QMenuBar *menubar = this->menuBar();        // 클래스에서 제공하는 메뉴바를 반환받아 사용하는 방식

    /////////////////////////////////////////////////////// File Menu ///////////////////////////////////////////////////////

    //    QAction *newAct = new QAction(QIcon("new1.png"),"&New",this);       // new 액션 객체 생성
    //    newAct->setShortcut(tr("Ctrl+N"));                                  // tr("Ctrl+N") - 컨트롤+N으로 트리거 발생
    //    newAct->setStatusTip(tr("make new file"));                          // 상태창에서 표시
    //    connect(newAct,SIGNAL(triggered()),SLOT(newFile()));                // 컨트롤+N을 눌렀을 때 시그널 슬롯 연결

    //    QAction *quitAct = new QAction(QIcon("quit.png"),"&Quit",this);     // quit 액션 객체 생성
    //    connect(quitAct,SIGNAL(triggered()),qApp,SLOT(quit()));             // quit 버튼 눌렀을 때 시그널 슬롯 연결, quit은 메인위젯에서 수행
    //    quitAct->setShortcut(tr("Ctrl+Q"));                                 // tr("Ctrl+Q") - 컨트롤+Q로 트리거 발생



    ////////////// File 메뉴 Action 구현
    QAction *newAct = makeAction("new1.png","&New",tr("ctrl+N"),          // 아이콘을 사용하지 않을 경우 "" 입력
                                 tr("make new file"),this,SLOT(newFile()));
    QAction *openAct = makeAction("open1.png","&Open",tr("ctrl+O"),
                                  tr("open a file"),this,SLOT(openFile()));
    QAction *saveAct = makeAction("save1.png","&Save",tr("ctrl+S"),
                                  tr("save this file"),this,SLOT(saveFile()));
    QAction *saveAsAct = makeAction("saveAs.png","Save &as...",tr("Ctrl+Shift+S"),
                                    tr("other name save this program"),this,SLOT(saveAsFile()));
    QAction *printAct = makeAction("print.png","&Print",tr("ctrl+P"),
                                   tr("print this program"),this,SLOT(printFile()));
    QAction *quitAct = makeAction("quit.png","&Quit",tr("ctrl+Q"),
                                  tr("quit this program"),qApp,SLOT(quit()));

    QMenu *fileMenu = menubar->addMenu("&File");                        // 메뉴바에 메뉴 추가
    fileMenu->addAction(newAct);                                        // newAct에 대한 액션 추가
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();                                           // 메뉴바에 구분선 생성
    fileMenu->addAction(quitAct);


    //////////// File Menu Tool Bar
    QToolBar *fileToolBar = addToolBar("&File");

    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);       // 툴바스타일-> 아이콘,텍스트,아이콘옆텍스트,아이콘아래텍스트
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(saveAsAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(printAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);
    addToolBarBreak();          // ToolBar 줄 바꿈


    ///////////// Font, FontSize
    QFontComboBox *fontComboBox = new QFontComboBox(this);
    connect(fontComboBox,SIGNAL(currentFontChanged(QFont)),textedit,SLOT(setCurrentFont(QFont)));

    QDoubleSpinBox *sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox,SIGNAL(valueChanged(double)),textedit,SLOT(setFontPointSize(qreal)));

    /////////////////////////////////////////////////////// Edit Menu ///////////////////////////////////////////////
    QMenu *editMenu = menubar->addMenu("&Edit");

    QAction *undoAct = makeAction("undo.png","&Undo",tr("Ctrl+Z"),tr("Undo"),textedit,SLOT(undo()));
    QAction *redoAct = makeAction("redo.png","&Redo",tr("ctrl+Y"),tr("Redo"),textedit,SLOT(redo()));
    QAction *copyAct = makeAction("copy1.png","&Copy",tr("ctrl+C"),tr("text copy"),textedit,SLOT(copy()));
    QAction *cutAct = makeAction("cut1.png","Cu&t",tr("ctrl+X"),tr("text cut"),textedit,SLOT(cut()));
    QAction *pasteAct = makeAction("paste1.png","&Paste",tr("ctrl+V"),tr("text paste"),textedit,SLOT(paste()));
    QAction *zoomInAct = makeAction("zoomin.png","zoom&In",tr("ctrl+]"),tr("zoomIn"),textedit,SLOT(zoomIn()));
    QAction *zoomOutAct = makeAction("zoomout.png","zoom&Out",tr("ctrl+["),tr("zoomOut"),textedit,SLOT(zoomOut()));

    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(copyAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(zoomInAct);
    editMenu->addAction(zoomOutAct);

    QToolBar *editToolBar = addToolBar("&Edit");
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addSeparator();
    editToolBar->addAction(copyAct);
    editToolBar->addAction(cutAct);
    editToolBar->addAction(pasteAct);
    editToolBar->addSeparator();
    editToolBar->addAction(zoomInAct);
    editToolBar->addAction(zoomOutAct);

    addToolBarBreak();          // editToolBar 만들고 줄 바꿈

    //////// Font , Font Size Tool Bar 출력
    QToolBar *formatToolbar = addToolBar("&Format");
    formatToolbar->addSeparator();
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);

    ///////////////////////////////////// Format Menu //////////////////////////////////////
    QMenu *formatMenu = menubar->addMenu("&Format");

    QMenu *alignMenu = formatMenu->addMenu(QIcon("align.png"),"&Align");

    //QAction *alignCenterAct = new QAction("&Center",this);
    //alignMenu->addAction(alignCenterAct);
//    QAction *alignLeftAct = new QAction("&Left",this);
//    alignMenu->addAction(alignLeftAct);
//    QAction *alignRightAct = new QAction("&Right",this);
//    alignMenu->addAction(alignRightAct);
//    QAction *alignJustifyAct = new QAction("&Justify",this);
//    alignMenu->addAction(alignJustifyAct);

//    connect(alignCenterAct , &QAction::triggered, this, [=]{ textedit->setAlignment(Qt::AlignCenter);});;
//    connect(alignLeftAct, &QAction::triggered,this,[=]{ textedit->setAlignment(Qt::AlignLeft);});
//    connect(alignRightAct, &QAction::triggered,this,[=]{ textedit->setAlignment(Qt::AlignRight);});
//    connect(alignJustifyAct, &QAction::triggered,this,[=]{ textedit->setAlignment(Qt::AlignJustify);});

    QAction *alignCenterAct = makeAction("center.png", tr("&Center"), tr("Ctrl+Shift+M"),
                                  tr("Center"), [=]{ textedit->setAlignment(Qt::AlignCenter);});
    QAction *alignLeftAct = makeAction("left.png", tr("&Left"), tr("Ctrl+Shift+L"),
                                  tr("left"), [=]{ textedit->setAlignment(Qt::AlignLeft);});
    QAction *alignRightAct = makeAction("right.png", tr("&Right"), tr("Ctrl+Shift+R"),
                                  tr("right"), [=]{ textedit->setAlignment(Qt::AlignRight);});
    QAction *alignJustifyAct = makeAction("justify.png", tr("&Justify"), tr("Ctrl+Shift+J"),
                                  tr("justify"), [=]{ textedit->setAlignment(Qt::AlignJustify);});

    alignMenu->addAction(alignCenterAct);
    alignMenu->addAction(alignLeftAct);
    alignMenu->addAction(alignRightAct);
    alignMenu->addAction(alignJustifyAct);

    QToolBar *alignToolbar = addToolBar("&Align");
    alignToolbar->addAction(alignCenterAct);
    alignToolbar->addAction(alignLeftAct);
    alignToolbar->addAction(alignRightAct);
    alignToolbar->addAction(alignJustifyAct);

    QMenu *windowMenu = menubar->addMenu("&Window");
    windowMenu->addAction(fileToolBar->toggleViewAction());
    windowMenu->addAction(formatToolbar->toggleViewAction());
}

// 헤더파일에서 선언한 makeAction 함수 구현
//QAction *QtEditor::makeAction(QString icon,QString name, QString shortCut, QString toolTip, QObject *recv, const char* slot)
//{
//    QAction *act = new QAction(name,this);          // 액션 객체 생성
//    if(icon.length())                               // 아이콘이 존재한다면(파일명이 있으면), 존재하지않으면 아이콘은 빈 아이콘으로 들어감
//        act->setIcon(QIcon(icon));                  // 아이콘 변경
//    act->setShortcut(shortCut);                     // 단축키 설정
//    act->setStatusTip(toolTip);                     // 툴팁 상태 표시
//    connect(act,SIGNAL(triggered()),recv,slot);     // act 실행 됐을 때 시그널과 슬롯 연결
//    return act;
//}

template <typename T>
QAction *QtEditor::makeAction(QString icon, QString text, \
                              T shortCut, QString toolTip, \
                              QObject* recv, const char* slot)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
        act->setIcon(QIcon(icon));
    act->setShortcut(shortCut); // setShortcut 의 반환형은 QString
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered( )), recv, slot);
    return act;
}

// 템플릿 함수는 오버로딩이 안된다
//////////////////////////////템플릿의 특수화 ////////////////////////
template <>
QAction *QtEditor::makeAction(QString icon, QString text, \
                              const char* shortCut, QString toolTip, \
                              QObject* recv, const char* slot)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
        act->setIcon(QIcon(icon));
    act->setShortcut(QString(shortCut));   // setShortcut 의 반환형은 QString
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered( )), recv, slot);
    return act;
}
/////////////////////////////////////////////////////////////////////

template <typename T, typename Functor>
QAction* QtEditor::makeAction(QString icon, QString text, T shortCut,
                              QString toolTip, Functor lambda)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
         act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    act->setToolTip(toolTip);
    connect(act, &QAction::triggered, this, lambda);
    return act;
}

void QtEditor::newFile()
{
    qDebug("Make New File");
}
void QtEditor::openFile()
{
    qDebug("Open a File");
}
void QtEditor::saveFile()
{
    qDebug("Save this File");
}
void QtEditor::saveAsFile()
{
    qDebug("Other of name save this File");
}
void QtEditor::printFile()
{
    qDebug("print this File");
}
QtEditor::~QtEditor()
{
}

