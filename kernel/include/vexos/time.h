#ifndef _TIME_H
#define _TIME_H

#include <vexos/lib/types.h>

typedef struct {

    uint16_t    year;
    uint8_t     month;
    uint8_t     day;
    uint8_t     hour;
    uint8_t     minute;
    uint8_t     second;

} time_t;

void time_get(time_t* time);
void time_tick();
void time_sleep(uint64_t millisec);
uint64_t time_ms_boot();

void time_init();

#endif