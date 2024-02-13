#ifndef TIMELIB_H_INCLUDED
#define TIMELIB_H_INCLUDED

#define SEC_IN_AN_HOUR 3600  // am pus aici constantele de care am nevoie si in bitpacking.c si planner.c
#define MONTHS_IN_A_YEAR 12
#define MAX_LITERE_IN_LUNA 10
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
#define START_YEAR 1970

#define MAX_NAME 5

typedef struct {
    unsigned char hour;
    unsigned char min;
    unsigned char sec;
} TTime;

typedef struct {
    unsigned char day;
    unsigned char month;
    unsigned int year;
} TDate;

typedef struct {
    char name[MAX_NAME];  // am modificat aici pt ca aveam eroare de coding style (5 era magic number)
    signed char utc_hour_difference;
} TTimezone;

typedef struct {
    TDate date;
    TTime time;
    TTimezone *tz;
} TDateTimeTZ;

TTime convertUnixTimestampToTime(unsigned int timestamp);
TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp);
TDate convertUnixTimestampToDate(unsigned int timestamp);
TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp, TTimezone *timezones, int timezone_index);
unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ);
void printDateTimeTZ(TDateTimeTZ datetimetz);

#endif  // TIMELIB_H_INCLUDED
