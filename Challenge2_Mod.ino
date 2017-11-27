/*
* This is the code for the Launchpad which will be used in the heating system of the bioreactor.
* All parameters can only be amended by changing the code and no input is required.
*/


#include<math.h>
int buttonstate = 0;
const int Tempin = A0;
const int Heaterpin = P2_7;
const int Buttonpin = PUSH2;

void setup() {

Serial.begin(9600);
pinMode(Tempin, INPUT);
pinMode(Buttonpin, INPUT);
pinMode(Heaterpin, OUTPUT)

/*Steinhart-Hart Equation*/
double getTemperature(int rawADC) {
rawADC -= 200; // Modify the input value to calibrate the temperature.
double temp;
temp = logf(((10240000/rawADC) - 10000));
temp = 1 / (0.001129148 +
(0.000234125 + (0.0000000876741 * temp * temp ))* temp );
return temp - 273.15; // Convert Kelvin to Celsius
//return (temp * 9.0)/ 5.0 + 32.0; // Celsius to Fahrenheit 

}

/********************************************************************************/

void loop() {
  /*Pressing the button will turn the heater controller system on.*/
  if(digitalRead(Buttonpin) == LOW)
  {
    buttonstate = 1;
    delay(1000)
  }

  while(buttonstate = 1)
  {
    /*Pressing the button again will turn the system off.*/
    if(digitalRead(Buttonpin) == LOW)
    {
      buttonstate = 0;
      delay(1000);
    }
    RAWTemp = analogRead( Tempin );
    /*Use Steinhart-Hart equation to get temperature*/
    Temperature = getTemperature(RAWTemp);
    /*For Testing*/
    Serial.print(Temperature);

    /*
     * Based on the knowledge I have, The launchpad could only be used as a controller 
     * that controls ON or OFF of the heater power system. Therefore, the power of the heater is 
     * determined by the frequency of powering up, although this might be less efficient. It will
     * be better if I could use PWM output to control the power of the heater.
     */

     /*PWM control system*/
    If (Temperature < 28)
    {
      analogWrite(Heaterpin, CurrentHIGH);
    }
    else if(Temperature >= 28 && Temperature <= 32)
    {
      analogWrite(Heatermin, CurrentMedi);
    }
    else if(Temperature > 32)
    {
      analogWrite(Heaterpin, 0);
    }

    /*Digital control system*/
    /*
    If (Temperature < 28)
    {
      digitalWrite(Heaterpin, HIGH);
      delay(10000);
      digitalWrite(Heaterpin, LOW);
      delay(1000);
    }
    else if(Temperature >= 28 && Temperature <= 32)
    {
      digitalWrite(Heaterpin, HIGH);
      delay(4000);
      digitalWrite(Heaterpin, LOW);
      delay(3000);
    }
    else if(Temperature > 32)
    {
      digitalWrite(Heaterpin, LOW);
      delay(2000);
    }
    */

  }

