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
    resize(420, 420);
    _blankGridNum = 15; // default setting
    _sudoku = new Sudoku();
    setEnabled(false);  // 点开始游戏之后才能填入数字
    setToolTip(QStringLiteral("请点击开始游戏, 开始挑战"));
    _glayout = NULL;
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
    _items.clear();
    _groups.clear();
    _glayout = new QGridLayout;

    for (int i = 0; i < 9; ++i) {
        QGroupBox* group = new QGroupBox;
        QGridLayout *layout = new QGridLayout;
        layout->setContentsMargins(0, 0, 0, 0);
        group->setLayout(layout);
        _glayout->addWidget(group, i / 3 * 3, i % 3 * 3, 3, 3);
        _groups.append(group);
    }
    _glayout->setSpacing(1);

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            ItemWidget *w = new ItemWidget(_going_data[i][j]);
            _items.append(w);
            int pos = i / 3 * 3 + j / 3; //计算所属的3 * 3 方框在列表group中的索引

            QGridLayout *layout = qobject_cast<QGridLayout*>(_groups[pos]->layout());
            if (!layout) {
                qDebug() << "internal error!";
                continue;
            }

            layout->addWidget(w, i % 3, j % 3);
        }
    }
    _current = _items.begin();
    setLayout(_glayout);
}


ItemWidget* SudokuBoard::nextItemWidget() {
    if (_current == _items.end()) {
        _current = _items.begin();
        return nullptr;
    }
    return *(_current++);
}

void SudokuBoard::resetData()
{
    initData();
    updateItems();
}

void SudokuBoard::updateItems()
{
    int index = 0;
    foreach(ItemWidget *w, _items) {
        if (!w) {
            qDebug() << "Error, invalid pointers";
            ++index;
            continue;
        }
        w->setValue(_going_data[index / 9][index % 9], true);
        ++index;
    }
}

bool SudokuBoard::checkAnswer()
{
    int index = 0;
    foreach(ItemWidget *w, _items) {
        if (!w) {
            qDebug() << "Error, invalid pointers";
            ++index;
            continue;
        }
        _going_data[index / 9][index % 9] = w->text().toInt();
        ++index;
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


void SudokuBoard::keyPressEvent(QKeyEvent *ev) {
    int key = ev->key();
    qDebug() << key;
    if (_current != _items.end()) {
        (*_current)->setFocusPolicy(Qt::StrongFocus);
        (*_current)->setFocus();
    }
    switch (key) {
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        (*_current)->setText(QString::number(key - '0'));
        break;
    case Qt::Key_Delete:

        (*_current)->setText(QString(""));
        break;
    case Qt::Key_Escape:
        setFocus(Qt::TabFocusReason);
        break;
    case Qt::Key_Alt :
        //find next empty brick
        ItemWidget *last_w = *_current;
        QPalette p = last_w->palette();
        while (true) {
            ItemWidget *w = nextItemWidget();
            if (!w) {
                break;
            }
            if (w->text().isEmpty()) {
                w->setEditable(true);
                w->setFocus();
                w->setStyleSheet("background:yellow");
                break;
            }
            last_w->setPalette(p);
            last_w = w;
        }
        break;
    }
}

void SudokuBoard::clearAnswer()
{
    _sudoku->copyArray(_raw_data, _going_data);
    updateItems();
}
