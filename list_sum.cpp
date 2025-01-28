#include <iostream>
#include <omp.h>

const int arr_size = 1000000;
int array[arr_size];

void init() {
    for (int i = 0; i < arr_size; i++) {
        array[i] = i;
    }
}

void sum_reduction() {
    init();

    int res = 0;
    for (int i = 0; i < arr_size; i++) {
        res += array[i];
    }

    int s = 0;

    double start;
    double end;
    start = omp_get_wtime();
#pragma omp parallel for reduction(+:s)
    for (int i = 0; i < arr_size; i++) {
        s += array[i];
    }
    end = omp_get_wtime();
    printf("Parallel array sum took %f seconds\n", end - start);

    int error = 0;
    if (res != s) error = 1;

    if (error) std::cout << "error" << '\n';
    else std::cout << "no error" << '\n';
}

struct Node {
    int data;
    Node* next;
};

void append(Node*& head, int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

int sum_list(Node* head) {
    int sum = 0;

    double start;
    double end;
    start = omp_get_wtime();
    for (int i = 0; i < arr_size; i++) {
        sum += head->data;
        head = head->next;
    }
    end = omp_get_wtime();
    printf("Basic list sum took %f seconds\n", end - start);
    return sum;
}

int main() {
    Node* head = nullptr;

    for (int i = 0; i < arr_size; i++) {
        append(head, i);
    }

    int sum = sum_list(head);
    std::cout << "Sum of list elements: " << sum << std::endl;

    std::cout << std::endl;

    sum_reduction();

    std::cout << std::endl;

    init();
    int res = 0;
    double start2;
    double end;
    start2 = omp_get_wtime();
    for (int i = 0; i < arr_size; i++) {
        res += array[i];
    }
    end = omp_get_wtime();
    printf("Basic took %f seconds\n", end - start2);
    std::cout << "Sum of array elements: " << res << std::endl;

    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}