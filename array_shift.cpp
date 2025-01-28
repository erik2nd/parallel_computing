#include <iostream>
#include <omp.h>

void shift_left(int* arr, int size) {
    int temp = arr[0];

#pragma omp parallel for
    for (int i = 0; i < size - 1; ++i) {
        arr[i] = arr[i + 1];
    }

    arr[size - 1] = temp; 
}

const int arr_size = 10;
int arr[arr_size];

void init() {
    for (int i = 0; i < arr_size; i++) {
        arr[i] = i;
    }
}

int main() {
    init();

    std::cout << "Source array: ";
    for (int i = 0; i < arr_size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    shift_left(arr, arr_size);

    std::cout << "Array after shift on 1 element left: ";
    for (int i = 0; i < arr_size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}