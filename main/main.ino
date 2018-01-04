bool  sensors[8]; /* (!) requires revision (!) */
int  sensors_int[8]; /* (!) requires revision (!) */

bool robot_work = true;

/* ### METHODS ###*/


void setup()
{
  led_setup();
  beepSetup();

  motorsSetup();
  motorsForward();

  sensorsSetup();
  //calibrate();
  old_sensors_values();
  EEPROM_setup();
  bluetoothSetup();
}

void loop()
{
  readLine();
  led_sensors_indication();
  algorithm2();
  beep_check();
  bluetoothMonitoring();

  if(!robot_work)
  {
    motors(0, 0);

    while(!robot_work) bluetoothMonitoring();
  }

}


