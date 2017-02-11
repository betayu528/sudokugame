#ifndef SUBWIDGET33
#define SUBWIDGET33

#include <QFrame>


//3 * 3矩阵的底层数据层
class Data33
{
public:
    Data33(int array[9]);
    Data33();
    ~Data33();
    /**
     * @brief 检查3 * 3矩阵的合法性， 只能填入1~9的数字
     * @return bool; true: 合法， false不合法
     */
    bool valid() const;
    void randomGenerate();

    bool operator == (const Data33& other);

    int ** data() {
        return _data;
    }

private:
    void init();

    int **_data;
};


/***
 * 一个小窗件的容器
 * 3*3 的九宫格数据的UI层
 *
 *
 */
class Widget33: public QFrame
{
    Q_OBJECT
public:
    explicit Widget33(QWidget *parent = 0);
    Widget33(Data33 *data);
    ~Widget33();

    void setup();

protected:
    void paintEvent(QPaintEvent *);

private:
    Data33 *_d_data;
};

#endif // SUBWIDGET33

