double e_last = 0;
unsigned long long int time_last = 0; 

void algorithm1()
{
  
  int left, right;
  
  for(int i = 0; i < 4; i++) left += sensors[i];
  for(int i = 4; i < 8; i++) right += sensors[i];

  //with inversiya
  int left_speed = map(left, 0, 1024*4, 0, 255)*5/2;
  int right_speed = map(right, 0, 1024*4, 0, 255)*5/2;

  motorsOnlySpeed(left_speed, right_speed);
}

void algorithm2()
{
  float array_weight[8] = {-4,-3,-2,-1,1,2,3,4};
  int len = 8;

  /*for(int i = 0; i < len/2; i++)
    array_weight[i] = (-1)*(len/2 - i);

  for(int i = len/2; i < len; i++)
    array_weight[i] = (i - len/2) + 1;*/

  float wi = 0;
  float bi = 0;
  for(int i = 0; i < len; i++)
  {
    wi += array_weight[i] * sensors[i];
    bi += sensors[i];
  }
  float e;
  if(bi == 0) e = 0;
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



