#include <Wire.h>

void setup() {
    Wire.begin();                  // join i2c bus with address 0x38
    Wire.onReceive(receiveEvent);  // register event
    Serial.begin(9600);            // start serial for output
}

void loop() { delay(100); }

int16_t recv(uint8_t *buf, uint8_t len, uint16_t *cs = NULL) {
    uint8_t i, j, n;
    if (cs) *cs = 0;
    for (i = 0; i < len; i += n) {
        // n is the number read -- it most likely won't be equal to len
        n = Wire.requestFrom((uint8_t)0x54, (uint8_t)(len - i));
        for (j = 0; j < n; j++) {
            buf[j + i] = Wire.read();
            if (cs) *cs += buf[j + i];
        }
    }
    return len;
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
    while (1 < Wire.available()) {  // loop through all but the last
        byte c = Wire.read();       // receive byte as a character
        Serial.print(c);            // print the character
        Serial.print("\r");
        delay(1000);
    }
    int x = Wire.read();  // receive byte as an integer
    //  Serial.println(x);         // print the integer
    //   lcd.print(x);
}