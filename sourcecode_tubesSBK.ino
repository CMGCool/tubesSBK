#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd (0x27, 16, 2);

//Deklarasi nomor pin

const int buzzer = 8;
const int merahPin = 2;
const int hijauPin = 3;
const int trigPin = 5;
const int echoPin = 4;

//Deklarasi variabel

long duration;
int temp;
int distance;
int safetyDistance;

void setup (){
  pinMode (buzzer, OUTPUT);
  pinMode (merahPin, OUTPUT);
  pinMode (hijauPin, OUTPUT);
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);

  Serial.begin(9600);
  mlx.begin();
  lcd.init();
  lcd.backlight();

}

void loop(){
  //trigpin mode

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //setting trigpin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //BACA ECHO PIN DALAM MILISECOND
  duration = pulseIn(echoPin, HIGH);

  //BACA TEMP
  temp = mlx.readObjectTempC();

  //KALKULASI JARAK
  distance = duration * 0.034/2;
  safetyDistance = distance;

  //PERNYATAAN KONDISI

  if (safetyDistance <= 5){
    digitalWrite(hijauPin, HIGH);

    lcd.setCursor(0,0);
    lcd.print("   SUHU NORMAL !!           ");

    lcd.setCursor(1,1);
    lcd.print(" SUHU: ");
    lcd.print(mlx.readObjectTempC());
    lcd.print("'C     ");
    delay(1000);
    lcd.clear();

  }else {
    lcd.setCursor(0,0);
    lcd.print("   DIGITHERM");
    lcd.setCursor(0,1);
    lcd.print("DEKATKAN TANGAN !!       ");

    digitalWrite(buzzer, LOW);
    digitalWrite(hijauPin, LOW);
  }

//PERNYATAAN KONDISI 2

if (mlx.readObjectTempC() > 37){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);

  digitalWrite(merahPin, HIGH);
  digitalWrite(hijauPin, LOW);

  lcd.setCursor(0,0);
    lcd.print("ANDA DEMAM !!          ");
    lcd.setCursor(1,1);
    lcd.print(" SUHU: ");
    lcd.print(mlx.readObjectTempC());
    lcd.print("'C    ");
} else {
  lcd.setCursor(0,0);
    lcd.print("   DIGITHERM");
    lcd.setCursor(0,1);
    lcd.print("DEKATKAN TANGAN!!    ");

    digitalWrite(buzzer, LOW);
    digitalWrite(hijauPin, LOW);
    digitalWrite(merahPin, LOW);

}

//print ke serial monitor

Serial.print("Jarak: ");
Serial.println(distance);
Serial.println(" cm");
Serial.print("Suhu: ");
Serial.println(temp);

}