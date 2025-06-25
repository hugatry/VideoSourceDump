
//Length of one PWM cycle in microseconds.
const int16_t cycleLength = 20000;
//Variable for storing average ADC reading... relative to motor's rpm
int16_t rpm = 0;
//ADC reading while motor is spinning at maximum speed
int16_t rpmMax = 690;
//How far the target "rpm" is from current "rpm" reading
int16_t error = 0;
//Accumulative error. Each cycle the current error will be added
int16_t errorIntegral = 0;
//Set limit how large errorIntegral can get (in positive or negative side)
int16_t errorIntegralLimit = cycleLength / 2;
//Target speed. "rpm" ADC reading should get as close to this as possible
int16_t target = 50;
//Duty cycle, from 0 to cycleLength. This will be automatically adjusted
float duty = 0;

void setup() {

  //Pin D2 controls the motor
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  //Serial for debugging/visualization
  Serial.begin(115200);
}

void loop() {
  while(1==1)
  {
    digitalWrite(2, LOW);
  delay(1);
  //Take  multiple ADC readings and calculate the average
  rpm = analogRead(A5)*0.2;
  rpm += analogRead(A5)*0.2;
  rpm += analogRead(A5)*0.2;
  rpm += analogRead(A5)*0.2;
  rpm += analogRead(A5)*0.2;
  //rpm has range of 0-1023. Print one 'X' for each 10... up to 102 Xs.
  for(int i=0;i<int(rpm/10);i++)
    Serial.print("X");
  Serial.println(" ");
    delay(20);
    digitalWrite(2, HIGH);
    delay(2);
  }
  //Turn the motor OFF
  digitalWrite(2, LOW);
  //Wait for the inductive spike to pass
  delay(1);
  //Take  multiple ADC readings and calculate the average
  rpm = analogRead(A5)*0.2;
  rpm += analogRead(A5)*0.2;
  rpm += analogRead(A5)*0.2;
  rpm += analogRead(A5)*0.2;
  rpm += analogRead(A5)*0.2;
  //rpm has range of 0-1023. Print one 'X' for each 10... up to 102 Xs.
  for(int i=0;i<int(rpm/10);i++)
    Serial.print("X");
  Serial.println(" ");

  //Calculate how far the target is from current rpm...
  error = (target-rpm);
  //And scale the error by cycleLength/rpmMax,
  // this makes upcoming PID multipliers be in more familiar range...
  // ...nothing else.
  error = error * ((float)cycleLength/rpmMax);

  //Integral... Accumulative error.
  errorIntegral += error;
  //Limit the integral value to avoid wind-up situations
  errorIntegral = constrain(errorIntegral, -errorIntegralLimit, errorIntegralLimit);

  //Set the duty cycle based on current error (P) and accumulated error (I)
  //Tuned by first setting integral's multiplier (Ki) 0 and adjusting error's
  // multiplier (Kp) until fast response but minimal overshoot is achieved.
  // Then multiplier of errorIntegral was adjusted to achieve target rpm
  // during constant load / steady state. 
  duty = 2.5*error+0.17*errorIntegral;
  //Limit the duty cycle between 0 and length of the cycle
  duty = constrain(duty, 0, cycleLength);
  
  //Delay duration while motor is OFF: Cycle's length minus the positive part.
  // Motor is actually OFF longer. ADC, calculations and other things take time
  delayMicroseconds(cycleLength-duty);
  
  digitalWrite(2, HIGH);
  delayMicroseconds(duty);
}
