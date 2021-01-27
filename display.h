
// REGISTRE DE DECALAGE SN"74HC595"
#define NX_DATA     8
#define NX_LATCH    9
#define NX_CLOCK   10

// For Nixe => first h:h , second m:m 
int firstPart;
int secondPart;

// LED 
#define ledPin 12

// -------------------------------------------------------------------

void displayFreq(unsigned int firstFreq, unsigned int secondFreq) 
{
  
  PORTB &= ~_BV(PB1);   // replace digitalWrite(NX_LATCH, LOW); // pin 9 PB1  
                      
  shiftOut(NX_DATA, NX_CLOCK, MSBFIRST, inverse_bcd(secondFreq));
  shiftOut(NX_DATA, NX_CLOCK, MSBFIRST, inverse_bcd(firstFreq));
  
  PORTB |= _BV(PB1);   // replace digitalWrite(NX_LATCH, HIGH); // pin 9 PB1                           
}

// -------------------------------------------------------------------

void updateDisplay(int nixies) 
{
  firstPart = nixies / 100;
  secondPart = nixies % 100;
  displayFreq(decimal_to_bcd(firstPart), decimal_to_bcd(secondPart));
}

// -------------------------------------------------------------------

void flashLed() 
{
  for (int i = 0 ; i <= 10; i++) {
    PORTB |= _BV(PB4);    // replace  digitalWrite(12, HIGH);
    delay(50);
    PORTB &= ~_BV(PB4);   // replace  digitalWrite(12, LOW);
    delay(50);
  }
} 
