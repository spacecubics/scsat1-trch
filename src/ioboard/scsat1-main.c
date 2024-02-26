/*
 * Copyright (c) 2024 Space Cubics, LLC.
 */

#include "ioboard.h"
#include "trch.h"

/* Map signal names */
#define T_UART_DE          UIO3_00
#define T_UART_RE_B        UIO3_01
#define T_3V3_SYS_EN       UIO3_02

void enable_srs3_485(void)
{
        T_UART_DE = 1;
        T_UART_RE_B = 0;
        __delay_ms(1000);
}

void disable_srs3_485(void)
{
        T_UART_DE = 0;
        T_UART_RE_B = 1;
}

int ioboard_init(void)
{
        T_3V3_SYS_EN = 1;
        enable_srs3_485();

        return 0;
}
