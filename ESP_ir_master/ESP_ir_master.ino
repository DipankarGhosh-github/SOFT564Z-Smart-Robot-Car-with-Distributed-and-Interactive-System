#include <IRremote.h>
#include <Wire.h>
#include <DHT.h>

IRrecv irReceiver(4);
decode_results result;
unsigned long ir;

#define Type DHT11
int dhtsensor = 5;
DHT HT (dhtsensor,Type);
int hum;
int temp;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  irReceiver.enableIRIn();
  HT.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  hum= HT.readHumidity();
  temp = HT.readTemperature();
 
if (irReceiver.decode(&result)){
 
    irReceiver.resume();
    ir=(result.value);
  }
 
   if (ir==3772793023){
   Wire.beginTransmission(4); 
   Wire.write("Humidity=");
   Wire.write(hum);
   Wire.endTransmission();

   Wire.beginTransmission(4); 
   Wire.write("Temperature=");
   Wire.write(temp);
   Wire.endTransmission();
   ir =0;
   }
  delay(1000);
    }
    
