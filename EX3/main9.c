#include <stdio.h>

int calculate_combinations(int n, int r) {
	int combinations = 1;
	int temp = n;
	for(int i = 1; i <= r; i++) {
		combinations *= n;
		n--;
	}
		for(int i = 1; i <= r; i++) {
		combinations /= i;
	}
	return combinations;
}

void print_sp(int i, int n) {
	for(; i<n; i++) {
		printf(" ");
	}
}

void print_pascal_number(int n) {
	for(int i = 0; i<=n; i++) {
		printf("%d ",calculate_combinations(n,i));
	}
	printf("\n");
}

int main() {
	int rows = 5;
	for(int i = 1; i<=rows; i++) {
		print_sp(i,rows);
		print_pascal_number(i-1);
	}
	return 0;
}
