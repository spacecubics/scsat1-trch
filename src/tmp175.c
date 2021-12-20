/*
 * Space Cubics OBC TRCH Software
 *  TMP175 Driver
 *
 * (C) Copyright 2021
 *         Space Cubics, LLC
 *
 */

#include <pic.h>
#include <interrupt.h>
#include <i2c-gpio.h>
#include <tmp175.h>

int tmp175_data_read (tmp175_data *td, int fpga_state) {
        char addr = (char)((*td).addr << 1);
        int err = 0;
        if (get_i2c((*td).master, fpga_state))
                return 1;

        interrupt_lock(1);        
        send_start((*td).master);
        err |= i2c_send_data((*td).master, addr);
        err |= i2c_send_data((*td).master, REG_TEMP);
        send_start((*td).master);
        err |= i2c_send_data((*td).master, addr | 0x01);
        (*td).data[0] = i2c_receive_data((*td).master);
        (*td).data[1] = i2c_receive_data((*td).master);
        send_stop((*td).master);
        interrupt_lock(0);

        (*td).error = err;
        return 0;
}
