/**
* Author: by cdhmuer333@126.com
*/

#include "mainwindow.h"
#include "gameboard.h"

#include <QLayout>
#include <QPushButton>
#include <QPalette>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //resize(680, 500);
    srand((unsigned)(time(NULL)));
    setMinimumSize(700, 500);
    setWindowIcon(QIcon(":/images/sudoku.icon"));
    GameBoard * gameBoard = new GameBoard(this);
    connect(gameBoard, SIGNAL(gameOver()), this, SLOT(close()));
    setCentralWidget(gameBoard);
}

MainWindow::~MainWindow()
{
}
