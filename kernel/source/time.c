#include <vexos/lib/def.h>
#include <vexos/time.h>
#include <vexos/kprintf.h>
#include <vexos/arch/serial.h>
#include <vexos/info/kinfo.h>

volatile uefi_time efitime;
uint64_t current_ms = 0;

void
time_get(time_t* time) {

    kinfo->get_time((uefi_time*) &efitime, NULL);

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

    current_ms++;

    return;
}

void
time_sleep(uint64_t millisec) {

    volatile uint64_t ms_now = current_ms;

    while (current_ms - ms_now < millisec) {
        asm volatile("nop"); /* ? */
    };

    return;
}

uint64_t
time_ms_boot() {
    return current_ms;
}

void
time_init() {

    current_ms = 0;

    return;
}