// Arduino compatible code to read the temperature from a DHT22 sensor and play with an 8 leds neopixel strip
//
// 2022-07-01 Pierre Rossel  Initial version for NS Magic @ y-fablab


// Sensor
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

// FastLED
#include <FastLED.h>
#define NUM_LEDS 8
#define DATA_PIN 3

CRGB leds[NUM_LEDS];


void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  // Init sensor
  dht.begin();

  // Init FastLED
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));


  // Update leds

  for (int i = 0; i < NUM_LEDS; i++) {
    // Clignotte toutes les leds toutes les 2 secondes (TEST)
    //leds[i] = millis() / 2000 % 2 == 0 ? CRGB::Black : CRGB::Red;

    // Allume un nombre de LED rouge en fonction de la température
    // const int TEMP_LED_LOW = 20; // Teméprature de la 1ère LED
    // const int TEMP_LED_HIGH = 55; // Température de la dernière LED
    // leds[i] = t >= TEMP_LED_LOW + (i * (TEMP_LED_HIGH - TEMP_LED_LOW) / (NUM_LEDS-1)) ? CRGB::Red : CRGB::Black;


    // Allume un nombre de LED en couleur en fonction de la température
     const int TEMP_LED_LOW = 20; // Teméprature de la 1ère LED
     const int TEMP_LED_HIGH = 55; // Température de la dernière LED
     const CRGB colors[] = {CRGB::Blue, CRGB::Blue, CRGB::Green, CRGB::Green, CRGB::DarkOrange, CRGB::DarkOrange, CRGB::Red, CRGB::Red};
     leds[i] = t >= TEMP_LED_LOW + (i * (TEMP_LED_HIGH - TEMP_LED_LOW) / (NUM_LEDS-1)) ? colors[i] : CRGB::Black;

  }
  FastLED.show();
}
