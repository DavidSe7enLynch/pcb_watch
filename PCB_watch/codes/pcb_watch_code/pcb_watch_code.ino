/*
   Compile and upload for:
   ATtiny414 @ 5 MHz (internal oscillator; BOD disabled)
*/
// Include interrupt abilities, sleep, and input/output
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

int highs[12] = {1, 2, 0, 2, 8, 1, 8, 0, 2, 0, 1, 8}; //digital pins for high
int lows[12] =  {2, 1, 2, 8, 2, 8, 0, 8, 0, 1, 0, 1}; //digital pins low

int buttonPin = 9; //pa2
unsigned long t1; //timer variable
unsigned long t2; //timer variable
volatile int showTime = -1; //flag for showing time
int timeOn = 3; // seconds to show the time
int blinkRate = 4; //How often to blink an LED in Hz
int constantRate = 100; //How quickly to blink an LED to make it appear continuous in Hz
int refreshRate = 500; //How often to refresh the screen in Hz
int blinkTime = 500 / blinkRate; //time to wait in millis
int constantTime = 500 / constantRate; //time to wait in millis
volatile int LED1 = 1; //the LEDs to display (from 1 to 12)
volatile int LED2 = 1;
volatile int LED1_on = 1; //flag for if the LEDs should be on or off at a moment
volatile int LED2_on = 1;

volatile unsigned int Secs = 0;
volatile unsigned int offset_secs = 0;    // number of offset seconds
volatile int Hours = 1;                   // From 1 to 12
volatile int Remaining_sec = 0;           // How many seconds in the hour
volatile int Fivemins = 0;                // How many 5 minutes are in those seconds

// When the watch is turned on, set the time
void setTime() {
  // blink every LED for 1.5 seconds to set hour and wait for a button press
  int i = 0; // start at hour 1
  int flag = 1; //flag for if the button was pressed
  while (flag == 1) { // button is not pressed
    pinMode(lows[i], OUTPUT); //turn on the low and high pin as outputs
    pinMode(highs[i], OUTPUT);
    digitalWrite(lows[i], LOW); //turn on this LED
    digitalWrite(highs[i], HIGH);
    // wait 1.5 seconds
    t1 = millis();
    while ((millis() - t1) < 1500) { //wait 1.5 seconds --> if button is pressed flip the flag
      if (digitalRead(buttonPin) == LOW) { //if the button was pressed
        delay(100); // debounce
        flag = flag * -1; // flip the flag
      }
    }
    pinMode(lows[i], INPUT); // turn those LED pins back to inputs
    pinMode(highs[i], INPUT);
    i++;
    if (i >= 12) {
      i = 0;
    }
  } // This loop is left once the button is pressed
  int set_hours = i; //the hours we set is 'i'
  offset_secs = set_hours * (60 * 60);

  // Now we will set the minutes
  i = 0; // start at 5 min
  flag = 1; //flag for if the button was pressed
  while (flag == 1) { // button is not pressed
    pinMode(lows[i], OUTPUT); //turn on the low and high pin as outputs
    pinMode(highs[i], OUTPUT);
    digitalWrite(lows[i], LOW); //turn on this LED
    digitalWrite(highs[i], HIGH);
    // wait 1.5 seconds
    t1 = millis();
    while ((millis() - t1) < 1500) { //wait 1.5 seconds --> if button is pressed flip the flag
      if (digitalRead(buttonPin) == LOW) { //if the button was pressed
        delay(100); // debounce
        flag = flag * -1; // flip the flag
      }
    }
    pinMode(lows[i], INPUT); // turn those LED pins back to inputs
    pinMode(highs[i], INPUT);
    i++;
    if (i >= 12) {
      i = 0;
    }
  } // This loop is left once the button is pressed
  int set_minutes = i; //the hours we set is 'i'
  offset_secs = offset_secs + set_minutes*5*60; // add the number of minutes to the offset in seconds
  // Start the number of seconds as the offset
  Secs = offset_secs;
}

// If the button was pressed, show the time
void buttonPressed() {
  showTime = showTime * -1;
}

