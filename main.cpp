#include <Arduino.h>

// LCD Library
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,4);

// Pushbutton Pins
#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4
#define BUTTON4 5

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
int previousButtonState1;
int previousButtonState2;
int previousButtonState3;
int previousButtonState4;

int presentButtonState1;
int presentButtonState2;
int presentButtonState3;
int presentButtonState4;

// Water Flow Sensor
volatile int flow_frequency;
unsigned int l_hour;
unsigned char flowmeter = 6
    ;
unsigned long currentTime;
unsigned long cloopTime;

// Interrupt Function
void flow() {
    flow_frequency++;
}

void setup() {
  Serial.begin(9600);

  // LCD
  lcd.init();
  lcd.backlight();

  // Flow Meter
  pinMode(flowmeter, INPUT);
  attachInterrupt(0, flow, RISING);
  sei();
  currentTime = millis();
  cloopTime = currentTime;

  // Pusbutton
  pinMode(BUTTON1, INPUT_PULLUP); 
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);

  // Relay
  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1, LOW);
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY2, LOW);
  pinMode(RELAY3, OUTPUT);
  digitalWrite(RELAY3, LOW);
  pinMode(RELAY4, OUTPUT);
  digitalWrite(RELAY4, LOW);

  // Read Button State
  presentButtonState1 = digitalRead(BUTTON1);
  presentButtonState2 = digitalRead(BUTTON2);
  presentButtonState3 = digitalRead(BUTTON3);
  presentButtonState4 = digitalRead(BUTTON4);
}

void loop() {

  // Flow Sensor
  currentTime = millis();
  if (currentTime >= (cloopTime + 1000)) {
    cloopTime = currentTime;
    l_hour = (flow_frequency * 60 / 7.5);
    flow_frequency = 0;
    //lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Flow Rate:");
    lcd.setCursor(0, 1);
    lcd.print(l_hour, DEC);
    lcd.println(" L/hour");
  }

  // Relay 1
  previousButtonState1 = presentButtonState1;      
  presentButtonState1 = digitalRead(BUTTON1); 
  if (previousButtonState1 == LOW && presentButtonState1 == HIGH) {
    relayState1 = !relayState1;
    digitalWrite(RELAY1, relayState1);
    digitalRead(relayState1);
  }

  // Relay 2
  previousButtonState2 = presentButtonState2;      
  presentButtonState2 = digitalRead(BUTTON2); 
  if (previousButtonState2 == HIGH && presentButtonState2 == LOW) {
    relayState2 = !relayState2;
    digitalWrite(RELAY2, relayState2);
    digitalRead(relayState2);
  }

  // Relay 3
  previousButtonState3 = presentButtonState3;      
  presentButtonState3 = digitalRead(BUTTON3); 
  if (previousButtonState3 == HIGH && presentButtonState3 == LOW) {
    relayState3 = !relayState3;
    digitalWrite(RELAY3, relayState3);
    digitalRead(relayState3);
  }

  // Relay 4
  previousButtonState4 = presentButtonState4;      
  presentButtonState4 = digitalRead(BUTTON4); 
  if (previousButtonState4 == HIGH && presentButtonState4 == LOW) {
    relayState4 = !relayState4;
    digitalWrite(RELAY4, relayState4);
    digitalRead(relayState4);
  }
}
