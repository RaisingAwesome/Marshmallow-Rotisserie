//Marshmallow Rotisserie by Sean and Connor Miller.  2018 for Element1.com Project 14
//Join us at Raising Awesome on Youtube.com

int motorPin = 0;//for the Trinket, this output pin is the same as the physical label
int alarmPin = 1;//for the Trinket, this output pin is the same as the physical label
int speedInput=1;//GPIO pin 2 is analog 1 for analog on the Trinket
int timerInput=3;//GPIO pin 3 is analog 3 for analog on the Trinket

int speedValue = 0;  // variable to store the value coming from the speed potentiometer.
int timerValue=0;  //variable to store the value coming from the desired time potentiometer.
int start_timer;  //the milliseconds gone by after boot up to compare the timer against with each pass of the loop().
bool alarm; //a flag to let us know if the timer has been reached.

void setup() {
  
  pinMode(0, OUTPUT);  //PWM output for the motor.  We'll set the output between 0 and 255 based on some epic math from the speed potentiometer.
  pinMode(1, OUTPUT);  //Alarm output.  It sets the pin to 5Vs or 0 volts.
  pinMode(2, INPUT);  //speed potentiometer input.  It reads as a value of 0-1023
  pinMode(3, INPUT);  //timer potentiometer input  It reads as a value of 0-1023
  start_timer=millis();//used with the timer pot to determine if it is time to alarm.
  alarm=false; //this will flag when to alarm by setting the alarm pin high;
}

void loop() {
  //we'll check the sensors every 1/2 second (500 milliseconds)
  delay(500); 
  speedValue = analogRead(speedInput);//store what the potentiometer is reading for speed.
  timerValue = analogRead(timerInput);//store what the potentiometer is reading for the timer.
  
  if (millis()>(start_timer+(1000*map(timerValue,0,1023,0,60*4)))) {//scale it to max time to be 4 minutes.  If they need more time, they need to lower the rig closer to the heat.
    alarm=true;
  } 
  else alarm=false; //Note:  If they turn the knob after it alarms, they'll get more time.  Or they can lower it when they see the perfect marshmallow so the next one can be just as scrumdiddlyumptious.

  if (alarm) digitalWrite(alarmPin, HIGH); else digitalWrite(alarmPin,LOW); //sound the alarm if calculated to do so above.
    
  analogWrite(motorPin, map(speedValue,0,1023,0,255));//set the motor speed by doing a ratio of the knob setting versus its max setting (255) of analog write
}
