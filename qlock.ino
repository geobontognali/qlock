// LED Library
#include <FastLED.h>

#define NUM_LEDS 402

CRGB leds[NUM_LEDS];

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
int qh = 12; // Hours

int qr = 2999; // Qlock Refresher
bool showUhr = false; // Qlock bool
bool showHalb = false;

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
const char FUNFZEHN[] = "FUNFZEHN ";
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
      qm = qm + 5;
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
        qh++;
        if(qh == 13) { qh = 1; }
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
          qm = qm - 5;
          if(qm < 0) { qm = 0; }
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
            qh--;
            if(qh <= 0) { qh = 12; }
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
  qr++;
  if(qr == 3000) // Refresh every 5 min
  {
    qr = 0;
    showUhr = false;
    showHalb = false;
    FastLED.clear() // Clear previous setting
    
    Serial.println("*****************");

    // Refresh Display
    if(random(0,2))
    {
      Serial.println(ESIST);  
    }

    // Display minutes
    if(qm >= 57 || qm < 3)
    {
      showUhr = true; 
    }
    else if(qm >= 3 && qm < 7)
    {
      Serial.println(FUNF);
      Serial.println(NACH);
    }
    else if(qm >= 7 && qm < 13)
    {
      Serial.println(ZEHN);
      Serial.println(NACH);
    }
    else if(qm >= 13 && qm < 17)
    {
      if(random(0,2)) { Serial.println(VIERTEL); }
      else { Serial.println(FUNFZEHN); }
      Serial.println(NACH);
    }
    else if(qm >= 17 && qm < 25)
    {
      Serial.println(ZWANZIG);
      Serial.println(NACH);
    }
    else if(qm >= 25 && qm < 37)
    {
      Serial.println(HALB);
      showHalb = true;
      qh++;
      if(qh == 13) { qh = 1; }
    }
    else if(qm >= 37 && qm < 43)
    {
      Serial.println(ZWANZIG);
      Serial.println(VOR);
    }
    else if(qm >= 43 && qm < 47)
    {
      if(random(0,2)) { Serial.println(VIERTEL); }
      else { Serial.println(FUNFZEHN); }
      Serial.println(VOR);
    }
    else if(qm >= 47 && qm < 53)
    {
      Serial.println(ZEHN);
      Serial.println(VOR);
    }
    else if(qm >= 53 && qm < 57)
    {
      Serial.println(FUNF);
      Serial.println(VOR);
    }

    // Show hour
    if(qh == 1) { Serial.println(EINS); }
    else if(qh == 2) { Serial.println(ZWEI); }
    else if(qh == 3) { Serial.println(DREI); }
    else if(qh == 4) { Serial.println(VIER); }
    else if(qh == 5) { Serial.println(FUNF); }
    else if(qh == 6) { Serial.println(SECHS); }
    else if(qh == 7) { Serial.println(SIEBEN); }
    else if(qh == 8) { Serial.println(ACHT); }
    else if(qh == 9) { Serial.println(NEUN); }
    else if(qh == 10) { Serial.println(ZEHN); }
    else if(qh == 11) { Serial.println(ELF); }
    else if(qh == 12) { Serial.println(ZWOLF); }


    
    if(random(0,2) && showUhr)
    {
      Serial.println(UHR);
    } 
  
    Serial.println("*****************");
    Serial.println(qh);
    Serial.println(qm);
  
    if(showHalb) // wegem deutsch und seine sinnlosigkeit
    {
      if(qh == 1) { qh = 12; }
      else { qh--; }
    }
  }
  
  // Run the clock ***********************************************
  delay(1); // Should be 100 for tenth of second

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
