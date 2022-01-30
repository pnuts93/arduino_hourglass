const int     pinSwitch = 8;
unsigned long prevTime = 0;
int           interval = 10000;
int           secPin = 2;
int           minPin = 9;

void routine() {
  int mod = 0;
  int actualState = digitalRead(8);
  while (actualState) {
    for (int i = 2; i + (mod % 2) < 14; i += 2) {
      digitalWrite(i + (mod % 2), HIGH);
      if (i + (mod % 2) == 5 || i + (mod % 2) == 6)
        i += 2;
    }
    for (int i = 2; i + (mod % 2) - 1 < 14; i += 2) {
      if (i + (mod % 2) - 1 > 1)
        digitalWrite(i + (mod % 2 - 1), LOW);
      if (i == 5 || i == 6)
        i += 2;
    }
    mod++;
    delay(100);
    actualState = digitalRead(8);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(pinSwitch, INPUT);
  for (int i = 2; i < 7; i++)
    pinMode(i, OUTPUT);
  for (int i = 9; i < 14; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long actualTime = millis();
  int           actualState = digitalRead(8);

  if (!actualState) {
    for (int i = 2; i < 7; i++)
      digitalWrite(i, LOW);
    for (int i = 9; i < 14; i++)
      digitalWrite(i, LOW);
    secPin = 2;
    minPin = 9;
    prevTime = actualTime;
  }
  else {
    if (actualTime - prevTime >= interval) {
      prevTime = actualTime;
      if (secPin == 7){
        if (minPin == 13) {
          routine();
        }
        digitalWrite(minPin, HIGH);
        minPin++;
        secPin = 2;
        for (int i = 2; i < 7; i++)
          digitalWrite(i, LOW);
      }
      else {
        digitalWrite(secPin, HIGH);
        secPin++;
      }
    }
  }
}
