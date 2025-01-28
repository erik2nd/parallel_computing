#include <iostream>
#include <fstream>
#include <omp.h>

std::string path = "size.txt";

int read_size_from_file() {
    int M = 0;
    std::ifstream file(path);
    if (file.is_open()) {
        file >> M;
        file.close();
    }
    else {
        std::cerr << "Unable to open file " << path << '\n';
    }
    return M;
}

void write_size_to_file(int M) {
    std::ofstream file(path);
    if (file.is_open()) {
        file << M;
        file.close();
        std::cout << "Threshold size M saved to " << path << '\n';
    }
    else {
        std::cerr << "Unable to open file " << path << '\n';
    }
}

void fake_parallel() {
#pragma omp parallel
    {
        int test = 0;
    }
}

void init(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = 1;
    }
}

double partial_sum_basic(int* arr, int n) {
    double start, end;
    start = omp_get_wtime();

    for (int i = 1; i < n; i++) {
        arr[i] += arr[i - 1];
    }

    end = omp_get_wtime();
    printf("Basic took %f seconds\n", end - start);

    return end - start;
}

double partial_sum_parallel(int* arr, int n) {
    double start, end;
    start = omp_get_wtime();
    int num_threads = 0;

#pragma omp parallel 
    num_threads = omp_get_num_threads();

    int part_size = (n + num_threads - 1) / num_threads;

#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int start = thread_id * part_size;
        int end = (thread_id == num_threads - 1) ? n : start + part_size;

        for (int i = start + 1; i < end; i++) {
            arr[i] += arr[i - 1];
        }
    }

    for (int i = part_size * 2 - 1; i < n; i += part_size) {
        arr[i] += arr[i - part_size];
        if (i != n - 1 && i + part_size > n - 1) {
            arr[n - 1] += arr[i];
        }
    }

#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int start = thread_id * part_size;
        int end = (thread_id == num_threads - 1) ? n : start + part_size;

        if (thread_id != 0 && thread_id * part_size - 1 < n) {
            int last = arr[thread_id * part_size - 1];
            for (int i = start; i < end - 1; i++) {
                arr[i] += last;
            }
        }
    }

    end = omp_get_wtime();
    printf("Parallel took %f seconds\n", end - start);

    return end - start;
}

void partial_sum_hybrid(int* arr, int n) {
    int M = read_size_from_file();
    if (n >= M) partial_sum_parallel(arr, n);
    else partial_sum_basic(arr, n);
}

bool is_sum_correct(int* arr1, int* arr2, int n) {
    bool res = true;
    for (int i = 0; i < n; i++) {
        if (arr1[i] != arr2[i]) {
            res = false;
            break;
        }
    }
    return res;
}

void find_array_size() {
    int M = 0;
    int min = 300000;
    int max = 100000000;
    int t = 100000;
    int count = 100;
    int valid_count = 0;

    for (int i = min; i <= max; i += t) {
        double basic_time = 0;
        double parallel_time = 0;

        for (int j = 0; j < count; j++) {
            int* arr1 = new int[i];
            int* arr2 = new int[i];

            init(arr1, i);
            basic_time += partial_sum_basic(arr1, i);


            init(arr2, i);
            parallel_time += partial_sum_parallel(arr2, i);

            if (!is_sum_correct(arr1, arr2, i)) {
                std::cerr << "Error: Partial sum check failed!" << std::endl;
                std::exit(EXIT_FAILURE);
            }

            delete[] arr1;
            delete[] arr2;
        }

        basic_time = basic_time / count;
        parallel_time = parallel_time / count;

        if (parallel_time <= basic_time * 0.8) {
            valid_count++;
            if (valid_count == 4) {
                M = i - 3 * t;
                break;
            }
        }
        else {
            valid_count = 0;
        }
    }

    write_size_to_file(M);
}

void build_diagram() {
    std::string data = "data.csv";
    int M = read_size_from_file();
    int N = 2 * M;
    int* arr1 = new int[N];
    int* arr2 = new int[N];
    init(arr1, N);
    init(arr2, N);

    partial_sum_basic(arr2, N);

    std::ofstream file(data);
    if (!file.is_open()) {
        std::cerr << "Unable to open file" << '\n';
        delete[] arr1;
        delete[] arr2;
        return;
    }

    file << "Threads,Time\n";
    int count = 10;

    for (int num_threads = 1; num_threads <= 16; num_threads++) {
        omp_set_num_threads(num_threads);
        double elapsed_time = 0;

        for (int j = 0; j < count; j++) {
            elapsed_time += partial_sum_parallel(arr1, N);
            if (!is_sum_correct(arr1, arr2, N)) {
                std::cerr << "Error: Partial sum check failed!" << std::endl;
                std::exit(EXIT_FAILURE);
            }
            init(arr1, N);
        }

        elapsed_time = elapsed_time / count;
        file << num_threads << "," << elapsed_time << "\n";
        init(arr1, N);
    }

    file.close();
    delete[] arr1;
    delete[] arr2;

    omp_set_num_threads(omp_get_max_threads());

    std::string script = "diagram.py";
    std::string command = "py " + script;

    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Error executing script\n";
    }
    else {
        std::cout << "Script executed successfully\n";
    }
}

int main() {
    fake_parallel();

    find_array_size();

    const int n = 500000;
    int* arr1 = new int[n];
    int* arr2 = new int[n];

    init(arr1, n);
    init(arr2, n);

    partial_sum_basic(arr2, n);
    partial_sum_hybrid(arr1, n);

    if (!is_sum_correct(arr1, arr2, n)) std::cout << "\nError" << '\n';
    else std::cout << "\nNo error" << '\n';

    build_diagram();

    return 0;
}