const int measurePin = A5;                         //Connect dust sensor to Arduino A5 pin
const int ledPower = 2;                           //Connect 3 led driver pins of dust sensor to Arduino D2
const int LEDR = 3;                               //LED red Arduino pin 3
const int LEDG = 5;                               //LED green Arduino pin 3
const int LEDB = 6; 
  
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
  
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void showBreathing(int R, int G, int B){
  int gap = 100;
  //漸亮
  for(int i=1; i<=gap; i++){
  	analogWrite(LEDR, int(R/gap*i));
    analogWrite(LEDG, int(G/gap*i));
    analogWrite(LEDB, int(B/gap*i));
    delay(10);
  }
  //漸暗
  for(int i=gap; i>0; i--){
  	analogWrite(LEDR, int(R/gap*i));
    analogWrite(LEDG, int(G/gap*i));
    analogWrite(LEDB, int(B/gap*i));
    delay(10);
  }
}
void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}
  
void loop(){
  digitalWrite(ledPower,LOW);                                           // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);                                  // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);                                         // turn the LED off
  delayMicroseconds(sleepTime);
  
  calcVoltage = voMeasured * (5.0 / 1024.0);

  dustDensity = (170 * calcVoltage - 0.1)*0.1;

  Serial.println(dustDensity); // unit: ug/m3

  if(dustDensity>=35.5){
    Serial.println("Red");
    showBreathing(255, 0, 0);
  }
  else if(35.5>dustDensity && dustDensity>=15.5){
    Serial.println("Yellow");
    showBreathing(255, 255, 0);
  }
  else{
    Serial.println("Green");
    showBreathing(0, 255, 0);
  }
}
