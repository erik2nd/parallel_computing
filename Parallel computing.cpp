// 1 

//#include <iostream>
//
//int main()
//{
//#pragma omp parallel
//	std::cout << "Hello World!\n";
//}
//


// 2

//#include <iostream>
//#include <omp.h>
//
//double f(double x) {
//	return x * x * x;
//}
//
//double square_parallel(double a, double b, int n) {
//	double h = (b - a) / n; 
//	double res = 0.0;
//	int num_threads = 0;
//
//#pragma omp parallel 
//	num_threads = omp_get_num_threads();
//
//	double* array = new double[n] {0};
//
//#pragma omp parallel 
//	{
//		int thread_id = omp_get_thread_num();
//
//		std::cout << thread_id << ' ';
//
//		for (int i = thread_id; i < n; i += num_threads) {
//			double x1 = a + i * h;
//			double x2 = a + (i + 1) * h;
//			array[i] = ((f(x1) + f(x2)) / 2.0) * h;
//		}
//	}
//
//	for (int i = 0; i < n; i++) {
//		res += array[i];
//	}
//
//	return res;
//}
//
//double square(double a, double b, int n) {
//	double h = (b - a) / n;
//	double res = 0.0;
//
//		for (int i = 0; i < n; i++) {
//			double x1 = a + i * h;
//			double x2 = a + (i + 1) * h;
//			res += ((f(x1) + f(x2)) / 2.0) * h;
//		}
//	return res;
//}
//
//int main()
//{
//	int n = 100000;
//	std::cout << square(1, 10, n);
//	std::cout << '\n';
//	std::cout << square_parallel(1, 10, n);
//}

//
//#include <iostream>
//#include <omp.h>
//
//double f(double x) {
//	return x * x * x;
//}
//
//double square_parallel(double a, double b, int n) {
//	double h = (b - a) / n;
//	double res = 0.0;
//	int num_threads = 0;
//
//#pragma omp parallel 
//	num_threads = omp_get_num_threads();
//
//	double* array = new double[n] {0};
//
//#pragma omp parallel 
//	{
//		int thread_id = omp_get_thread_num();
//
//		std::cout << thread_id << ' ';
//
//		for (int i = thread_id; i < n; i += num_threads) {
//			double x1 = a + i * h;
//			double x2 = a + (i + 1) * h;
//			array[i] = ((f(x1) + f(x2)) / 2.0) * h;
//		}
//	}
//
//	for (int i = 0; i < n; i++) {
//		res += array[i];
//	}
//
//	return res;
//}
//
//double square(double a, double b, int n) {
//	double h = (b - a) / n;
//	double res = 0.0;
//
//	for (int i = 0; i < n; i++) {
//		double x1 = a + i * h;
//		double x2 = a + (i + 1) * h;
//		res += ((f(x1) + f(x2)) / 2.0) * h;
//	}
//	return res;
//}
//
//int main()
//{
//	int n = 100000;
//	std::cout << square(1, 10, n);
//	std::cout << '\n';
//	std::cout << square_parallel(1, 10, n);
//}


// 3

//#include <iostream>
//#include <omp.h>
//#include <random>
//using namespace std;
//
//const int size1 = 100000;
//
//int array1[size1];
//int array2[size1];
//int array3[size1];
//int array4[size1];
//
//void init() {
//    for (int i = 0; i < size1; ++i) {
//        array1[i] = i;
//    }
//    for (int i = 0; i < size1; ++i) {
//        array2[i] = i;
//    }
//
//    for (int i = 0; i < size1; ++i) {
//        array3[i] = 0;
//    }
//    for (int i = 0; i < size1; ++i) {
//        array4[i] = 0;
//    }
//}
//
//void alg1() {
// 
//
//    init();
//
//    for (int i = 0; i < size1; i++) {
//        array4[i] = array1[i] + array2[i];
//    }
//
//    double start;
//    double end;
//    start = omp_get_wtime();
//#pragma omp parallel
//    {
//        int thread_id = omp_get_thread_num();
//        int num_threads = omp_get_num_threads();
//
//        for (int i = thread_id; i < size1; i += num_threads) {
//            array3[i] = array1[i] + array2[i];
//        }
//    }
//    end = omp_get_wtime();
//    printf("Parallel 1 took %f seconds\n", end - start);
//
//    int error = 0;
//    for (int i = 0; i < size1; i++) {
//        if (array3[i] != array4[i]) {
//            error = 1;
//            break;
//        }
//    }
//
//    if (error) cout << "error";
//    else cout << "no error";
//}
//
//void alg2() {
//
//    init();
//
//    for (int i = 0; i < size1; i++) {
//        array4[i] = array1[i] + array2[i];
//    }
//
//    //int num_threads = 4;
//    //int part_size = size1 / num_threads;
//
//    double start2;
//    double end;
//    start2 = omp_get_wtime();
//#pragma omp parallel
//    {
//        int thread_id = omp_get_thread_num();
//        int num_threads = omp_get_num_threads();
//        int part_size = size1 / num_threads;
//        int start = thread_id * part_size;
//        int end = (thread_id == num_threads - 1) ? size1 : start + part_size;
//
//
//        for (int i = start; i < end; ++i) {
//            array3[i] = array1[i] + array2[i];
//        }
//    }
//    end = omp_get_wtime();
//    cout << '\n';
//    printf("Parallel 2 took %f seconds\n", end - start2);
//    
//    int error = 0;
//    for (int i = 0; i < size1; i++) {
//        if (array3[i] != array4[i]) {
//            error = 1;
//            break;
//        }
//    }
//
//    if (error) cout << "error";
//    else cout << "no error";
//}
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//
//     alg1();
//     alg2();
//
//     init();
//     double start2;
//     double end;
//     start2 = omp_get_wtime();
//     for (int i = 0; i < size1; i++) {
//         array4[i] = array1[i] + array2[i];
//     }
//     end = omp_get_wtime();
//     cout << '\n';
//     printf("Basic took %f seconds\n", end - start2);
//
//    return 0;
//}


