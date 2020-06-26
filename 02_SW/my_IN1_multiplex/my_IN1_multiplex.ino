//Optiboot on 28-pin cpu
//16MHz
//ATmega88

#include <Time.h>
#include "RTClib.h"

#define PIN_TUBE_HOUR_x0 PC3 //hardware 26 - arduino
#define PIN_TUBE_HOUR_0x PC2 //hardware 25 - arduino

#define PIN_TUBE_MIN_x0 PD6 //hardware 12 - arduino
#define PIN_TUBE_MIN_0x PD7 //hardware 13 - arduino

#define PIN_TUBE_SEC_x0 PC1 //hardware 6 - arduino
#define PIN_TUBE_SEC_0x PC0 //hardware 11 - arduino

#define PIN_A PD2//hardware 4 - arduino
#define PIN_B PD1//hardware 3 - arduino 
#define PIN_C PD0//hardware 2 - arduino 
#define PIN_D PD3//hardware 5 - arduino 

//RTC_DS3231 RTC;
RTC_DS1307 RTC;
DateTime now;
const int buttonPin_1 = PB1;  //hw 13    // the pin that the pushbutton is attached to

int lastButtonState = 0;     // previous state of the button
int buttonState = 0;         // current state of the button
/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int address = 0;

void setup() {
  
  RTC.begin();
  // put your setup code here, to run once:
 // DDRB = 0b11111111; // PB0 is used
  DDRC = 0b11111111; // PC0 - PC3 are used
  DDRD = 0b11111111; // PD0 - PD7 are used

// initialize the button pin as a input:
  //pinMode(PB1, INPUT);

  //if (RTC.lostPower())
  {
    //Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
#if 0
  cli();//stop interrupts
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK |= (1 << OCIE1A);

  sei();//allow interrupts
#endif
  delay(500);
}

void(* resetFunc) (void) = 0;//declare reset function at address 0
void switch_Winter_Summer_Hour()
{
  int local_hour = 0;
  // read the pushbutton input pin:
  //buttonState = digitalRead(PB1);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    local_hour = now.hour();
    if (buttonState == HIGH) 
    {
      // if the current state is LOW then the button went from on to off:
      local_hour++;
    } 
    else 
    {
      // if the current state is LOW then the button went from on to off:
      local_hour--;
    }
    RTC.adjust(
      DateTime(
        now.year(),
        now.month(),
        now.day(),
        local_hour, 
        now.minute(), 
        now.second()
        ));// Format: YYYY,MM,DD,HH,MM,SS
 resetFunc();  //call reset 
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
}
#if 0
int counter_isr = 0;
ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)

  if(counter_isr==10)
  {counter_isr = 0;}
  counter_isr++;
}
#endif
/*
#define PIN_A PD2//hardware 4 - arduino
#define PIN_B PD1//hardware 3 - arduino 
#define PIN_C PD0//hardware 2 - arduino 
#define PIN_D PD3//hardware 5 - arduino 
*/
int counter = 89;


// 1 - PD3
// 2 - PD0
// 3 - PD0 PD3
// 4 - PD1
// 5 - PD1 PD3
// 6 - PD1 PD0
// 7 - PD1 PD0 PD3
// 8 - PD2
// 9 - PD2 PD3
// 0 - 

//

void Write_0()
{
  DDRD &= ~(1 << PD0);
  DDRD &= ~(1 << PD1);
  DDRD &= ~(1 << PD2);
  DDRD &= ~(1 << PD3);
}
void Write_1()
{
  DDRD &= ~(1 << PD0);
  DDRD &= ~(1 << PD1);
  DDRD &= ~(1 << PD2);
  DDRD |= (1 << PD3);
}
void Write_2()
{
  DDRD |= (1 << PD0);
  DDRD &= ~(1 << PD1);
  DDRD &= ~(1 << PD2);
  DDRD &= ~(1 << PD3);
}
void Write_3()
{
  DDRD |= (1 << PD0);
  DDRD &= ~(1 << PD1);
  DDRD &= ~(1 << PD2);
  DDRD |= (1 << PD3);
}

void Write_4()
{
  DDRD &= ~(1 << PD0);
  DDRD |= (1 << PD1);
  DDRD &= ~(1 << PD2);
  DDRD &= ~(1 << PD3);
}
void Write_5()
{
  DDRD &= ~(1 << PD0);
  DDRD |= (1 << PD1);
  DDRD &= ~(1 << PD2);
  DDRD |= (1 << PD3);
}
void Write_6()
{
  DDRD |= (1 << PD0);
  DDRD |= (1 << PD1);
  DDRD &= ~(1 << PD2);
  DDRD &= ~(1 << PD3);
}
void Write_7()
{
  DDRD |= (1 << PD0);
  DDRD |= (1 << PD1);
  DDRD &= ~(1 << PD2);
  DDRD |= (1 << PD3);
}
void Write_8()
{
  DDRD &= ~(1 << PD0);
  DDRD &= ~(1 << PD1);
  DDRD |= (1 << PD2);
  DDRD &= ~(1 << PD3);
}
void Write_9()
{
  DDRD &= ~(1 << PD0);
  DDRD &= ~(1 << PD1);
  DDRD |= (1 << PD2);
  DDRD |= (1 << PD3);
}

/* Select a digit 0-9 and call the appropriate send function */
void selectDigit(int d)  
{
 switch(d)
 {
  case 0: Write_0(); break;
  case 1: Write_1(); break;
  case 2: Write_2(); break;
  case 3: Write_3(); break;
  case 4: Write_4(); break;
  case 5: Write_5(); break;
  case 6: Write_6(); break;
  case 7: Write_7(); break;
  case 8: Write_8(); break;
  case 9: Write_9(); break;
  default: Write_0(); break;
 } 
}
 
void display_clock(int pin, int digit)
{
  digitalWrite(pin, HIGH);
  selectDigit(digit);
  delay(2);     
  digitalWrite(pin, LOW);
  delay(1); 
}

byte display_now = 5;
void loop() 
{
  // Read from the real time clock
  now = RTC.now();

  //check button press
  //switch_Winter_Summer_Hour();
  //PIN_TUBE_SEC_0x
  display_clock(PD3, display_now/*(now.second())%10*/); 
  //PIN_TUBE_SEC_x0
  display_clock(PD4, display_now/*(now.second())/10*/);

  //PIN_TUBE_MIN_0x
  display_clock(PD7, display_now/*(now.minute())%10*/);
  //PIN_TUBE_MIN_x0
  display_clock(PD6, display_now/*(now.minute())/10*/);

  //PIN_TUBE_HOUR_0x
  display_clock(PC2, display_now/*(now.hour())%10*/);//PC2
  //PIN_TUBE_HOUR_x0
  display_clock(PC3, display_now/*(now.hour())/10*/);
   
  //DDRD &= ~(1 << PD4);       
  //PORTD = PORTD & 0b11110000;
  //DDRC &= ~((1 << PC2) | (1 << PC3));
}
  
