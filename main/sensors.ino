const byte count_sensors = 8; /* (!) requires revision (!) */

const  byte sensors_pins[8] = {A0, A1, A2, A3, A4, A5, A6, A7};	/* (!) requires revision (!) */
//const  byte sensors_pins[8] = {A7, A6, A5, A4, A3, A2, A1, A0};
int sensors_black[8] = {0};





/* ### METHODS ###*/

void sensorsSetup()
{
	for(int i; i < count_sensors; i++)
		pinMode(sensors[i], INPUT);
}

void calibrate()
{
  byte min_value[8];
  byte max_value[8];

  readLine();
  for(int i = 0; i < count_sensors; i++)
  {
  	min_value[i] = sensors_byte[i];
  	max_value[i] = sensors_byte[i];
  }

  long unsigned int last_time = millis();

  while (millis() - last_time < 5000)
  {
  	readLine();
	  for(int i = 0; i < count_sensors; i++)
	  {
	  	if(min_value[i] > sensors_byte[i]) min_value[i] = sensors_byte[i];
	  	if(max_value[i] < sensors_byte[i]) max_value[i] = sensors_byte[i];
	  }
  }

  for(int i = 0; i < count_sensors; i++)
  	sensors_black[i] = (max_value[i] + min_value[i]) / 2;
}

void  readLine()
{
  for(int i = 0; i < count_sensors;  i++)
  {
  	sensors_byte[i] = analogRead(sensors_pins[i]);
  	if(sensors_byte[i] >= sensors_black[i]) sensors[i] = true;
  	else sensors[i] = false;
  }

}

byte countSensors()
{
  return count_sensors;
}

