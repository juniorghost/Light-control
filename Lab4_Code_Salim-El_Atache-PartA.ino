// Salim El Atache
// lab4 part a

#include <Wire.h> // I2C library
#include <Adafruit_SSD1306.h> // OLED display library
#define OLED_ADDR   0x3C    // I2C address
Adafruit_SSD1306 display(-1);   // no reset pin

int PR = A0; //Set A0(Analog Input) for LDR.
int value = 0;
int HighLimit = 0;
int LowLimit = 0;
int DB = 80;  // creates a gap between the high and low limit to avoid quick switching 
int SetPoint = 600; //chosen setpoint depending on the external light disturbances.

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  pinMode (LED_BUILTIN, OUTPUT);
}

void loop() {

  value = analogRead(PR); //Reads the Value of LDR(light).
  
  //setting the values of the limits
  HighLimit = SetPoint + DB / 2 ;
  LowLimit = SetPoint - DB / 2 ;
  
  if (value >= HighLimit)
  {
    digitalWrite(3, LOW); //turn the 1 watt off .
  }

  else if ( value <= LowLimit  )
  {
    digitalWrite(3, HIGH); //turn the 1 watt on .
  }

  display.clearDisplay(); // clear display
  display.setTextColor(WHITE);
  display.setTextSize(1); // bigger text
  if ( SetPoint < value) {
    display.setCursor(0, 0);//set the position
    display.print("Sufficient Light"); // print the degrees symbol
  }
  else {
    display.setCursor(0, 0);//set the position
    display.print("Insufficient Light"); // print the degrees symbol
  }

  display.setTextSize(2); // bigger text
  display.setCursor(0, 16);//set the position
  display.print("Value:"); // print the degrees symbol
  display.setCursor(90, 16);//set the position
  display.print(value); // print the degrees symbol
  display.display();  // update display

}
