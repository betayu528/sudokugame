#ifndef SUDOKU
#define SUDOKU

/**
 * @brief The Sudoku class
 * 封装数独的核心算法
 * 包括生成题目的回溯算法以及求解算法
 */
class Sudoku
{
public:
    Sudoku();
    ~Sudoku();

    bool getSolution(int question[9][9], int answer[9][9]);
    void initialize(int table[9][9]);

    bool checkSolution(int answer[9][9]);
    bool isvalidOfArray(int array[9]);
    void makeLevel(int table[9][9], int blankGridNum);
    void copyArray(int srcArray[9][9], int dstArray[9][9]);

private:
    void initsudoku();
    int  initialState(int i, int j);
    bool tryfill(int i, int j, int k);
    void next(int &x, int &y);
    void previous(int &x, int &y);
    void genRandom(int line[]);
    bool parseState(int i, int j);
    void clear();

    int _table[9][9];   // 作为各个算法的临时变量数组
    int _solution[9][9]; // 解题答案
};

#endif // SUDOKU

