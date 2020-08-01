#include <OneWire.h>
#include <DallasTemperature.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

#define humdity_relay 5 //Humidity controller 
#define temp_relay 6 //Temperature controller 

#define set_button 8
#define up_button 9
#define down_button 10

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  
// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

//Set LCD address for 16*2 LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

int temp, hum, days;

void setup(void)
{
  sensors.begin();  // Start up the library
  lcd.begin(); //begin lcd_I2c

  lcd.backlight(); //on backlight
  lcd.print(" Welcome" );
  delay(1000); 

  pinMode(set_button, INPUT_PULLUP);
  pinMode(up_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);

  
  Serial.begin(9600);
  //setMode(); true if setup cmplted

  

}

void loop(void)
{ 
  // Send the command to get temperatures
  sensors.requestTemperatures(); 

  //print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print((char)176);//shows degrees character
  Serial.print("C  |  ");

  delay(500);
}

void setMode(){
  int value = 15; //set value variable 
  int session = 0; //start a session
  int set, up, down; //read button value 
  lcd.print("Set Mode "); //welcome msg
  delay("1500);
  lcd.clear();

  lcd.print("Select temperature");

  while(session == 0){
    set = digitalRead(set_button);
    up = digitalRead(up_button);
    down = digitalRead(down_button);

    
    if(set == 0){
      lcd.clear();
      lcd.print("Temp value is:");
      lcd.print(value);
      temp = value;
      delay(1500);
      session = 1;
    }
    if(up == 1){
      value ++;
      lcd.setCursor();
      lcd.print(value);
      lcd.setCursor();
      lcd.print(" ºC");
    }
    if(down == 1){
      value --;
      lcd.setCursor();
      lcd.print(value);
      lcd.setCursor();
      lcd.print(" ºC");
    }
  }
  lcd.print("Select Humidity");
  session = 0;
  value = 45;
  
  while(session == 0){
    set = digitalRead(set_button);
    up = digitalRead(up_button);
    down = digitalRead(down_button);

    
    if(set == 0){
      lcd.clear();
      lcd.print("humidity value is:");
      lcd.print(value);
      hum = value;
      delay(1500);
      session = 1;
    }
    if(up == 1){
      value ++;
      lcd.setCursor();
      lcd.print(value);
      lcd.setCursor();
      lcd.print(" %");
    }
    if(down == 1){
      value --;
      lcd.setCursor();
      lcd.print(value);
      lcd.setCursor();
      lcd.print(" %");
    }
  }
  lcd.print("Select No of Days");
  session = 0;
  value = 20;
  while(session == 0){
    set = digitalRead(set_button);
    up = digitalRead(up_button);
    down = digitalRead(down_button);

    
    if(set == 0){
      lcd.clear();
      lcd.print("Days is:");
      lcd.print(value);
      days = value;
      delay(1500);
      session = 1;
    }
    if(up == 1){
      value ++;
      lcd.setCursor();
      lcd.print(value);
      lcd.setCursor();
      lcd.print(" Days");
    }
    if(down == 1){
      value --;
      lcd.setCursor();
      lcd.print(value);
      lcd.setCursor();
      lcd.print(" Days");
    }
  }
  return 1;
}
