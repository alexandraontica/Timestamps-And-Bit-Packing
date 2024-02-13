// Onțică Alexandra-Elena, 311CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"

#define MAX_NUME 11
#define MAX_TZ 5

typedef struct {
    TDate start_date;
    unsigned char start_hour;
    int duration;
} TTimeSlot;

typedef struct {
    char name[MAX_NUME];
    char timezone[MAX_TZ];
    int K;  // numar intervale libere
    TTimeSlot *timeslot;
    int is_available;
} TPerson;

typedef struct {
    unsigned int timestamp;
    int nr_attendees;
    char **attendees;
} TPossibleSlots;

int add_possible_time_slot(int nr_possible_slots, TPossibleSlots **possible_slots, TPerson *person, int i, int j, int T,
TTimezone *tz) {
    TPossibleSlots *aux = (TPossibleSlots *)realloc(*possible_slots, (nr_possible_slots + 1) * sizeof(TPossibleSlots));

    if (aux == NULL) {
        printf("Eroare la realocare");
        return 1;
    }

    *possible_slots = aux;

    (*possible_slots)[nr_possible_slots].attendees = (char **)calloc(1, sizeof(char *));

    if ((*possible_slots)[nr_possible_slots].attendees == NULL) {
        printf("Eroare la alocare");
        free(*possible_slots);
        return 1;
    }

    (*possible_slots)[nr_possible_slots].attendees[0] = (char *)calloc(strlen(person[i].name) + 1, sizeof(char));

    if ((*possible_slots)[nr_possible_slots].attendees[0] == NULL) {
        printf("Eroare la alocare");
        free((*possible_slots)[nr_possible_slots].attendees);

        for (i = 0; i < nr_possible_slots; i++) {
            free((*possible_slots)[i].attendees);
        }
        free(*possible_slots);

        return 1;
    }

    (*possible_slots)[nr_possible_slots].nr_attendees = 1;

    snprintf((*possible_slots)[nr_possible_slots].attendees[0], strlen(person[i].name) + 1, "%s", person[i].name);

    int index_tz = 0, k = 0;

    for (k = 0; k < T; k++) {
        if (strcmp(tz[k].name, person[i].timezone) == 0) {
            index_tz = k;
            break;
        }
    }

    TDateTimeTZ date_and_time;

    date_and_time.date = person[i].timeslot[j].start_date;
    date_and_time.time.hour = person[i].timeslot[j].start_hour;
    date_and_time.time.min = date_and_time.time.sec = 0;
    date_and_time.tz = &tz[index_tz];

    (*possible_slots)[nr_possible_slots].timestamp = convertDateTimeTZToUnixTimestamp(date_and_time);

    return 0;
}

int add_person_to_possible_time_slot(int nr_possible_slots, TPossibleSlots *possible_slots, int k, TPerson *person,
int i) {
    char **aux = (char **)realloc(possible_slots[k].attendees, (possible_slots[k].nr_attendees + 1) * sizeof(char *));

    if (aux == NULL) {
        printf("Eroare la realocare");
        free(possible_slots[nr_possible_slots].attendees);

        for (i = 0; i < nr_possible_slots; i++) {
            free(possible_slots[i].attendees);
        }
        free(possible_slots);

        return 1;
    }

    possible_slots[k].attendees = aux;

    possible_slots[k].attendees[possible_slots[k].nr_attendees] = (char *)calloc(strlen(person[i].name) + 1,
    sizeof(char));

    if (possible_slots[k].attendees[possible_slots[k].nr_attendees] == NULL) {
        printf("Eroare la alocare");
        return 1;
    }

    snprintf(possible_slots[k].attendees[possible_slots[k].nr_attendees], strlen(person[i].name) + 1, "%s",
    person[i].name);
    possible_slots[k].nr_attendees++;

    return 0;
}

int compare_slots(const void *a, const void *b) {
    TPossibleSlots *slot1 = (TPossibleSlots *)a;
    TPossibleSlots *slot2 = (TPossibleSlots *)b;

    return (int)slot1->timestamp - (int)slot2->timestamp;
}

int compare_people(const void *a, const void *b) {
    TPerson *person1 = (TPerson *)a;
    TPerson *person2 = (TPerson *)b;

    return strcasecmp(person1->name, person2->name);  // stricmp da eroare
}

