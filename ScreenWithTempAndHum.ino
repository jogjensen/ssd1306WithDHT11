#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 13     // what pin we're connected to
#define DHTTYPE DHT11   // DHT11
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


int hum;  //Stores humidity value
int temp; //Stores temperature value

void setup() {
  Serial.begin(9600);
  dht.begin();
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}

void loop() {
    display.clearDisplay();
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    
    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);

    //temp code
    display.setCursor(0, 10);
    display.print("TEMP:");
    display.print(temp);
    display.print("C");
    Serial.println(temp);

    //hum code
    display.setCursor(0, 40);
    display.print("HUM:");
    display.print(hum);
    display.print("%");
    Serial.println(hum);

    display.display();   
    delay(2000);
    

    

}