// 4
//
//#include <iostream>
//#include <omp.h>
//#include <cmath>
//using namespace std;
//
//void bubble_sort_basic(int arr[], int n) {
//    for (int i = 0; i < n - 1; i++) {
//        for (int j = 0; j < n - i - 1; j++) {
//            if (arr[j] > arr[j + 1]) {
//                int temp = arr[j];
//                arr[j] = arr[j + 1];
//                arr[j + 1] = temp;
//            }
//        }
//    }
//}
//
//void bubble_sort_parallel_static(int arr[], int n, int chunk_size=0) {
//    for (int i = 0; i < n ; i++) {
//#pragma omp parallel for schedule(static, chunk_size)
//        for (int j = i % 2; j < n - 1; j += 2) {
//            if (arr[j] > arr[j + 1]) {
//                int temp = arr[j];
//                arr[j] = arr[j + 1];
//                arr[j + 1] = temp;
//            }
//        }
//    }
//}
//
//void bubble_sort_parallel_dynamic(int arr[], int n, int chunk_size = 0) {
//    for (int i = 0; i < n; i++) {
//#pragma omp parallel for schedule(dynamic, chunk_size)
//        for (int j = i % 2; j < n - 1; j += 2) {
//            if (arr[j] > arr[j + 1]) {
//                int temp = arr[j];
//                arr[j] = arr[j + 1];
//                arr[j + 1] = temp;
//            }
//        }
//    }
//}
//
//void bubble_sort_parallel_guided(int arr[], int n, int chunk_size = 0) {
//    for (int i = 0; i < n; i++) {
//#pragma omp parallel for schedule(guided, chunk_size)
//        for (int j = i % 2; j < n - 1; j += 2) {
//            if (arr[j] > arr[j + 1]) {
//                int temp = arr[j];
//                arr[j] = arr[j + 1];
//                arr[j + 1] = temp;
//            }
//        }
//    }
//}
//
//void print_array(int arr[], int size) {
//    for (int i = 0; i < size; i++) {
//        cout << arr[i] << " ";
//    }
//    cout << endl;
//}
//
//bool is_sorted(int arr[], int size) {
//    bool res = true;
//    for (int i = 0; i < size - 1; i++) {
//        if (arr[i] > arr[i + 1]) {
//            res = false;
//            break;
//        }
//    }
//    return res;
//}
//
//const int n = 100000;
//int arr[n];
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//
//
//    for (int i = n, j = 0; j < n; i--, j++) {
//        arr[j] = i;
//    }
//
//    //cout << "Source array: ";
//    //print_array(arr, n);
//    //cout << '\n';
//
//    double start;
//    double end;
//    start = omp_get_wtime();
//
//    bubble_sort_basic(arr, n);
//
//    end = omp_get_wtime();
//    cout << '\n';
//    printf("Basic sort took %f seconds\n", end - start);
// 
//    //cout << "Sorted array: ";
//    //print_array(arr, n);
//
//    if (is_sorted(arr, n)) cout << "Sorted correctly" << '\n';
//    else cout << "Sorted incorrectly" << '\n';
//
//
//    for (int k = 0; k < 11; k++) {
//
//        int chunk_size = pow(2, k);
//
//        for (int i = n, j = 0; j < n; i--, j++) {
//            arr[j] = i;
//        }
//
//        start = omp_get_wtime();
//
//        bubble_sort_parallel_static(arr, n, chunk_size);
//
//        end = omp_get_wtime();
//        cout << '\n';
//        printf("Parallel static (chunk %d) sort took %f seconds\n", chunk_size, end - start);
//
//        if (is_sorted(arr, n)) cout << "Sorted correctly" << '\n';
//        else cout << "Sorted uncorrectly" << '\n';
//    }
//
//    for (int k = 0; k < 11; k++) {
//
//        int chunk_size = pow(2, k);
//
//        for (int i = n, j = 0; j < n; i--, j++) {
//            arr[j] = i;
//        }
//
//        start = omp_get_wtime();
//
//        bubble_sort_parallel_dynamic(arr, n, chunk_size);
//
//        end = omp_get_wtime();
//        cout << '\n';
//        printf("Parallel dynamic (chunk %d) sort took %f seconds\n", chunk_size, end - start);
//
//        if (is_sorted(arr, n)) cout << "Sorted correctly" << '\n';
//        else cout << "Sorted uncorrectly" << '\n';
//    }
//
//    for (int k = 0; k < 11; k++) {
//
//        int chunk_size = pow(2, k);
//
//        for (int i = n, j = 0; j < n; i--, j++) {
//            arr[j] = i;
//        }
//
//        start = omp_get_wtime();
//
//        bubble_sort_parallel_guided(arr, n, chunk_size);
//
//        end = omp_get_wtime();
//        cout << '\n';
//        printf("Parallel guided (chunk %d) sort took %f seconds\n", chunk_size, end - start);
//
//        if (is_sorted(arr, n)) cout << "Sorted correctly" << '\n';
//        else cout << "Sorted uncorrectly" << '\n';
//    }
//
//    //cout << "Sorted array: ";
//    //print_array(arr, n);
//
//    return 0;
//}


