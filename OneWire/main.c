//main.c

#include "delay.h"
#include "tempSensor.h"

int main( void )
{      
  float temp = 0;
  InitTimer();
  while(1){
  temp = OneWireTemp();
  }
  //return 0;
}
