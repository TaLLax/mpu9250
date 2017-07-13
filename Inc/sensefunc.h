
#include "stdint.h"
void write_spi(uint8_t *value,uint8_t amount);
void read_spi(uint8_t *value);
void setup_sensor(void);
void read_sensor(int16_t *values);
uint8_t read_mag_sensor(uint8_t address);