// 5

//
//#include <iostream>
//#include <omp.h>
//#include <random>
//using namespace std;
//
//const int size1 = 1000000;
//
//int array1[size1];
//int array2[size1];
//
//
//void init() {
//    for (int i = 0; i < size1; ++i) {
//        array1[i] = i;
//    }
//    for (int i = 0; i < size1; ++i) {
//        array2[i] = i;
//    }
//}
//
//void sum_reduction() {
// 
//    init();
//
//    int res = 0;
//    for (int i = 0; i < size1; i++) {
//        res += array1[i] + array2[i];
//    }
//
//    int s = 0;
//
//    double start;
//    double end;
//    start = omp_get_wtime();
//#pragma omp parallel for reduction(+:s)
//    for (int i = 0; i < size1; i++) {
//        s += array1[i] + array2[i];
//    }
//    end = omp_get_wtime();
//    printf("Parallel reduction took %f seconds\n", end - start);
//
//    int error = 0;
//    if (res != s) error = 1;
//
//    if (error) std::cout << "error" << '\n';
//    else std::cout << "no error" << '\n';
//}
//
//void sum_atomic() {
//
//    init();
//
//    int res = 0;
//    for (int i = 0; i < size1; i++) {
//        res += array1[i] + array2[i];
//    }
//
//    int s = 0;
//
//    double start;
//    double end;
//    start = omp_get_wtime();
//#pragma omp parallel for
//    for (int i = 0; i < size1; i++) {
//#pragma omp atomic
//        s += array1[i] + array2[i];
//    }
//    end = omp_get_wtime();
//    printf("Parallel atomic took %f seconds\n", end - start);
//
//    int error = 0;
//    if (res != s) error = 1;
//
//    if (error) std::cout << "error" << '\n';
//    else std::cout << "no error" << '\n';
//}
//
//
//void sum_critical() {
//
//    init();
//
//    int res = 0;
//    for (int i = 0; i < size1; i++) {
//        res += array1[i] + array2[i];
//    }
//
//    int s = 0;
//
//    double start;
//    double end;
//    start = omp_get_wtime();
//#pragma omp parallel for
//    for (int i = 0; i < size1; i++) {
//#pragma omp critical
//        s += array1[i] + array2[i];
//    }
//    end = omp_get_wtime();
//    printf("Parallel critical took %f seconds\n", end - start);
//
//    int error = 0;
//    if (res != s) error = 1;
//
//    if (error) std::cout << "error" << '\n';
//    else std::cout << "no error" << '\n';
//}
//
//void sum_mutecs() {
//
//    init();
//
//    int res = 0;
//    for (int i = 0; i < size1; i++) {
//        res += array1[i] + array2[i];
//    }
//
//    int s = 0;
//
//    double start;
//    double end;
//    start = omp_get_wtime();
//
//    omp_lock_t lock;
//    omp_init_lock(&lock);
//
//#pragma omp parallel for shared(lock)
//    for (int i = 0; i < size1; i++) {
//        omp_set_lock(&lock);
//        s += array1[i] + array2[i];
//        omp_unset_lock(&lock);
//    }
//    omp_destroy_lock(&lock);
//    end = omp_get_wtime();
//    printf("Parallel mutecs took %f seconds\n", end - start);
//
//    int error = 0;
//    if (res != s) error = 1;
//
//    if (error) std::cout << "error" << '\n';
//    else std::cout << "no error" << '\n';
//}
//
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//
//    sum_reduction();
//    std::cout << '\n';
//
//    sum_atomic();
//    std::cout << '\n';
//
//    sum_critical();
//    std::cout << '\n';
//
//    sum_mutecs();
//    std::cout << '\n';
//
//     init();
//     int res = 0;
//     double start2;
//     double end;
//     start2 = omp_get_wtime();
//     for (int i = 0; i < size1; i++) {
//         res += array1[i] + array2[i];
//     }
//     end = omp_get_wtime();
//     printf("Basic took %f seconds\n", end - start2);
//
//    return 0;
//}


