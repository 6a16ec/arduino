#include <EEPROM.h>
#define variables_count  4 /* (!) requires revision (!) */

const String variables_name[variables_count] = {"speed", "kp", "kd", "ki"}; /* (!) requires revision (!) */
const String variables_type[variables_count] = {"int", "float", "float", "float"}; /* (!) requires revision (!) */

const bool writeDebugInfo = true;

/* ### METHODS ###*/

int variables_address[variables_count];
float variables[variables_count];


void EEPROM_setup()
{
  int address = 0;
  for(int i = 0; i < variables_count; i++)
  {
    variables_address[i] = address;
    if(variables_type[i] == "byte") address += 1;
    if(variables_type[i] == "int") address += 2;
    if(variables_type[i] == "float") address += 4;
  }

  fromEEPROM("all");
  if(writeDebugInfo) variable_write("all");
}


void fromEEPROM(String name)
{
  for(int i = 0; i < variables_count; i++)
  {
    if(variables_name[i] == name || name == "all")
    {
      if(writeDebugInfo) Serial.print("local variable " + String(variables_name[i]) + " change from " + String(variables[i]) + " to ");

      if(variables_type[i] == "byte") variables[i] = EEPROM_readByte(variables_address[i]);
      if(variables_type[i] == "int") variables[i] = EEPROM_readInt(variables_address[i]);
      if(variables_type[i] == "float") variables[i] = EEPROM_readFloat(variables_address[i]);

      if(writeDebugInfo) Serial.println(String(variables[i]) + " (fromEEPROM)");

      if(name != "all") break;
    }
  }
}

void toEEPROM(String name)
{
  for(int i = 0; i < variables_count; i++)
  {
    if(variables_name[i] == name || name == "all")
    {
      if(writeDebugInfo) Serial.println("global variable " + String(variables_name[i]) + " change to " + String(variables[i]) + " (toEEPROM)");

      if(variables_type[i] == "byte") EEPROM_writeByte(variables_address[i], variables[i]);
      if(variables_type[i] == "int") EEPROM_writeInt(variables_address[i], variables[i]);
      if(variables_type[i] == "float") EEPROM_writeFloat(variables_address[i], variables[i]);

      if(name != "all") break;
    }
  }
}

double variable(String name)
{
  for(int i = 0; i < variables_count; i++)
  {
    if(variables_name[i] == name)
    {
      return variables[i];
    }
  }
}

void variable_change(String name, double number)
{
  for(int i = 0; i < variables_count; i++)
  {
    if(variables_name[i] == name)
    {
      if(writeDebugInfo) Serial.print("local variable " + String(variables_name[i]) + " change from " + String(variables[i]) + " to ");
      variables[i] = number;
      if(writeDebugInfo) Serial.println(String(variables[i]) + " (variable_change)");
      break;
    }
  }
}

void variable_write(String name)
{
  for(int i = 0; i < variables_count; i++)
  {
    if(variables_name[i] == name || name == "all")
    {
      Serial.print(variables_name[i] + " = "); Serial.println(variables[i]);
    }
  }
  Serial.println("_ _ _ _ _");
}

void EEPROM_writeByte(int addr, byte num) {
  EEPROM.write(addr, num);
}

int EEPROM_readByte(int addr) {
  return EEPROM.read(addr);
}

void EEPROM_writeInt(int addr, int num) {
  byte raw[2];
  (int&)raw = num;
  for(byte i = 0; i < 2; i++) EEPROM.write(addr+i, raw[i]);
}

int EEPROM_readInt(int addr) {    
  byte raw[2];
  for(byte i = 0; i < 2; i++) raw[i] = EEPROM.read(addr+i);
  int &num = (int&)raw;
  return num;
}

void EEPROM_writeFloat(int addr, float num) {
  byte raw[4];
  (float&)raw = num;
  for(byte i = 0; i < 4; i++) EEPROM.write(addr+i, raw[i]);
}

float EEPROM_readFloat(int addr) {    
  byte raw[4];
  for(byte i = 0; i < 4; i++) raw[i] = EEPROM.read(addr+i);
  float &num = (float&)raw;
  return num;
}





