/**
* Author: by cdhmuer333@126.com
*/

#include "sudoku.h"

#include <QTime>
#include <QPoint>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


Sudoku::Sudoku()
{
    srand((unsigned)time(NULL));
}

Sudoku::~Sudoku()
{}

/**
 * 产生一行1~9的随机数*
 * @param int line[] 产生结果存储在这里
 */
void Sudoku::genRandom(int line[])
{
    for (int i = 0; i < 9; ++i) {
        line[i] = i + 1;
    }
    for (int i = 0; i < 9; ++i) {
        int pos = rand() % (9 - i);  // 随机产生一个下标， 让它和第9 - i个数字交换
        if (pos == 8 - i) {
            continue;
        } else {
            int temp = line[pos];
            line[pos] = line[8 - i];
            line[8 - i] = temp;
        }
    }

}

/**
 * @brief Sudoku::initialState
 * 递归版本的算法 搜索第（ i, j ）位置处可以存储的数字,找到解则返回1，否则返回0
 * @param i
 * @param j
 * @return
 */
int Sudoku::initialState(int i, int j)
{
    int m, n, p, q;
    if (i >= 9 || j >= 9)
        return 1;

    int rpos[9] = {0}; // 可选项要随机打乱，不然生成的局面会有规律
    genRandom(rpos);
    for (int k = 0; k < 9 ; ++k) {
        int can = 1;                // can 变量用于记录数字k能否放在 (i, j) 处
        for (m = 0; m < i; ++m) {
            if (_table[m][j] == rpos[k]) { // 检查同一列是否出现过数字k
                can = 0;
                break;
            }
        }

        if (can) {
            for (n = 0; n < j; ++n) {
                if (_table[i][n] == rpos[k]) { // 检查同一行是否出现过数字k
                    can = 0;
                    break;
                }
            }
        }

        if (can) {
            int up1 = (i / 3) * 3 + 3 ; // (i,j)方格所在的3×3小方格i坐标的上限
            int up2 = (j / 3) * 3 + 3;   // (i,j)方格所在的3×3小方格在j坐标的上限

            for (p = up1 - 3; p < up1; ++p) { //检查在3×3的小方格中是否出现了同一个数字
                if (can == 0)   /* 跳出外层循环 */
                    break;
                for (q = up2-3; q < up2; ++q) {
                    if (_table[p][q] == rpos[k]) {
                        can = 0;
                        break;
                    }
                }
            }
        }

        if (can) {
            _table[i][j] = rpos[k];
            if (j < 8) {
                if (initialState(i, j + 1))   /* 到同一行的下一位置开始搜索 */
                    return 1 ;
            } else {
                if (i < 8) {
                    if (initialState(i + 1, 0))    /* 到下一行的第一个空格开始搜索 */
                        return 1;
                } else {
                    return 1;  /* i >= 9  && j >= 9, 搜索结束 */
                }
            }
            _table[i][j] = 0;   /* 关键这一步：找不到解就要回复原状，否则会对下面的搜索造成影响 */
        }
    }
    return 0 ;  /*  1到9都尝试过都不行，则返回递归的上一步 */
}

/**
 * @brief Sudoku::tryfill
 * //尝试将k填入位置（i，j）中
 * @param table
 * @param k
 * @return true 填写成功; false该位置无法填写成功
 */
bool Sudoku::tryfill(int i, int j, int k)
{
    if (_table[i][j] != 0) {
        return false;
    }

    //检查同一列是否已填入数字k
    for (int row = 0; row < 9; ++row) {
        if (_table[row][j] == k) {
            return false;
        }
    }

    //检查同一行是否已填入数字k
    for (int col = 0; col < 9; ++col) {
        if (_table[i][col] == k) {
           return false;
        }
    }

    //检查所属9方格是否已填入数字k
    int up1 = (i / 3) * 3 + 3 ; // (i,j)方格所在的3×3小方格i坐标的上限
    int up2 = (j / 3) * 3 + 3;   // (i,j)方格所在的3×3小方格在j坐标的上限
    for (int p = up1 - 3; p < up1; ++p) { //检查在3×3的小方格中是否出现了同一个数字
        for (int q = up2 - 3; q < up2; ++q) {
            if (_table[p][q] == k) {
               return false;
            }
        }
    }

    _table[i][j] = k;
    return true;
}

