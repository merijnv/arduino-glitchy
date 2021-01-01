#include <arduino-timer.h>
#include "Glitch.h"


#define LED_PIN D5
#define LED_PIN_2 D6

#define ANIM_INTERVAL 10

// Timer
auto timer = timer_create_default();

// Lets Glitch an LED
// First parameter: PIN
// Second parameter: OFF state of LED, typically LOW when using external pins.
Glitch glitch(LED_PIN, LOW);
Glitch glitch2(LED_PIN_2, LOW);

// Call this 100 times a second please
bool intHandlerOne(void* argument) {
  glitch.step();
  return true;
}

bool intHandlerTwo(void* argument) {
  glitch2.step();
  return true;
}

void initRandom() {
  // Getting good random is very hard...
  uint32_t seed = 0;
  for (int i = 0; i < 24; i++) {
    seed = seed + ((analogRead(A0) % 100) << i);
    delay(100);
    Serial.print("init random seed: ");
    Serial.println(seed);
  }
  
  randomSeed(seed);
}

void setup() {  
  Serial.begin(115200);
  Serial.println("Glitchy!");

  // init random seed
  initRandom();

  glitch.randomize();
  glitch2.randomize();

  // set up timers
  // The second one runs little bit faster to let the lights drift
  timer.every(ANIM_INTERVAL, intHandlerOne);
  timer.every(ANIM_INTERVAL - 1, intHandlerTwo);
}

void loop() {
  timer.tick();
}
