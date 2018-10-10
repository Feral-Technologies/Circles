// SIX mod May 15 2015

// in progress

/* code borrowed from Yann Seznec www.yannseznec.com
and pjrc - these sources are in public domain

remember to select MIDI as your USB Type in the Tools menu

*/
//
//// set analog pins

int const numPins = 4; //  set number of analog inputs to use
int currentVal[numPins];
int newVal[numPins];
int analogPins[] = {
  14, 15, 18, 19 // set which analog pins to use
};


// set digital pins

int const numDigPinsCC = 7; // number of digital pins to send CC
int currentDigcc[numDigPinsCC];
int digitalpincc[] = {
  0, 1, 2, 21, 24, 25, 26 // which digital pins to use for sending CC
};
int digInputcc[numDigPinsCC];

// the MIDI channel number to send messages
const int channel = 1;

elapsedMillis msec = 0;

void ccled (byte channel, byte number, byte value) {
  // this is for PWM out, dimmer for an LED

  if (number == 60) {
    analogWrite(3, value * 2);
  }
  if (number == 61) {
    analogWrite(4, value * 2);
  }
  if (number == 63) {
    analogWrite(6, value * 2);
  }
   if (number == 64) {
    analogWrite(9, value * 2);
  }
   if (number == 66) {
    analogWrite(10, value * 2);
  }
   if (number == 67) {
    analogWrite(16, value * 2);
  }
   if (number == 69) {
    analogWrite(17, value * 2);
  }
   if (number == 70) {
    analogWrite(20, value * 2);
  }
    if (number == 72) {
    analogWrite(22, value * 2);
  }
    if (number == 73) {
    analogWrite(23, value * 2);
  }
  if (number == 62 && value == 1) {
  digitalWrite(5, HIGH);
  }
  else
  {
  digitalWrite(5, LOW);
  }
  if (number == 65 && value == 1) {
  digitalWrite(7, HIGH);
  }
  else
  {
  digitalWrite(7, LOW);
  }
  if (number == 68 && value == 1) {
  digitalWrite(8, HIGH);
  }
  else
  {
  digitalWrite(8, LOW);
  }
  if (number == 74 && value == 1) {
  digitalWrite(12, HIGH);
  }
  else
  {
  digitalWrite(12, LOW);
  }
  if (number == 77 && value == 1) {
  digitalWrite(13, HIGH);
  }
  else
  {
  digitalWrite(13, LOW);
  }
}


void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(20, OUTPUT);
  pinMode(21, INPUT_PULLUP);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  
  

}

void loop() {
  if (msec >= 20) {
    msec = 0;

    // digital pins sending CC

    for (int i = 0; i < numDigPinsCC; i++) {
      if (digitalRead(digitalpincc[i]) == 1 && currentDigcc[i] == 0) {
        usbMIDI.sendControlChange(i + 50, 0, channel);
        currentDigcc[i] = 1;
      }
      if (digitalRead(digitalpincc[i]) == 0  && currentDigcc[i] == 1) {
        usbMIDI.sendControlChange(i + 50, 127, channel);
        currentDigcc[i] = 0;
      }
    }

    // analog pins

    for (int i = 0; i < numPins; i++) {

      newVal[i] = analogRead(analogPins[i]);

      if (abs(newVal[i] - currentVal[i]) > 3) {
        usbMIDI.sendControlChange(i + 100, newVal[i] >> 3, channel);
        currentVal[i] = newVal[i];
      }
    }
  }
  usbMIDI.setHandleControlChange(ccled) ;
  usbMIDI.read();

  //  while (usbMIDI.read()) {
  //    // ignore incoming messages
  //  }
}






