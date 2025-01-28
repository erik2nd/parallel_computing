#include <iostream>
#include <omp.h>
#include <random>
using namespace std;

const int size1 = 1000000;

int array1[size1];
int array2[size1];

void init() {
    for (int i = 0; i < size1; ++i) {
        array1[i] = i;
    }
    for (int i = 0; i < size1; ++i) {
        array2[i] = i;
    }
}

void sum_reduction() {
    init();

    int res = 0;
    for (int i = 0; i < size1; i++) {
        res += array1[i] + array2[i];
    }

    int s = 0;

    double start;
    double end;
    start = omp_get_wtime();
#pragma omp parallel for reduction(+:s)
    for (int i = 0; i < size1; i++) {
        s += array1[i] + array2[i];
    }
    end = omp_get_wtime();
    printf("Parallel reduction took %f seconds\n", end - start);

    int error = 0;
    if (res != s) error = 1;

    if (error) std::cout << "error" << '\n';
    else std::cout << "no error" << '\n';
}

void sum_atomic() {

    init();

    int res = 0;
    for (int i = 0; i < size1; i++) {
        res += array1[i] + array2[i];
    }

    int s = 0;

    double start;
    double end;
    start = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < size1; i++) {
#pragma omp atomic
        s += array1[i] + array2[i];
    }
    end = omp_get_wtime();
    printf("Parallel atomic took %f seconds\n", end - start);

    int error = 0;
    if (res != s) error = 1;

    if (error) std::cout << "error" << '\n';
    else std::cout << "no error" << '\n';
}


void sum_critical() {

    init();

    int res = 0;
    for (int i = 0; i < size1; i++) {
        res += array1[i] + array2[i];
    }

    int s = 0;

    double start;
    double end;
    start = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < size1; i++) {
#pragma omp critical
        s += array1[i] + array2[i];
    }
    end = omp_get_wtime();
    printf("Parallel critical took %f seconds\n", end - start);

    int error = 0;
    if (res != s) error = 1;

    if (error) std::cout << "error" << '\n';
    else std::cout << "no error" << '\n';
}

void sum_mutecs() {

    init();

    int res = 0;
    for (int i = 0; i < size1; i++) {
        res += array1[i] + array2[i];
    }

    int s = 0;

    double start;
    double end;
    start = omp_get_wtime();

    omp_lock_t lock;
    omp_init_lock(&lock);

#pragma omp parallel for shared(lock)
    for (int i = 0; i < size1; i++) {
        omp_set_lock(&lock);
        s += array1[i] + array2[i];
        omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
    end = omp_get_wtime();
    printf("Parallel mutecs took %f seconds\n", end - start);

    int error = 0;
    if (res != s) error = 1;

    if (error) std::cout << "error" << '\n';
    else std::cout << "no error" << '\n';
}


int main() {
    setlocale(LC_ALL, "Russian");

    sum_reduction();
    std::cout << '\n';

    sum_atomic();
    std::cout << '\n';

    sum_critical();
    std::cout << '\n';

    sum_mutecs();
    std::cout << '\n';

    init();
    int res = 0;
    double start2;
    double end;
    start2 = omp_get_wtime();
    for (int i = 0; i < size1; i++) {
        res += array1[i] + array2[i];
    }
    end = omp_get_wtime();
    printf("Basic took %f seconds\n", end - start2);

    return 0;
}