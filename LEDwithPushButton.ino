int led = D1;     // LED pin
int button = D3; // push button is connected
int temp = 0;    // temporary variable for reading the button pin status

void setup() {
  pinMode(led, OUTPUT);   // declare LED as output
  pinMode(button, INPUT); // declare push button as input
}

void loop() {
  temp = digitalRead(button);
     
     if (temp == HIGH) {
        digitalWrite(led, HIGH);
        Serial.println("LED Turned ON");
//        delay(1000);
       }
     else {
        digitalWrite(led, LOW);
        Serial.println("LED Turned OFF");
//        delay(1000);
       }
}
