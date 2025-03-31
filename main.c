#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

void meni() {
	printf("\n");
	printf("[1] Stvaranje novog niza\n");
	printf("[2] Pretraga kljuca preko m-arne pretrage\n");
	printf("[3] Pretraga niza kljuceva preko optimizovane m-arne pretrage\n");
	printf("[4] Evaluacija performansi m-arne pretrage\n");
	printf("[5] Evaluacija performansi optimizovane m-arne pretrage\n");
	printf("[6] Kraj programa\n");
}

int* generisanje_niza(int k, int gornja, int donja) {
	int* K;
	K = (int*)malloc(k * sizeof(int));
	if (K == NULL) {
		printf("Neuspela alokacija!\n");
		exit(1);
	}

	srand(time(NULL));
	int i;
	for (i = 0; i < k; i++) {
		K[i] = rand() % (gornja - donja + 1) + donja;
	}

	int pom, j;
	for (i = 0; i < k - 1;i++) {
		for (j = i + 1;j < k; j++) {
			if (K[i] > K[j]) {
				pom = K[i];
				K[i] = K[j];
				K[j] = pom;
			}
		}
	}

	return K;
}

int* mid_niz(int m, int low, int high) {
	int* mid;
	mid = (int*)malloc((m - 1) * sizeof(int));
	if (mid == NULL) {
		printf("Neuspela alokacija!\n");
		exit(1);
	}

	if (m == 1) {
		printf("Pogresan unos!");
		exit(1);
	}

	mid[0] = low + (high - low) / m;
	for (int i = 1; i < (m - 1); i++)
	{
		mid[i] = mid[i - 1] + (high - low) / m;
	}

	return mid;
}

int marna_pretraga(int* K, int kljuc, int k, int m) {
	int low = 0;
	int high = k - 1;

	while (low <= high) {
		int* mid = mid_niz(m, low, high);

		for (int i = 0; i < (m - 1); i++)
		{
			if (kljuc == K[mid[i]])
			{
				return mid[i];
			}

			else if (kljuc < K[mid[i]]) {
				high = mid[i] - 1;
			}

			else
			{
				low = mid[i] + 1;
			}
		}
	}
	return -1;
}

int* optimizovana_m_arna_pretraga(int* K, int* P, int k, int p, int m) {
	int* S = (int*)malloc(p * sizeof(int));
	int i, j = 0;
	for (i = 0; i < p; i++)
	{
		S[i] = -1;
	}

	int low = 0;
	int high = k - 1;

	while ((low <= high) && (j <= p))
	{
		int* mid = mid_niz(m, low, high);

		for (i = 0; i < (m - 1); i++)
		{
			if (P[j] == K[mid[i]])
			{
				S[j] = mid[i];
				low = mid[i] + 1;
				high = k - 1;
				j++;
			}

			else if (P[j] < K[mid[i]]) {
				high = mid[i] - 1;
			}

			else
			{
				low = mid[i] + 1;
			}
		}
	}

	return S;
}

int br_poredjenja(int* K, int kljuc, int k, int m) {
	int low = 0;
	int high = k - 1;
	int br = 0;
	//int m = 2;

	while (low <= high) {

		int* mid = mid_niz(m, low, high);

		for (int i = 0; i < (m - 1); i++)
		{
			if (kljuc == K[mid[i]])
			{
				br++;
				return br;
			}

			else if (kljuc < K[mid[i]]) {
				br = br + 2;
				high = mid[i] - 1;

			}

			else
			{
				br = br + 3;
				low = mid[i] + 1;
			}
		}
	}
}


