const int count_sensors = 8; /* (!) requires revision (!) */

const  int sensors_pins[8] = {A0, A1, A2, A3, A4, A5, A6, A7};	/* (!) requires revision (!) */
//const  int sensors_pins[8] = {A7, A6, A5, A4, A3, A2, A1, A0};
int sensors_black[8] = {0};

//Пин подключен к ST_CP входу 74HC595
int latchPin = 11;
//Пин подключен к SH_CP входу 74HC595
int clockPin = 12;
//Пин подключен к DS входу 74HC595
int dataPin = 10;

/* ### METHODS ###*/

void sensorsSetup()
{
  for (int i; i < count_sensors; i++)
    pinMode(sensors[i], INPUT);
}

void calibrate()
{
  byte min_value[8];
  byte max_value[8];

  readLine();
  for (int i = 0; i < count_sensors; i++)
  {
    min_value[i] = sensors_byte[i];
    max_value[i] = sensors_byte[i];
  }

  long unsigned int last_time = millis();

  while (millis() - last_time < 5000)
  {
    readLine();
    for (int i = 0; i < count_sensors; i++)
    {
      if (min_value[i] > sensors_byte[i]) min_value[i] = sensors_byte[i];
      if (max_value[i] < sensors_byte[i]) max_value[i] = sensors_byte[i];
    }
  }

  for (int i = 0; i < count_sensors; i++)
    sensors_black[i] = (max_value[i] + min_value[i]) / 2;
  for (int i = 0; i < count_sensors; i++)
  {
    int adrr = 512;
    adrr  += 2;
    EEPROM_writeInt(adrr, sensors_black[i]);
  }
}
void old_sensors_values()
{
  for (int i = 0; i < count_sensors; i++)
  {
    int adrr = 512;
    adrr  += 2;
    sensors_black[i] = EEPROM_readInt(adrr);
  }
}
void calibrate_after()
{
  int min_value = sensors_byte[0];
  int max_value = sensors_byte[0];

  for (int i = 0; i < count_sensors; i++)
  {
    if (sensors_byte[i] < min_value) min_value = sensors_byte[i];
    if (sensors_byte[i] > max_value) max_value = sensors_byte[i];
  }

  for (int i = 0; i < count_sensors; i++)
    sensors_black[i] = (max_value + min_value) / 2;
}


void inversion()
{
  int average = 0;

  for (int i = 0; i < count_sensors; i++)
    average += sensors_byte[i];

  average /= count_sensors;


  byte first = count_sensors - 1, last = 0;

  for (int i = 0; i < count_sensors; i++)
  {
    if (sensors[i] && i < first) first = i;
    if (sensors[i] && i > last) last = i;
  }

  bool need_inversion = false;
  for (int i = first + 1; i < last; i++)
  {
    if (!(sensors[i]))
    {
      need_inversion = true;
      break;
    }
  }

  if (need_inversion) for (int i = 0; i < count_sensors; i++) sensors[i] = !sensors[i];
}


void  readLine()
{
  for (int i = 0; i < count_sensors;  i++)
  {
    sensors_byte[i] = analogRead(sensors_pins[i]);
    if (sensors_byte[i] >= sensors_black[i]) sensors[i] = true;
    else sensors[i] = false;
  }

}

byte countSensors()
{
  return count_sensors;
}
void led_setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
void led_sensors_indication()
{
  byte byteToSend = 0; //Создаем пустой байт B00000000
  for (int i = 0; i < 8; i++)
  {
    if (sensors[i])
    {
      bitWrite(byteToSend, i, HIGH); // При bitPos=0 получим B00000001, при bitPos=1 - B00000010, при bitPos=2 - B00000100 и т.д.
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, byteToSend); // Инвертируем сигнал при помощи MSBFIRST, грузим с первого бита
      digitalWrite(latchPin, HIGH);
    }
    else
    {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, byteToSend); // Инвертируем сигнал при помощи MSBFIRST, грузим с первого бита
      digitalWrite(latchPin, HIGH);
    }
  }
  byteToSend = 0; // Обнуляем байт при каждом проходе
}

void pish ()
{
  long unsigned int last_time = millis();
  digitalWrite(2, HIGH);
  if (millis() - last_time > 500)
  {
    digitalWrite(2, LOW);
  }
}

void chek_sensors()
{
  for (int i = 0; i < 8; i++)
  {
    Serial.print(sensors_byte[i]);
    Serial.print("_");
    Serial.print(sensors_black[i]);
    Serial.print("      ");
  }
  Serial.println(" ");

}