/**
 * @brief Sudoku::next
  迭代到下一个坐标 (8, 8)下一个是(9, 9); (0, 0)上一个是(8, 8）
 * @param x
 * @param y
 */
void Sudoku::next(int &x, int &y)
{
    ++y;
    x += (y / 9);
    if (x < 9) {
        y %= 9;
    }
}

/**
 * @brief Sudoku::previous
 * 迭代到上一个坐标 (8, 8)下一个是(9, 9); (0, 0)上一个是(8, 8）
 * @param x
 * @param y
 */
void Sudoku::previous(int &x, int &y)
{
    --y;
    if (y < 0) {
        x -= 1;
        x < 0 ? x = 8: x;
        y = 8;
    }
}

/**
 * @brief Sudoku::initsudoku
 * 生成一个数独 非递归的生成方法
 * Author: by cdhmuer333@126.com
 */
void Sudoku::initsudoku()
{
   clear();
   genRandom(_table[0]);

   int row(1), col(0);//从第二行第一列开始填
   int marks[9][9][9] = { { {0} } }; //hash标记数组 marks[i][j][k] = 1表示（i，j）填 k + 1已经尝试过

   for (;;) {
       if (row == 9 && row == 9) { //生成局面成功
           return;
       }

       int ranNums[9] = {0};
       genRandom(ranNums);

       bool fill_row_success = false;
       for (int k = 0; k < 9; ++k) {
            if (marks[row][col][ranNums[k] - 1] != 0) {
                continue;
            }
            if(tryfill(row, col, ranNums[k])) {
                next(row, col);  //迭代row ，col的值 一般情境下二值都已经发生了变化

                fill_row_success = true;
                break;
            }
       }

       if (!fill_row_success) {
           for (int i = 0; i < 9; ++i) {
               marks[row][col][i] = 0; //重置状态
           }

           previous(row, col); // 回溯, 迭代后两个值都会发生变化
           if (_table[row][col] != 0) {
                marks[row][col][_table[row][col] - 1] = 1; //已尝试过，标记
           }

           if (row == 0 && col == 8) {  //结束
               break;
           }
           _table[row][col] = 0;
       }
   }
}

/**
 * @brief Sudoku::parseState 递归法求解答案
 *        从第（i，j）位置处可以存储的数字,找到解则返回true，否则返回false
 * (i, j)数组的两个下标
 * @return bool
 */
bool Sudoku::parseState(int i, int j)
{
    if (_solution[i][j] != 0) {
        if (j < 8) {
            if (parseState(i, j + 1))   /* 到同一行的下一位置开始搜索 */
                return true;
        } else {
            if (i < 8) {
                if (parseState(i + 1, 0))    /* 到下一行的第一个空格开始搜索 */
                    return true;
            } else {
                return true;  /* i >= 9  && j >= 9, 搜索结束 */
            }
        }
        return false;
    }
    int k, m, n, p, q;
    if (i >= 9 || j >= 9)
        return true;

    for (k = 1; k <= 9; k++) {
        int can = 1;                // can 变量用于记录数字k能否放在 (i, j) 处
        for (m = 0; m < 9; ++m) {
            if (_solution[m][j] == k) {  // 检查同一列是否出现过数字k
                can = 0 ;
                break ;
            }
        }

        if (can) {
            for (n = 0; n < 9; ++n) {
                if (_solution[i][n] == k) {  // 检查同一行是否出现过数字k
                    can = 0 ;
                    break;
                }
            }
        }

        if (can) {
            int up1 = (i / 3) * 3 + 3 ; // (i,j)方格所在的3×3小方格i坐标的上限
            int up2 = (j / 3) * 3 + 3;   // (i,j)方格所在的3×3小方格在j坐标的上限

            for (p = up1 - 3; p < up1; ++p) { /* 检查在3×3的小方格中是否出现了同一个数字 */
                if (can == 0)   //跳出外层循环
                    break ;
                for (q = up2-3; q < up2; ++q) {
                    if (_solution[p][q] == k) {
                        can = 0;
                        break;
                    }
                }
            }
        }
        if (can) {
            _solution[i][j] = k;
            if (j < 8) {
                if (parseState(i, j + 1))   /* 到同一行的下一位置开始搜索 */
                    return true;
            } else {
                if (i < 8) {
                    if (parseState(i + 1, 0))    /* 到下一行的第一个空格开始搜索 */
                        return true;
                } else {
                    return false; /* i >= 9  && j >= 9, 搜索结束 */
                }
            }
            _solution[i][j] = 0 ;  /*找不到解要回复原状，否则会对下面的搜索造成影响 */
        }
    }
    return false; /*  1到9都尝试过都不行，则返回递归的上一步 */
}


