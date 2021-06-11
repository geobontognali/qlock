
const int butL1 = 2;
const int butL2 = 3;
const int butR1 = 4;
const int butR2 = 5;

int but1 = 0;  // set by L1 + R1
int but2 = 0;  // set by L2 + R1
int but3 = 0;  // set by L1 + R2
int but4 = 0;  // set by L2 + R2

int buttonDown = false;


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
  // Reads button 
  // Fire L1 (Button 1 and 3)
  digitalWrite(butL1, HIGH);
  digitalWrite(butL2, LOW);
  
  // Check Button 1
  if(digitalRead(butR1) == HIGH) 
  {
    if(!buttonDown)
    {
      qs++;
      buttonDown = true;
    }
  }
  else 
  {
    // Check Button 3
    if(digitalRead(butR2) == HIGH) 
    { 
      if(!buttonDown)
      {
        qs = qs + 10;
        buttonDown = true;
      }
    }
    else 
    {
      // Fire L2 (Button 2 and 4)
      digitalWrite(butL1, LOW);
      digitalWrite(butL2, HIGH);

      // Check Button 2
      if(digitalRead(butR1) == HIGH)
      { 
        if(!buttonDown)
        {
          qs--;
          buttonDown = true;
        }
      }
      else
      {
        // Check Button 4
        if(digitalRead(butR2) == HIGH && !buttonDown)
        { 
          if(!buttonDown)
          {
            qs = qs - 10;
            buttonDown = true;
          }
        }
        else
        {
          buttonDown = false;
        }
      }
    }
  }
  
 
  delay(100);

  // Increate thenth of second
  qds++;
  if(qds == 10)
  {
    qds = 0;
    qs++;
    Serial.println("----");
    Serial.println(qs);
    Serial.println("----");
  }
}


/* 
   // Reads button 
  // Fire L1 (Button 1 and 3)
  digitalWrite(butL1, HIGH);
  // Check Button 1
  if(digitalRead(butR1) == HIGH) 
  {
    if(!but1actioned)
    {
      blob++;
      but1actioned = true;
    }
  }
  else { but1actioned = false; }
  
  // Check Button 3
  if(digitalRead(butR2) == HIGH) 
  { 
    if(!but3actioned)
      {
        blob++;
        but3actioned = true;
      }  
  }
  else { but3actioned = false; }
  digitalWrite(butL1, LOW);
  
  // Fire L2 (Button 2 and 4)
  digitalWrite(butL2, HIGH);
  // Check Button 2
  if(digitalRead(butR1) == HIGH)
  { 
  if(!but2actioned)
    {
      blob++;
      but2actioned = true;
    }  
  }
  else { but2actioned = false; }
  // Check Button 4
  if(digitalRead(butR2) == HIGH)
  { 
  if(!but4actioned)
    {
      blob++;
      but4actioned = true;
    }  
  }
  else { but4actioned = false; }
  digitalWrite(butL2, LOW);
*/
