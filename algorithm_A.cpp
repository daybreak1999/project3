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
bool ifready(Board board, int i ,int j);

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
            if (flag < 6 && mark[i][j] == 0) {
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

            // produce bomb (first order, the block's neighbor has enemy) 4
            if (flag < 5 && mark[i][j] == 0) {
                if (ifready(board, i, j) &&
                    (board.get_cell_color(i, j) == color || board.get_cell_color(i, j) == 'w')) {
                    switch(board.get_capacity(i, j)) {
                        case 2: 
                            int enemy = 0; int comrade = 0;
                            if (i == 0 && j == 0) {
                                if (ifenemy(board, 0, 1, color)) enemy++;
                                else if (board.get_cell_color(0, 1) != 'w') comrade++;
                                if (ifenemy(board, 1, 0, color)) enemy++;
                                else if (board.get_cell_color(1, 0) != 'w') comrade++;
                            }  
                            else if (i == 4 && j == 0) {
                                if (ifenemy(board, 3, 0, color)) enemy++;
                                else if (board.get_cell_color(3, 0) != 'w') comrade++;
                                if (ifenemy(board, 4, 1, color)) enemy++;
                                else if (board.get_cell_color(4, 1) != 'w') comrade++;
                            }
                            else if (i == 0 && j == 5) {
                                if (ifenemy(board, 1, 5, color)) enemy++;
                                else if (board.get_cell_color(1, 5) != 'w') comrade++;
                                if (ifenemy(board, 0, 4, color)) enemy++;
                                else if (board.get_cell_color(0, 4) != 'w') comrade++;
                            } 
                            else if (i == 4 && j == 5) {
                                if (ifenemy(board, 4, 4, color)) enemy++;
                                else if (board.get_cell_color(4, 4) != 'w') comrade++;
                                if (ifenemy(board, 3, 5, color)) enemy++;
                                else if (board.get_cell_color(3, 5) != 'w') comrade++;
                            }
                            if (enemy > 0) {
                                if (enemy == 2) map[i][j] = 4.95;
                                else if (enemy == 1 && comrade == 0) map[i][j] = 4.93;
                                else map[i][j] = 4.9;
                                flag = 4; mark[i][j] = 1;
                            } break;
                        case 3:
                            int enemy = 0; int comrade = 0;
                            if (i == 0) {
                                if (ifenemy(board, 0, j - 1, color)) enemy++;
                                else if (board.get_cell_color(0, j - 1) != 'w') comrade++;
                                if (ifenemy(board, 0, j + 1, color)) enemy++;
                                else if (board.get_cell_color(0, j + 1) != 'w') comrade++;
                                if (ifenemy(board, 1, j, color)) enemy++;
                                else if (board.get_cell_color(1, j) != 'w') comrade++;
                            }  
                            else if (i == 4) {
                                if (ifenemy(board, 4, j - 1, color)) enemy++;
                                else if (board.get_cell_color(4, j - 1) != 'w') comrade++;
                                if (ifenemy(board, 4, j + 1, color)) enemy++;
                                else if (board.get_cell_color(4, j + 1) != 'w') comrade++;
                                if (ifenemy(board, 3, j, color)) enemy++;
                                else if (board.get_cell_color(3, j) != 'w') comrade++;
                            }
                            else if (j == 0) {
                                if (ifenemy(board, i + 1, j, color)) enemy++;
                                else if (board.get_cell_color(i + 1, j) != 'w') comrade++;
                                if (ifenemy(board, i - 1, j, color)) enemy++;
                                else if (board.get_cell_color(i - 1, j) != 'w') comrade++;
                                if (ifenemy(board, i, 1, color)) enemy++;
                                else if (board.get_cell_color(i, 1) != 'w') comrade++;
                            } 
                            else if (j == 5) {
                                if (ifenemy(board, i + 1, j, color)) enemy++;
                                else if (board.get_cell_color(i + 1, j) != 'w') comrade++;
                                if (ifenemy(board, i - 1, j, color)) enemy++;
                                else if (board.get_cell_color(i - 1, j) != 'w') comrade++;
                                if (ifenemy(board, i, 4, color)) enemy++;
                                else if (board.get_cell_color(i, 4) != 'w') comrade++;
                            }
                            if (enemy > 0) {
                                if (enemy == 3) map[i][j] = 4.89;
                                else if (enemy == 2 && comrade == 0) map[i][j] = 4.85;
                                else if (enemy == 2 && comrade == 1) map[i][j] = 4.83;
                                else if (enemy == 1 && comrade == 0) map[i][j] = 4.82;
                                else if (enemy == 1 && comrade == 1) map[i][j] = 4.81;
                                else map[i][j] = 4.8;
                                flag = 4; mark[i][j] = 1;
                            } break;                          
                        case 4:
                            int enemy = 0; int comrade = 0;
                            if (ifenemy(board, i, j - 1, color)) enemy++;
                            else if (board.get_cell_color(i, j - 1) != 'w') comrade++;
                            if (ifenemy(board, i, j + 1, color)) enemy++;
                            else if (board.get_cell_color(i, j + 1) != 'w') comrade++;
                            if (ifenemy(board, i - 1, j, color)) enemy++;
                            else if (board.get_cell_color(i - 1, j) != 'w') comrade++;
                            if (ifenemy(board, i + 1, j, color)) enemy++;
                            else if (board.get_cell_color(i + 1, j) != 'w') comrade++;
                            if (enemy > 0) {
                                if (enemy == 4) map[i][j] = 4.79;
                                else if (enemy == 3 && comrade == 0) map[i][j] = 4.78;
                                else if (enemy == 3 && comrade == 1) map[i][j] = 4.77;
                                else if (enemy == 2 && comrade == 0) map[i][j] = 4.76;
                                else if (enemy == 2 && comrade == 1) map[i][j] = 4.75;
                                else if (enemy == 2 && comrade == 2) map[i][j] = 4.74;
                                else if (enemy == 1 && comrade == 0) map[i][j] = 4.73;
                                else if (enemy == 1 && comrade == 1) map[i][j] = 4.72;
                                else if (enemy == 1 && comrade == 2) map[i][j] = 4.71;
                                else map[i][j] = 4.7;
                                flag = 4; mark[i][j] = 1;
                            } break;
                }
            }

            // occupy (enemy isn't bomb) 3
            if (flag < 4 && mark[i][j] == 0) {
                if (board.get_cell_color(i, j) == 'w') {
                    switch(board.get_capacity(i, j)) {
                        case 2: 
                            int comrade = 0; 
                            if (i == 0 && j == 0) {
                                if (board.get_cell_color(0, 1) != 'w') comrade++;
                                if (board.get_cell_color(1, 0) != 'w') comrade++;
                            }  
                            else if (i == 4 && j == 0) {
                                if (board.get_cell_color(3, 0) != 'w') comrade++;
                                if (board.get_cell_color(4, 1) != 'w') comrade++;
                            }
                            else if (i == 0 && j == 5) {
                                if (board.get_cell_color(1, 5) != 'w') comrade++;
                                if (board.get_cell_color(0, 4) != 'w') comrade++;
                            } 
                            else if (i == 4 && j == 5) {
                                if (board.get_cell_color(4, 4) != 'w') comrade++;
                                if (board.get_cell_color(3, 5) != 'w') comrade++;
                            }
                            if (comrade == 0) map[i][j] = 3.99;
                            else if (comrade == 1) map[i][j] = 3.95;
                            else map[i][j] = 3.9;
                            flag = 3; mark[i][j] = 1; break;
                        case 3:
                            int enemy = 0; int comrade = 0;
                            if (i == 0) {
                                if (ifenemy(board, 0, j - 1, color) && ifbomb(board, 0, j - 1)) break;
                                else if (ifenemy(board, 0, j - 1, color)) enemy++;
                                else if (board.get_cell_color(0, j - 1) != 'w') comrade++;
                                if (ifenemy(board, 0, j + 1, color) && ifbomb(board, 0, j + 1)) break;
                                else if (ifenemy(board, 0, j + 1, color)) enemy++;
                                else if (board.get_cell_color(0, j + 1) != 'w') comrade++;
                                if (ifenemy(board, 1, j, color) && ifbomb(board, 1, j)) break;
                                else if (ifenemy(board, 1, j, color)) enemy++;
                                else if (board.get_cell_color(1, j) != 'w') comrade++;
                            }  
                            else if (i == 4) {
                                if (ifenemy(board, 4, j - 1, color) && ifbomb(board, 4, j - 1)) break;
                                else if (ifenemy(board, 4, j - 1, color)) enemy++;
                                else if (board.get_cell_color(4, j - 1) != 'w') comrade++;
                                if (ifenemy(board, 4, j + 1, color) && ifbomb(board, 4, j + 1)) break;
                                else if (ifenemy(board, 4, j + 1, color)) enemy++;
                                else if (board.get_cell_color(4, j + 1) != 'w') comrade++;
                                if (ifenemy(board, 3, j, color) && ifbomb(board, 3, j)) break;
                                else if (ifenemy(board, 3, j, color)) enemy++;
                                else if (board.get_cell_color(3, j) != 'w') comrade++;
                            }
                            else if (j == 0) {
                                if (ifenemy(board, i + 1, j, color) && ifbomb(board, i + 1, j)) break;
                                else if (ifenemy(board, i + 1, j, color)) enemy++;
                                else if (board.get_cell_color(i + 1, j) != 'w') comrade++;
                                if (ifenemy(board, i - 1, j, color) && ifbomb(board, i - 1, j)) break;
                                else if (ifenemy(board, i - 1, j, color)) enemy++;
                                else if (board.get_cell_color(i - 1, j) != 'w') comrade++;
                                if (ifenemy(board, i, 1, color) && ifbomb(board, i, 1)) break;
                                else if (ifenemy(board, i, 1, color)) enemy++;
                                else if (board.get_cell_color(i, 1) != 'w') comrade++;
                            } 
                            else if (j == 5) {
                                if (ifenemy(board, i + 1, j, color) && ifbomb(board, i + 1, j)) break;
                                else if (ifenemy(board, i + 1, j, color)) enemy++;
                                else if (board.get_cell_color(i + 1, j) != 'w') comrade++;
                                if (ifenemy(board, i - 1, j, color) && ifbomb(board, i - 1, j)) break;
                                else if (ifenemy(board, i - 1, j, color)) enemy++;
                                else if (board.get_cell_color(i - 1, j) != 'w') comrade++;
                                if (ifenemy(board, i, 4, color) && ifbomb(board, i, 4)) break;
                                else if (ifenemy(board, i, 4, color)) enemy++;
                                else if (board.get_cell_color(i, 4) != 'w') comrade++;
                            }
                            if (enemy == 3) map[i][j] = 3.89;
                            else if (enemy == 2 && comrade == 0) map[i][j] = 3.88;
                            else if (enemy == 2 && comrade == 1) map[i][j] = 3.87;
                            else if (enemy == 1 && comrade == 0) map[i][j] = 3.86;
                            else if (enemy == 1 && comrade == 1) map[i][j] = 3.85;
                            else if (enemy == 1 && comrade == 2) map[i][j] = 3.84;
                            else if (enemy == 0 && comrade == 0) map[i][j] = 3.83;
                            else if (enemy == 0 && comrade == 1) map[i][j] = 3.82;
                            else if (enemy == 0 && comrade == 2) map[i][j] = 3.81;
                            else map[i][j] = 3.8;
                            flag = 3; mark[i][j] = 1; break;                          
                        case 4:
                            int enemy = 0; int comrade = 0;
                            if (ifenemy(board, i, j - 1, color) && ifbomb(board, i, j - 1)) break;
                            else if (ifenemy(board, i, j - 1, color)) enemy++;
                            else if (board.get_cell_color(i, j - 1) != 'w') comrade++;
                            if (ifenemy(board, i, j + 1, color) && ifbomb(board, i, j + 1)) break;
                            else if (ifenemy(board, i, j + 1, color)) enemy++;
                            else if (board.get_cell_color(i, j + 1) != 'w') comrade++;
                            if (ifenemy(board, i - 1, j, color) && ifbomb(board, i - 1, j)) break;
                            else if (ifenemy(board, i - 1, j, color)) enemy++;
                            else if (board.get_cell_color(i - 1, j) != 'w') comrade++;
                            if (ifenemy(board, i + 1, j, color) && ifbomb(board, i + 1, j)) break;
                            else if (ifenemy(board, i + 1, j, color)) enemy++;
                            else if (board.get_cell_color(i + 1, j) != 'w') comrade++;
                            if (enemy == 4) map[i][j] = 3.79;
                            else if (enemy == 3 && comrade == 0) map[i][j] = 3.78;
                            else if (enemy == 3 && comrade == 1) map[i][j] = 3.76;
                            else if (enemy == 2 && comrade == 0) map[i][j] = 3.75;
                            else if (enemy == 2 && comrade == 1) map[i][j] = 3.74;
                            else if (enemy == 2 && comrade == 2) map[i][j] = 3.73;
                            else if (enemy == 1 && comrade == 0) map[i][j] = 3.72;
                            else if (enemy == 1 && comrade == 1) map[i][j] = 3.71;
                            else if (enemy == 1 && comrade == 2) map[i][j] = 3.7;
                            else if (enemy == 1 && comrade == 3) map[i][j] = 3.69;
                            else if (enemy == 0 && comrade == 0) map[i][j] = 3.68;
                            else if (enemy == 0 && comrade == 1) map[i][j] = 3.67;
                            else if (enemy == 0 && comrade == 2) map[i][j] = 3.66;
                            else if (enemy == 0 && comrade == 3) map[i][j] = 3.65;
                            else map[i][j] = 3.64;
                            flag = 4; mark[i][j] = 1; break;
                }
            }

            // produce bomb (second order, the block's neighbor hasn't enemy) 2
            if (flag < 3 && mark[i][j] == 0) {
                if (ifready(board, i, j) && board.get_cell_color(i, j) == color) {
                    switch(board.get_capacity(i, j)) {
                        case 3:
                            int comrade = 0;
                            if (i == 0) {
                                if (board.get_cell_color(0, j - 1) == color) comrade++;
                                if (board.get_cell_color(0, j + 1) == color) comrade++;
                                if (board.get_cell_color(1, j) == color) comrade++;
                            }  
                            else if (i == 4) {
                                if (board.get_cell_color(4, j - 1) == color) comrade++;
                                if (board.get_cell_color(4, j + 1) == color) comrade++;
                                if (board.get_cell_color(3, j) == color) comrade++;
                            }
                            else if (j == 0) {
                                if (board.get_cell_color(i + 1, j) == color) comrade++;
                                if (board.get_cell_color(i - 1, j) == color) comrade++;
                                if (board.get_cell_color(i, 1) == color) comrade++;
                            } 
                            else if (j == 5) {
                                if (board.get_cell_color(i + 1, j) == color) comrade++;
                                if (board.get_cell_color(i - 1, j) == color) comrade++;
                                if (board.get_cell_color(i, 4) == color) comrade++;
                            }
                            if (comrade == 0) map[i][j] = 2.99;
                            else if (comrade == 1) map[i][j] = 2.98;
                            else if (comrade == 2) map[i][j] = 2.95;
                            else map[i][j] = 2.9;
                            flag = 2; mark[i][j] = 1; break;                          
                        case 4:
                            int comrade = 0;
                            if (board.get_cell_color(i, j - 1) == color) comrade++;
                            if (board.get_cell_color(i, j + 1) == color) comrade++;
                            if (board.get_cell_color(i - 1, j) == color) comrade++;
                            if (board.get_cell_color(i + 1, j) == color) comrade++;
                            if (comrade == 0) map[i][j] = 2.89;
                            else if (comrade == 1) map[i][j] = 2.87;
                            else if (comrade == 2) map[i][j] = 2.85;
                            else if (comrade == 3) map[i][j] = 2.83;
                            else map[i][j] = 2.81;
                            flag = 2; mark[i][j] = 1; break;
                    }
                }
            }
            
            // draft 1
            if (flag < 2 && mark[i][j] == 0) {
                if((!ifready(board, i, j) && !ifbomb(board, i, j) && board.get_cell_color(i, j) == color)) {
                    map[i][j] = 1; flag = 1; mark[i][j] = 1;
                }            
            }

            // enemy
            if (flag < 1 && mark[i][j] == 0) {
                if(ifenemy(board, i, j)) {
                    map[i][j] = -1; flag = -1; mark[i][j] = 1;
                }
            }
        }
    }

    int max = -1;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if(map[i][j] > max) {
                max = map[i][j];
                row = i; col = j;
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

bool ifready(Board board, int i, int j) {
    if (board.get_orbs_num(i, j) == board.get_capacity(i, j) - 2) 
        return 1;
    return 0;
}
bool ifenemy(Board board, int i, int j, char color) {
    if (board.get_cell_color(i, j) != color && board.get_cell_color(i, j) != 'w')
        return 1;
    return 0;
}