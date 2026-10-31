// --- THE ULTIMATE STANDALONE ROVER: BLINK EDITION ---
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 
const int EXG_PIN = A0;      
const int BUZZER_PIN = 13;   
// L298N Motor Pins
const int IN1 = 12;           
const int IN2 = 11;
const int IN3 = 10;
const int IN4 = 3;           
int threshold = 150;         // Safe threshold based on your hardware
int baseline = 512;          
void setup() {
  Serial.begin(9600); 
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM BOOTING..");
  lcd.setCursor(0, 1);
  lcd.print("PLEASE RELAX");
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  // 1-Second Calibration (LAB RAT MUST BE TOTALLY STILL)
  long sum = 0;
  for(int i=0; i<100; i++) {
    sum += analogRead(EXG_PIN);
    delay(10);
  }
  baseline = sum / 100; 
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM READY!");
  lcd.setCursor(0, 1);
  lcd.print("AWAITING BLINK");
  
  // Ready Beep!
  digitalWrite(BUZZER_PIN, HIGH); delay(400); digitalWrite(BUZZER_PIN, LOW);
}
void loop() {
  int exgRaw = analogRead(EXG_PIN);
  int spike = abs(exgRaw - baseline); 
  
  // --- FIRST BLINK DETECTED ---
  if (spike > threshold) {
    int blinkCount = 1; 
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BLINK DETECTED!");
    lcd.setCursor(0, 1);
    lcd.print("Count: 1");
    
    // Audio Feedback Beep!
    digitalWrite(BUZZER_PIN, HIGH); delay(100); digitalWrite(BUZZER_PIN, LOW);
    
    // The Cooldown Shield (Prevents 1 long blink from counting as 3)
    delay(300); 
    // Start 2-second timer for extra blinks
    unsigned long startTime = millis();
    while (millis() - startTime < 2000) { 
      int newSpike = abs(analogRead(EXG_PIN) - baseline);
      
      if (newSpike > threshold) {
        blinkCount++; 
        
        lcd.setCursor(7, 1); 
        lcd.print(blinkCount);
        
        // Audio Feedback Beep!
        digitalWrite(BUZZER_PIN, HIGH); delay(100); digitalWrite(BUZZER_PIN, LOW);
        
        delay(300); // Cooldown Shield
      }
    }
    // --- EXECUTE MOTOR COMMAND ---
    lcd.clear();
    lcd.setCursor(0, 0);
    
    // 🛑 Stop Motors
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    
    // Add these two lines right here!
    lcd.clear();
    lcd.print("STABILIZING...");
    delay(1500); // 1.5 second shield against motor noise!
    
    // Reset Screen for next command
    lcd.clear();
    
    if (blinkCount == 0) {
      lcd.print("DRIVING STOPPED");
       digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
       
    } else if (blinkCount == 1) {
      lcd.print("DRIVING FORWARD");
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
      
    } else if (blinkCount == 2) {
      lcd.print("TURNING RIGHT");
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
      
    } else if (blinkCount == 3) {
      lcd.print("TURNING LEFT");
      digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
      
    } else if (blinkCount >= 4) {
      lcd.print("DRIVING BACKWD");
      digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    }
    // Let the rover drive for 1 full second
    delay(1000); 
    // 🛑 Stop Motors
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    
    // Reset Screen for next command
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SYSTEM READY!");
    lcd.setCursor(0, 1);
    lcd.print("AWAITING BLINK");
  }
}