int main() {
	int k, donja, gornja;
	int* K;
	int m, kljuc;
	int* P;
	int p, m2;
	int brk;
	double prosecan_br_poredjenja;
	int suma;
	float prosek;

	while (1)
	{
		meni();
		printf("\n");
		printf("Izaberite opciju : ");
		int opcija;
		scanf("%d", &opcija);

		switch (opcija) {
		case 1:
			printf("\nIzaberite kako zelite da unesete opseg i duzinu niza:\n");
			printf("1) Preko datoteke\n");
			printf("2) Preko standarnog ulaza\n");
			int izbor;
			scanf("%d", &izbor);
			if (izbor == 1)
			{
				FILE* fp = fopen("unos.txt", "r");
				if (fp == NULL) {
					printf("Ne postoji datoteka pod tim nazivom");
					exit(1);
				}
				fscanf(fp, "%d", &k);
				fscanf(fp, "%d", &donja);
				fscanf(fp, "%d", &gornja);

				fclose(fp);
			}
			else
			{
				printf("Unesite duzinu niza: ");
				scanf("%d", &k);
				printf("\nUnesite donju granicu niza: ");
				scanf("%d", &donja);
				printf("\nUnesite gornju granicu niza: ");
				scanf("%d", &gornja);
				printf("\n");
			}
			break;

		case 2:

			K = generisanje_niza(k, gornja, donja);
			if (K == NULL) {
				printf("Neuspela alokacija!\n");
				exit(1);
			}
			printf("\nIspis generisanog niza: ");
			for (int i = 0; i < k; i++)
			{
				printf("%d ", K[i]);
			}
			printf("\n");

			printf("\nUnesite broj m: ");
			scanf("%d", &m);
			printf("\nUnesite kljuc koji pretrazujete: ");
			scanf("%d", &kljuc);

			printf("\nKljuc se nalazi na poziciji %d\n\n", marna_pretraga(K, kljuc, k, m));
			break;

		case 3:
			K = generisanje_niza(k, gornja, donja);
			if (K == NULL) {
				printf("Neuspela alokacija!\n");
				exit(1);
			}
			printf("\nIspis generisanog niza: ");

			for (int i = 0; i < k; i++)
			{
				printf("%d ", K[i]);
			}
			printf("\n");

			printf("\nUnesite duzinu niza kljuceva: ");
			scanf("%d", &p);

			P = (int*)malloc(p * sizeof(int));
			if (P == NULL) {
				printf("Neuspela alokacija!\n");
				exit(1);
			}
			printf("\nUnesite elemente niza: ");
			for (int i = 0; i < p; i++)
			{
				scanf("%d", &P[i]);
			}

			printf("\n");
			printf("unesite broj m: ");
			scanf("%d", &m2);

			int* S = optimizovana_m_arna_pretraga(K, P, k, p, m2);
			for (int i = 0; i < p; i++)
			{
				printf("%d ", S[i]);
			}
			break;

		case 4:
			K = generisanje_niza(k, gornja, donja);
			if (K == NULL) {
				printf("Neuspela alokacija!\n");
				exit(1);
			}
			printf("\nIspis generisanog niza: ");

			for (int i = 0; i < k; i++)
			{
				printf("%d ", K[i]);
			}
			printf("\n");

			printf("\nUnesite broj kljuceva: ");
			scanf("%d", &brk);

			int* arr = (int*)malloc(brk * sizeof(int));
			if (arr == NULL) {
				printf("Neuspela alokacija!\n");
				exit(1);
			}

			printf("\nUnesite vrednosti kljuceva: \n");
			for (int i = 0; i < brk; i++)
			{
				scanf("%d", &arr[i]);
			}

			for (int j = 2; j < 7; j++)
			{
				for (int i = 0; i < brk; i++)
				{
					printf("\nBroj poredjenja za %d kljuceve je %d \n", j, br_poredjenja(K, arr[i], k, j));

				}
			}

			for (int j = 2; j < 7; j++)
			{
				int suma = 0;
				for (int i = 0; i < brk; i++)
				{
					suma += br_poredjenja(K, arr[i], k, j);
				}
				//printf("\nSuma je %d\n", suma);
				double sum = (double)suma;
				double brr = (double)brk;
				prosecan_br_poredjenja = sum / brr;
				printf("\nProsecan broj poredjenja za m=%d je %f\n", j, prosecan_br_poredjenja);
			}
			break;

		case 5:
			K = generisanje_niza(k, gornja, donja);
			if (K == NULL) {
				printf("Neuspela alokacija!\n");
				exit(1);
			}
			printf("\nIspis generisanog niza: ");

			for (int i = 0; i < k; i++)
			{
				printf("%d ", K[i]);
			}
			printf("\n");

			printf("\nUnesite duzinu niza kljuceva: ");
			scanf("%d", &p);

			P = (int*)malloc(p * sizeof(int));
			if (P == NULL) {
				printf("Neuspela alokacija!\n");
				exit(1);
			}
			printf("\nUnesite elemente niza: ");
			for (int i = 0; i < p; i++)
			{
				scanf("%d", &P[i]);
			}

			printf("\n");
			for (int j = 2; j < 7; j++)
			{
				suma = 0;
				for (int i = 0; i < p; i++)
				{
					suma = suma + br_poredjenja(K, P[i], k, j);
				}
				double zbir = (double)suma;
				double brojic = (double)p;
				prosek = zbir / brojic;
				printf("\nProsecan broj poredjenja za m=%d u optimizovanoj pretrazi je %f\n", j, prosek);

			}
			break;

		case 6:
			printf("Kraj programa!\n");
			exit(1);
			break;

		default:
			printf("Uneli ste pogresan broj");
			break;

		}
	}
	return 0;
}