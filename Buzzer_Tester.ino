int ledNum = 8; //the number of the led you attach
byte ledPin[] = { 2, 3, 4, 5, 6, 7, 8, 9 };    // Create array for LED pins
byte ledVal = 1;
int ledDelay; // delay between changes
bool direction_forward = true;
int currentLED = 0;
unsigned long changeTime;
int potPin = 0;    // select the input pin for the potentiometer

void setup() {
  pinMode(12, OUTPUT);
  for (int x = 0; x < ledNum; x++)
    pinMode(ledPin[x], OUTPUT); // set all pins to output
    
  changeTime = millis();

  Serial.begin(9600);
}

void loop() {

  // put your main code here, to run repeatedly:
  ledDelay = analogRead(potPin); // read the value from the pot
  Serial.println(ledDelay);
  tone(12, map(ledDelay, 0, 1023, 440, 261));

  if ((millis() - changeTime) > ledDelay) { 
       // if it has been ledDelay ms since last change
    changeLED();
    changeTime = millis();
  }
}

void changeLED()  
{
  for (int x=0; x < ledNum; x++)
  {   // turn off all LED's
    digitalWrite(ledPin[x], LOW);
  }
  
  if(direction_forward)
    ledVal <<= 1;
  else
    ledVal >>= 1;
  
  for (int x=0; x < ledNum; x++)
  {   // turn off all LED's
    digitalWrite(ledPin[x], (ledVal >> x) & 1);
  }
  
  if(ledVal < 2 || ledVal > 127) {
    direction_forward = !direction_forward;
  }
}
