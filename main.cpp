#include <Arduino.h>

// LCD Library
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pushbutton Pins
#define BUTTON1 3
#define BUTTON2 4
#define BUTTON3 5
#define BUTTON4 6

// Relay Pins
#define RELAY1 10
#define RELAY2 11
#define RELAY3 12
#define RELAY4 13

// Relay State
int relayState1 = LOW;
int relayState2 = LOW;
int relayState3 = LOW;
int relayState4 = LOW;

// Previous and Present Button State
int previousButtonState1 = LOW;
int previousButtonState2 = LOW;
int previousButtonState3 = LOW;
int previousButtonState4 = LOW;

int presentButtonState1;
int presentButtonState2;
int presentButtonState3;
int presentButtonState4;

// The last time the output pin was toggled
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long lastDebounceTime4 = 0;

// The debounce time; increase if the output flickers
unsigned long debounceDelay1 = 50;    
unsigned long debounceDelay2 = 50; 
unsigned long debounceDelay3 = 50; 
unsigned long debounceDelay4 = 50; 

// Store the value of Button Pins
int reading1;
int reading2;
int reading3;
int reading4;

// Water Flow Sensor
#define flowmeter 2
double flow;
unsigned long currentTime;
unsigned long lastTime;
unsigned long pulse_freq;

void pulse() {
  pulse_freq++;
}

void setup()
{
    Serial.begin(9600);

    // LCD
    lcd.begin();
    lcd.backlight();

    // Flow Meter
    pinMode(flowmeter, INPUT);
    attachInterrupt(0, pulse, RISING); // Setup Interrupt
    currentTime = millis();
    lastTime = currentTime;

    // Pushbutton
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);
    pinMode(BUTTON3, INPUT_PULLUP);
    pinMode(BUTTON4, INPUT_PULLUP);

    // Relay
    pinMode(RELAY1, OUTPUT);
    digitalWrite(RELAY1, relayState1);
    pinMode(RELAY2, OUTPUT);
    digitalWrite(RELAY2, relayState2);
    pinMode(RELAY3, OUTPUT);
    digitalWrite(RELAY3, relayState3);
    pinMode(RELAY4, OUTPUT);
    digitalWrite(RELAY4, relayState4);
}

void loop()
{
  currentTime = millis();
   // Every second, calculate and print L/Min
   if(currentTime >= (lastTime + 1000))
   {
      lastTime = currentTime; 
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      flow = (pulse_freq / 7.5); 
      pulse_freq = 0; // Reset Counter
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Flow Rate");
      lcd.setCursor(0, 1);
      lcd.print(flow);
      lcd.print("L/min");
      Serial.print(flow); 
      Serial.println(" L/Min");
   }

    // Relay1
    reading1 = digitalRead(BUTTON1);
    if (reading1 != previousButtonState1) {
        lastDebounceTime1 = millis();
    }
    if ((millis() - lastDebounceTime1) > debounceDelay1) {
        if (reading1 != presentButtonState1) {
            presentButtonState1 = reading1;
            if (presentButtonState1 == HIGH) {
                relayState1 = !relayState1;
            }
        }
    }
    digitalWrite(RELAY1, relayState1);
    //Serial.println(relayState1);
    previousButtonState1 = reading1;

    // Relay2
    reading2 = digitalRead(BUTTON2);
    if (reading2 != previousButtonState2) {
        lastDebounceTime2 = millis();
    }
    if ((millis() - lastDebounceTime2) > debounceDelay2) {
        if (reading2 != presentButtonState2) {
            presentButtonState2 = reading2;
            if (presentButtonState2 == HIGH) {
                relayState2 = !relayState2;
            }
        }
    }
    digitalWrite(RELAY2, relayState2);
    previousButtonState2 = reading2;

    // Relay3
    reading3 = digitalRead(BUTTON3);
    if (reading3 != previousButtonState3) {
        lastDebounceTime3 = millis();
    }
    if ((millis() - lastDebounceTime3) > debounceDelay3) {
        if (reading3 != presentButtonState3) {
            presentButtonState3 = reading3;
            if (presentButtonState3 == HIGH) {
                relayState3 = !relayState3;
            }
        }
    }
    digitalWrite(RELAY3, relayState3);
    previousButtonState3 = reading3;

    // Relay4
    reading4 = digitalRead(BUTTON4);
    if (reading4 != previousButtonState4) {
        lastDebounceTime4 = millis();
    }
    if ((millis() - lastDebounceTime4) > debounceDelay4) {
        if (reading4 != presentButtonState4) {
            presentButtonState4 = reading4;
            if (presentButtonState4 == HIGH) {
                relayState4 = !relayState4;
            }
        }
    }
    digitalWrite(RELAY4, relayState4);
    previousButtonState4 = reading4;
}
