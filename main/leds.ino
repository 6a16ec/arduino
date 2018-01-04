const byte latchPin = 11;// The pin is connected to the ST_CP input 74HC595 /* (!) requires revision (!) */
const byte clockPin = 12;// The pin is connected to the SH_CP input 74HC595 /* (!) requires revision (!) */
const byte dataPin = 10;// The pin is connected to the DS input 74HC595 /* (!) requires revision (!) */

void led_setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void led_indication(byte number)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, number); 
  digitalWrite(latchPin, HIGH);
}

void led_sensors_indication()
{
  byte number = 0;
  byte weigher = 128;

  for(int i = 0; i < countSensors(); i++)
    number += weigher*sensors[i];

  led_indication(number);
}