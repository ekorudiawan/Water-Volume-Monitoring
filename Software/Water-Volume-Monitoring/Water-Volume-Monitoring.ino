#include <LiquidCrystal.h>
#include <stdio.h>

#define  trigPin  2
#define  echoPin  3

#define  R        8.5

static FILE lcdout = {0} ;

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

static int lcd_putchar(char ch, FILE* stream) {
  lcd.write(ch);
  return (0);
}

void setup() {
  lcd.begin(16, 2);
  fdev_setup_stream (&lcdout, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
}

void loop() {
  long duration; 
  double tinggi;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  
  tinggi = microsecondsToCentimeters(duration);
  double luasLingkaran = 2.0 * PI * R;
  long volume = (long)luasLingkaran * (long)tinggi;
  lcd.setCursor(0,0);
  fprintf(&lcdout, "Volume %d cm2        ", volume);
  delay(300);
  
}

double microsecondsToCentimeters(long t) {
  return (double)t / 29.0 / 2.0;
}

