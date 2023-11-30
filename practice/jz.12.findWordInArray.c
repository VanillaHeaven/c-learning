#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int directions[][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

bool path_find(char** grid, int gridSize, int gridColSize, char* target, char **footprint, int i, int j) {
    if (grid[i][j] != *target) return false;
    if (*(target + 1) == '\0') return true;

    // 记录足迹
    footprint[i][j] = 1;

    // 向四个方向探索
    int index = 0;
    for (; index < 4; index++) {
        int newi = i + directions[index][0];
        int newj = j + directions[index][1];
        if (
            newi >= 0 && newi < gridSize &&
            newj >= 0 && newj < gridColSize &&
            footprint[newi][newj] != 1
        ) {
            if (path_find(grid, gridSize, gridColSize, target + 1, footprint, newi, newj)) return true;
        }
    }


    // 回退足迹
    footprint[i][j] = 0;

    return false;
}


bool word_puzzle(char** grid, int gridSize, int* gridColSize, char* target) {
    int i = 0, j = 0;

    // 初始化足迹数组, 用于记录走过的路径
    char **footprint = (char **) malloc(gridSize * sizeof(char *));
    for (i = 0; i < gridSize; i++) {
        footprint[i] = (char *) calloc(*gridColSize, sizeof(char));
    }

    // 寻找起点
    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < *gridColSize; j++) {
            if (path_find(grid, gridSize, *gridColSize, target, footprint, i, j)) return true;
        }
    }

    return false;
}


int main() {
    int    i = 0, j = 0;
    int    row = 3;
    int    col = 4;
    char **grid = NULL;
    char  *target = "SEEA";

    char data[][4] = {
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'S'},
        {'A', 'B', 'E', 'E'},
    };

    grid = (char **) malloc(row * sizeof(char *));
    for (i = 0; i < row; i++) {
        grid[i] = data[i];
    }

    printf("%d\n", word_puzzle(grid, row, &col, target));

    return 0;
}