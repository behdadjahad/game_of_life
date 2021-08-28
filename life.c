#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define size 22
#define alive 1
#define dead 0
#define wall -1

void initial ();
void underpopulate ();
void overpopulate ();
void repopulate ();
int check (int i , int j);
void alive_cell ();
void print ();
void stablize ();

int plate_1[size][size];
int plate_2[size][size];

int main ()
{
	initial();
	alive_cell();

	while (1) {
		system("cls");
		print();
		sleep(1);
		underpopulate();
		overpopulate();
		repopulate();
		stablize();
	}


	return 0;
}

void initial ()
{
	int i, j;
	for (i = 0 ; i < size ; i++) {
		for (j = 0; j < size ; j++) {
			if (i == 0 || j == size - 1 || i == size - 1 || j == 0) {
				plate_1[i][j] = wall;
				plate_2[i][j] = wall;
			} else {
				plate_1[i][j] = dead;
				plate_2[i][j] = dead;
			}
		}
	}
}

void alive_cell ()
{
	plate_1[5][5] = alive;
	plate_1[5][4] = alive;
	plate_1[5][3] = alive;

	plate_2[5][5] = alive;
	plate_2[5][4] = alive;
	plate_2[5][3] = alive;
}

void underpopulate ()
{
	int i, j;
	int state = -1;
	for (i = 1 ; i < size - 1 ; i++) {
		for (j = 1 ; j < size - 1 ; j++ ) {
			if (plate_1[i][j] == alive) {
				state = check(i, j);
				if (state < 2) {
					plate_2[i][j] = dead;
				}
			}
		}
	}
}

void overpopulate ()
{
	int i, j;
	int state;
	for (i = 1 ; i < size - 1 ; i++) {
		for (j = 1 ; j < size - 1 ; j++ ) {
			if (plate_1[i][j] == alive) {
				state = check(i, j);
				if (state > 3) {
					plate_2[i][j] = dead;
				}
			}
		}
	}
}


void repopulate ()
{
	int i, j;
	int state;
	for (i = 1 ; i < size - 1 ; i++) {
		for (j = 1 ; j < size - 1 ; j++ ) {
			if (plate_1[i][j] == dead) {
				state = check(i, j);
				if (state == 3) {
					plate_2[i][j] = alive;
				}
			}
		}
	}
}

int check (int i, int j)
{
	int k, l;
	int count = 0;
	for (k = i - 1 ; k <= i + 1; k++) {
		for (l = j - 1 ; l <= j + 1 ; l++) {
			if (plate_1[k][l] == alive) {
				count++;
			}
		}
	}
	if (plate_1[i][j] == alive) {
		count--;
	}
	return count;
}

void print ()
{
	int i, j;
	for (i = 0 ; i < size; i++) {
		for (j = 0 ; j < size ; j++) {
			switch (plate_1[i][j]) {
				case dead:
					printf(" ");
					break;
				case alive:
					printf("*");
					break;
				case wall:
					printf(".");
					break;
			}
		}
		printf("\n");
	}
}

void stablize ()
{
	int i, j;
	for (i = 0 ; i < size ; i++) {
		for (j = 0 ; j < size ; j++) {
			plate_1[i][j] = plate_2[i][j];
		}
	}
}







