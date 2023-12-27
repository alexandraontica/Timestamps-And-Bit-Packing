// Onțică Alexandra-Elena, 311CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"

#define SEC_IN_A_MIN 60
#define SEC_IN_AN_HOUR 3600
#define SEC_IN_A_DAY 86400
#define HOURS_IN_A_DAY 24
#define START_YEAR 1970
#define START_MONTH 1
#define START_DAY 1
#define IANUARIE 1
#define FEBRUARIE 2
#define MARTIE 3
#define APRILIE 4
#define MAI 5
#define IUNIE 6
#define IULIE 7
#define AUGUST 8
#define SEPTEMBRIE 9
#define OCTOMBRIE 10
#define NOIEMBRIE 11
#define DECEMBRIE 12
#define FINAL_LUNA_30 30
#define FINAL_LUNA_31 31
#define FINAL_FEB 28
#define FINAL_FEB_AN_BISECT 29
#define DAYS_IN_A_YEAR 365
#define DAYS_IN_A_LEAP_YEAR 366

// Task 1
TTime convertUnixTimestampToTime(unsigned int timestamp) {
	TTime result;

	result.sec = timestamp % SEC_IN_A_MIN;
	result.min = timestamp % SEC_IN_AN_HOUR / SEC_IN_A_MIN;
	result.hour = timestamp % SEC_IN_A_DAY / SEC_IN_AN_HOUR;

	return result;
}

// Task 2
TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp) {
	TDate result;

	for (result.day = START_DAY, result.month = START_MONTH, result.year = START_YEAR;
	timestamp >= SEC_IN_A_DAY; timestamp = timestamp - SEC_IN_A_DAY) {
        if (result.month == 12 && result.day == 31) {
			result.year++;
			result.month = IANUARIE;
			result.day = 1;

		} else if ((result.month == FEBRUARIE && result.day == FINAL_FEB) ||  // e final de februarie
		((result.month == IANUARIE || result.month == MARTIE || result.month == MAI || result.month == IULIE ||
		result.month == AUGUST || result.month == OCTOMBRIE)
		&& result.day == FINAL_LUNA_31) ||  // sau e final de luna cu 31 zile
		((result.month == APRILIE || result.month == IUNIE || result.month == SEPTEMBRIE || result.month == NOIEMBRIE)
		&& result.day == FINAL_LUNA_30)) {  // sau e final de luna cu 30 zile
            result.month++;
			result.day = 1;
			// am scris asa conditia din if pt ca altfel am eroare de coding style (>120 caractere/rand)

		} else {
			result.day++;
		}
	}

	return result;
}

// Task 3
TDate convertUnixTimestampToDate(unsigned int timestamp) {
	TDate result;

    // am adaptat algoritmul de la taskul 2
	// singurul lucru schimbat este momentul cand se ajunge la finalul lunii februarie
	for (result.day = START_DAY, result.month = START_MONTH, result.year = START_YEAR; 
	timestamp >= SEC_IN_A_DAY; timestamp = timestamp - SEC_IN_A_DAY) {
        int an_bisect = 0;

        // verific daca anul este bisect sau nu:
        if ((result.year % 400 == 0) || (result.year % 4 == 0 && result.year % 100 != 0)) {
            an_bisect = 1;
		}

        if (result.month == DECEMBRIE && result.day == FINAL_LUNA_31) {
			result.year++;
			result.month = IANUARIE;
			result.day = 1;

		} else if ((result.month == FEBRUARIE && ((an_bisect == 1 && result.day == FINAL_FEB_AN_BISECT) ||
		(an_bisect == 0 && result.day == FINAL_FEB))) ||  // e final de feb, depinde daca e an bisect sau nu
		((result.month == IANUARIE || result.month == MARTIE || result.month == MAI || result.month == IULIE ||
		result.month == AUGUST || result.month == OCTOMBRIE) &&
		result.day == FINAL_LUNA_31) ||  // sau e final de luna cu 31 zile
		((result.month == APRILIE || result.month == IUNIE || result.month == SEPTEMBRIE || result.month == NOIEMBRIE)
		&& result.day == FINAL_LUNA_30)) {  // sau e final de luna cu 30 zile
            result.month++;
			result.day = 1;

		} else {
			result.day++;
		}
	}

	return result;
}

