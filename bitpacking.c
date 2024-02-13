// Onțică Alexandra-Elena, 311CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"

#define TASK_7 7
#define TASK_8 8
#define BITI_ZI 5
#define BITI_LUNA 4
#define BITI_AN 6
#define BITI_DATA 15
#define BITI_UNSIGNED_INT 32

void extrage_data(unsigned int data_biti, TDate *data, unsigned int i) {
    unsigned int mask_zi = (1 << BITI_ZI) - 1;  // bitii de 1 sunt pe poz coresp zilei
    unsigned int zi = data_biti & mask_zi;  // raman doar bitii ce contin ziua
    data[i].day = (unsigned char)zi;

    unsigned int mask_luna = (1 << BITI_LUNA) - 1;
    mask_luna <<= BITI_ZI;  // ajung cu bitii de 1 pe poz coresp lunii
    unsigned int luna = (data_biti & mask_luna) >> BITI_ZI;  // raman doar bitii ce contin luna
    data[i].month = (unsigned char)luna;

    unsigned int mask_an = (1 << BITI_AN) - 1;
    mask_an <<= (BITI_LUNA + BITI_ZI);  // ajung cu bitii de 1 pe poz coresp anului
    data[i].year = START_YEAR + ((data_biti & mask_an) >> (BITI_LUNA + BITI_ZI));  // bitii ce contin anul
}

int comparare_date(const void *a, const void *b) {
    TDate *data1 = (TDate *)a;
    TDate *data2 = (TDate *)b;

    if (data1->year != data2->year) {
        return (int)data1->year - (int)data2->year;
    }

    if (data1->month != data2->month) {
        return (int)data1->month - (int)data2->month;
    }

    return (int)data1->day - (int)data2->day;
}

void afisare_date(int N, TDate *data, char (*luna)[MAX_LITERE_IN_LUNA + 1]) {
    int i = 0;

    for (i = 0; i < N; i++) {
        printf("%hhu %s %u\n", data[i].day, luna[data[i].month], data[i].year);
    }
}

