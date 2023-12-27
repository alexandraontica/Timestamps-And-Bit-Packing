// Onțică Alexandra-Elena, 311CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"

#define TASK_7 7
#define TASK_8 8
#define BINAR_11111 31
#define BINAR_1111 15
#define BINAR_111111 63
#define BITI_ZI 5
#define BITI_LUNA 4

int main () {
    // Task 7 & 8
	int task = 0;
    scanf("%d", &task);

    char luna[MONTHS_IN_A_YEAR + 1][MAX_LITERE_IN_LUNA + 1];  // creat pentru a afisa mai usor numele lunii
	strcpy(luna[IANUARIE], "ianuarie");
	strcpy(luna[FEBRUARIE], "februarie");
	strcpy(luna[MARTIE], "martie");
	strcpy(luna[APRILIE], "aprilie");
    strcpy(luna[MAI], "mai");
	strcpy(luna[IUNIE], "iunie");
	strcpy(luna[IULIE], "iulie");
	strcpy(luna[AUGUST], "august");
	strcpy(luna[SEPTEMBRIE], "septembrie");
	strcpy(luna[OCTOMBRIE], "octombrie");
	strcpy(luna[NOIEMBRIE], "noiembrie");
	strcpy(luna[DECEMBRIE], "decembrie");

    if (task == TASK_7) {
        int N = 0;
        scanf("%d", &N);

        unsigned int data_biti[N], i = 0, j = 0;
        for (i = 0; i < N; i++) {
            scanf("%u", &data_biti[i]);
        }

        TDate data[N];
        for (i = 0; i < N; i++) {
            unsigned int mask_zi = BINAR_11111;  // bitii de 1 sunt pe poz coresp zilei
            unsigned int zi = data_biti[i] & mask_zi;  // raman doar bitii ce contin ziua
            data[i].day = (unsigned char)zi;

            unsigned int mask_luna = BINAR_1111;
            mask_luna <<= BITI_ZI;  // ajung cu bitii de 1 pe poz coresp lunii
            unsigned int luna = (data_biti[i] & mask_luna) >> BITI_ZI;  // raman doar bitii ce contin luna
            data[i].month = (unsigned char)luna;

            unsigned int mask_an = BINAR_111111;
            mask_an <<= (BITI_LUNA + BITI_ZI);  // ajung cu bitii de 1 pe poz coresp anului
            data[i].year = START_YEAR + ((data_biti[i] & mask_an) >> (BITI_LUNA + BITI_ZI));  // bitii ce contin anul
        }

        // sortez datele crescator:
        for (i = 0; i < N - 1; i++) {
            for (j = i + 1; j < N; j++) {
                if (data[i].year > data[j].year) {
                    TDate aux = data[i];
                    data[i] = data[j];
                    data[j] = aux;
                } else if (data[i].year == data[j].year) {
                    if (data[i].month > data[j].month) {
                        TDate aux = data[i];
                        data[i] = data[j];
                        data[j] = aux;
                    } else if (data[i].month == data[j].month) {
                        if (data[i].day > data[j].day) {
                            TDate aux = data[i];
                            data[i] = data[j];
                            data[j] = aux;
                        }
                    }
                }
            }
        }

        for (i = 0; i < N; i++) {
            printf("%hhu %s %u\n", data[i].day, luna[data[i].month], data[i].year);
        }

    } else if (task == TASK_8) {
        // code
    }
	
    return 0;
}