// 6
//
//#include <iostream>
//#include <omp.h>
//
//
//void shift_left(int* arr, int size) {
//    int temp = arr[0];
//
//#pragma omp parallel for
//    for (int i = 0; i < size - 1; ++i) {
//        arr[i] = arr[i + 1];
//    }
//
//
//    arr[size - 1] = temp; 
//}
//
//
//const int arr_size = 10;
//int arr[arr_size];
//
//void init() {
//    for (int i = 0; i < arr_size; i++) {
//        arr[i] = i;
//    }
//}
//
//int main() {
//    init();
//
//    std::cout << "Source array: ";
//    for (int i = 0; i < arr_size; ++i) {
//        std::cout << arr[i] << " ";
//    }
//    std::cout << std::endl;
//
//    shift_left(arr, arr_size);
//
//    std::cout << "Array after shift on 1 element left: ";
//    for (int i = 0; i < arr_size; ++i) {
//        std::cout << arr[i] << " ";
//    }
//    std::cout << std::endl;
//
//    return 0;
//}
//
//#include <iostream>
//#include <omp.h>
//
//const int arr_size = 1000000;
//int array[arr_size];
//
//
//void init() {
//    for (int i = 0; i < arr_size; i++) {
//        array[i] = i;
//    }
//}
//
//void sum_reduction() {
// 
//    init();
//
//    int res = 0;
//    for (int i = 0; i < arr_size; i++) {
//        res += array[i];
//    }
//
//    int s = 0;
//
//    double start;
//    double end;
//    start = omp_get_wtime();
//#pragma omp parallel for reduction(+:s)
//    for (int i = 0; i < arr_size; i++) {
//        s += array[i];
//    }
//    end = omp_get_wtime();
//    printf("Parallel array sum took %f seconds\n", end - start);
//
//    int error = 0;
//    if (res != s) error = 1;
//
//    if (error) std::cout << "error" << '\n';
//    else std::cout << "no error" << '\n';
//}
//
//struct Node {
//    int data;
//    Node* next;
//};
//
//void append(Node*& head, int data) {
//    Node* newNode = new Node;
//    newNode->data = data;
//    newNode->next = head;
//    head = newNode;
//}
//
//void printList(Node* head) {
//    Node* temp = head;
//    while (temp != nullptr) {
//        std::cout << temp->data << " ";
//        temp = temp->next;
//    }
//    std::cout << std::endl;
//}
//
//int sum_list(Node* head) {
//    int sum = 0;
//
//    double start;
//    double end;
//    start = omp_get_wtime();
//    for (int i = 0; i < arr_size; i++) {
//        sum += head->data;
//        head = head->next;
//    }
//    end = omp_get_wtime();
//    printf("Basic list sum took %f seconds\n", end - start);
//    return sum;
//}
//
//int main() {
//    Node* head = nullptr;
//
//    for (int i = 0; i < arr_size; i++) {
//        append(head, i);
//    }
//
//    //std::cout << "List: ";
//    //printList(head);
//
//    int sum = sum_list(head);
//    std::cout << "Sum of list elements: " << sum << std::endl;
//
//    std::cout << std::endl;
//
//    sum_reduction();
//
//    std::cout << std::endl;
//
//     init();
//     int res = 0;
//     double start2;
//     double end;
//     start2 = omp_get_wtime();
//     for (int i = 0; i < arr_size; i++) {
//         res += array[i];
//     }
//     end = omp_get_wtime();
//     printf("Basic took %f seconds\n", end - start2);
//     std::cout << "Sum of array elements: " << res << std::endl;
//
//    while (head != nullptr) {
//        Node* temp = head;
//        head = head->next;
//        delete temp;
//    }
//
//    return 0;
//}
//
//#include <iostream>
//#include <omp.h>
//
//void mul_matrix(int** A, int** B, int& C, int N) {
//
//    C = 0;
//    for (int i = 0; i < N; ++i) {
//        for (int j = 0; j < N; ++j) {
//             C += A[i][j];
//        }
//    }
//}
//
//void mul_matrix_parallel_1(int** A, int** B, int& C, int N) {
//    int s = 0;
//#pragma omp parallel for reduction(+:s)
//    for (int i = 0; i < N; ++i) {
//        for (int j = 0; j < N; ++j) {
//            s += A[i][j];
//        }
//    }
//    C = s;
//}
//
//void mul_matrix_parallel_2(int** A, int** B, int& C, int N) {
//    int s = 0;
//#pragma omp parallel for reduction(+:s)
//    for (int i = 0; i < N; ++i) {
//        for (int j = 0; j < N; ++j) {
//            s += A[j][i];
//        }
//    }
//    C = s;
//}
//
//int main() {
//    const int N = 5000;
//
//    int** A = new int* [N];
//    int** B = new int* [N];
//    int C = 0;
//    for (int i = 0; i < N; ++i) {
//        A[i] = new int[N];
//        B[i] = new int[N];
//    }
//    for (int i = 0; i < N; ++i) {
//        for (int j = 0; j < N; ++j) {
//            A[i][j] = i * N + j + 1;
//            B[i][j] = (N - i - 1) * N + (N - j);
//        }
//    }
//
//    std::cout << std::endl;
//
//    //std::cout << "A:" << std::endl;
//    //for (int i = 0; i < N; ++i) {
//    //    for (int j = 0; j < N; ++j) {
//    //        std::cout << A[i][j] << " ";
//    //    }
//    //    std::cout << std::endl;
//    //}
//
//    //std::cout << std::endl;
//
//    //std::cout << "B:" << std::endl;
//    //for (int i = 0; i < N; ++i) {
//    //    for (int j = 0; j < N; ++j) {
//    //        std::cout << B[i][j] << " ";
//    //    }
//    //    std::cout << std::endl;
//    //}
//
//    std::cout << std::endl;
//
//    double start;
//    double end;
//    start = omp_get_wtime();
//
//    mul_matrix(A, B, C, N);
//
//    end = omp_get_wtime();
//    printf("Basic took %f seconds\n", end - start);
//
//    /*std::cout << "Result basic:" << std::endl;
//    for (int i = 0; i < N; ++i) {
//        for (int j = 0; j < N; ++j) {
//            std::cout << C[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }*/
//
//    mul_matrix_parallel_1(A, B, C, N);
//
//    std::cout << C;
//
//    std::cout << std::endl;
//
//    start = omp_get_wtime();
//
//    mul_matrix_parallel_1(A, B, C, N);
//
//    end = omp_get_wtime();
//    printf("Parallel 1 took %f seconds\n", end - start);
//
//    std::cout << C;
//
//    /*std::cout << "Result parallel:" << std::endl;
//    for (int i = 0; i < N; ++i) {
//        for (int j = 0; j < N; ++j) {
//            std::cout << C[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }*/
//
//    mul_matrix_parallel_2(A, B, C, N);
//
//    std::cout << std::endl;
//
//    C = 0;
//
//    start = omp_get_wtime();
//
//    mul_matrix_parallel_2(A, B, C, N);
//
//    end = omp_get_wtime();
//    printf("Parallel 2 took %f seconds\n", end - start);
//
//    std::cout << C;
//
//
//    for (int i = 0; i < N; ++i) {
//        delete[] A[i];
//        delete[] B[i];
//        //delete[] C[i];
//    }
//    delete[] A;
//    delete[] B;
//    //delete[] C;
//
//    return 0;
//}
//
//
//
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

void init(int *arr, int n) {
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

    std::string script = "C:\\Users\\eriki\\PycharmProjects\\computer_vision\\other\\diagram.py"; 
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
    /*fake_parallel();

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
    
    build_diagram();*/

    omp_set_num_threads(5);

    printf("%d", omp_get_max_threads());

//#pragma omp parallel
//    {
//        int thread_id = omp_get_thread_num();
//        printf("%d", thread_id);
//    }

    return 0;
}