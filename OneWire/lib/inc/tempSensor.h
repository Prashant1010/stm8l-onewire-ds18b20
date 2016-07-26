//tempSensor.h



#ifndef DS18B20_H
#define DS18B20_H

#include "stm8l15x.h"

#define dsport          GPIOD
#define dspin           GPIO_Pin_1

#define ds_out          dsport->DDR |= dspin
#define ds_in           dsport->DDR &= (uint8_t)(~(dspin))
#define ds_high         dsport->ODR |= dspin
#define ds_low          dsport->ODR &= (uint8_t)(~(dspin))

#define ds_pull_up      dsport->CR1 |= dspin
#define ds_floating     dsport->CR1 &= (uint8_t)(~(dspin))
#define ds_push_pull    dsport->CR1 |= dspin
#define ds_open_drain   dsport->CR1 &= (uint8_t)(~(dspin))
#define ds_value        (BitStatus)(dsport->IDR & (uint8_t)dspin)


// Available Functions:
long OneWireTemp(void); // Returns the temperature in celsius 
unsigned int OneWireReset(void); // Sends a reset pulse to the sensor 
void OneWireWriteBit(unsigned char); // write a single bit to the OneWire
unsigned char OneWireReadBit(void); // reads a single bit 
void OneWireWriteByte(unsigned char); // writes a byte 
unsigned char OneWireReadByte(void); // reads a byte 
unsigned char OneWireRead(void); // reads the current status of the bus
void OneWireHigh(void); // sets the bus high
void OneWireRelease(void); // releases the bus 

#endif // DS18B20_H