// Task 4
TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp, TTimezone *timezones, int timezone_index) {
	TDateTimeTZ result;

    result.tz = &timezones[timezone_index];
    result.date = convertUnixTimestampToDate(timestamp);
	result.time = convertUnixTimestampToTime(timestamp);

	if (result.time.hour + result.tz->utc_hour_difference >= HOURS_IN_A_DAY) {
		// conditia pusa nu este adevarata decat daca result.tz->utc_hour_difference > 0

		// se trece la ziua urmatoare
		// verific daca se trece si in alta luna sau in alt an (exact ca la task 3)

		int an_bisect = 0;

        // verific daca anul este bisect sau nu:
        if ((result.date.year % 400 == 0) || (result.date.year % 4 == 0 && result.date.year % 100 != 0)) {
            an_bisect = 1;
        }

		if (result.date.month == DECEMBRIE && result.date.day == FINAL_LUNA_31) {
		    result.date.year++;
		    result.date.month = IANUARIE;
		    result.date.day = 1;

	    } else if ((result.date.month == FEBRUARIE && ((an_bisect == 1 && result.date.day == FINAL_FEB_AN_BISECT) ||
	    (an_bisect == 0 && result.date.day == FINAL_FEB))) ||  // e final de feb, depinde daca e an bisect sau nu
	    ((result.date.month == IANUARIE || result.date.month == MARTIE || result.date.month == MAI ||
		result.date.month == IULIE || result.date.month == AUGUST || result.date.month == OCTOMBRIE) &&
		result.date.day == FINAL_LUNA_31) ||  // sau e final de luna cu 31 zile
	    ((result.date.month == APRILIE || result.date.month == IUNIE || result.date.month == SEPTEMBRIE ||
		result.date.month == NOIEMBRIE) && result.date.day == FINAL_LUNA_30)) {  // sau e final de luna cu 30 zile
            result.date.month++;
    	    result.date.day = 1;

		} else {
		    result.date.day++;
	    }

		result.time.hour = result.time.hour + result.tz->utc_hour_difference - HOURS_IN_A_DAY;

	} else if (result.time.hour < (-1) * result.tz->utc_hour_difference) {
		// conditia pusa nu este adevarata decat daca result.tz->utc_hour_difference < 0
		// am pus conditia astfel pt ca ora e de tip unsigned
		// daca era signed verificam daca result.time.hour + result.tz->utc_hour_difference < 0 (de aici am dedus)

		// se trece la ziua anterioara
		// verific daca se trece si in alta luna sau in alt an

		int an_bisect = 0;

        // verific daca anul este bisect sau nu:
        if ((result.date.year % 400 == 0) || (result.date.year % 4 == 0 && result.date.year % 100 != 0)) {
            an_bisect = 1;
        }

		if (result.date.month == IANUARIE && result.date.day == 1) {
			result.date.year--;
			result.date.month = DECEMBRIE;
			result.date.day = FINAL_LUNA_31; 
		} else if (result.date.month == MARTIE && result.date.day == 1) {
			result.date.month = FEBRUARIE;

            // ziua depinde de tipul anului (bisect sau nu):
			if (an_bisect == 1) {
				result.date.day = FINAL_FEB_AN_BISECT;
			} else {
				result.date.day = FINAL_FEB;
			}
		} else if ((result.date.month == FEBRUARIE || result.date.month == APRILIE || result.date.month == IUNIE ||
		result.date.month == AUGUST || result.date.month == SEPTEMBRIE || result.date.month == NOIEMBRIE) &&
		result.date.day == 1) { // e inceputul unei luni care urmeaza dupa o luna cu 31 zile
            result.date.month--;
			result.date.day = FINAL_LUNA_31;

		} else if ((result.date.month == MAI || result.date.month == IULIE || result.date.month == OCTOMBRIE ||
		result.date.month == DECEMBRIE) && result.date.day == 1) {
			// e inceputul unei luni care urmeaza dupa o luna cu 30 zile
			result.date.month--;
			result.date.day = FINAL_LUNA_30;

		} else {
			result.date.day--;
		}

		result.time.hour = result.time.hour + result.tz->utc_hour_difference + HOURS_IN_A_DAY;

	} else {
		result.time.hour = result.time.hour + result.tz->utc_hour_difference;
	}

	return result;
}

