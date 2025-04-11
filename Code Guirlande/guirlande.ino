const int joystickX = A0; 
const int joystickY = A1;
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const int numLeds = 12;

// Seuils pour la détection de direction du joystick
const int threshold = 500;
const int delayTime = 200; 
const int holdTime = 500;
const int blinkCount = 5;       
const int blinkDuration = 250;  

void setup() {
  // Initialisation des broches des LEDs en sortie
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); 
  }
  
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(joystickX);
  int yValue = analogRead(joystickY);
  
  if (yValue < threshold) {
    // Joystick vers l'avant - allumer les LEDs de 1 à 12
    allumerSequence(0, numLeds - 1, 1);
  } 
  else if (yValue > 1023 - threshold) {
    // Joystick vers l'arrière - éteindre les LEDs de 12 à 1
    eteindreSequence(numLeds - 1, 0, -1);
  } 
  else if (xValue > 1023 - threshold) {
    // Joystick vers la droite - séquence paires puis impaires
    sequencePairesImpaires();
  } 
  else if (xValue < threshold) {
    // Joystick vers la gauche - clignoter toutes les LEDs 5 fois
    clignoterToutesLeds();
  }
  
  delay(10);
}

void clignoterToutesLeds() {
  for (int i = 0; i < blinkCount; i++) {
    // Allumer toutes les LEDs
    for (int j = 0; j < numLeds; j++) {
      digitalWrite(ledPins[j], HIGH);
    }
    delay(blinkDuration);
    
    // Éteindre toutes les LEDs
    for (int j = 0; j < numLeds; j++) {
      digitalWrite(ledPins[j], LOW);
    }
    delay(blinkDuration);
  }
}

void sequencePairesImpaires() {
  // Éteindre toutes les LEDs
  eteindreToutes();
  
  // 1. Allumage progressif des LEDs paires (broches 3,5,7,9,11,13)
  for (int i = 1; i < numLeds; i += 2) {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
  }
  
  // Maintenir allumé 2 secondes
  delay(holdTime);
  
  // Extinction progressive des LEDs paires
  for (int i = 1; i < numLeds; i += 2) {
    digitalWrite(ledPins[i], LOW);
    delay(delayTime);
  }
  
  // 2. Allumage progressif des LEDs impaires (broches 2,4,6,8,10,12)
  for (int i = 0; i < numLeds; i += 2) {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
  }
  
  // Maintenir allumé 2 secondes
  delay(holdTime);
  
  // Extinction progressive des LEDs impaires
  for (int i = 0; i < numLeds; i += 2) {
    digitalWrite(ledPins[i], LOW);
    delay(delayTime);
  }
}

void allumerSequence(int start, int end, int step) {
  for (int i = start; i != end + step; i += step) {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
  }
}

void eteindreSequence(int start, int end, int step) {
  for (int i = start; i != end + step; i += step) {
    digitalWrite(ledPins[i], LOW);
    delay(delayTime);
  }
}

void allumerPaires() {
  eteindreToutes();
  for (int i = 1; i < numLeds; i += 2) {
    digitalWrite(ledPins[i], HIGH);
  }
}

void allumerImpaires() {
  eteindreToutes();
  for (int i = 0; i < numLeds; i += 2) {
    digitalWrite(ledPins[i], HIGH);
  }
}

void eteindreToutes() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}