void Sudoku::initialize(int table[9][9])
{
    //clear();
    //第1行随即数产生
    //genRandom(_table[0]);
    //从第2行第1个位置开始检索

    //这里采用非递归方法生成局面
    initsudoku();
    //initialState(1, 0);
    //copy
    copyArray(_table, table);
}

/**
 * @brief Sudoku::copyArray
 *        二维整型数组的复制函数
 * @param srcArray
 * @param dstArray
 * @param row 数组的行数
 * @param col 数组的列
 */
void Sudoku::copyArray(int srcArray[9][9], int dstArray[9][9])
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            dstArray[i][j] = srcArray[i][j];
        }
    }
}

/**
 * @brief Sudoku::getSolution
 * @param question, answser 参数分别是一个题目， 和一个接收答案的数组
 * @return
 */
bool Sudoku::getSolution(int question[9][9], int answer[9][9])
{
    copyArray(question, _table);
    if (parseState(0, 0)) {
        copyArray(_solution, answer);
        return true;
    }
    return false;
}


/**
 * @brief checkSolution 检查答案是否正确
 * @param answer 一个二维数组
 * @return 答案正确，返回true， 否则返回false
 */
bool Sudoku::checkSolution(int answer[9][9])
{
    int rows[9][9] = {{0}};
    int colums[9][9] = {{0}};
    int grid[3][3][9] = {{{0}}};

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int n = answer[i][j];

            rows[i][n]++;
            colums[j][n]++;
            grid[i / 3][j / 3][n]++;
            if (rows[i][n] > 1 || colums[j][n] > 1 || grid[i / 3][j / 3][n] > 1) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Sudoku::isvalidOfArray
 *   检查一个9元素的数组是不是刚好由1~9的数字填充
 * @param array
 * @return true 1~9刚好填满;否则返回false
 */
bool Sudoku::isvalidOfArray(int array[])
{
    int bucket[9] = {0};
    for (int i = 0; i < 9; ++i) {
        bucket[array[i] - 1]++;
    }

    for (int i = 0; i < 9; ++i) {
        if (bucket[i] != 1)
            return false;
    }
    return true;
}

/**
 * @brief Sudoku::makeLevel
 * 创建一个指定难度的数独游戏，随机选择位置打码
 * @param table
 * @param blankGridNum 空白个字的数量， 底层数据设置为0
 */
void Sudoku::makeLevel(int table[9][9], int blankGridNum)
{
    initialize(table);
    int answer[9][9];
    int backupArray[9][9]; //用于失败回溯的临时矩阵
    copyArray(table, backupArray);

    for (int k = 0; k < blankGridNum;) {
        int i = rand() % 9;
        int j = rand() % 9;
        if (table[i][j] == 0) {
            //已设置mask
            continue;
        }

        table[i][j] = 0;
        if (this->getSolution(table, answer)) {
            ++k;
            backupArray[i][j] = table[i][j]; //保持数据的同步
        } else {
            //restore array
            copyArray(backupArray, table);
        }
    }
}

/**
 * @brief Sudoku::clear
 * 将本地的 table 清0
 */
void Sudoku::clear()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            _table[i][j] = 0;
        }
    }
}
