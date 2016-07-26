//tempSensor.c

 #include "tempSensor.h"

/*
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
*/

void testgpio_init(){
  GPIO_DeInit(GPIOE);
  GPIO_Init(GPIOE, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Fast);
}

long OneWireTemp(){
    //testgpio_init();
    OneWireReset(); // Reset Pulse 
    OneWireWriteByte(0xCC); // Issue skip ROM command (CCh)
    OneWireWriteByte(0x44); // Convert T command (44h)
    while(!ds_value); // DS will hold line low while making measurement
    OneWireReset(); // Start new command sequence 
    OneWireWriteByte(0xCC); // Issue skip ROM command 
    OneWireWriteByte(0xBE); // Read Scratchpad (BEh) - 15 bits
    unsigned char LSB = OneWireReadByte();
    unsigned char MSB = OneWireReadByte();
    OneWireReset(); // Stop Reading 
    unsigned int data = MSB;
    long temperature =  (((data << 8) | LSB) * 10 )  ;
    temperature /= 16;
    return (temperature);   
}


void OneWireHigh(){
    //BUSDIR = 0; // Set as output
    ds_out;
    ds_push_pull;
    //BUSOUT = 1; // Set high 
    ds_high;
}

void OneWireRelease(){
    //BUSDIR = 0; // Set as output
    ds_out;
    ds_push_pull;
    //BUSOUT = 0; // Set low
    ds_low;
}

unsigned char OneWireRead(){
    return ds_value;
}

unsigned int OneWireReset(){
    OneWireRelease();
    __delay_us(480); // 480uS Delay
    //__delay_us(240);
    OneWireHigh();
    __delay_us(70); // wait 70 uS before reading
    //OneWireRelease(); //debugging
    unsigned int OW = OneWireRead(); // check for OneWire
    __delay_us(205); // 410 uS delay
    __delay_us(205);
    OneWireHigh(); // give bus back to OneWire
    return OW; 
}


void OneWireWriteBit(unsigned char b){
    if(b){
        OneWireRelease();
        //__delay_us(6); // wait 6uS
        _delay_(6);
        OneWireHigh();
        __delay_us(64); // wait 64uS
    }
    else{
        OneWireRelease();
        __delay_us(60); // wait 60uS
        OneWireHigh();
        //__delay_us(10); // wait 10uS
        _delay_(12);
    }
}



unsigned char OneWireReadBit(){
    OneWireRelease();
    //__delay_us(6); // wait 6uS
    _delay_(6);
    OneWireHigh();
    //__delay_us(9); // wait 9uS
    _delay_(11);
    unsigned char out = OneWireRead();
    
    
    if(out){
      out = 0x01;
      //GPIO_SetBits(GPIOE, GPIO_Pin_1);
    }
    else{
      out = 0x00;
      //GPIO_ResetBits(GPIOE, GPIO_Pin_1);
    }
    
    
    __delay_us(55); // wait 55uS
    return out;
}

void OneWireWriteByte(unsigned char b){
    for(int i = 0; i < 8; i++){
        OneWireWriteBit(b & 0x01); // send LS bit first 
        b = b >> 1;
    }
}

unsigned char OneWireReadByte(void){
    unsigned char out; 
    for(int i = 0; i < 8; i++){ // read in LS bit first
        out = out >> 1; // get out ready for next bit
        if(OneWireReadBit() & 0x01) // if its a one 
            out = out | 0x80; // place a 1 
    }
    return out;
}