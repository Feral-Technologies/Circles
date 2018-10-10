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

int const numDigPinsCC = 15; // number of digital pins to send CC
int currentDigcc[numDigPinsCC];
int digitalpincc[] = {
  0, 1, 2, 5, 7, 8, 11, 12, 13, 17, 20, 21, 22, 23, 26 // which digital pins to use for sending CC
};
int digInputcc[numDigPinsCC];

// the MIDI channel number to send messages
const int channel = 17;

elapsedMillis msec = 0;

void ccled (byte channel, byte number, byte value) {
  // this is for PWM out, dimmer for an LED

  if (number == 75) {
    analogWrite(3, value * 2);
  }
  if (number == 76) {
    analogWrite(4, value * 2);
  }
  if (number == 78) {
    analogWrite(6, value * 2);
  }
   if (number == 79) {
    analogWrite(9, value * 2);
  }
   if (number == 81) {
    analogWrite(10, value * 2);
  }
   if (number == 82) {
    analogWrite(16, value * 2);
  }
  if (number == 80 && value == 1) {
  digitalWrite(24, HIGH);
  }
  else
  {
  digitalWrite(24, LOW);
  }
  if (number == 83 && value == 1) {
  digitalWrite(25, HIGH);
  }
  else
  {
  digitalWrite(25, LOW);
  }
}


void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, OUTPUT);
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
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






