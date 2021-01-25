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
  // setup code to run once:
  Wire.begin();            // join i2c bus
  irReceiver.enableIRIn();
  HT.begin();
}

void loop() {
  // getting DHT11 sensor values
  hum= HT.readHumidity();          // measures humidity value
  temp = HT.readTemperature();      // measures temperature in degree Celcius
 
 //  decodes received signsl
if (irReceiver.decode(&result)){    
    irReceiver.resume();
    ir=(result.value);
  }
  
   if (ir==3772793023){             //compares with reference value
   Wire.beginTransmission(4);       //starts transmission
   Wire.write("Humidity=");         //sends data
   Wire.write(hum);       
   Wire.endTransmission();          //end transmission

   Wire.beginTransmission(4);        //restarts transmission
   Wire.write("Temperature=");         //sends data
   Wire.write(temp);
   Wire.endTransmission();           //end transmission
   ir =0;                   //resets value
   }
  delay(500);
    }
    
