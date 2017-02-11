#include "gameboard.h"
#include "sudokuboard.h"

#include <QLCDNumber>
#include <QGroupBox>
#include <QPushButton>
#include <QLayout>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QComboBox>
#include <QLabel>

GameBoard::GameBoard(QWidget *parent)
    :QWidget(parent)
{
    _iTimeMinute = 0;
    _iTimeSecond = 0;
    setup();
    updateButtonStates();
}

void GameBoard::setup()
{
    _pTimer = new QTimer(this);
    connect(_pTimer, SIGNAL(timeout()), this, SLOT(updateTimeWidget()));

    initCheckBox();

    _showTimeWidget = new QLCDNumber();
    _showTimeWidget->display("00:00:00");

    QVBoxLayout *lcdNumberLayout = new QVBoxLayout;
    lcdNumberLayout->addWidget(_showTimeWidget);
    lcdNumberLayout->setSpacing(0);
    QGroupBox *lcdNumberGroup = new QGroupBox;
    lcdNumberGroup->setLayout(lcdNumberLayout);
    lcdNumberGroup->setTitle("计时器");

    QVBoxLayout *levelLayout = new QVBoxLayout;
    levelLayout->addWidget(_levelCheckBox);
    QGroupBox *levelGroup = new QGroupBox;
    levelGroup->setTitle("难度选择");
    levelGroup->setLayout(levelLayout);

    _sudoku_board = new SudokuBoard();
    _resetGameButton = new QPushButton(tr("重置游戏"));
    _startGameButton = new QPushButton(tr("开始游戏"));
    _submitButon = new QPushButton("完成提交");
    _clearAnswerButton = new QPushButton("清除答案");
    _suspendButton = new QPushButton("暂停游戏");
    _logoutButton = new QPushButton("退出游戏");

    connect(_resetGameButton, SIGNAL(clicked()), _sudoku_board, SLOT(resetData()));
    connect(_resetGameButton, SIGNAL(clicked()), this, SLOT(updateTimer()));
    connect(_startGameButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(_submitButon, SIGNAL(clicked()), this, SLOT(finished()));
    connect(_clearAnswerButton, SIGNAL(clicked()), this, SLOT(clearAnswer()));
    connect(_suspendButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(_logoutButton, SIGNAL(clicked()), this, SLOT(logout()));

    QHBoxLayout *mainLayout = new QHBoxLayout;

    QGroupBox *buttonsBox = new QGroupBox;
    buttonsBox->setTitle("游戏控制");
    QGridLayout *buttonsLayout = new QGridLayout;
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->addWidget(_startGameButton, 0, 0);
    buttonsLayout->addWidget(_suspendButton, 0, 1);
    buttonsLayout->addWidget(_clearAnswerButton, 1, 0);
    buttonsLayout->addWidget(_submitButon, 1, 1);
    buttonsLayout->addWidget(_resetGameButton, 2, 0);
    buttonsLayout->addWidget(_logoutButton, 2, 1);
    buttonsBox->setLayout(buttonsLayout);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->setMargin(12);
    leftLayout->setSpacing(10);

    leftLayout->addWidget(lcdNumberGroup);

    leftLayout->addWidget(createSeperator());
    leftLayout->addWidget(levelGroup);

    leftLayout->addWidget(createSeperator());
    leftLayout->addWidget(buttonsBox);

    mainLayout->addWidget(_sudoku_board, Qt::AlignJustify);
    mainLayout->addLayout(leftLayout, Qt::AlignRight);

    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    setLayout(mainLayout);
}

void GameBoard::initCheckBox()
{
    _levelCheckBox = new QComboBox();
    _levelCheckBox->setToolTip("选择难度");
    _levelCheckBox->addItems(QStringList() << "初级" << "中等" << "高级"
                             << "大师" << "骨灰");
    connect(_levelCheckBox, SIGNAL(currentIndexChanged(int)), this, SLOT(switchLevel()));
}

void GameBoard::start()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) {
        return;
    }

    if (button->text() == "再来一局") {
        emit _resetGameButton->clicked();
    }

    _pTimer->start();
    _pTimer->setInterval(1000);
    _sudoku_board->setEnabled(true);
    updateButtonStates();
}

void GameBoard::stop()
{
    _pTimer->stop();
    _startGameButton->setText("继续游戏");
    updateButtonStates();
    _sudoku_board->setEnabled(false);
}

void GameBoard::updateTimeWidget()
{
    QString strTime = QString(":");
    strTime.push_front(QString(_iTimeMinute % 10 + '0'));
    strTime.push_front(QString((_iTimeMinute % 100) / 10 + '0'));
    strTime.push_back(QString((_iTimeSecond % 100) / 10 + '0'));
    strTime.push_back(QString(_iTimeSecond % 10 + '0'));
    _showTimeWidget->display(QString(strTime));
    _iTimeSecond++;
    if (_iTimeSecond >= 60) {
        _iTimeSecond = 0;
        _iTimeMinute++;
        if(_iTimeMinute >= 60) {
            _iTimeMinute = 0;
        }
    }
}

void GameBoard::updateTimer()
{
    _iTimeMinute = 0;
    _iTimeSecond = 0;
}

void GameBoard::finished()
{
    if (_sudoku_board->checkAnswer()) {
        QMessageBox::information(this, "过关", "恭喜你，答对了!", QMessageBox::Ok);
        _pTimer->stop();
        _startGameButton->setText("再来一局");
        _startGameButton->setEnabled(true);
        updateButtonStates();
    } else {
        QMessageBox::information(this, "失败", "不对哦, 再试试看", QMessageBox::Ok);
    }
}

void GameBoard::clearAnswer()
{
    _sudoku_board->clearAnswer();
}


void GameBoard::switchLevel()
{
    int index = _levelCheckBox->currentIndex();
    switch(index) {
    case 0:
        _sudoku_board->setLevel(SudokuBoard::Easy);
        break;
    case 1:
        _sudoku_board->setLevel(SudokuBoard::Middle);
        break;
    case 2:
        _sudoku_board->setLevel(SudokuBoard::Hard);
        break;
    case 3:
        _sudoku_board->setLevel(SudokuBoard::Master);
        break;
    case 4:
        _sudoku_board->setLevel(SudokuBoard::SuperMaster);
        break;
    default:
        break;
    }
}

void GameBoard::updateButtonStates()
{
    if (_pTimer->isActive()) {
        _startGameButton->setEnabled(false);
        _suspendButton->setEnabled(true);
    } else {
        _startGameButton->setEnabled(true);
        _suspendButton->setEnabled(false);
    }
    //_resetGameButton->setEnabled(_suspendButton->isEnabled());
    _clearAnswerButton->setEnabled(_suspendButton->isEnabled());
}

QFrame* GameBoard::createSeperator()
{
    QFrame *splitLine = new QFrame;
    splitLine->setFrameShape(QFrame::HLine);
    splitLine->setFrameShadow(QFrame::Sunken);
    return splitLine;
}

void GameBoard::logout() {
    if ((QMessageBox::information(this, "提示", "你确定要退出游戏吗?",
            QMessageBox::Ok | QMessageBox::Cancel))
        == QMessageBox::Ok) {
        emit gameOver(); //发出一个游戏终止的信号， 通知主窗口
    }
}
