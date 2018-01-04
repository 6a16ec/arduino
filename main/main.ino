bool  sensors[8]; /* (!) requires revision (!) */
int  sensors_int[8]; /* (!) requires revision (!) */



/* ### METHODS ###*/


void setup()
{
  led_setup();
  beepSetup();

  motorsSetup();
  motorsON();
  motors(0, 0);
  motorsForward();

  sensorsSetup();
  //calibrate();
  old_sensors_values();
  EEPROM_setup();
  bluetoothSetup();
  pinMode (2, OUTPUT);
  // pish();


}

void loop()
{
  readLine();
  beep_check();
  //chek_sensors();
  led_sensors_indication();
  algorithm2();
  // check_turns();
  //chek_perek();
  //blue_debug();
  bluetoothMonitoring();

}