void showTheTime() {
  Hours = Secs / (60 * 60); // 60sec*60min = number of seconds in an hour --> auto truncated
  Remaining_sec = Secs % (60 * 60); // how many seconds past the last hour?
  Fivemins = Remaining_sec / (60 * 5); //how many 5min windows fit in this?

  // if Hours = 0 --> LED to show is 12
  LED1 = Hours - 1;
  if (Hours == 0){
    LED1 = 11;
  }

  // if Fivemins = 0 --> LED to show is 12
  LED2 = Fivemins - 1;
  if (Fivemins == 0){
    LED2 = 11;
  }

  t1 = millis();
  while ((millis() - t1) < (timeOn * 1000)) { //display the time for timeOn seconds

    // LED 1
    t2 = micros();
    // Always keep LED 2 off in this part
    pinMode(lows[LED2], INPUT); //turn on the low and high pin as inputs
    pinMode(highs[LED2], INPUT);
    while ((micros() - t2) < ((1000 / refreshRate)*1000)) {
      // should LED 1 be on?
      if (LED1_on == 1) {
        //turn it on
        pinMode(lows[LED1], OUTPUT); //turn on the low and high pin as outputs
        pinMode(highs[LED1], OUTPUT);
        digitalWrite(lows[LED1], LOW); //turn on this LED
        digitalWrite(highs[LED1], HIGH);
      }
    }

    // LED 2
    t2 = micros();
    // Always keep LED 1 off in this part
    pinMode(lows[LED1], INPUT); //turn on the low and high pin as inputs
    pinMode(highs[LED1], INPUT);
    while ((micros() - t2) < ((1000 / refreshRate)*1000)) {
      // should LED 2 be on?
      if (LED2_on == 1) {
        //turn it on
        pinMode(lows[LED2], OUTPUT); //turn on the low and high pin as outputs
        pinMode(highs[LED2], OUTPUT);
        digitalWrite(lows[LED2], LOW); //turn on this LED
        digitalWrite(highs[LED2], HIGH);
      }
    }

    // Should LED 1 or 2 be on?
    // if t1 is a multiple of blinkTime or constantTime, flip the flags

    if (((t1-millis()) % blinkTime) == 0) {
    // flip LED2
    LED2_on = LED2_on * -1;
  }
  if (((t1-millis()) % constantTime) == 0) {
    // flip LED1
    LED1_on = LED1_on * -1;
  }
}
showTime = showTime * -1; //stop showing the time by flipping back the flag
}


// Setup the RTC to work
// http://ww1.microchip.com/downloads/en/AppNotes/TB3213-Getting-Started-with-RTC-90003213A.pdf
// From this website
void RTCsetup() {
  uint8_t temp;
  // Initialize 32.768kHz Oscillator:
  // Disable oscillator:
  temp = CLKCTRL.XOSC32KCTRLA & ~CLKCTRL_ENABLE_bm;
  // Enable writing to protected register
  CPU_CCP = CCP_IOREG_gc;
  CLKCTRL.XOSC32KCTRLA = temp;
  while (CLKCTRL.MCLKSTATUS & CLKCTRL_XOSC32KS_bm);   // Wait until XOSC32KS is 0
  temp = CLKCTRL.XOSC32KCTRLA & ~CLKCTRL_SEL_bm;      // Use External Crystal
  // Enable writing to protected register
  CPU_CCP = CCP_IOREG_gc;
  CLKCTRL.XOSC32KCTRLA = temp;
  temp = CLKCTRL.XOSC32KCTRLA | CLKCTRL_ENABLE_bm;    // Enable oscillator
  // Enable writing to protected register
  CPU_CCP = CCP_IOREG_gc;
  CLKCTRL.XOSC32KCTRLA = temp;
  // Initialize RTC
  while (RTC.STATUS > 0);                             // Wait until registers synchronized
  // 32.768kHz External Crystal Oscillator (XOSC32K)
  RTC.CLKSEL = RTC_CLKSEL_TOSC32K_gc;
  RTC.DBGCTRL = RTC_DBGRUN_bm;                        // Run in debug: enabled
  RTC.PITINTCTRL = RTC_PI_bm;                         // Periodic Interrupt: enabled
  // RTC Clock Cycles 32768, enabled ie 1Hz interrupt
  RTC.PITCTRLA = RTC_PERIOD_CYC32768_gc | RTC_PITEN_bm;
}
// Interrupt Service Routine called every second by the RTC
ISR(RTC_PIT_vect) {
  RTC.PITINTFLAGS = RTC_PI_bm;                        // Clear interrupt flag
  Secs = (Secs + 1) % 43200;                          // Wrap around after 12 hours
}

void setup() {
  // Turn on pullup on PA2 (digital pin 9) (pull up for button)
  pinMode(buttonPin, INPUT_PULLUP);

  // Set all the LED output pins to inputs at first
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(8, INPUT);

  // Setup sleep
  SLPCTRL.CTRLA |= SLPCTRL_SMODE_PDOWN_gc;
  SLPCTRL.CTRLA |= SLPCTRL_SEN_bm;

  // Set time
  setTime();

  // Attach interrupt to showtime button
  // Interrupts wake from sleep!
  attachInterrupt(9, buttonPressed, FALLING);

  // Setup real-time clock
  RTCsetup();
}

void loop() {
  if (showTime == 1) { //If the button was pressed
    showTheTime();
  }
  sleep_cpu(); //stay asleep unless something happens
}
