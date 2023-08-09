#ifndef BOARD
#define BOARD

#include <QFrame>

class QGroupBox;
class QGridLayout;
class ItemWidget;
class Sudoku;
class SudokuBoard : public QFrame
{
    Q_OBJECT
public:
    enum Level {
        Easy,
        Middle,
        Hard,
        Master,
        SuperMaster
    };
    typedef QList<ItemWidget*> Items;
    typedef QVector<QGroupBox*> Groups;
    SudokuBoard(QWidget *parent = 0);
    ~SudokuBoard();

    void setLevel(Level level);
    bool checkAnswer();
    void clearAnswer();
protected:
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);

private slots:
    void resetData();
    void updateItems();

private:
    void init();
    ItemWidget* nextItemWidget();

    void initData();


    int _blankGridNum;
    int _raw_data[9][9];  //原始题目的数据
    int _going_data[9][9];  //正在解答的数据

    QGridLayout *_glayout;
    Groups _groups;
    Items _items;
    Items::iterator _current;

    Sudoku *_sudoku;
    Level _cur_level;
};

#endif // BOARD

