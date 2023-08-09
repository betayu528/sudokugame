#ifndef GAMEBOARD
#define GAMEBOARD

#include <QWidget>

class QGroupBox;
class QPushButton;
class QLCDNumber;
class SudokuBoard;
class QComboBox;
class QFrame;
class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = 0);

Q_SIGNALS:
    void gameOver();

private slots:
    void setup(); //
    void start();
    void stop();
    void updateTimeWidget();
    void finished();
    void updateTimer();
    void clearAnswer();
    void switchLevel();
    void updateButtonStates();
    void logout();

private:
    void initCheckBox();
    QFrame *createSeperator();

    QPushButton *_resetGameButton;
    QPushButton *_startGameButton;
    QPushButton *_submitButon;
    QPushButton *_clearAnswerButton;
    QPushButton *_suspendButton;
    QPushButton *_logoutButton;

    QTimer *_pTimer;
    SudokuBoard * _sudoku_board;
    QLCDNumber *_showTimeWidget;

    QComboBox *_levelCheckBox;
    int _iTimeSecond;
    int _iTimeMinute;
};

#endif // GAMEBOARD

