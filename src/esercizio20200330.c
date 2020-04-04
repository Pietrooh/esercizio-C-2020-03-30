#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//0, 1, 1, 2, 3, 5, 8, ... con n = 0, 1, 2, ...
unsigned long fibonacci(unsigned int n) {
	if (n == 0 || n == 1)
		return n;
	unsigned long a = 0, b = 1, c;
	for (int i = 2; i <= n; i++) {
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}
// TODO: metodo di bisezione per trovare threshold dipendente da int.
// Passare funzione come argomento

unsigned long* fibonacci_array(unsigned int n) {
	unsigned long *fib = malloc(sizeof(long) * (n + 1));
	if (fib == NULL) {
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	fib[0] = 0;
	if (n > 0)
		fib[1] = 1;
	for (int i = 2; i <= n; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	return fib;
}

void swap(unsigned long *a, unsigned long *b) {
	unsigned long c = *a;
	*a = *b;
	*b = c;
}

//scambia: array[i] e array[j], array[i+1] e array [j-1], ...
void reverse(unsigned long *array, unsigned int i, unsigned int j) {
	while (i < j)
		swap(&array[i++], &array[j--]);
}

void complete_reverse(unsigned long *array, unsigned int array_len) {
	reverse(array, 0, array_len - 1);
}

void bubble_sort(unsigned long *array, unsigned int array_len) {
	unsigned int new_array_len = 0;
	do {
		new_array_len = 0;
		for (int i = 1; i < array_len; i++)
			if (array[i - 1] > array[i]) {
				swap(&array[i - 1], &array[i]);
				new_array_len = i;
			}
		array_len = new_array_len;
	} while (array_len > 0);
}

void print_array_ulong(unsigned long *array, unsigned int array_len) {
	for (int i = 0; i < array_len; i++)
		printf("%lu ", array[i]);
	printf("\n");
}

unsigned int max_fib = 39;

int main(int argc, char *argv[]) {

// Usando il seguente loop si trova che il massimo valore per cui fibonacci(n) restituisce il valore corretto è, sul mio pc, 94.
// Si può ottenere lo stesso risultato usando la formula chiusa per la succ. di fibonacci (ottenuta, per Es., con la trasformata Z), trascurando gli infinitesimi a +inf e considerano il fatto che sizeof(unsigned long) = 8 sul mio pc
//	unsigned int n = 3;
//	unsigned long la = 1, lb = 2;// la = fibonacci(2), lb = fibonacci(3)
//
//	while (la < lb) {
//		la = lb;
//		lb = fibonacci(++n);
//	}
//	printf("%u", n);

	unsigned long *fibonacci_result = fibonacci_array(max_fib);

	printf("fibonacci_result = ");
	print_array_ulong(fibonacci_result, max_fib + 1);

	unsigned long *fibonacci_result_copy = malloc((max_fib + 1) * sizeof(long));

	if (fibonacci_result_copy == NULL) {
		perror("malloc error");
		exit(EXIT_FAILURE);
	}

	memcpy(fibonacci_result_copy, fibonacci_result,
			(max_fib + 1) * sizeof(long));

	printf("fibonacci_result_copy = ");
	print_array_ulong(fibonacci_result_copy, max_fib + 1);

	printf("\ncomplete_reverse\n");
	complete_reverse(fibonacci_result_copy, (max_fib + 1));
	printf("fibonacci_result_copy = ");
	print_array_ulong(fibonacci_result_copy, max_fib + 1);

	printf("\nbubble_sort\n");
	bubble_sort(fibonacci_result_copy, (max_fib + 1));
	printf("fibonacci_result_copy = ");
	print_array_ulong(fibonacci_result_copy, max_fib + 1);

	int diff = memcmp(fibonacci_result, fibonacci_result_copy, (max_fib + 1));
	printf("memcmp di fibonacci_result e fibonacci_result_copy: %d", diff);

	return 0;
}
