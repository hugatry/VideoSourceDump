/*This is sketch used in YouTube video: https://youtu.be/JLdUKz8555w
 * This is only for reference to those following along at home, 
 * one unnecessary while-loop was removed and some comments changed,
 * there will be no more changes to this sketch. This code isn't actively developed
  */

/*Hardware:
 * Attiny85 and TTP223 module share common 5V and GND for power.
 * TTP223's output pin is connected to ATTiny85's PB4, (pin 3 on DIP8 package).
 * ATTiny85's PB0 (physical pin 5) goes to gate of the N-channel mosfet through 100ohm resistor).
 * COB LED with series resistor (calculated based on LED current and voltage) between 5V and mosfet's drain.
 * Source of mosfet connected to ground.
 * 10kOhm resistor betweeen ATTiny85's /RST and VCC.
 * 
 * TTP223 was modified by soldering piece of copper wire, looped into spiral shape, increasing the touch area 
 */

//WAITING = Button isn't pressed, not waiting for double-click.
//FIRST_PRESS  = Button is pressed for the first time after/during "WAITING" state
//AFTER_FIRST_PRESS = Button was released after/during "FIRST_PRESS" state
//LONG_PRESS = Button has been pressed down for longer than set threshold
enum State {WAITING, FIRST_PRESS, AFTER_FIRST_PRESS, LONG_PRESS};
State currentState = WAITING;

//Variables to store time of certain events
unsigned long pressStarted = 0;
unsigned long pressReleased = 0;

//Threshold how long button should be pressed to activate long press
uint16_t longPressDelay = 1000;
//... and how soon second click should happe to trigger double click
uint16_t doubleClickDelay = 1000;

uint8_t pwm = 0;
void setup() {
  //Pin 0 (Physical pin 5) is PWM output
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  //Pin 4 (Physical pin 3) is active high input
  pinMode(4, INPUT);
}
void loop() {


  switch (currentState) {
    //In WAITING state, wait for the button press,
    //  save time and go to FIRST_PRESS state.
    case WAITING:
      if (digitalRead(4)) {
        pressStarted = millis();
        currentState = FIRST_PRESS;
      }
      break;
    //In FIRST_PRESS, check if button is released,
    //  or long press threshold has passed.

    case FIRST_PRESS:
      //If button was released before long press,
      //  turn LED ON at low brightness if it was off,
      //  or OFF if it was already ON.
      //  Go to AFTER_FIRST_PRESS
      if (!digitalRead(4)) {
        pressReleased = millis();
        if (pwm == 0) {
          pwm = 10;
          analogWrite(0 , pwm);
          currentState = AFTER_FIRST_PRESS;
        } else {
          pwm = 0;
          analogWrite(0, pwm);
          currentState = AFTER_FIRST_PRESS;
        }
      // If button wasn't released and long press was detected,
      // switch to "LONG_PRESS" state
      } else if (millis() - pressStarted > longPressDelay) {
        currentState = LONG_PRESS;
      }
      break;
    //Wait for  the second press, which will turn LED to max.
    case AFTER_FIRST_PRESS:
      if (digitalRead(4)) {
        pwm = 255;
        analogWrite(0, pwm);
        while(digitalRead(4)){
        };
        currentState = WAITING;
      //Or go to WAITING state, if second press didn't happen
      } else if (millis() - pressReleased > doubleClickDelay) {
        currentState = WAITING;
      }
      break;
    //During LONG_PRESS, cycle LED pwm from 0 to 255
    //  When button is released, current brightness is left active
    case LONG_PRESS:
        if (digitalRead(4)) {
          if (pwm == 255) {
            pwm = 0;
          } else {
            pwm++;
          }
          analogWrite(0, pwm);
          delay(10);
        } else {
          currentState = WAITING;
        }
      break;
  }
}
