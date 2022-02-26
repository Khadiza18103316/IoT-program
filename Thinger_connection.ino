  #include <ThingerESP8266.h>
  #define SSID "Khadiza"
  #define SSID_PASSWORD "12345678"
  #define USERNAME "Khadiza"
  #define DEVICE_ID "KHADIZAIOTID"
  #define DEVICE_CREDENTIAL "khadiza123456"
  ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);


  #include <OneWire.h>
  #include <DallasTemperature.h>
  #define ONE_WIRE_BUS 5 //d1 pin for temperature sensor
  OneWire oneWire(ONE_WIRE_BUS);
  DallasTemperature sensors(&oneWire);
 
  #include <Wire.h> 
  #include <LiquidCrystal_I2C.h>
  LiquidCrystal_I2C lcd(0x27, 16, 2); 
  
  float gasval;
  float temp; 
  
  void setup() {
   pinMode(D3,OUTPUT);// FOR SIREN BUT WORKS ON CONDITION
   pinMode(D6,OUTPUT);// FOR SIREN
   pinMode(D7,OUTPUT);// FOR PUMP ACCORDING DIAGRAM
   pinMode(D8,OUTPUT);// FOR SOLENOYED VALVE
   
   Serial.begin(115200);
   sensors.begin();
   thing.add_wifi(SSID, SSID_PASSWORD);
  }

  void loop() {

   sensors.requestTemperatures();
   temp = sensors.getTempCByIndex(0);
   gasval = analogRead(A0);// A0 pin + gas sensor
   lcd.begin();
   lcd.backlight();
   lcd.print("Temp(C):");
   lcd.print(temp);
   lcd.setCursor(0,1);
   lcd.print("Gas Cnt:");
   lcd.print(gasval);




  thing["temperature"] >> [](pson& out){
      out = temp;};

  thing["gasValue"] >> [](pson& out){
      out = gasval;};
  
   

   thing["siren"] << digitalPin(D6);
   thing["pump"] << digitalPin(D7);
   thing["gasvalve"] << digitalPin(D8);
   

 if (temp   > 60)   {digitalWrite(D3,HIGH);} else if(temp < 60){digitalWrite(D3,LOW);}
 if (gasval > 1000) {digitalWrite(D3,HIGH);thing.call_endpoint("khadizaakhi756@gmai.com");} else if(gasval < 1000){digitalWrite(D3,LOW);}
    
  thing.handle();
  }
