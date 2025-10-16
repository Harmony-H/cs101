#include <stdio.h>
void move_the_rod(int n, char from_rod, char to_rod, char aux_rod) {
	if(n==1) {
		printf("Move disk %d from rod %c to rod %c\n", n,from_rod, to_rod);
		return;
	}
	move_the_rod(n-1,from_rod, aux_rod, to_rod);
	printf("Move disk %d from rod %c to rod %c\n", n,from_rod, to_rod);
	move_the_rod(n-1, aux_rod, to_rod, from_rod);
}

int main() {
	int n=3;
	move_the_rod(n, 'A', 'B', 'C');
	return 0;
}
