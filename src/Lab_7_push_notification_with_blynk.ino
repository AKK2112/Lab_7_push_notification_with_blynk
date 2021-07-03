
#include "oled-wing-adafruit.h"
#include "blynk.h"


SYSTEM_THREAD(ENABLED);
OledWingAdafruit display;


uint16_t tempPin = A4;

double temperatureC = 0.0;

double temperatureF = 0.0;

void setup() {
 pinMode(A4, INPUT);
 Serial.begin(9600);
    //setting up display
    display.setup();
    display.clearDisplay();
    display.display();
  Blynk.begin("DISy_9aRsQHnyt8mtvZXh09rT-tdy72R", IPAddress(167, 172, 234, 162), 9090);
    //initalizes blynk with the proper authorized token and ip address.
}

void loop() {
  display.loop();
  //telling the board where the tmp36 is and what it should do with the values from the temp sensor. 
  Blynk.run();
  

  if (display.pressedA()) { //When the A button is pressed, everything in this bracket is executed instead of the temperature.
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("SECRET MESSAGE SENT!"); //displays "SECRET MESSAGE SENT!" on the OLED display
    display.display();
    Blynk.notify("The secret message notification"); //sends a notification to my iPhone via blynk
    delay(5000);
  }
  //after the 5 second delay, continues to display the temperature. 
  uint64_t reading = analogRead(A4);

  double voltage = (reading * 3.3) / 4095.0;

  double temperatureC = (voltage - 0.5) * 100;

  double temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

    //displaying the temperatures to a mini OLED display for easy reading of the ambient temperature in my room.
    display.clearDisplay();

    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("Temp (C):"); display.println(temperatureC); //prints the temp in Celsius with a unit for clarity
    display.display();
    display.print("Temp (F):"); display.print(temperatureF); // prints the temp in Fahrenheit  with a unit for clarity
    display.display();
    Serial.print(reading); Serial.print(temperatureC); Serial.print(","); Serial.println(temperatureF); //prints the different values I should be seeing on my OLED into my
                                                                                                        //serial monitor so I can make sure the OLED is working correctly.
delay(500); 
}
