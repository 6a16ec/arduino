double e_last = 0;
unsigned long long int time_last = 0;

void algorithm1()
{

  int left, right;

  for (int i = 0; i < 4; i++) left += sensors[i];
  for (int i = 4; i < 8; i++) right += sensors[i];

  //with inversiya
  int left_speed = map(left, 0, 1024 * 4, 0, 255) * 5 / 2;
  int right_speed = map(right, 0, 1024 * 4, 0, 255) * 5 / 2;

  motorsOnlySpeed(left_speed, right_speed);
}

/*working variables*/
unsigned long lastTime;                                                     //последнее время
double errSum, lastErr, error;                                              //сумма ошибок, последняя ошибка, ошибка
double sensors_weight[8] = { -4, -3, -2, -1, 1, 2, 3, 4};                   //вес сенсоров
void algorithm2()
{
  double sum_weight_sensors, Output, count_sensors_on_black;                  //входные значения, выходные значения, заданное значение
  for (int i = 0; i < 8; i++)
  {
    sum_weight_sensors += sensors_weight[i] * sensors[i];                    // сумма весов сенсоров
    count_sensors_on_black += sensors[i];                                    //количество сенсоров на черном
  }
  if (count_sensors_on_black == 0) error = lastErr;
  else error = sum_weight_sensors / (4 * count_sensors_on_black);            //формула, которая работает
  /*Как давно мы рассчитывали*/
  unsigned long now = millis();                                              //время сейчас
  double timeChange = (double)(now - lastTime);                              //настоящее - прошлое, промежуток времени

  /*Вычисляем все переменные рабочей ошибки*/
  errSum += (error * timeChange);                                            // сумма ошбок = ошибка * (настоящее - прошлое)
  double dErr = (error - lastErr) / timeChange;                              //ошибка - прошлая ошибка /  (настоящее - прошлое)

  /*Вычисляем выходной сигнал PID*/
  Output = variable ("kp") * error + variable ("ki") * errSum + variable ("kd") * dErr;;

  /**/
  float speed_left = variable("speed") + Output;
  float speed_right = variable("speed") - Output;

  if (speed_left < 0) speed_left = 0;
  if (speed_right < 0) speed_right = 0;
/*
  Serial.print(speed_left);
  Serial.print(" ");
  Serial.print(speed_right);
  Serial.print(" ");
  Serial.println(error);
*/
  motorsOnlySpeed(speed_left, speed_right);

  /*Запоминаем некоторые переменные для следующего раза*/
  lastErr = error;
  lastTime = now;
}

int count_turns = 0; bool turn_now = 0;
long unsigned int l_time = 0;
void chek_perek ()
{
  int count_black = 0;
  for (int i = 0; i < 8; i++)
    count_black += sensors[i];
  if (turn_now == 0 && count_black >= 6)
  {
    count_turns++;
    turn_now = 1;
    //beep(1);
  }
  else if (count_black < 3)
  {
    turn_now = 0;
  }
  /* switch (count_turns)
    {
     case 1:

       inver = true;
       count_turns++;
       break;
     case 2:

       break;
     case 3:

       break;
     case 4:
       inver = false;
       break;
     case 5:
       motorsOFF();
       break;
    }
  */
}
