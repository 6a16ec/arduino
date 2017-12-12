bool  sensors[8]; /* (!) requires revision (!) */
byte  sensors_byte[8]; /* (!) requires revision (!) */

String string_in; //string_in.clear();



/* ### METHODS ###*/


void setup()
{
  motorsSetup();
  motorsON();
  motors(0, 0);
  motorsForward();

  sensorsSetup();
  calibrate();
  EEPROM_setup();
  bluetoothSetup();
 
 }

void loop()
{
  algorithm2();
  check_turns();
  
  bluetoothMonitoring();
}
//дорова, как оно?
//збс


