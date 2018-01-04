#define count_data 255
char data[count_data] = {0};
int addr = 0;

void bluetoothSetup() 
{ 
	Serial.begin(57600); 
} 

void bluetoothMonitoring1() 
{ 

if (Serial.available()) { // если пришли данные по Bluetooth 
  data[count_data-1] = Serial.read(); // записываем принятые данные, в последний элемент массива 
  if (data[count_data-1] == 32 && data[count_data-2] == 48) pinMode(12, OUTPUT); // Перед началом загрузки sketch, еще до RESET, поступает (DTR сигнал) (48 и 32) три раза. ASCII Code (48 = Zero / 0) - (32 = Space / пробел). проверяем если пришёл (DTR сигнал), делаем RESET. ( на Pro Mini, PIN-A3 соединён через Резистор 220 Ом с PIN-RESET) 
  
  for(int i = 0; i < count_data-1; i++)
    data[i] = data[i+1];
}
/* 
if(Serial.available()) 
{ 
char character; 
character = Serial.read(); 
if(character == '\n') Serial.print("LINE! ok"); 
} 
*/ 
}

/////


//unsigned long  last_time_out = 0;
void blue_debug()
{
  if (Serial.available()) {
    char priem = Serial.read();
    //  if (millis() - last_time_out >= 600)
    //{
    int kp = 10;
    int kd = 0.1;
    byte speed1 = 150;
    switch (priem)
    {
      case 'q':
        kd -= 0.2;
        variable_change ("kd", kd);
        break;
      case 'w':
        kd += 0.2;
        variable_change ("kd", kd);
        break;
      case 'e':
        kp -= 5;
        variable_change ("kp", kp);
        break;
      case 'r':
        kp += 5;
        variable_change ("kp", kp);
        break;
      case 't':
        speed1 -= 5;
        variable_change ("speed", speed1);
        break;
      case 'y':
        speed1 += 5;
        variable_change ("speed", speed1);
        break;
      case 'u':
        toEEPROM("all_variables");
        break;
    }

    Serial.print(kd);
    Serial.print(" ");
    Serial.print(kd);
    Serial.print(" ");
    Serial.println(speed1);
    //  last_time_out = millis();
    // }
  }
}




void bluetoothMonitoring()
{
	if(Serial.available()) 
	{ 
		char character; 
		character = Serial.read(); 

		if(character == '\n' || character == ';') 
		{
			parse();
			addr = 0;
		}
		else 
		{
			data[addr] = character;
			addr ++;
      		if(addr > count_data) addr = 0;
		}
	} 
}


void parse()
{
	String string = "";
	String variable_name;
	float variable_value;   
  
	for(int i = 0; i < addr; i++)
	{

    if(data[i] == ' ') continue;
    
		if(data[i] != '=') 
		{
		  string += data[i];
		}
		else
		{
			variable_name = string;
			string = "";
		}
	}
	variable_value = string.toFloat();
	variable_change(variable_name, variable_value);
}
