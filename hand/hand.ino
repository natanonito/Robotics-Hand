#include <Servo.h>

Servo thumb, index, middle, ring, pinky;

int Ypin = A0; 
int Xpin = A1;

void setup() {
  Serial.begin(9600);
  
  thumb.attach(3);
  index.attach(5);
  middle.attach(6);
  ring.attach(8);
  pinky.attach(11);

  // Print the Table Header once
  Serial.println("JX\tJY\tTHM\tIDX\tMID\tRNG\tPNK");
  Serial.println("--------------------------------------------------");
}

void loop() {
  int Xval = analogRead(Xpin);
  int Yval = analogRead(Ypin);

  // Initialize all angles to 0
  int thmA = 0, idxA = 0, midA = 0, rngA = 0, pnkA = 0;

  // --- Logic for Y-AXIS ---
  if (Yval > 520) {
    idxA = map(Yval, 310, 620, 0, 180);
  } else if (Yval < 500) {
    rngA = map(Yval, 290, 10, 0, 180);
  }

  // --- Logic for X-AXIS ---
  if (Xval > 520) {
    pnkA = map(Xval, 310, 660, 0, 180);
  } else if (Xval < 500) {
    int leftVal = map(Xval,300, 240, 0, 180);
    midA = leftVal;
    thmA = leftVal;
  }
  idxA = constrain(idxA, 0, 180);
  rngA = constrain(rngA, 0, 180);
  pnkA = constrain(pnkA, 0, 180);
  midA = constrain(midA, 0, 180);
  thmA = constrain(thmA, 0, 180);

  // Write to Servos
  index.write(idxA);
  ring.write(rngA);
  pinky.write(pnkA);
  middle.write(midA);
  thumb.write(thmA);

  // Print Table Row
  Serial.print(Xval);   Serial.print("\t");
  Serial.print(Yval);   Serial.print("\t");
  Serial.print(thmA);   Serial.print("\t");
  Serial.print(idxA);   Serial.print("\t");
  Serial.print(midA);   Serial.print("\t");
  Serial.print(rngA);   Serial.print("\t");
  Serial.println(pnkA);

  delay(150); // Increased delay slightly so the Serial Monitor is readable
}
