#define private public
#include <QString>
#include <QtTest>
#include <stdio.h>

#include "sudoku.cpp"

class SudokutestTest : public QObject
{
    Q_OBJECT
public:
    SudokutestTest(){}

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testIsvalidOfArray();
    void testCheckSolution();
    void testInitialize();
    void testGetSolution();
    void testGenRandom();

    void testNextAndPrevious();

private:
    Sudoku *_inst;
};

void SudokutestTest::initTestCase()
{
    _inst = new Sudoku();
}

void SudokutestTest::cleanupTestCase()
{
    delete _inst;
}

void SudokutestTest::testIsvalidOfArray()
{
    int array1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    QVERIFY(_inst->isvalidOfArray(array1) == true);
    int array2[9] = {1, 2, 7, 4, 5, 6, 7, 8, 9};
    QVERIFY(_inst->isvalidOfArray(array2) == false);
    int array3[9] = {1, 2, 3, 4, 5, 6, 7, 3, 9};
    QVERIFY(_inst->isvalidOfArray(array3) == false);
}

void SudokutestTest::testCheckSolution()
{
    int array1[9][9] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
    };
    QVERIFY(_inst->checkSolution(array1) == false);
    int array2[9][9] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {4, 5, 6, 7, 8, 9, 1, 2, 3},
        {7, 8, 9, 1, 2, 3, 4, 5, 6},
        {2, 3, 4, 5, 6, 7, 8, 9, 1},
        {5, 6, 7, 8, 9, 1, 2, 3, 4},
        {8, 9, 1, 2, 3, 4, 5, 6, 7},
        {3, 4, 5, 6, 7, 8, 9, 1, 2},
        {6, 7, 8, 9, 1, 2, 3, 4, 5},
        {9, 1, 2, 3, 4, 5, 6, 7, 8},
    };
    QVERIFY(_inst->checkSolution(array2) == true);

    int array3[9][9] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {4, 5, 6, 7, 8, 9, 1, 2, 3},
        {7, 8, 9, 1, 2, 3, 4, 5, 6},
        {2, 3, 4, 5, 6, 7, 8, 9, 1},
        {5, 6, 7, 8, 9, 1, 2, 3, 4},
        {8, 9, 1, 7, 3, 4, 5, 6, 7},
        {3, 4, 5, 6, 7, 8, 9, 1, 2},
        {6, 7, 8, 9, 1, 2, 3, 4, 5},
        {9, 1, 2, 3, 4, 5, 6, 7, 8},
    };
    QVERIFY(_inst->checkSolution(array3) == false);
}

void SudokutestTest::testInitialize()
{
    int cc[9][9] = {0};
    _inst->initialize(cc);
    QVERIFY(_inst->checkSolution(cc) == true);

    int dd[9][9] = {0};
    _inst->initialize(dd);
    QVERIFY(_inst->checkSolution(dd) == true);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            printf("  %d", dd[i][j]);
        }
        printf("\n");
    }
}

void SudokutestTest::testGetSolution()
{
    int data[9][9] = {
        {8, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 0, 0, 0, 2, 0, 0, 0, 3},
        {0, 3, 0, 0, 5, 0, 0, 7, 0},
        {0, 0, 5, 0, 0, 0, 4, 0, 0},
        {0, 0, 4, 5, 0, 9, 6, 0, 0},
        {0, 0, 0, 8, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 4, 6, 0, 0, 0, 8, 2, 0},
        {0, 2, 0, 3, 0, 5, 0, 9, 0}
    };
    int solution[9][9];
    bool res = _inst->getSolution(data, solution);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            printf("  %d", solution[i][j]);
        }
        printf("\n");
    }
    QVERIFY(res == true);
}

void SudokutestTest::testGenRandom()
{
    const int T = 30000;
    int array[T][9];
    for (int i = 0; i < T; ++i) {
        _inst->genRandom(array[i]);
    }

    //static every column average
    int randPos= rand() % 9; //随机选取一列
    int position_message[9] = {0}; //统计该列上出现1-9各自出现的次数
    for (int i = 0; i < T; ++i) {
        position_message[array[i][randPos] - 1]++;
    }

    for (int i = 0; i < 9; ++i) {
        printf("%d ", position_message[i]);
        QVERIFY((position_message[i] + 0.0) / T - 0.1 < 0.1); //粗略估算
    }
    //观察分布是否均匀
}

void SudokutestTest::testNextAndPrevious()
{
    int fcase_x(0), fcase_y(0);
    _inst->previous(fcase_x, fcase_y);
    QVERIFY(fcase_x == 8 && fcase_y == 8);

    _inst->next(fcase_x, fcase_y);
    QVERIFY(fcase_x == 9 && fcase_y == 9);


    int case1p_x(1), case1p_y(8);
    _inst->next(case1p_x, case1p_y);
    QVERIFY(case1p_x == 2 && case1p_y == 0);

    _inst->previous(case1p_x, case1p_y);
    QVERIFY(case1p_x == 1 && case1p_y == 8);

    int case2p_x(5), case2p_y(3);
    _inst->next(case2p_x, case2p_y);
    QVERIFY(case2p_x == 5 && case2p_y == 4);

    _inst->previous(case2p_x, case2p_y);
    QVERIFY(case2p_x == 5 && case2p_y == 3);
}

QTEST_APPLESS_MAIN(SudokutestTest)

#include "tst_sudokutesttest.moc"
