bool  sensors[8]; /* (!) requires revision (!) */
int  sensors_int[8]; /* (!) requires revision (!) */

#define analogRead analogReadFast
#define digitalRead digitalReadFast
#define digitalWrite digitalWriteFast

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
    Serial.println("robot stop");

    while(!robot_work) 
    {
      readLine();
      led_sensors_indication();
      bluetoothMonitoring();
    }

    Serial.println("robot start");
  }

}


