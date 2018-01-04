const byte beepPin = 2;
const int time_beep_play = 500;
const int time_beep_break = 500;

long long unsigned int last_time = millis();
bool beep_play = false;
int count = 0;

void beepSetup()
{
	pinMode(beepPin, OUTPUT);
}

void beep_ON() {digitalWrite(beepPin, HIGH);}

void beep_OFF() {digitalWrite(beepPin, LOW);}


void beep(int count_beeps = 1)
{
  cout = count_beeps;
  beep_check();
}

void beep_check()
{
	if(beep_play && millis() - last_time >= time_beep_play) 
	{
		beep_OFF(); 
		last_time = millis();
	}
	if(!beep_play && count > 0 && millis() - last_time >= time_beep_break)
	{
		beep_ON(); 
		cout -= 1;
		last_time = millis();
	}
}