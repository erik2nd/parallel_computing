#include <iostream>
#include <omp.h>
#include <cmath>
using namespace std;

void bubble_sort_basic(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_parallel_static(int arr[], int n, int chunk_size=0) {
    for (int i = 0; i < n ; i++) {
#pragma omp parallel for schedule(static, chunk_size)
        for (int j = i % 2; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_parallel_dynamic(int arr[], int n, int chunk_size = 0) {
    for (int i = 0; i < n; i++) {
#pragma omp parallel for schedule(dynamic, chunk_size)
        for (int j = i % 2; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_parallel_guided(int arr[], int n, int chunk_size = 0) {
    for (int i = 0; i < n; i++) {
#pragma omp parallel for schedule(guided, chunk_size)
        for (int j = i % 2; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

bool is_sorted(int arr[], int size) {
    bool res = true;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            res = false;
            break;
        }
    }
    return res;
}

const int n = 100000;
int arr[n];

int main() {
    for (int i = n, j = 0; j < n; i--, j++) {
        arr[j] = i;
    }

    double start;
    double end;
    start = omp_get_wtime();

    bubble_sort_basic(arr, n);

    end = omp_get_wtime();
    cout << '\n';
    printf("Basic sort took %f seconds\n", end - start);

    if (is_sorted(arr, n)) cout << "Sorted correctly" << '\n';
    else cout << "Sorted incorrectly" << '\n';


    for (int k = 0; k < 11; k++) {

        int chunk_size = pow(2, k);

        for (int i = n, j = 0; j < n; i--, j++) {
            arr[j] = i;
        }

        start = omp_get_wtime();

        bubble_sort_parallel_static(arr, n, chunk_size);

        end = omp_get_wtime();
        cout << '\n';
        printf("Parallel static (chunk %d) sort took %f seconds\n", chunk_size, end - start);

        if (is_sorted(arr, n)) cout << "Sorted correctly" << '\n';
        else cout << "Sorted uncorrectly" << '\n';
    }

    for (int k = 0; k < 11; k++) {

        int chunk_size = pow(2, k);

        for (int i = n, j = 0; j < n; i--, j++) {
            arr[j] = i;
        }

        start = omp_get_wtime();

        bubble_sort_parallel_dynamic(arr, n, chunk_size);

        end = omp_get_wtime();
        cout << '\n';
        printf("Parallel dynamic (chunk %d) sort took %f seconds\n", chunk_size, end - start);

        if (is_sorted(arr, n)) cout << "Sorted correctly" << '\n';
        else cout << "Sorted uncorrectly" << '\n';
    }

    for (int k = 0; k < 11; k++) {

        int chunk_size = pow(2, k);

        for (int i = n, j = 0; j < n; i--, j++) {
            arr[j] = i;
        }

        start = omp_get_wtime();

        bubble_sort_parallel_guided(arr, n, chunk_size);

        end = omp_get_wtime();
        cout << '\n';
        printf("Parallel guided (chunk %d) sort took %f seconds\n", chunk_size, end - start);

        if (is_sorted(arr, n)) cout << "Sorted correctly" << '\n';
        else cout << "Sorted uncorrectly" << '\n';
    }

    return 0;
}