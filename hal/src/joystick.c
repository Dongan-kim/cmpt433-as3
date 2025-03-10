#include "hal/joystick.h"
#include <gpiod.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <string.h>


#define I2C_BUS "/dev/i2c-1"
#define I2C_DEVICE_ADDRESS 0x48
#define REG_DATA 0x00
#define REG_CONVERSION 0x00  
#define REG_CONFIG 0x01
#define MUX_CHANNEL_Y 0x83C2
static int i2c_file_desc;

#define GPIO_CHIP "/dev/gpiochip2"
#define GPIO_BUTTON 15  // GPIO Line for pressing in

static struct gpiod_chip *chip;
static struct gpiod_line *button_line;


void joystick_init(void) {
    i2c_file_desc = open(I2C_BUS, O_RDWR);
    if (i2c_file_desc == -1) {
        perror("Unable to open I2C bus");
        exit(EXIT_FAILURE);
    }

    if (ioctl(i2c_file_desc, I2C_SLAVE, I2C_DEVICE_ADDRESS) == -1) {
        perror("Unable to set I2C device to slave address");
        exit(EXIT_FAILURE);
    }

    // Initialize GPIO for joystick button press
    chip = gpiod_chip_open(GPIO_CHIP);
    if (!chip) {
        perror("Failed to open GPIO chip");
        exit(EXIT_FAILURE);
    }

    button_line = gpiod_chip_get_line(chip, GPIO_BUTTON);
    if (!button_line) {
        perror("Failed to get GPIO line for joystick button");
        exit(EXIT_FAILURE);
    }

    gpiod_line_request_input(button_line, "joystick_btn");
}

static void write_i2c_reg16(int i2c_file_desc, uint8_t reg_addr, uint16_t value) {
    uint8_t buffer[3] = {reg_addr, (value >> 8) & 0xFF, value & 0xFF};
    if (write(i2c_file_desc, buffer, 3) != 3) {
        perror("Unable to write I2C register");
        exit(EXIT_FAILURE);
    }
}

int16_t read_i2c_reg16(int fd, uint8_t reg_addr) {
    if (write(fd, &reg_addr, 1) != 1) {
        perror("I2C: Unable to write register address");
        exit(EXIT_FAILURE);
    }


    uint8_t data[2];
    if (read(fd, data, 2) != 2) {
        perror("I2C: Unable to read register");
        exit(EXIT_FAILURE);
    }

    uint16_t raw_value = (data[0] << 8) | data[1];

    // **Right-align 12-bit ADC value (shift by 4)**
    raw_value = raw_value >> 4;

    return raw_value;
}

Joystick_dir joystick_get_dir(void) {
    uint16_t raw_read = read_joystick_y();
    int joystick_value = (int) raw_read; 
    
    if (joystick_value >= 2000 && joystick_value <=4000){
        return 0;
    }else if (joystick_value >=  500 && joystick_value < 2000){
        return 1;
    }else{
        return 2;
    }
}

uint16_t read_joystick_y() {
    write_i2c_reg16(i2c_file_desc, REG_CONFIG, MUX_CHANNEL_Y);
    return read_i2c_reg16(i2c_file_desc, REG_CONVERSION);
}

int joystick_pressed() {
    if (!button_line) {
        return 0; // Button not initialized
    }
    
    return gpiod_line_get_value(button_line) == 0;  // Active LOW
}


void joystick_cleanup(void) {
    if (button_line) {
        gpiod_line_release(button_line);
    }
    if (chip) {
        gpiod_chip_close(chip);
    }
    close(i2c_file_desc);
}