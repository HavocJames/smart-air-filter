#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <MQUnifiedsensor.h>

#define Board ("Arduino UNO")
#define Pinmq3 (A0)
#define Pinmq135 (A1)
#define Pinmq9 (A2)
#define RelayPinbio (8)
#define RelayPinphy (7)
#define RelayPinche (4)
#define measurePin A3
#define ledPower (12)

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define RatioMQ3CleanAir (60)     //RS / R0 = 60 ppm
#define RatioMQ135CleanAir (3.6)  //RS / R0 = 10 ppm
#define RatioMQ9CleanAir (9.6)    //RS / R0 = 9.6 ppm
#define ADC_Bit_Resolution (10)   // 10 bit ADC
#define Voltage_Resolution (5)    // Volt resolution to calc the voltage
#define typemq135 "MQ-135"  
#define typemq3 "MQ-3"   
#define typemq9 "MQ-9"  

//Declare Sensor
MQUnifiedsensor MQ3(Board, Voltage_Resolution, ADC_Bit_Resolution, Pinmq3, typemq3);
MQUnifiedsensor MQ135(Board, Voltage_Resolution, ADC_Bit_Resolution, Pinmq135, typemq135);
MQUnifiedsensor MQ9(Board, Voltage_Resolution, ADC_Bit_Resolution, Pinmq9, typemq9);
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

String str;

SoftwareSerial espSerial(0, 1);//(rxPin, txPin, inverse_logic)


