#include <iostream>
#include <omp.h>

void mul_matrix(int** A, int** B, int& C, int N) {

    C = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
             C += A[i][j];
        }
    }
}

void mul_matrix_parallel_1(int** A, int** B, int& C, int N) {
    int s = 0;
#pragma omp parallel for reduction(+:s)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            s += A[i][j];
        }
    }
    C = s;
}

void mul_matrix_parallel_2(int** A, int** B, int& C, int N) {
    int s = 0;
#pragma omp parallel for reduction(+:s)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            s += A[j][i];
        }
    }
    C = s;
}

int main() {
    const int N = 5000;

    int** A = new int* [N];
    int** B = new int* [N];
    int C = 0;
    for (int i = 0; i < N; ++i) {
        A[i] = new int[N];
        B[i] = new int[N];
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = i * N + j + 1;
            B[i][j] = (N - i - 1) * N + (N - j);
        }
    }

    std::cout << std::endl;

    double start;
    double end;
    start = omp_get_wtime();

    mul_matrix(A, B, C, N);

    end = omp_get_wtime();
    printf("Basic took %f seconds\n", end - start);

    mul_matrix_parallel_1(A, B, C, N);

    std::cout << C;
    std::cout << std::endl;

    start = omp_get_wtime();

    mul_matrix_parallel_1(A, B, C, N);

    end = omp_get_wtime();
    printf("Parallel 1 took %f seconds\n", end - start);

    std::cout << C;

    mul_matrix_parallel_2(A, B, C, N);

    std::cout << std::endl;

    C = 0;

    start = omp_get_wtime();

    mul_matrix_parallel_2(A, B, C, N);

    end = omp_get_wtime();
    printf("Parallel 2 took %f seconds\n", end - start);

    std::cout << C;

    for (int i = 0; i < N; ++i) {
        delete[] A[i];
        delete[] B[i];
    }
    delete[] A;
    delete[] B;

    return 0;
}