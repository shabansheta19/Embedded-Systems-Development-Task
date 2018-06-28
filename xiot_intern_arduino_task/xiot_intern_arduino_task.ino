/* 
 To send data from the Arduino to the serial monitor window,
 we use the Serial.print() function. You can print variables
 or text (within quotes).
*/

/*
  TEMPERATURE SENSOR
  The TMP36 is an easy-to-use temperature sensor that outputs
  a voltage that's proportional to the ambient temperature.
  You can use it for all kinds of automation tasks where you'd
  like to know or control the temperature of something.
*/


// We'll use analog input 0 to measure the temperature sensor's
// signal pin
const int temperaturePin = 0;
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
volatile int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  //setup the serial baud rates
  Serial.begin(9600); // Other baud rates can be used.
  // initialize the LED pin as an output.
  pinMode(ledPin, OUTPUT);
  // initialize the push button pin as an input.
  pinMode(buttonPin, INPUT);
  // Attach an interrupt to the ISR vector.
  attachInterrupt(0, pin_ISR, CHANGE);
}

void loop() {
  // We'll declare three floating-point variables
  // (We can declare multiple variables of the same type on one line:)

  float voltage, degreesC;

  // First we'll measure the voltage at the analog pin. Normally
  // we'd use analogRead(), which returns a number from 0 to 1023.
  // Here we've written a function (further down) called
  // getVoltage() that returns the true voltage (0 to 5 Volts)
  // present on an analog input pin.

  voltage = getVoltage(temperaturePin);

  // Now we'll convert the voltage to degrees Celsius.
  // This formula comes from the temperature sensor datasheet:

  degreesC = (voltage - 0.5) * 100.0;

  // Now we'll use the serial port to print these values
  // to the serial monitor!
  Serial.print(degreesC);

  delay(3000); // repeat once per second (change as you wish!)
}

/**
 * This type of function is called an interrupt service routine
 * its job is to run quickly and handle the interrupt and let 
 * the processor get back to the main program
 */
void pin_ISR() {
  buttonState = digitalRead(buttonPin);
  digitalWrite(ledPin, buttonState);
  Serial.println("pressed");
  Serial.println(buttonState);
}

/**
 * This equation converts the 0 to 1023 value that analogRead()
 * returns, into a 0.0 to 5.0 value that is the true voltage
 * being read at that pin.
 */
float getVoltage(int pin)
{ 
  return (analogRead(pin) * 0.004882814);
}
