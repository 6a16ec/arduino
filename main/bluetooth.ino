/*
  examples:

speed = 12345;
kp = 123.45;

speed + 10;
speed - 20;

speed * print;
speed * write
speed * read;
all * print;
all * write;
all * read;

speed * toEEPROM;
speed * fromEEPROM;
all * toEEPROM;
all * fromEEPROM;
*/

#define count_data 255
char data[count_data] = {0};
int addr = 0;

void bluetoothSetup() 
{ 
  Serial.begin(57600); 
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
  char action = '0';
  String string = "";
  String variable_name;
  float variable_value;   
  
  for(int i = 0; i < addr; i++)
  {
    if(data[i] == ' ') continue;

    if(data[i] == '=' || data[i] == '+' || data[i] == '-' || data[i] == '*') 
    {
      action = data[i];
      variable_name = string;
      string = "";
    }
    else
    {
      string += data[i];
    }
  }

  if(action == '=' || action == '+' || action == '-')
  {
    variable_value = string.toFloat();

    if(action == '+') variable_value = variable(variable_name) + variable_value;
    if(action == '-') variable_value = variable(variable_name) - variable_value;

    variable_change(variable_name, variable_value);   
  }

  if(action == '*')
  {
    if(string == "toEEPROM") toEEPROM(variable_name);
    if(string == "fromEEPROM") fromEEPROM(variable_name);
    if(string == "read" || string == "print" || string == "write") variable_write(variable_name);

  }
}