int main() {
    int T = 0, i = 0;
    scanf("%d", &T);  // numar fusuri orare

    TTimezone *tz = (TTimezone *)calloc(T, sizeof(TTimezone));

    if (tz == NULL) {
        printf("Eroare la alocare");
        return 1;
    }

    for (i = 0; i < T; i++) {
        scanf("%s", tz[i].name);
        int utc_hour_difference_int = 0;
        scanf("%d", &utc_hour_difference_int);
        tz[i].utc_hour_difference = (char)utc_hour_difference_int;  // daca citeam direct tz[i].utc_hour_difference,
        // fiind caracter, pe 0 mi-l interpreta ca 48 (codul sau ASCII) (la fel si la celelalte numere)
    }

    int P = 0;
    scanf("%d", &P);  // numar de persoane

    TPerson *person = (TPerson *)calloc(P, sizeof(TPerson));
    int j = 0;

    if (person == NULL) {
        printf("Eroare la alocare");
        free(tz);
        return 1;
    }

    for (i = 0; i < P; i++) {
        scanf("%s", person[i].name);
        person[i].name[MAX_NUME - 1] = '\0';
        getchar();
        scanf("%s", person[i].timezone);
        scanf("%d", &person[i].K);  // numar intervale libere

        person[i].timeslot = (TTimeSlot *)calloc(person[i].K, sizeof(TTimeSlot));

        if (person[i].timeslot == NULL) {
            printf("Eroare la alocare");
            free(tz);

            for (j = 0; j < i; j++) {
                free(person[j].timeslot);
            }
            free(person);

            return 1;
        }

        for (j = 0; j < person[i].K; j++) {
            scanf("%u", &person[i].timeslot[j].start_date.year);
            scanf("%hhu", &person[i].timeslot[j].start_date.month);
            scanf("%hhu", &person[i].timeslot[j].start_date.day);
            scanf("%hhu", &person[i].timeslot[j].start_hour);
            scanf("%d", &person[i].timeslot[j].duration);
        }
    }

    int F = 0, duration_event = 0;

    scanf("%d%d", &F, &duration_event);

    TPossibleSlots *possible_slots = NULL;
    int nr_possible_slots = 0;

    for (i = 0; i < P; i++) {
        for (j = 0; j < person[i].K; j++) {
            if (person[i].timeslot[j].duration >= duration_event) {
                if (possible_slots == NULL) {
                    int verify_alloc = add_possible_time_slot(nr_possible_slots, &possible_slots, person, i, j, T, tz);

                    if (verify_alloc == 1) {
                        free(tz);

                        for (i = 0; i < P; i++) {
                            free(person[i].timeslot);
                        }
                        free(person);

                        return 1;
                    }

                    nr_possible_slots++;
                }  else {
                    // verific daca intrevalul exista deja

                    int index_tz = 0, k = 0;

                    for (k = 0; k < T; k++) {
                        if (strcmp(tz[k].name, person[i].timezone) == 0) {
                            index_tz = k;
                        }
                    }

                    TDateTimeTZ date_and_time;

                    date_and_time.date = person[i].timeslot[j].start_date;
                    date_and_time.time.hour = person[i].timeslot[j].start_hour;
                    date_and_time.time.min = date_and_time.time.sec = 0;
                    date_and_time.tz = &tz[index_tz];

                    unsigned int ts = convertDateTimeTZToUnixTimestamp(date_and_time);

                    int ok = 0;
                    for (k = 0; k < nr_possible_slots; k++) {
                        if (possible_slots[k].timestamp == ts) {
                            ok = 1;  // exista deja acest interval de timp
                            // adaug persoana in vectorul participantilor in cadrul acestui interval

                            int verify_alloc = add_person_to_possible_time_slot(nr_possible_slots, possible_slots, k,
                            person, i);

                            if (verify_alloc == 1) {
                                free(tz);

                                for (i = 0; i < P; i++) {
                                    free(person[i].timeslot);
                                }
                                free(person);

                                return 1;
                            }
                        } else if (ts < possible_slots[k].timestamp) {
                            unsigned int current_slot_end = ts + person[i].timeslot[j].duration * SEC_IN_AN_HOUR;
                            unsigned int possible_slot_end = possible_slots[k].timestamp +
                            duration_event * SEC_IN_AN_HOUR;

                            if (possible_slot_end <= current_slot_end) {
                                // intervalul de timp nu exita ca atare
                                // (sa fie unul deja care sa inceapa la aceeasi ora)
                                // persoana este totusi disponibila
                                // o adaug la vectorul de participanti, dar adaug si intervalul separat dupa aceea

                                int verify_alloc = add_person_to_possible_time_slot(nr_possible_slots, possible_slots,
                                k, person, i);

                                if (verify_alloc == 1) {
                                    free(tz);

                                    for (i = 0; i < P; i++) {
                                        free(person[i].timeslot);
                                    }
                                    free(person);

                                    return 1;
                                }
                            }
                        }
                    }

                    if (ok == 0) {
                        // adauga intervalul nou

                        int verify_alloc = add_possible_time_slot(nr_possible_slots, &possible_slots, person, i, j,
                        T, tz);

                        if (verify_alloc == 1) {
                            free(tz);

                            for (i = 0; i < P; i++) {
                                free(person[i].timeslot);
                            }
                            free(person);

                            return 1;
                        }

                        nr_possible_slots++;
                    }
                }
            }
        }
    }

    qsort(possible_slots, nr_possible_slots, sizeof(TPossibleSlots), compare_slots);

    int index_slot = 0, gasit = 0;

    for (i = 0; i < nr_possible_slots; i++) {
        if (possible_slots[i].nr_attendees >= F) {
            index_slot = i;
            gasit = 1;
            break;  // am gasit intervalul, ma opresc din cautat
        }
    }

    if (gasit == 0) {
        printf("imposibil\n");
    } else {
        qsort(person, P, sizeof(TPerson), compare_people);

        for (i = 0; i < P; i++) {
            for (j = 0; j < possible_slots[index_slot].nr_attendees; j++) {
                if (strcmp(possible_slots[index_slot].attendees[j], person[i].name) == 0) {
                    person[i].is_available = 1;
                }
            }
        }

        for (i = 0; i < P; i++) {
            if (person[i].is_available == 0) {
                printf("%s: invalid\n", person[i].name);
            } else {
                printf("%s: ", person[i].name);

                int index_tz = 0;
                for (j = 0; j < T; j++) {
                    if (strcmp(tz[j].name, person[i].timezone) == 0) {
                        index_tz = j;
                        break;
                    }
                }

                TDateTimeTZ date_and_time = convertUnixTimestampToDateTimeTZ(possible_slots[index_slot].timestamp, tz,
                index_tz);

                printDateTimeTZ(date_and_time);
            }
        }
    }

    free(tz);

    for (i = 0; i < P; i++) {
        free(person[i].timeslot);
    }
    free(person);


    for (i = 0; i < nr_possible_slots; i++) {
        for (j = 0; j < possible_slots[i].nr_attendees; j++) {
            free(possible_slots[i].attendees[j]);
        }
        free(possible_slots[i].attendees);
    }
    free(possible_slots);

    return 0;
}
