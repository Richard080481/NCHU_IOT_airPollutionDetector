int LEDR = 3;
int LEDG = 5;
int LEDB = 6;

void showBreathing(int R, int G, int B){
  int gap = 100;
  for(int i=1; i<=gap; i++){
  	analogWrite(LEDR, int(R/gap*i));
    analogWrite(LEDG, int(G/gap*i));
    analogWrite(LEDB, int(B/gap*i));
    delay(10);
  }
  for(int i=gap; i>0; i--){
  	analogWrite(LEDR, int(R/gap*i));
    analogWrite(LEDG, int(G/gap*i));
    analogWrite(LEDB, int(B/gap*i));
    delay(10);
  }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  showBreathing(255, 0, 0);
  showBreathing(255, 165, 0);
  showBreathing(255, 255, 0);
  showBreathing(0, 255, 0);
  showBreathing(0, 127, 255);
  showBreathing(0, 0, 255);
  showBreathing(148, 0, 211);
}
