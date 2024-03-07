// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(1, OUTPUT); // LED on Model A   
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(1, HIGH);
  delay(1000);
  digitalWrite(1, LOW); 
  delay(100);
}

