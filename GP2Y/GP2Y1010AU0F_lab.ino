const int measurePin = A5;
const int ledPower = 2;
const int LEDR = 3;
const int LEDG = 5;
const int LEDB = 6;

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void turnoff(){
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
}

void showBreathing(int R,  int G, int B)
{
  int gap = 100;
  for(int i = 1; i <= gap; i++)
  {
    analogWrite(LEDR, int(R/gap*i));
    analogWrite(LEDG, int(G/gap*i));
    analogWrite(LEDB, int(B/gap*i));
    delay(10);
  }
  for(int i = gap; i > 0; i--)
  {
    analogWrite(LEDR, int(R/gap*i));
    analogWrite(LEDG, int(G/gap*i));
    analogWrite(LEDB, int(B/gap*i));
    delay(10);    
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPower, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  turnoff();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPower, LOW);
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured * (5.0 / 1024.0);

  dustDensity = (170 * calcVoltage - 0.1) * 0.1;

  Serial.println(dustDensity);

  if(dustDensity >= 35.5)
  {
    turnoff();
    digitalWrite(LEDR, HIGH);
    Serial.println("RED");
  }
  else if(35.5 > dustDensity && dustDensity >= 15.5)
  {
    Serial.println("Yellow");
    turnoff();
    analogWrite(LEDG, 255);
    analogWrite(LEDR, 150);
  }
  else
  {
    turnoff();
    digitalWrite(LEDG, HIGH);
    Serial.println("Green");
  }
  delay(1000);
};
