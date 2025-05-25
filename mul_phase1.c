#include <stdio.h>
#include "data.h"
#define ROWS_A 4
#define COLS_A 8
#define ROWS_B 8
#define COLS_B 4
#define NUM_BLOCKS 3

typedef struct {
    unsigned int data[ROWS_A][COLS_A];
} MatrixA;

typedef struct {
    unsigned int data[ROWS_B][COLS_B];
} MatrixB;

typedef struct {
    unsigned int data[ROWS_A][COLS_B];
} MatrixResult;


// 加载一块 input_stimuli 的数据为矩阵
void load_matrix_a(MatrixA* mat, const unsigned int* input_block) {
    for (int col = 0; col < COLS_A; col++) {
        for (int row = 0; row < ROWS_A; row++) {
            mat->data[row][col] = *input_block++;
        }
    }
}

// 加载 ROM 系数矩阵
void load_matrix_b(MatrixB* mat, const unsigned int* coeffs) {
    for (int col = 0; col < COLS_B; col++) {
        for (int row = 0; row < ROWS_B; row++) {
            mat->data[row][col] = *coeffs++;
        }
    }
}

// 矩阵乘法：result = A × B
void multiply_matrices(const MatrixA* A, const MatrixB* B, MatrixResult* result) {
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            unsigned int sum = 0;
            for (int k = 0; k < COLS_A; k++) {
                sum += A->data[i][k] * B->data[k][j];
            }
            result->data[i][j] = sum;
        }
    }
}

// 打印矩阵
void print_result(const MatrixResult* result) {
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            printf("%5u ", result->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    MatrixB coeff_matrix;
    load_matrix_b(&coeff_matrix, rom_coeff);

    for (int block = 0; block < NUM_BLOCKS; block++) {
        const unsigned int* input_block = input_stimuli + block * ROWS_A * COLS_A;

        MatrixA input_matrix;
        MatrixResult result;

        load_matrix_a(&input_matrix, input_block);
        multiply_matrices(&input_matrix, &coeff_matrix, &result);

        printf("Result Matrix #%d:\n", block + 1);
        print_result(&result);
    }

    return 0;
}
