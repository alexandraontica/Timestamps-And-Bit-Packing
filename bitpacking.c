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
#define BINAR_111111111111111 32767  // 15 de 1 (masca pt data)
#define BITI_ZI 5
#define BITI_LUNA 4
#define BITI_DATA 15
#define BITI_UNSIGNED_INT 32

void extrage_data (unsigned int data_biti, TDate *data, unsigned int i) {
    unsigned int mask_zi = BINAR_11111;  // bitii de 1 sunt pe poz coresp zilei
    unsigned int zi = data_biti & mask_zi;  // raman doar bitii ce contin ziua
    data[i].day = (unsigned char)zi;

    unsigned int mask_luna = BINAR_1111;
    mask_luna <<= BITI_ZI;  // ajung cu bitii de 1 pe poz coresp lunii
    unsigned int luna = (data_biti & mask_luna) >> BITI_ZI;  // raman doar bitii ce contin luna
    data[i].month = (unsigned char)luna;

    unsigned int mask_an = BINAR_111111;
    mask_an <<= (BITI_LUNA + BITI_ZI);  // ajung cu bitii de 1 pe poz coresp anului
    data[i].year = START_YEAR + ((data_biti & mask_an) >> (BITI_LUNA + BITI_ZI));  // bitii ce contin anul
}

void sortare_date (int N, TDate *data) {
    int i = 0, j = 0;

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
}

void afisare_data (int N, TDate *data, char (*luna)[MAX_LITERE_IN_LUNA + 1]) {
    int i = 0;

    for (i = 0; i < N; i++) {
        printf("%hhu %s %u\n", data[i].day, luna[data[i].month], data[i].year);
    }
}

int main () {
    // Task 7 & 8
	int task = 0;
    scanf("%d", &task);

    char luna[MONTHS_IN_A_YEAR + 1][MAX_LITERE_IN_LUNA + 1];  // creat pentru a afisa mai usor numele lunii
    strcpy(luna[0], "\0");  // rezolvare eroare de memorie neinitializata (valgrind) 
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

        unsigned int *data_biti = (unsigned int *)malloc(N * sizeof(unsigned int));

        if (data_biti == NULL) {
            printf("Eroare la alocare");
            return 1;
        }
        
        unsigned int i = 0;

        for (i = 0; i < N; i++) {
            scanf("%u", &data_biti[i]);
        }

        TDate *data = (TDate *)malloc(N * sizeof(TDate));

        if (data == NULL) {
            printf("Eroare la alocare");
            return 1;
        }

        for (i = 0; i < N; i++) {
            extrage_data(data_biti[i], data, i);
        }

        sortare_date(N, data);

        afisare_data(N, data, luna);

        free(data_biti);
        free(data);

    } else if (task == TASK_8) {
        int N = 0;
        scanf("%d", &N);

        int inturi_necesare = BITI_DATA * N;
        if (inturi_necesare % BITI_UNSIGNED_INT != 0) {
            inturi_necesare /= BITI_UNSIGNED_INT;
            inturi_necesare++;
        } else {
            inturi_necesare /= BITI_UNSIGNED_INT;
        }

        unsigned int *inturi = (unsigned int *)malloc(inturi_necesare * sizeof(unsigned int));

        if (inturi == NULL) {
            printf("Eroare la alocare");
            return 1;
        }
        
        unsigned int i = 0, j = 0, k = 0;

        for (i = 0; i < inturi_necesare; i++) {
            scanf("%u", &inturi[i]);
        }

        int inturi_control_necesare = N;
        if (inturi_control_necesare % BITI_UNSIGNED_INT != 0) {
            inturi_control_necesare /= BITI_UNSIGNED_INT;
            inturi_control_necesare++;
        } else {
            inturi_control_necesare /= BITI_UNSIGNED_INT;
        }

        unsigned int *inturi_control = (unsigned int *)malloc(inturi_control_necesare * sizeof(unsigned int));

        if (inturi_control == NULL) {
            printf("Eroare la alocare");
            return 1;
        }

        for (i = 0; i < inturi_control_necesare; i++) {
            scanf("%u", &inturi_control[i]);
        }

        TDate *data = (TDate *)malloc(N * sizeof(TDate));

        if (data == NULL) {
            printf("Eroare la alocare");
            return 1;
        }

        unsigned int mask_data = BINAR_111111111111111;
        unsigned int data_extrasa = 0;
        unsigned int nr_biti_data_anterioara = 0;

        unsigned int *biti_1 = (unsigned int *)calloc(N, sizeof(unsigned int));

        if (biti_1 == NULL) {
            printf("Eroare la alocare");
            return 1;
        }

        for (i = 0; i < inturi_necesare; i++) {
            unsigned int biti_neprelucrati = BITI_UNSIGNED_INT - nr_biti_data_anterioara;

            while (biti_neprelucrati >= BITI_DATA) {
                data_extrasa = (inturi[i] >> nr_biti_data_anterioara) & mask_data;

                extrage_data(data_extrasa, data, j);

                biti_neprelucrati -= BITI_DATA;

                while (data_extrasa != 0) {
                    if ((data_extrasa & 1) == 1) {
                        biti_1[j]++;
                    }

                    data_extrasa >>= 1;
                }

                if (j < N - 1)    
                    j++;
            }

            nr_biti_data_anterioara = BITI_UNSIGNED_INT - biti_neprelucrati;
            unsigned int data_incompleta = (inturi[i] >> (BITI_UNSIGNED_INT - biti_neprelucrati));

            unsigned int putere_2 = 1, mask_data_incompleta = 0;
            for (k = 1; k <= nr_biti_data_anterioara; k++) {
                   putere_2 *= 2;
                   mask_data_incompleta += putere_2;
            }

            data_extrasa = data_incompleta + ((inturi[i + 1] & mask_data_incompleta) << biti_neprelucrati);

            extrage_data(data_extrasa, data, j);

            while (data_extrasa != 0) {
                if ((data_extrasa & 1) == 1) {
                    biti_1[j]++;
                }

                data_extrasa >>= 1;
            }

            j++;
        }

        // verific bitii de control:
        j = 0;
        unsigned int biti_control = inturi_control[j];

        for (i = 0; i < N; i++) {
            if (biti_1[i] % 2 != (inturi_control[j] & 1)) {
                for (k = i; k < N - 1; k++) {
                    data[k] = data[k + 1];
                }

                N--;
                i--;
            }

            biti_control >>= 1;

            if (biti_control == 0 && j < inturi_control_necesare - 1) {
                j++;
                biti_control = inturi_control[j];
            }
        }

        sortare_date(N, data);
        
        afisare_data(N, data, luna);

        free(inturi);
        free(inturi_control);
        free(biti_1);
        free(data);

    } else {
        printf("Numar task invalid");
    }
	
    return 0;
}
