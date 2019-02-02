#include <avr/power.h>
#include <avr/sleep.h>
#include <DHT.h>

#define DHTTYPE DHT11

// Pin 13 has a LED connected so we give it a name:
int led = 13;
int mPin = 0;
int tPin = A2;

DHT dht(tPin, DHTTYPE);

// the setup routine runs once when you press reset:
void setup()
{
  Serial.begin(9600); 
  // initialize the digital pin as an output.
//  pinMode(led, OUTPUT);
    dht.begin();
}

// the loop routine runs over and over again forever:
void loop()
{
 
// outputMoisture();
 outputTemp();
 
 getInput();
  
  
 
 Serial.println();
 delay(300000); //5min
 //delay(3000);
}

void outputMoisture() {
  int moisture=analogRead(mPin);
  //int tempreature=analogRead(tPin);
  //Serial.print("Soil moisture: ");
  //Serial.print(moisture); // print the analogical measurement of the experiment 
}

void outputTemp() {
  float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
  Serial.print("humidity:");
  Serial.print(h);
  Serial.print(",");
  Serial.print("temp:");
  Serial.print(t);
}


void getInput() {
  if (Serial.available()) {
      int val = Serial.read();
      if (val == 'S') {
        delay(100);     // this delay is needed, the sleep 
                        //function will provoke a Serial error otherwise!
        sleepNow();     // sleep function called here
      }
  }
}

void sleepNow()
{
    // Choose our preferred sleep mode:
    set_sleep_mode(SLEEP_MODE_IDLE);
 
    // Set sleep enable (SE) bit:
    sleep_enable();
    
    power_adc_disable();
    power_spi_disable();
    power_timer0_disable();
    power_timer1_disable();
    power_timer2_disable();
    power_twi_disable();
 
    // Put the device to sleep:
    sleep_mode();
 
    // Upon waking up, sketch continues from this point.
    sleep_disable();
}