int main() {
    int task = 0;
    scanf("%d", &task);

    char luna[MONTHS_IN_A_YEAR + 1][MAX_LITERE_IN_LUNA + 1];  // creat pentru a afisa mai usor numele lunii
    snprintf(luna[0], MAX_LITERE_IN_LUNA + 1, "%s", "");
    snprintf(luna[IANUARIE], MAX_LITERE_IN_LUNA + 1, "%s", "ianuarie");
    snprintf(luna[FEBRUARIE], MAX_LITERE_IN_LUNA + 1, "%s", "februarie");
    snprintf(luna[MARTIE], MAX_LITERE_IN_LUNA + 1, "%s", "martie");
    snprintf(luna[APRILIE], MAX_LITERE_IN_LUNA + 1, "%s", "aprilie");
    snprintf(luna[MAI], MAX_LITERE_IN_LUNA + 1, "%s", "mai");
    snprintf(luna[IUNIE], MAX_LITERE_IN_LUNA + 1, "%s", "iunie");
    snprintf(luna[IULIE], MAX_LITERE_IN_LUNA + 1, "%s", "iulie");
    snprintf(luna[AUGUST], MAX_LITERE_IN_LUNA + 1, "%s", "august");
    snprintf(luna[SEPTEMBRIE], MAX_LITERE_IN_LUNA + 1, "%s", "septembrie");
    snprintf(luna[OCTOMBRIE], MAX_LITERE_IN_LUNA + 1, "%s", "octombrie");
    snprintf(luna[NOIEMBRIE], MAX_LITERE_IN_LUNA + 1, "%s", "noiembrie");
    snprintf(luna[DECEMBRIE], MAX_LITERE_IN_LUNA + 1, "%s", "decembrie");

    if (task == TASK_7) {
        int N = 0;
        scanf("%d", &N);

        unsigned int *data_biti = (unsigned int *)calloc(N, sizeof(unsigned int));

        if (data_biti == NULL) {
            printf("Eroare la alocare");
            return 1;
        }

        unsigned int i = 0;

        for (i = 0; i < N; i++) {
            scanf("%u", &data_biti[i]);
        }

        TDate *data = (TDate *)calloc(N, sizeof(TDate));

        if (data == NULL) {
            printf("Eroare la alocare");
            free(data_biti);
            return 1;
        }

        for (i = 0; i < N; i++) {
            extrage_data(data_biti[i], data, i);
        }

        qsort(data, N, sizeof(TDate), comparare_date);
        afisare_date(N, data, luna);

        free(data_biti);
        free(data);

    } else if (task == TASK_8) {
        int N = 0;
        scanf("%d", &N);

        int inturi_necesare = BITI_DATA * N;
        if (inturi_necesare % BITI_UNSIGNED_INT != 0) {
            inturi_necesare /= BITI_UNSIGNED_INT;  // atatea int-uri sunt ocupate complet
            inturi_necesare++;  // aici ramane un nr de biti egal cu restul impartirii la 32 (BITI_UNSIGNED_INT)
        } else {
            inturi_necesare /= BITI_UNSIGNED_INT;
        }

        unsigned int *inturi = (unsigned int *)calloc(inturi_necesare, sizeof(unsigned int));

        if (inturi == NULL) {
            printf("Eroare la alocare");
            return 1;
        }

        unsigned int i = 0;

        for (i = 0; i < inturi_necesare; i++) {
            scanf("%u", &inturi[i]);
        }

        int inturi_control_necesare = inturi_necesare;
        if (inturi_control_necesare % BITI_UNSIGNED_INT != 0) {
            inturi_control_necesare /= BITI_UNSIGNED_INT;
            inturi_control_necesare++;
        } else {
            inturi_control_necesare /= BITI_UNSIGNED_INT;
        }

        unsigned int *inturi_control = (unsigned int *)calloc(inturi_control_necesare, sizeof(unsigned int));

        if (inturi_control == NULL) {
            printf("Eroare la alocare");
            free(inturi);
            return 1;
        }

        for (i = 0; i < inturi_control_necesare; i++) {
            scanf("%u", &inturi_control[i]);
        }

        TDate *data = (TDate *)calloc(N, sizeof(TDate));

        if (data == NULL) {
            printf("Eroare la alocare");
            free(inturi);
            free(inturi_control);
            return 1;
        }

        int *corupt = (int *)calloc(N, sizeof(int));

        if (corupt == NULL) {
            printf("Eroare la alocare");
            free(inturi);
            free(inturi_control);
            free(data);
            return 1;
        }

        unsigned int mask_data = (1 << BITI_DATA) - 1;
        unsigned int data_extrasa = 0;  // aici salvez toti biti dintr-o data
        unsigned int nr_biti_data_anterioara = 0;
        unsigned int j = 0;
        unsigned int k = 0;  // cu k parcurg vectorul de inturi de control

        for (i = 0; i < inturi_necesare; i++) {
            unsigned int copie = inturi[i];
            int biti_1 = 0;
            int int_corupt = 0;

            while (copie != 0) {
                if ((copie & 1) == 1) {
                    biti_1++;
                }
                copie >>= 1;
            }

            if (biti_1 % 2 != (inturi_control[k] & 1)) {
                int_corupt = 1;
            }

            if (i % BITI_UNSIGNED_INT == (BITI_UNSIGNED_INT - 1)) {
                k++;
            } else {
                inturi_control[k] >>= 1;
            }

            if (nr_biti_data_anterioara != 0 && int_corupt == 1) {
                corupt[j - 1] = 1;
            }

            unsigned int nr_biti_neprelucrati = BITI_UNSIGNED_INT - nr_biti_data_anterioara;

            while (nr_biti_neprelucrati >= BITI_DATA && j < N) {
                data_extrasa = (inturi[i] >> nr_biti_data_anterioara) & mask_data;

                extrage_data(data_extrasa, data, j);

                nr_biti_neprelucrati -= BITI_DATA;
                nr_biti_data_anterioara += BITI_DATA;

                if (nr_biti_data_anterioara == BITI_UNSIGNED_INT) {
                    nr_biti_data_anterioara = 0;
                }

                if (int_corupt == 1) {
                    corupt[j] = 1;
                }

                j++;
            }

            if (nr_biti_neprelucrati > 0 && i < inturi_necesare - 1) {  // exita cativa biti dintr-o alta data
                // merg cu i pana la inturi_necesare - 1 pt ca ulterior o sa folosesc elementul de pe poz i + 1
                // din inturi si trebuie sa ma asigur ca acesta exista si ca nu depasesc memoria alocata

                unsigned int mask_data_incompleta1 = (1 << nr_biti_neprelucrati) - 1;
                unsigned int data_incompleta1 = ((inturi[i] >> nr_biti_data_anterioara) & mask_data_incompleta1);

                nr_biti_data_anterioara = BITI_DATA - nr_biti_neprelucrati;
                unsigned int mask_data_incompleta2 = (1 << nr_biti_data_anterioara) - 1;
                unsigned int data_incompleta2 = inturi[i + 1] & mask_data_incompleta2;

                data_extrasa = (data_incompleta1 + (data_incompleta2 << nr_biti_neprelucrati));

                extrage_data(data_extrasa, data, j);

                if (int_corupt == 1) {
                    corupt[j] = 1;
                }

                j++;

            } else {  // toate datele prelucrate sunt complete, urmatoarea data incepe in urmatorul unsigned int
                nr_biti_data_anterioara = 0;
            }
        }

        int nr_date_necorupte = 0;

        for (i = 0; i < N; i++) {
            if (corupt[i] == 1) {
                for (j = i; j < N - 1; j++) {
                    data[j] = data[j + 1];
                }
            } else {
                nr_date_necorupte++;
            }
        }

        qsort(data, nr_date_necorupte, sizeof(TDate), comparare_date);
        afisare_date(nr_date_necorupte, data, luna);

        free(inturi);
        free(inturi_control);
        free(data);
        free(corupt);
    }

    return 0;
}
