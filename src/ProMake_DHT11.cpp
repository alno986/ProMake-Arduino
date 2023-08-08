#include "ProMake_DHT11.h"

void ProMake_DHT11::read(int pin)
{
    uint8_t bits[5];
    uint8_t cnt = 7;
    uint8_t idx = 0;
    for (int i=0; i< 5; i++) bits[i] = 0;
	delay(200);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(18);
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);
	digitalWrite(pin,LOW);
    pinMode(pin, INPUT);
    unsigned int loopCnt = 10000;
	while(digitalRead(pin) == LOW){
		if(loopCnt-- == 0)
		{
			break;
		}
	}
	loopCnt = 30000;
	while(digitalRead(pin) == HIGH){
		if(loopCnt-- == 0){
			break;
		}
	}
	for(int i=0;i<40;i++){
		loopCnt = 10000;
		while(digitalRead(pin) == LOW)
        {
			if(loopCnt-- == 0){
				break;
			}
		}
        unsigned long t = micros();
        while(digitalRead(pin) == HIGH)
        {
			if(loopCnt-- == 0){
				break;
			}
		}
		if ((micros() - t) > 50) bits[idx] |= (1 << cnt);
        if (cnt == 0)
        {
            cnt = 7;   
            idx++;      
        }else{
			cnt--;
		} 
	}
    humidity    = bits[0]; 
    temperature = bits[2]; 
}
