#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "timelib.h"

#define INDEX_UTC 12

int main () {
    unsigned int timestamp;
    printf("timestamp = ");
    scanf("%u", &timestamp);

    // test task 1
    printf("Task 1: ");
    TTime a = convertUnixTimestampToTime(timestamp);
    printf("%02hhu:%02hhu:%02hhu\n", a.hour, a.min, a.sec);

    // test task 2
    printf("Task 2: ");
    TDate b = convertUnixTimestampToDateWithoutLeapYears(timestamp);
    printf("%02hhu.%02hhu.%u\n", b.day, b.month, b.year);

    // test task 3
    printf("Task 3: ");
    TDate c = convertUnixTimestampToDate(timestamp);
    printf("%02hhu.%02hhu.%u\n", c.day, c.month, c.year);

    // test task 4
    printf("Task 4: \n");
    TTimezone tz[] = {
    {"IDLW", -12},  // poz 0
    {"X", -11},
    {"HST", -10},
    {"AKST", -9},
    {"PST", -8},
    {"MST", -7},
    {"CST", -6},
    {"EST", -5},
    {"AST", -4},
    {"BRT", -3},
    {"GST", -2},
    {"CVT", -1},
    {"UTC", 0},  // poz 12
    {"CET", 1},
    {"EET", 2},
    {"FET", 3},
    {"GET", 4},
    {"MAWT", 5},
    {"IOT", 6},
    {"ICT", 7},
    {"CST", 8},
    {"JST", 9},
    {"AEST", 10},
    {"SBT", 11},
    {"FJT", 12}  // poz 24
    };

    printf("tz_index = ");
    int index = 0;
    scanf("%d", &index);
    TDateTimeTZ d = convertUnixTimestampToDateTimeTZ(timestamp, tz, index);
    printf("%02hhu.%02hhu.%u %02hhu:%02hhu:%02hhu", d.date.day, d.date.month, d.date.year, d.time.hour, d.time.min, 
    d.time.sec);
    printf("\n");
    
    // test task 5
    printf("Task 5: ");
    unsigned int ts = convertDateTimeTZToUnixTimestamp(d);
    printf("%u\n", ts);
    TDateTimeTZ e = convertUnixTimestampToDateTimeTZ(ts, tz, INDEX_UTC);

    //test task 6
    printf("Task 6: \n");
    printDateTimeTZ(d);
    printDateTimeTZ(e);

    return 0;
}