void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.print(" Air");
  lcd.setCursor(0, 1);
  lcd.print("purifer");
  delay(1000);
  lcd.clear();

  pinMode(RelayPinbio, OUTPUT);
  pinMode(RelayPinphy, OUTPUT);
  pinMode(RelayPinbio, OUTPUT);
  pinMode(ledPower, OUTPUT);

  MQ3.setRegressionMethod(1);  //_PPM = a*ratio^b
  MQ3.init();

  MQ135.setRegressionMethod(1);  //_PPM = a*ratio^b
  MQ135.init();
 
  MQ9.setRegressionMethod(1);  //_PPM = a*ratio^b
  MQ9.init();

  //If the RL value is different from 10K please assign your RL value with the following method:
  MQ3.setR0(0.45);
  MQ135.setR0(9.03);
  MQ9.setR0(13.93);  
 
  /*****************************  MQ CAlibration ********************************************/ 
  // Explanation: 
  // In this routine the sensor will measure the resistance of the sensor supposedly before being pre-heated
  // and on clean air (Calibration conditions), setting up R0 value.
  // We recomend executing this routine only on setup in laboratory conditions.
  // This routine does not need to be executed on each restart, you can load your R0 value from eeprom.
  // Acknowledgements: https://jayconsystems.com/blog/understanding-a-gas-
  Serial.print("Calibrating please wait.");
  float MQ3calcR0 = 0, MQ135calcR0 = 0, MQ9calcR0 = 0;

  for (int i = 1; i <= 10; i++) {
    //Update the voltage lectures

    MQ3.update();
    MQ135.update();
    MQ9.update();

    MQ3calcR0 += MQ3.calibrate(RatioMQ3CleanAir);
    MQ135calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    MQ9calcR0 += MQ9.calibrate(RatioMQ9CleanAir);

    Serial.print(".");
  }

  MQ3.setR0(MQ3calcR0 / 10);
  MQ135.setR0(MQ135calcR0 / 10);
  MQ9.setR0(MQ9calcR0 / 10);
  Serial.println(" done!.");

  Serial.print("(MQ3 MQ135 MQ9):");
  Serial.print(MQ3calcR0 / 10);
  Serial.print(" | ");
  Serial.print(MQ135calcR0 / 10);
  Serial.print(" | ");
  Serial.print(MQ9calcR0 / 10);
  Serial.println(" |");
  /*****************************  MQ CAlibration *************************/

  mySerial.begin(9600);

}
void loop() 
{
 /*
  Exponential regression of mq3:
  Gas    | a      | b
  LPG    | 44771  | -3.245
  CH4    | 2*10^31| 19.01
  CO     | 521853 | -3.821
  Alcohol| 0.3934 | -1.504
  Benzene| 4.8387 | -2.68
  Hexane | 7585.3 | -2.849
  Exponential regression of mq135:
  GAS      | a      | b
  CO       | 605.18 | -3.937  
  Alcohol  | 77.255 | -3.18 
  CO2      | 110.47 | -2.862
  Toluen  | 44.947 | -3.445
  NH4      | 102.2  | -2.473
  Aceton  | 34.668 | -3.369
  Exponential regression:
  GAS     | a      | b
  LPG     | 1000.5 | -2.186
  CH4     | 4269.6 | -2.648
  CO      | 599.65 | -2.244
  */
  MQ3.setA(0.3934);
  MQ3.setB(-1.504);  //Alcohol
  float Alcohol = MQ3.readSensor();

  MQ3.setA(4.8387);
  MQ3.setB(-2.68);  //Benzene
  float Benzene = MQ3.readSensor();

  MQ3.setA(7585.3);
  MQ3.setB(-2.849);  //Hexane
  float Hexane = MQ3.readSensor();

  MQ135.setA(110.47);
  MQ135.setB(-2.862);  //CO2
  float CO2 = MQ135.readSensor();

  MQ135.setA(44.947);
  MQ135.setB(-3.445);  // Toluene
  float Toluene = MQ135.readSensor();

  MQ135.setA(102.2);
  MQ135.setB(-2.473);  //NH4
  float NH4 = MQ135.readSensor();

  MQ135.setA(34.668);
  MQ135.setB(-3.369);  //Acetone
  float Acetone = MQ135.readSensor();

  MQ9.setA(1000.5);
  MQ9.setB(-2.186);  //flamable gas
  float FG = MQ9.readSensor();

  //dust sensor
  digitalWrite(ledPower, LOW);  // power on the LED
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin);  // read the dust value
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH);  // turn the LED off
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured * (5.0 / 1024.0);
  dustDensity = 170 * calcVoltage - 0.1;

  float sensorValuemq3 = analogRead(Pinmq3);      // read analog input pin 0
  float sensorValuemq135 = analogRead(Pinmq135);  // read analog input pin 0
  float sensorValuemq9 = analogRead(Pinmq9);      // read analog input pin 0

  //bio filter
  if ( Alcohol > 100) {
    digitalWrite(RelayPinbio, LOW);  //turn off the relay
  }
  else if(Benzene > 10) {
    digitalWrite(RelayPinbio, LOW);  // Let's turn on the relay...
  }
  else if(Hexane > 10) {
    digitalWrite(RelayPinbio, LOW);  // Let's turn on the relay...
  }
  else if(Toluene > 10) {
    digitalWrite(RelayPinbio, LOW);  // Let's turn on the relay...
  }
  else if( Acetone > 10) {
    digitalWrite(RelayPinbio, LOW);  // Let's turn on the relay...
  }
  else {
    digitalWrite(RelayPinbio, HIGH);  // Let's turn off the relay...
  }
    
 //phy filter
  if (dustDensity > 35) {
    digitalWrite(RelayPinphy, LOW);  //turn on the relay
  } 
  else {
    digitalWrite(RelayPinphy, HIGH);  // turn off the relay...
  }

 //chem filter
  if (CO2 > 20) 
  {
    digitalWrite(RelayPinche, LOW);  //turn on the relay
  }
  else if (FG > 10) 
  {
    digitalWrite(RelayPinche, LOW);  //turn on the relay...
  }
  else if (NH4 > 25) 
  {
    digitalWrite(RelayPinche, LOW);  //turn on the relay...
  }
  else 
  {
    digitalWrite(RelayPinche, HIGH);  // turn off the relay...
  }

  float biological = (Alcohol + NH4 ) / 2;
  float chemical = (Benzene + Hexane + CO2 + Acetone + FG) / 2;

 //serial displaing
  Serial.println(".............");
  Serial.print("Dust Density: "); Serial.println(dustDensity);
  Serial.print("biological: "); Serial.println(biological);
  Serial.print("Alcohol: "); Serial.println(Alcohol);
  Serial.print("Benzene: "); Serial.println(Benzene);
  Serial.print("Hexane: "); Serial.println(Hexane);
  Serial.print("CO2: "); Serial.println(CO2);
  Serial.print("Toluene: "); Serial.println(Toluene);
  Serial.print("NH4: "); Serial.println(NH4);
  Serial.print("Acetone: "); Serial.println(Acetone);
  Serial.print("FG: "); Serial.println(FG);

 //lcd displaing
  lcd.clear();
  delay(70);
  lcd.setCursor(0, 0);
  lcd.print("DustDensity "); lcd.print(dustDensity); lcd.print("ug/m3");
  lcd.setCursor(0, 1);
  lcd.print("biological "); lcd.print(biological); lcd.print("ppm");
  delay(2000);

  lcd.clear();
  delay(70);
  lcd.setCursor(0, 0);
  lcd.print("Alcohol "); lcd.print(Alcohol); lcd.print("ppm");
  lcd.setCursor(0, 1);
  lcd.print("Benzene "); lcd.print(Benzene); lcd.print("ppm");
  delay(2000);

  lcd.clear();
  delay(70);
  lcd.setCursor(0, 0);
  lcd.print("Hexane "); lcd.print(Hexane); lcd.print("ppm");
  lcd.setCursor(0, 1);
  lcd.print("CO2 "); lcd.print(CO2); lcd.print("ppm");
  delay(2000);

  lcd.clear();
  delay(70);
  lcd.setCursor(0, 0);
  lcd.print("Toluene "); lcd.print(Toluene); lcd.print("ppm");
  lcd.setCursor(0, 1);
  lcd.print("NH4 "); lcd.print(NH4); lcd.print("ppm");
  delay(2000);

  lcd.clear();
  delay(70);
  lcd.setCursor(0, 0);
  lcd.print("Acetone "); lcd.print(Acetone); lcd.print("ppm");
  lcd.setCursor(0, 1);
  lcd.print("FG "); lcd.print(FG); lcd.print("ppm");
  delay(2000);
  
  str =String(biological)+String(",")+String(chemical)+String(",")+String(dustDensity);
  mySerial.println(str);
  delay(1000);
}
 
