#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/
bool ifbomb(Board board, int i ,int j);
bool ifenemy(Board board, int i ,int j, char color);

void algorithm_A(Board board, Player player, int index[]) {

    //////////// Random Algorithm ////////////
    // Here is the random algorithm for your reference, you can delete or comment it.
  
    int row, col;
    char color = player.get_color();
    float flag = 0;

    bool mark[ROW][COL] = {0};
    float map[ROW][COL] = {0};

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {

            // find conflict 6
            if (flag <= 6) {
                if (ifbomb(board, i, j) && board.get_cell_color(i, j) == color) {
                    switch(board.get_capacity(i, j)) {
                        case 2:
                            if (i == 0 && j == 0 &&
                                (ifbomb(board, 0, 1) && ifenemy(board, 0, 1, color) ||
                                ifbomb(board, 1, 0) && ifenemy(board, 1, 0, color)))
                                {flag = 6; map[i][j] = 6; mark[i][j] = 1; break;}
                            else if (i == 4 && j == 0 &&
                                (ifbomb(board, 4, 1) && ifenemy(board, 4, 1, color) ||
                                ifbomb(board, 3, 0) && ifenemy(board, 3, 0, color)))
                                {flag = 6; map[i][j] = 6; mark[i][j] = 1; break;}
                            else if (i == 0 && j == 5 &&
                                (ifbomb(board, 1, 5) && ifenemy(board, 1, 5, color) ||
                                ifbomb(board, 0, 4) && ifenemy(board, 0, 4, color)))
                                {flag = 6; map[i][j] = 6; mark[i][j] = 1; break;}
                            else if (i == 4 && j == 5 &&
                                (ifbomb(board, 4, 4) && ifenemy(board, 4, 4, color) ||
                                ifbomb(board, 3, 5) && ifenemy(board, 3, 5, color)))
                                {flag = 6; map[i][j] = 6; mark[i][j] = 1; break;}
                            else break;
                        case 3:
                            if (i == 0 && 
                            (ifbomb(board, 0, j - 1) && ifenemy(board, 0, j - 1, color) ||
                            ifbomb(board, 0, j + 1) && ifenemy(board, 0, j + 1, color) ||
                            ifbomb(board, 1, j) && ifenemy(board, 1, j, color)))
                            {flag = 6; map[i][j] = 6; mark[i][j] = 1; break;}
                            else if (i == 4 && 
                            (ifbomb(board, 4, j - 1) && ifenemy(board, 4, j - 1, color) ||
                            ifbomb(board, 4, j + 1) && ifenemy(board, 4, j + 1, color)||
                            ifbomb(board, 3, j) && ifenemy(board, 3, j, color)))
                            {flag = 6; map[i][j] = 6; mark[i][j] = 1; break;}
                            else if (j == 0 && 
                            (ifbomb(board, i + 1, j) && ifenemy(board, i + 1, j, color) ||
                            ifbomb(board, i - 1, j) && ifenemy(board, i - 1, j, color) ||
                            ifbomb(board, i, 1) && ifenemy(board, i, 1, color)))
                            {flag = 6; map[i][j] = 6; mark[i][j] = 1; break;}
                            else if (j == 5 && 
                            (ifbomb(board, i + 1, j) && ifenemy(board, i + 1, j, color) ||
                            ifbomb(board, i - 1, j) && ifenemy(board, i - 1, j, color) ||
                            ifbomb(board, i, 4) && ifenemy(board, i, 4, color)))
                            {flag = 6; map[i][j] = 6; mark[i][j] = 1; break;}
                            else break;                          
                        case 4:
                            if (ifbomb(board, i + 1, j) && ifenemy(board, i + 1, j, color) ||
                            ifbomb(board, i - 1, j) && ifenemy(board, i - 1, j, color) ||
                            ifbomb(board, i, j + 1) && ifenemy(board, i, j + 1, color) ||
                            ifbomb(board, i, j - 1) && ifenemy(board, i, j - 1, color))
                            {flag = 6; map[i][j] = 6; mark[i][j] = 1; break;}
                            else break;
                    }
                }
            }

            // find bomb need to explose (can conquer enemy) 5
            if (flag <= 5 && mark[i][j] == 0) {
                if (ifbomb(board, i, j) && board.get_cell_color(i, j) == color) {
                    switch(board.get_capacity(i, j)) {
                        case 2:
                            if (i == 0 && j == 0 && (ifenemy(board, 0, 1, color) || ifenemy(board, 1, 0, color)))
                                {flag = 5; map[i][j] = 5; mark[i][j] = 1; break;}
                            else if (i == 4 && j == 0 && (ifenemy(board, 4, 1, color) || ifenemy(board, 3, 0, color)))
                                {flag = 5; map[i][j] = 5; mark[i][j] = 1; break;}
                            else if (i == 0 && j == 5 && (ifenemy(board, 1, 5, color) || ifenemy(board, 0, 4, color)))
                                {flag = 5; map[i][j] = 5; mark[i][j] = 1; break;}
                            else if (i == 4 && j == 5 && (ifenemy(board, 4, 4, color) || ifenemy(board, 3, 5, color)))
                                {flag = 5; map[i][j] = 5; mark[i][j] = 1; break;}
                            else break;
                        case 3:
                            if (i == 0 && (ifenemy(board, 0, j - 1, color) || ifenemy(board, 0, j + 1, color) || ifenemy(board, 1, j, color)))
                            {flag = 5; map[i][j] = 5; mark[i][j] = 1; break;}
                            else if (i == 4 && (ifenemy(board, 4, j - 1, color) || ifenemy(board, 4, j + 1, color) || ifenemy(board, 3, j, color)))
                            {flag = 5; map[i][j] = 5; mark[i][j] = 1; break;}
                            else if (j == 0 && (ifenemy(board, i + 1, j, color) || ifenemy(board, i - 1, j, color) || ifenemy(board, i, 1, color)))
                            {flag = 5; map[i][j] = 5; mark[i][j] = 1; break;}
                            else if (j == 5 && (ifenemy(board, i + 1, j, color) || ifenemy(board, i - 1, j, color) || ifenemy(board, i, 4, color)))
                            {flag = 5; map[i][j] = 5; mark[i][j] = 1; break;}
                            else break;                          
                        case 4:
                            if (ifenemy(board, i - 1, j, color) || ifenemy(board, i + 1, j, color) ||
                                ifenemy(board, i, j + 1, color) || ifenemy(board, i, j - 1, color))
                            {flag = 5; map[i][j] = 5; mark[i][j] = 1; break;}
                            else break;      
                    }
                }
            }
        }
    }


    index[0] = row;
    index[1] = col;
}

bool ifbomb(Board board, int i, int j) {
    if (board.get_orbs_num(i, j) == board.get_capacity(i, j) - 1) 
        return 1;
    return 0;
}

bool ifenemy(Board board, int i, int j, char color) {
    if (board.get_cell_color(i, j) != color && board.get_cell_color(i, j) != 'w')
        return 1;
    return 0;
}