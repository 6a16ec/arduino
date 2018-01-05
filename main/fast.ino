uint8_t anotherView(uint8_t pin)
{
  if(pin == A0) return B01000000;
  if(pin == A1) return B01000001;
  if(pin == A2) return B01000010;
  if(pin == A3) return B01000011;
  if(pin == A4) return B01000100;
  if(pin == A5) return B01000101;
  if(pin == A6) return B01000110;
  if(pin == A7) return B01000111;
}

uint16_t analogReadFast(uint8_t An_pin)
{
  An_pin = anotherView(An_pin);

  ADMUX=An_pin;   
  delayMicroseconds(10);    
  ADCSRA=B11000110; //B11000111-125kHz) return B11000110-250kHz 
  while (ADCSRA & (1 << ADSC));
  An_pin = ADCL;
  uint16_t An = ADCH; 
  return (An<<8) + An_pin;
}

bool digitalReadFast(uint8_t pin)
{
  if(pin == 0) return DDRD |=B00000001;
  if(pin == 1) return DDRD |=B00000010;
  if(pin == 2) return DDRD |=B00000100;
  if(pin == 3) return DDRD |=B00001000;
  if(pin == 4) return DDRD |=B00010000;
  if(pin == 5) return DDRD |=B00100000;
  if(pin == 6) return DDRD |=B01000000;
  if(pin == 7) return DDRD |=B10000000;

  if(pin == 8) return DDRB |= B00000001;
  if(pin == 9) return DDRB |= B00000010;
  if(pin == 10) return DDRB |=B00000100;
  if(pin == 11) return DDRB |=B10001000;
  if(pin == 12) return DDRB |=B00010000;
  if(pin == 13) return DDRB |=B00100000;

  if(pin == 14) return DDRC |=B00000001;
  if(pin == 15) return DDRC |=B00000010;
  if(pin == 16) return DDRC |=B00000100;
  if(pin == 17) return DDRC |=B00001000;
  if(pin == 18) return DDRC |=B00010000;
  if(pin == 19) return DDRC |=B00100000;
}

void digitalWriteFast(uint8_t pin, uint8_t status)
{
  if(status == HIGH)
  {
   if(pin == 0) PORTD |=B00000001;
   if(pin == 1) PORTD |=B00000010;
   if(pin == 2) PORTD |=B00000100; 
   if(pin == 3) PORTD |=B00001000; 
   if(pin == 4) PORTD |=B00010000; 
   if(pin == 5) PORTD |=B00100000;    
   if(pin == 6) PORTD |=B01000000;     
   if(pin == 7) PORTD |=B10000000;    

   if(pin == 8) PORTB |=B00000001;    
   if(pin == 9) PORTB |=B00000010;  
   if(pin == 10) PORTB|=B00000100;    
   if(pin == 11) PORTB|=B00001000;  
   if(pin == 12) PORTB|=B00010000;  
   if(pin == 13) PORTB|=B00100000;  

   if(pin == 14) PORTC |=B00000001;
   if(pin == 15) PORTC |=B00000010;   
   if(pin == 16) PORTC |=B00000100;  
   if(pin == 17) PORTC |=B00001000;     
   if(pin == 18) PORTC |=B00010000;    
   if(pin == 19) PORTC |=B00100000;  
  }
  //***************Status Low Pins*************
  if(status == LOW)
  {
   if(pin == 0) PORTD &= B11111110;
   if(pin == 1) PORTD &= B11111101;
   if(pin == 2) PORTD &= B11111011;
   if(pin == 3) PORTD &= B11110111;
   if(pin == 4) PORTD &= B11101111;
   if(pin == 5) PORTD &= B11011111;
   if(pin == 6) PORTD &= B10111111;
   if(pin == 7) PORTD &= B01111111;

   if(pin == 8) PORTB &= B11111110;
   if(pin == 9) PORTB &= B11111101;
   if(pin == 10) PORTB &=B11111011;
   if(pin == 11) PORTB &=B11110111;
   if(pin == 12) PORTB &=B11101111;
   if(pin == 13) PORTB &=B11011111;

   if(pin == 14) PORTC &= B11111110;
   if(pin == 15) PORTC &= B11111101;
   if(pin == 16) PORTC &= B11111011;
   if(pin == 17) PORTC &= B11110111;
   if(pin == 18) PORTC &= B11101111;
   if(pin == 19) PORTC &= B11011111;
  }
}