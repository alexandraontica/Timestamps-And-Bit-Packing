#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "timelib.h"

int main () {
    unsigned int timestamp;
    printf("timestamp = ");
    scanf("%u", &timestamp);

    // test task 1
    printf("Task 1: ");
    TTime a = convertUnixTimestampToTime(timestamp);
    printf("%02hhu %02hhu %02hhu\n", a.hour, a.min, a.sec);

    // test task 2
    printf("Task 2: ");
    TDate b = convertUnixTimestampToDateWithoutLeapYears(timestamp);
    printf("%u %02hhu %02hhu\n", b.year, b.month, b.day);

    // test task 3
    printf("Task 3: ");
    TDate c = convertUnixTimestampToDate(timestamp);
    printf("%u %02hhu %02hhu\n", c.year, c.month, c.day);

    // test task 4
    printf("Task 4: \n");
    TTimezone tz[] = {
    {"UTC-", -12}, // poz 0
    {"UTC-", -11},
    {"UTC-", -10},
    {"UTC-", -9},
    {"UTC-", -8},
    {"UTC-", -7},
    {"UTC-", -6},
    {"UTC-", -5},
    {"UTC-", -4},
    {"UTC-", -3},
    {"UTC-", -2},
    {"UTC-", -1},
    {"UTC", 0}, // poz 12
    {"UTC+", 1},
    {"EET", 2},
    {"UTC+", 3},
    {"UTC+", 4},
    {"UTC+", 5},
    {"UTC+", 6},
    {"UTC+", 7},
    {"UTC+", 8},
    {"UTC+", 9},
    {"UTC+", 10},
    {"UTC+", 11},
    {"UTC+", 12} // poz 24
    };

    printf("tz_index = ");
    int index = 0;
    scanf("%d", &index);
    TDateTimeTZ d = convertUnixTimestampToDateTimeTZ(timestamp, tz, index);
    printf("%02hhu.%02hhu.%u %02hhu:%02hhu:%02hhu", d.date.day, d.date.month, d.date.year, d.time.hour, d.time.min, d.time.sec);
    printf("\n");
    
    // test task 5
    printf("Task 5: ");
    unsigned int ts = convertDateTimeTZToUnixTimestamp(d);
    printf("%u\n", ts);

    //test task 6
    printf("Task 6: \n");
    printDateTimeTZ(d);

    return 0;
}
