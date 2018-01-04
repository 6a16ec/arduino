bool  sensors[8]; /* (!) requires revision (!) */
int  sensors_byte[8]; /* (!) requires revision (!) */

String string_in; //string_in.clear();



/* ### METHODS ###*/


void setup()
{
  led_setup();

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
  //chek_sensors();
  led_sensors_indication();
  readLine();
  algorithm2();
  // check_turns();
  //chek_perek();
  blue_debug();

}


