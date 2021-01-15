#include <IRremote.h>
#include <Wire.h>

IRrecv irReceiver(4);
decode_results result;
unsigned long ir;

void setup() {

  Wire.begin();
  irReceiver.enableIRIn();
  Serial.begin(9600);
}

void loop() {
 

if (irReceiver.decode(&result)){
 
    irReceiver.resume();
    ir=(result.value);
  }
  Serial.print(ir);
   if (ir==3772793023){
   Wire.beginTransmission(4); 
   Wire.write("s");
   Wire.endTransmission();
   ir =0;
  
    }
    delay (1000);
}
