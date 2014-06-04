int outPin = 11;

int freqPin = A0;
int fineFreqPin = A2;

int dutyPin = A1;

float maxFreq = 60.; // in Hz
float fineFreq = 2.;

float maxDuty = 5000; // maximum flash duration in µS

float freq = 60.; // in Hz
float ffreq = 0;
float duty = .1; // ratio
long strobeDelay = 100.; // in µS
long dutyDelay = 100.;

void setup() {
  pinMode(outPin, OUTPUT);
  pinMode(freqPin, INPUT);
  pinMode(fineFreqPin, INPUT);
  pinMode(dutyPin, INPUT);
}

void loop() {
  setFreq(getVal(freqPin));
  setFineFreq(getVal(fineFreqPin));
  setDuty(getVal(dutyPin));

  strobeDelay = getOffTime(freq);
  dutyDelay = getDutyTime(duty);

  digitalWrite(outPin, HIGH);

  if(dutyDelay < 16000.)
    delayMicroseconds(dutyDelay);
  else delay(dutyDelay / 1000.);

  digitalWrite(outPin, LOW);

  if(strobeDelay < 16000.)  
    delayMicroseconds(strobeDelay - dutyDelay);
  else delay((strobeDelay - dutyDelay) / 1000.);
}

float getVal(int pin) {
  float val = analogRead(pin) / 1023.;
  return val;
}

void setFreq(float in) {
  if(in > .02)
    freq = maxFreq * in + ffreq;
  else freq = maxFreq * .01 + ffreq;
}

void setFineFreq(float in) {
  ffreq = (in - .5) * 2. * fineFreq;
}

void setDuty(float in) {
  duty = in;
}

// Returns delay time in µS
long getOffTime(long f) {
  return 1. / f * 1000000;
}

long getDutyTime(float d) {
  return d * maxDuty + 1;
}

