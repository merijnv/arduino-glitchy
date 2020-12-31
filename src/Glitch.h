
#ifndef GLITCH_h
#define GLITCH_h

#define _GLITCH_STATE_START 0
#define _GLITCH_STATE_ON 1
#define _GLITCH_STATE_GLITCH 2

/**
 * Glitchy starts an LED and then sometimes glitches out
 */
class Glitch {
  public:
    Glitch(int pin, int led_off_state);
    void step();
    void randomize();
    
  private:
    int _pin;
    uint32_t _counter;
    uint8_t _state;
    uint8_t _led;
    uint8_t _led_off;

    // Zero terminated array of how to animate the LED
    // I may introduce some randomness into this soon-ish.
    uint16_t _data[64];
};

Glitch::Glitch(int pin, int led_off_state) {
  pinMode(pin, OUTPUT);
  _pin = pin;
  _led = led_off_state;
  _led_off = led_off_state;  

  _counter = 0;
  _state = 0;

  for (int i = 0 ; i < 64; i++) {
    _data[i] = 0;
  }

  // Probably my bad but I can't find a way to create a block of data in C++
  // so just initializing an array here the long way.  
  // This data is specific for each indivitual instance of a Glitch class, that is why randominzing
  // it works and will create slowly drifting lights when you connect multiple leds.
  
  _data[0] =            5;   // on
  _data[1] = _data[0] + 200;  // off
  _data[2] = _data[1] + 10;   // on
  _data[3] = _data[2] + 100;   // off
  _data[4] = _data[3] + 40;   // on
  _data[5] = _data[4] + 100;   // off
  _data[6] = _data[5] + 5;   // on
  _data[7] = _data[6] + 5;   // off
  _data[8] = _data[7] + 5;   // on
  _data[9] = _data[8] + 5;   // off
  _data[10] = _data[9] + 200;  // on
  _data[11] = _data[10] + 10;   // off
  _data[12] = _data[11] + 2000; // on  
  _data[13] = _data[12] + 40;  // off
  
};

void Glitch::randomize() {
  int i = 0;
  int d = _data[0];
   while(d != 0) {    _data[i] = max(0L, _data[i] + random(10) - 5);
    i++;
    d = _data[i];
  }
}

// Please call this 100 times a second.
void Glitch::step() {
  if (_counter == 0) {    
    _led = !_led_off;
  }

  if (_counter > _data[_state]) {
    _state++;
    // at the end of the animation, set counter to zero
    if (_data[_state] == 0) {
      _counter = 0;
      _state = 0;
      return;
    }    
    _led = !_led; // TOGGLE LED
    
  }
  
//  Serial.print("counter: ");
//  Serial.print(_counter);
//  Serial.print(" state: ");
//  Serial.println(_state);

  Serial.println(_led);
  digitalWrite(_pin, _led);
  _counter++;  
}


#endif
