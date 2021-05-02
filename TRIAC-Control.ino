// Salim El Atache
// lab4 part b

#include <Wire.h> // I2C library
#include <Adafruit_SSD1306.h> // OLED display library
#define OLED_ADDR   0x3C    // I2C address
Adafruit_SSD1306 display(-1);   // no reset pin

#define PWM 3
int PR = A0; //Set A0(Analog Input) for LDR.

int value = 0;
int Case; //flag variable for the OLED display

void setup() {
  TCCR3B = TCCR3B & B11111000 | B00000101;    // for PWM frequency of 30.64 Hz
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  pinMode(PWM, OUTPUT);
}

void loop() {
  value = analogRead(PR); //Reads the Value of Photoresistor(light).

  //setting the values  for the cases.
  int  case1 = 400 ; //setting the setpoint of the first case
  int  case2 = 650;  //setting the setpoint of the second case
  int case3 = 900;   //setting the setpoint of the Third case case


  //PWM of 255, LIGHT 100% ON
  if ( value < case1) {
    analogWrite(PWM, 255);
    Case = 1;// triggers the display if statement condistions to print 100% light
  }
  //PWM of 127, LIGHT 75% ON
  else if ( (case1 < value) && (value < case2)) {
    analogWrite(PWM, 191);
    Case = 2;// triggers the display if statement condistions to print 75% light
  }
  //PWM of 64, LIGHT 50% ON
  else if ( (case2 < value) && (value < case3)) {
    analogWrite(PWM, 127);
    Case = 3;// triggers the display if statement condistions to print 50% light
  }
  //PWM of 0, LIGHT OFF
  else if ( value > case3) {
    analogWrite(PWM, 0);
    Case = 4;// triggers the display if statement condistions to print 0% light
  }

  Display(); //calling the display function.

}
void Display() {

  display.clearDisplay(); // clear display
  display.setTextColor(WHITE);
  display.setTextSize(2); // bigger text
  if ( Case == 1) {// When light is OFF
    display.setCursor(0, 0);//set the position
    display.print("OFF STATE"); // print LIGHT STATE
  }
  else if ( Case == 2) {// When light is 50% ON
    display.setCursor(0, 0);//set the position
    display.print("50% LIGHT"); // print LIGHT STATE
  }
  else if ( Case == 3) {// When light is 75% ON
    display.setCursor(0, 0);//set the position
    display.print("75% LIGHT"); // print LIGHT STATE
  }
  else if ( Case == 4) {// When light is 100% ON
    display.setCursor(0, 0);//set the position
    display.print("100% LIGHT"); // print LIGHT STATE
  }
  display.setCursor(0, 16);//set the position
  display.print("Value:"); // print the degrees symbol
  display.setCursor(90, 16);//set the position
  display.print(value); // print the degrees symbol
  display.display();  // update display

}
