#include <vexos/time.h>
#include <vexos/printk.h>
#include <vexos/bootinfo.h>

#include <vexos/lib/def.h>

#include <vexos/iobus/serial.h>

volatile uefi_time_t efitime;
uint64_t ms = 0;

void
time_get(time_t* time) {

    bootinfo.get_time((uefi_time_t*) &efitime, NULL);

    time->year      = efitime.year;
    time->month     = efitime.month;
    time->day       = efitime.day;
    time->hour      = efitime.hour;
    time->minute    = efitime.minute;
    time->second    = efitime.second;

    return;
}

void
time_tick() {

    ms++;

    return;
}

void
time_sleep(uint64_t millisec) {

    volatile uint64_t ms_now = ms;

    while (ms - ms_now < millisec) {
        asm volatile("nop"); /* ? */
    };

    return;
}

uint64_t
time_ms_boot() {
    return ms;
}

void
time_init() {

    ms = 0;

    return;
}