// Task 5
unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ datetimetz) {
    unsigned int timestamp = datetimetz.time.sec + datetimetz.time.min * SEC_IN_A_MIN
	+ datetimetz.time.hour * SEC_IN_AN_HOUR + (datetimetz.date.day - 1) * SEC_IN_A_DAY;

	int nr_ani_bisecti = 0, este_an_bisect = 0;

	for (int i = START_YEAR; i < datetimetz.date.year; i++) {
		if ((i % 400 == 0) || (i % 4 == 0 && i % 100 != 0)) {
			nr_ani_bisecti++;
		}
	}

	if (datetimetz.date.month >= FEBRUARIE) {
		if ((datetimetz.date.year % 400 == 0) || (datetimetz.date.year % 4 == 0 && datetimetz.date.year % 100 != 0)) {
			este_an_bisect = 1;
		}
	}

	for (int i = IANUARIE; i <= DECEMBRIE; i++) {
		if (datetimetz.date.month > i) {
			if (i == IANUARIE || i == MARTIE || i == MAI || i == IULIE || i == AUGUST || i== OCTOMBRIE ||
			i == DECEMBRIE) {
				timestamp = timestamp + FINAL_LUNA_31 * SEC_IN_A_DAY;
			} else if (i == FEBRUARIE) {
				if (este_an_bisect == 1) {
					timestamp = timestamp + FINAL_FEB_AN_BISECT * SEC_IN_A_DAY;
				} else {
					timestamp = timestamp + FINAL_FEB * SEC_IN_A_DAY;
				}
			} else if (i == APRILIE || i == IUNIE || i == SEPTEMBRIE || i == NOIEMBRIE) {
				timestamp = timestamp + FINAL_LUNA_30 * SEC_IN_A_DAY;
			}
		}
	}

    timestamp = timestamp + nr_ani_bisecti * DAYS_IN_A_LEAP_YEAR * SEC_IN_A_DAY;
	timestamp = timestamp + (datetimetz.date.year - START_YEAR - nr_ani_bisecti) * DAYS_IN_A_YEAR * SEC_IN_A_DAY;

	int diferenta_tz = datetimetz.tz->utc_hour_difference * SEC_IN_AN_HOUR;
	timestamp = timestamp - diferenta_tz;

	return timestamp;
}

// Task 6
void printDateTimeTZ(TDateTimeTZ datetimetz) {
	char luna[13][11];
	strcpy(luna[1], "ianuarie");
	strcpy(luna[2], "februarie");
	strcpy(luna[3], "martie");
	strcpy(luna[4], "aprilie");
    strcpy(luna[5], "mai");
	strcpy(luna[6], "iunie");
	strcpy(luna[7], "iulie");
	strcpy(luna[8], "august");
	strcpy(luna[9], "septembrie");
	strcpy(luna[10], "octombrie");
	strcpy(luna[11], "noiembrie");
	strcpy(luna[12], "decembrie");

	printf("%hhu %s %u, ", datetimetz.date.day, luna[datetimetz.date.month], datetimetz.date.year);
	printf("%02hhu:%02hhu:%02hhu ", datetimetz.time.hour, datetimetz.time.min, datetimetz.time.sec);
	printf("%s (UTC%+d)\n", datetimetz.tz->name, datetimetz.tz->utc_hour_difference);
}
