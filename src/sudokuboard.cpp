/**
* Author: by cdhmuer333@126.com
*/
#include "sudokuboard.h"
#include "sudoku.h"
#include "itemwidget.h"

#include <QLayout>
#include <QPushButton>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QGroupBox>


SudokuBoard::SudokuBoard(QWidget *parent)
    :QFrame(parent)
{
    //setStyleSheet("Board{background-color:rgb(148,248,255);;border:true;}")
    resize(380, 380);
    _blankGridNum = 20; // default setting
    _sudoku = new Sudoku();
    setEnabled(false);  // 点开始游戏之后才能填入数字
    setToolTip(QStringLiteral("请选择难度开始游戏"));
    _glayout = NULL;
    setMouseTracking(true);
    init();
}

SudokuBoard::~SudokuBoard()
{
    delete _sudoku;
}

void SudokuBoard::initData()
{
    _sudoku->makeLevel(_raw_data, _blankGridNum);
    _sudoku->copyArray(_raw_data, _going_data);
}

void SudokuBoard::init()
{
    initData();
    _itemsArray.clear();
    _curPos = QPair<int, int>(0, 0);

    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignCenter);
    layout->setMargin(0);

    _itemsArray = QVector<QVector<ItemWidget*>>(9, QVector<ItemWidget*>(9));

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            ItemWidget *w = new ItemWidget(_raw_data[i][j]);
            _itemsArray[i][j] = w;
            layout->addWidget(w, i, j);
        }
    }
    setLayout(layout);
}


void SudokuBoard::resetData()
{
    initData();
    updateItems();
}

void SudokuBoard::updateItems()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0;j < 9; ++j) {
            _itemsArray[i][j]->setValue(_going_data[i][j]);
        }
    }
}

bool SudokuBoard::checkAnswer()
{

    for (int i = 0; i < 9; ++i) {
        for (int j = 0;j < 9; ++j) {
            _going_data[i][j] = _itemsArray[i][j]->text().toInt();
        }
    }

    return _sudoku->checkSolution(_going_data);
}

void SudokuBoard::setLevel(Level level)
{
    switch (level) {
    case Easy:
        _blankGridNum = 20;
        break;
    case Middle:
        _blankGridNum = 30;
        break;
    case Hard:
        _blankGridNum = 45;
        break;
    case Master:
        _blankGridNum = 60;
        break;
    case SuperMaster:
        _blankGridNum = 64;
        break;
    default:
        _blankGridNum = 15;
        break;
    }
}

void SudokuBoard::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
}

ItemWidget* SudokuBoard::upItemWidget() {
    _curPos.first -= 1;
    if (_curPos.first < 0)
        _curPos.first = 8;

    return currentWidget();
}

ItemWidget* SudokuBoard::downItemWidget()
{
    _curPos.first += 1;
    if (_curPos.first > 8)
        _curPos.first = 0;
    return currentWidget();
}

ItemWidget* SudokuBoard::leftItemWidget() {
    _curPos.second -= 1;
    if (_curPos.second < 0)
        _curPos.second = 8;
    return currentWidget();
}

ItemWidget* SudokuBoard::rightItemWidget(){
    _curPos.second += 1;
    if (_curPos.second > 8) {
        _curPos.second = 0;
    }
    return currentWidget();
}

ItemWidget* SudokuBoard::nextItemWidget(){
    QPair<int, int> pos;
    pos.second = _curPos.second + 1;
    pos.first = _curPos.first;
    if (pos.second > 8) {
        pos.second = 0;
        pos.first += 1;
        if (pos.first > 8) {
            pos.first = 0;
        }
    }

    _curPos = pos;
    return currentWidget();
}

ItemWidget* SudokuBoard::currentWidget() {
    return _itemsArray[_curPos.first][_curPos.second];
}

void SudokuBoard::keyPressEvent(QKeyEvent *ev) {
    int key = ev->key();
    qDebug() << key;

    ItemWidget * current = currentWidget();

    current->setFocusPolicy(Qt::StrongFocus);
    current->setFocus();


    switch (key) {
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        current->setText(QString::number(key - '0'));
        break;
    case Qt::Key_Delete:
        current->setText(QString(""));
        break;
    case Qt::Key_Escape:
        setFocus(Qt::TabFocusReason);
        break;
    case Qt::Key_Up:
        upItemWidget()->setFocus(Qt::MouseFocusReason);
        break;

    case Qt::Key_Left:
        leftItemWidget()->setFocus(Qt::TabFocusReason);
        break;

    case Qt::Key_Down:
        downItemWidget()->setFocus(Qt::TabFocusReason);
        break;

    case Qt::Key_Right:
        rightItemWidget()->setFocus(Qt::TabFocusReason);
        break;

    case Qt::Key_Alt :
        //find next empty brick
        ItemWidget *last_w = current;
        QPalette p = last_w->palette();

        ItemWidget *it = nextItemWidget();
        while (it != nullptr && it != current) {

            if (!it) {
                break;
            }
            if (it->text().isEmpty()) {
                it->setEditable(true);
                it->setFocus();
                it->setStyleSheet("background:blue");
            }
            last_w->setPalette(p);
            last_w = it;
            it = nextItemWidget();
        }
        break;
    }
}

void SudokuBoard::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    qDebug() << pos.x() << pos.y();

   // QGridLayout* mainLayout = qobject_cast<QGridLayout*>(this->layout());
   // mainLayout->itemAtPosition();
}

void SudokuBoard::clearAnswer()
{
    _sudoku->copyArray(_raw_data, _going_data);
    updateItems();
}
