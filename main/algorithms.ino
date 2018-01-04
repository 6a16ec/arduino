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

void algorithm2()
{
  float array_weight[8] = { -4, -3, -2, -1, 1, 2, 3, 4};
  int len = 8;

  /*for(int i = 0; i < len/2; i++)
    array_weight[i] = (-1)*(len/2 - i);

    for(int i = len/2; i < len; i++)
    array_weight[i] = (i - len/2) + 1;*/

  float wi = 0;
  float bi = 0;
  for (int i = 0; i < len; i++)
  {
    wi += array_weight[i] * sensors[i];
    bi += sensors[i];
  }
  float e;
  if (bi == 0) e = e_last;
  else e = wi / (4 * bi);

  /*Serial.print(e);
    Serial.print(" ");
    Serial.print(speed1);
    Serial.print(" ");
    Serial.print(wi);
    Serial.print(" ");
      Serial.print(bi);
    Serial.print(" ");*/
  float delta_e = e - e_last;
  float delta_time = millis() - time_last;
  float prop = (float)((float)e * (float)variable("kp"));
  float speed_left =  variable("speed") - ((prop) + (delta_e / delta_time) * variable("kd"));
  float speed_right = variable("speed") + (prop) + (delta_e / delta_time) * variable("kd");
  //
  //  //Serial.print(delta_e / delta_time);
  //   Serial.print(delta_e);
  //  Serial.print(" ");
  //      Serial.print(delta_time);
  //  Serial.print(" ");
  //      Serial.print(prop);
  //  Serial.println(" ");

  /*
    Serial.print(speed_left);
    Serial.print(" ");
    Serial.print(speed_right);
    Serial.println(" ");
    Serial.print(prop);
    Serial.println(" ");
  */
  motorsOnlySpeed(speed_left, speed_right);

  e_last = e;
  time_last = millis();
}

const int count_move = 2; const int turns[2] = {2, 12};
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
    digitalWrite(2, HIGH);
    l_time = millis();
  }
  else if (count_black < 3)
  {
    turn_now = 0;
  }
  if (millis() - l_time > 600)
  {
    digitalWrite(2, LOW);
  }
  /* switch (count_turns)
    {
      case 1:
        left();
        count_turns++;
        break;
      case 2:
        motorsOFF();
        break;
    }*/

}
void check_turns()
{
  byte count_black = 0;

  for (int i = 0; i < 8; i++)
    count_black += sensors[i];

  if (turn_now == 0 && count_black >= 5)
  {
    count_turns++;
    turn_now = 1;

    for (int i = 0; i < count_move; i++)
    {
      if (turns[i] == count_turns)
      {
        motorsOnlySpeed(255, 0);
        while (1)
        {
          readLine();
          if (sensors[4] == 1) break;
        }
        while (1)
        {
          readLine();
          if (sensors[4] == 0) break;
        }
      }
      if (turns[i] > count_turns) break;
    }
  }
  else turn_now = 0;
}






