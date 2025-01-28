#include <iostream>
#include <omp.h>
#include <random>
using namespace std;

const int size1 = 100000;

int array1[size1];
int array2[size1];
int array3[size1];
int array4[size1];

void init() {
    for (int i = 0; i < size1; ++i) {
        array1[i] = i;
    }
    for (int i = 0; i < size1; ++i) {
        array2[i] = i;
    }

    for (int i = 0; i < size1; ++i) {
        array3[i] = 0;
    }
    for (int i = 0; i < size1; ++i) {
        array4[i] = 0;
    }
}

void alg1() {
    init();

    for (int i = 0; i < size1; i++) {
        array4[i] = array1[i] + array2[i];
    }

    double start;
    double end;
    start = omp_get_wtime();
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        for (int i = thread_id; i < size1; i += num_threads) {
            array3[i] = array1[i] + array2[i];
        }
    }
    end = omp_get_wtime();
    printf("Parallel 1 took %f seconds\n", end - start);

    int error = 0;
    for (int i = 0; i < size1; i++) {
        if (array3[i] != array4[i]) {
            error = 1;
            break;
        }
    }

    if (error) cout << "error";
    else cout << "no error";
}

void alg2() {
    init();

    for (int i = 0; i < size1; i++) {
        array4[i] = array1[i] + array2[i];
    }

    double start2;
    double end;
    start2 = omp_get_wtime();
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int part_size = size1 / num_threads;
        int start = thread_id * part_size;
        int end = (thread_id == num_threads - 1) ? size1 : start + part_size;


        for (int i = start; i < end; ++i) {
            array3[i] = array1[i] + array2[i];
        }
    }
    end = omp_get_wtime();
    cout << '\n';
    printf("Parallel 2 took %f seconds\n", end - start2);
    
    int error = 0;
    for (int i = 0; i < size1; i++) {
        if (array3[i] != array4[i]) {
            error = 1;
            break;
        }
    }

    if (error) cout << "error";
    else cout << "no error";
}

int main() {
    alg1();
    alg2();

    init();
    double start2;
    double end;
    start2 = omp_get_wtime();
    for (int i = 0; i < size1; i++) {
        array4[i] = array1[i] + array2[i];
    }
    end = omp_get_wtime();
    cout << '\n';
    printf("Basic took %f seconds\n", end - start2);

    return 0;
}