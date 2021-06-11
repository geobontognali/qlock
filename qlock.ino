
const int butL1 = 2;
const int butL2 = 3;
const int butR1 = 4;
const int butR2 = 5;

int but1 = 0;  // set by L1 + R1
int but2 = 0;  // set by L2 + R1
int but3 = 0;  // set by L1 + R2
int but4 = 0;  // set by L2 + R2

int qds = 0;
int qs = 0;

void setup() {
  // init serial
  Serial.begin(9600);

  // init pins
  pinMode(butL1, OUTPUT);
  pinMode(butL2, OUTPUT);
  pinMode(butR1, INPUT);
  pinMode(butR2, INPUT);

  digitalWrite(butL1, LOW);
  digitalWrite(butL2, LOW);
  
}

void loop() {
  // Fire L1 (Button 1 and 3)
  digitalWrite(butL1, HIGH);
  // Check Button 1
  if(digitalRead(butR1) == HIGH)
  {
    but1 = 1;
  }
  else
  {
    but1 = 0;
  }
  // Check Button 3
  if(digitalRead(butR2) == HIGH)
  {
    but3 = 1;
  }
  else
  {
    but3 = 0;
  }
  digitalWrite(butL1, LOW);
  // Fire L2 (Button 2 and 4)
  digitalWrite(butL2, HIGH);
  if(digitalRead(butR1) == HIGH)
  {
    but2 = 1;
  }
  else
  {
    but2 = 0;
  }
  if(digitalRead(butR2) == HIGH)
  {
    but4 = 1;
  }
  else
  {
    but4 = 0;
  }
  digitalWrite(butL2, LOW);
  
  Serial.println(but1);
  Serial.println(but2);
  Serial.println(but3);
  Serial.println(but4);
  Serial.println("----");
  Serial.println(qs);
  Serial.println("----");
  delay(100);

  // Increate thenth of second
  qds++;
  if(qds == 10)
  {
    qds = 0;
    qs++;
  }
}
