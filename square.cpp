#include <iostream>
#include <omp.h>

double f(double x) {
	return x * x * x;
}

double square_parallel(double a, double b, int n) {
	double h = (b - a) / n;
	double res = 0.0;
	int num_threads = 0;

#pragma omp parallel 
	num_threads = omp_get_num_threads();

	double* array = new double[n] {0};

#pragma omp parallel 
	{
		int thread_id = omp_get_thread_num();

		std::cout << thread_id << ' ';

		for (int i = thread_id; i < n; i += num_threads) {
			double x1 = a + i * h;
			double x2 = a + (i + 1) * h;
			array[i] = ((f(x1) + f(x2)) / 2.0) * h;
		}
	}

	for (int i = 0; i < n; i++) {
		res += array[i];
	}

	return res;
}

double square(double a, double b, int n) {
	double h = (b - a) / n;
	double res = 0.0;

	for (int i = 0; i < n; i++) {
		double x1 = a + i * h;
		double x2 = a + (i + 1) * h;
		res += ((f(x1) + f(x2)) / 2.0) * h;
	}
	return res;
}

int main()
{
	int n = 100000;
	std::cout << square(1, 10, n);
	std::cout << '\n';
	std::cout << square_parallel(1, 10, n);
}