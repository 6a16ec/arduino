const byte count_sensors = 8; /* (!) requires revision (!) */

const  byte sensors_pins[8] = {A0, A1, A2, A3, A4, A5, A6, A7};	/* (!) requires revision (!) */
//const  byte sensors_pins[8] = {A7, A6, A5, A4, A3, A2, A1, A0};





/* ### METHODS ###*/

void sensorsSetup()
{
	for(int i; i < count_sensors; i++)
		pinMode(sensors[i], INPUT);
}

void  readLine()
{
  for(int i = 0; i < count_sensors;  i++)
  	sensors[i] = analogRead(sensors_pins[i]);
}

byte countSensors()
{
  return count_sensors;
}

