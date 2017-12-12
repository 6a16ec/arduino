#define count_data 20
byte data[count_data] = {0};

void bluetoothSetup() 
{ 
Serial.begin(57600); 
} 

void bluetoothMonitoring() 
{ 

if (Serial.available()) { // если пришли данные по Bluetooth 
	data[count_data-1] = Serial.read(); // записываем принятые данные, в последний элемент массива 
	if (data[count_data-1] == 32 && data[count_data-2] == 48) pinMode(12, OUTPUT); // Перед началом загрузки sketch, еще до RESET, поступает (DTR сигнал) (48 и 32) три раза. ASCII Code (48 = Zero / 0) - (32 = Space / пробел). проверяем если пришёл (DTR сигнал), делаем RESET. ( на Pro Mini, PIN-A3 соединён через Резистор 220 Ом с PIN-RESET) 
	
	for(int i = 0; i < count_data-1; i++)
		data[i] = data[i+1]
}
else
{

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
