
// PIN Addresses
const int butL1 = 2;
const int butL2 = 3;
const int butR1 = 4;
const int butR2 = 5;

// Register for the button-press-action
bool buttonDown = false;

// Clock
int qds = 0; // Tenth of second
int qs = 0; // Seconds
int qm = 0; // Minutes
int qh = 0; // Hours

// WORD Addresses
const char ESIST[] = "ES IST ";
const char VOR[] = "VOR ";
const char NACH[] = "NACH ";
const char HALB[] = "HALB ";
const char UHR[] = "UHR ";
const char VIERTEL[] = "VIERTEL ";

const char EINS[] = "EINS ";
const char ZWEI[] = "ZWEI ";
const char DREI[] = "DREI ";
const char VIER[] = "VIER ";
const char FUNF[] = "FUNF ";
const char SECHS[] = "SECHS ";
const char SIEBEN[] = "SIEBEN ";
const char ACHT[] = "ACHT ";
const char NEUN[] = "NEUN ";
const char ZEHN[] = "ZEHN ";
const char ELF[] = "ELF ";
const char ZWOLF[] = "ZWOLF ";
const char FUNFZEHEN[] = "FUNFZEHEN ";
const char ZWANZIG[] = "ZWANZIG ";

char output[] = "";

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
  
  // Reads button  ******************************
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
        if(digitalRead(butR2) == HIGH)
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
  // Display the Clock ***********************************************
  
  

  // Run the clock ***********************************************
  delay(100);

  qds++;
  if(qds == 10)
  {
    qds = 0;
    qs++;
  }
  if(qs == 60)
  {
    qs = 0;
    qm++;
  }
  if(qm == 60)
  {
    qm = 0;
    qh++;
  }
  if(qh == 13)
  {
    qh = 1;
  }
}
