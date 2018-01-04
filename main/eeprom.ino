#include <EEPROM.h>
#define variables_count  3 /* (!) requires revision (!) */

const String variables_name[variables_count] = {"speed", "kp", "kd"}; /* (!) requires revision (!) */
const String variables_type[variables_count] = {"int", "float", "float"}; /* (!) requires revision (!) */




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

  fromEEPROM("all_variables");
}


void fromEEPROM(String name)
{
  for(int i = 0; i < variables_count; i++)
  {
    if(variables_name[i] == name || name == "all_variables")
    {
      if(variables_type[i] == "byte") variables[i] = EEPROM_readByte(variables_address[i]);
      if(variables_type[i] == "int") variables[i] = EEPROM_readInt(variables_address[i]);
      if(variables_type[i] == "float") variables[i] = EEPROM_readByte(variables_address[i]);

      if(name != "all_variables") break;
    }
  }
}

void toEEPROM(String name)
{
  for(int i = 0; i < variables_count; i++)
  {
    if(variables_name[i] == name || name == "all_variables")
    {
      if(variables_type[i] == "byte") EEPROM_writeByte(variables_address[i], variables[i]);
      if(variables_type[i] == "int") EEPROM_writeInt(variables_address[i], variables[i]);
      if(variables_type[i] == "float") EEPROM_writeByte(variables_address[i], variables[i]);

      if(name != "all_variables") break;
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
      variables[i] = number;
      break;
    }
  }
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




