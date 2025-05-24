#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int move = 5;
int size = 0;
size_t bsize = 0; // board's byte-size
int max = 0;

// operate and return localMax
int mutate(int board[400], int (*calc)(int, int), int *isMoved) {
    int max = 0;
    for (int i = 0; i < size; i++) { // col
        int filledIndex = 0;
        int keptNumber = 0;
        for (int j = 0; j < size; j++) { // row
            int number = board[calc(i, j)];
            if (!number) continue;
            if (max < number) max = number; // update max
            // keep
            if (!keptNumber) {
                *isMoved = 1;
                keptNumber = number;
                continue;
            }
            // merge
            int idx = calc(i, filledIndex);
            if (keptNumber == number) {
                *isMoved = 1; // moved
                number <<= 1; // double
                if (max < number) max = number; // update max
                board[idx] = number;
                keptNumber = 0;
                filledIndex++;
            }
            // change
            else {
                *isMoved = 1; // moved
                board[idx] = keptNumber;
                keptNumber = number;
                filledIndex++;
            }
        }
        // flush
        board[calc(i, filledIndex++)] = keptNumber;
        for (int j = filledIndex; j < size; j++) {
            board[calc(i, j)] = 0;
        }
    }
    return max;
}

// operate by index convert
int left(int i, int j) {
    return i * size + j;
}

int right(int i, int j) {
    return i * size + (size - j - 1);
}

int up(int i, int j) {
    return j * size + i;
}

int down(int i, int j) {
    return (size - j - 1) * size + i;
}

int (*ops[4])(int, int) = { left, right, up, down };

// step
int game(int board[400], int remain, int noMoveFlag) {
    remain--;
    int newBoard[400] = { 0, };
    int localMax = 0;
    int maxMult = 1 << (remain - 1); // for early return
    int result = 0;

    for (int i = 0; i < 4; i++) {
        if (noMoveFlag == i) continue; // check this direction has no effect
        int isMoved = 0;
        memcpy(newBoard, board, bsize);
        result = mutate(newBoard, ops[i], &isMoved); // move once
        if (remain && result * maxMult >= max) { // check this game might create new high score
            result = game(newBoard, remain, isMoved ? -1 : i);
        }
        if (localMax < result) localMax = result;
    }
    if (max < localMax) max = localMax;

    return localMax;
}

int main() {
    scanf("%d", &size);
    int board[400] = { 0, };
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &board[i * size + j]);
        }
    }
    bsize = sizeof(int) * size * size;
    game(board, move, -1);
    printf("%d", max);
}
