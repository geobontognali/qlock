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
const char _ESIST[] = "ES IST "; // ****

const char _VOR[] = "VOR "; // ****
const char _NACH[] = "NACH "; // ****
const char _HALB[] = "HALB "; // ****
const char UHR[] = "UHR ";
const char _VIERTEL[] = "VIERTEL "; // *****

const char _EINS[] = "EINS "; // ****
const char ZWEI[] = "ZWEI "; 
const char _DREI[] = "DREI "; // ****
const char VIER[] = "VIER "; // ****
const char _FUNF[] = "FUNF "; // *****
const char SECHS[] = "SECHS "; 
const char SIEBEN[] = "SIEBEN ";
const char ACHT[] = "ACHT "; 
const char NEUN[] = "NEUN ";
const char _ZEHN[] = "ZEHN "; // *****
const char ELF[] = "ELF ";
const char ZWOLF[] = "ZWOLF ";
const char _FUNFZEHN[] = "FUNFZEHN ";
const char _ZWANZIG[] = "ZWANZIG "; // *****

char output[] = "";

void setup() {
  // init serial
  Serial.begin(9600);

  // init LEDs
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
    
  // init pins
  pinMode(butL1, OUTPUT);
  pinMode(butL2, OUTPUT);
  pinMode(butR1, INPUT);
  pinMode(butR2, INPUT);

  digitalWrite(butL1, LOW);
  digitalWrite(butL2, LOW);

  delay(6000);
}

void loop() {

  //EINS();
  //delay(50000);
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
    FastLED.clear(); // Clear previous setting
    

    // Refresh Display
    if(random(0,2))
    {
      Serial.println(_ESIST);
      ESIST();  
    }

    // Display minutes
    if(qm >= 57 || qm < 3)
    {
      showUhr = true; 
    }
    else if(qm >= 3 && qm < 7)
    {
      Serial.println(_FUNF);
      FUNF_M();
      Serial.println(_NACH);
      NACH();
    }
    else if(qm >= 7 && qm < 13)
    {
      Serial.println(_ZEHN);
      ZEHN();
      Serial.println(_NACH);
      NACH();
    }
    else if(qm >= 13 && qm < 17)
    {
      if(random(0,2)) { Serial.println(_VIERTEL); VIERTEL(); }
      else { Serial.println(_FUNFZEHN); FUNFZEHN(); }
      Serial.println(_NACH); NACH();
    }
    else if(qm >= 17 && qm < 25)
    {
      Serial.println(_ZWANZIG);
      Serial.println(_NACH);
    }
    else if(qm >= 25 && qm < 37)
    {
      Serial.println(_HALB);
      HALB();
      showHalb = true;
      qh++;
      if(qh == 13) { qh = 1; }
    }
    else if(qm >= 37 && qm < 43)
    {
      Serial.println(_ZWANZIG);
      ZWANZIG();
      Serial.println(_VOR);
      VOR();
    }
    else if(qm >= 43 && qm < 47)
    {
      if(random(0,2)) { Serial.println(_VIERTEL); VIERTEL(); }
      else { Serial.println(_FUNFZEHN); FUNFZEHN(); }
      Serial.println(_VOR); VOR();
    }
    else if(qm >= 47 && qm < 53)
    {
      Serial.println(_ZEHN); ZEHN();
      Serial.println(_VOR); VOR();
    }
    else if(qm >= 53 && qm < 57)
    {
      Serial.println(_FUNF); FUNF_M();
      Serial.println(_VOR); VOR();
    }

    // Show hour
    if(qh == 1) { Serial.println(_EINS); EINS(); }
    else if(qh == 2) { Serial.println(ZWEI); }
    else if(qh == 3) { Serial.println(_DREI); }
    else if(qh == 4) { Serial.println(VIER); }
    else if(qh == 5) { Serial.println(_FUNF); FUNF(); }
    else if(qh == 6) { Serial.println(SECHS); }
    else if(qh == 7) { Serial.println(SIEBEN); }
    else if(qh == 8) { Serial.println(ACHT); }
    else if(qh == 9) { Serial.println(NEUN); }
    else if(qh == 10) { Serial.println(_ZEHN); ZEHN(); }
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

// WORDS
void ESIST()
{
  //leds[0] = CRGB::White; FastLED.show();
  leds[1] = CRGB::White; FastLED.show();
  //leds[2] = CRGB::White; FastLED.show();

  //leds[4] = CRGB::White; FastLED.show();
  leds[5] = CRGB::White; FastLED.show();


  //leds[12] = CRGB::White; FastLED.show();
  leds[13] = CRGB::White; FastLED.show();

  //leds[16] = CRGB::White; FastLED.show();
  leds[17] = CRGB::White; FastLED.show();

  //leds[20] = CRGB::White; FastLED.show();
  leds[21] = CRGB::White; FastLED.show();
}

void FUNF_M()
{
  //leds[28] = CRGB::White; FastLED.show();
  leds[29] = CRGB::White; FastLED.show();

  //leds[32] = CRGB::White; FastLED.show();
  //leds[33] = CRGB::White; FastLED.show();
  leds[34] = CRGB::White; FastLED.show();

  //leds[36] = CRGB::White; FastLED.show();
  leds[37] = CRGB::White; FastLED.show();
  //leds[38] = CRGB::White; FastLED.show();

  //leds[40] = CRGB::White; FastLED.show();
  leds[41] = CRGB::White; FastLED.show();
  //leds[42] = CRGB::White; FastLED.show();
}

void FUNFZEHN()
{
  //leds[28] = CRGB::White; FastLED.show();
  leds[29] = CRGB::White; FastLED.show();

  //leds[32] = CRGB::White; FastLED.show();
  //leds[33] = CRGB::White; FastLED.show();
  leds[34] = CRGB::White; FastLED.show();

  //leds[36] = CRGB::White; FastLED.show();
  leds[37] = CRGB::White; FastLED.show();
  //leds[38] = CRGB::White; FastLED.show();

  //leds[40] = CRGB::White; FastLED.show();
  leds[41] = CRGB::White; FastLED.show();
  //leds[42] = CRGB::White; FastLED.show();

    //leds[71] = CRGB::White; FastLED.show();
  leds[72] = CRGB::White; FastLED.show();
  //leds[73] = CRGB::White; FastLED.show();

  //leds[75] = CRGB::White; FastLED.show();
  leds[76] = CRGB::White; FastLED.show();
  //leds[77] = CRGB::White; FastLED.show();


  //leds[80] = CRGB::White; FastLED.show();
  leds[81] = CRGB::White; FastLED.show();

  //leds[84] = CRGB::White; FastLED.show();
  leds[85] = CRGB::White; FastLED.show();
  //leds[86] = CRGB::White; FastLED.show();
}

void ZWANZIG()
{
  //leds[43] = CRGB::White; FastLED.show();
  leds[44] = CRGB::White; FastLED.show();
  //leds[45] = CRGB::White; FastLED.show();

  //leds[47] = CRGB::White; FastLED.show();
  leds[48] = CRGB::White; FastLED.show();
  //leds[49] = CRGB::White; FastLED.show();

  //leds[51] = CRGB::White; FastLED.show();
  leds[52] = CRGB::White; FastLED.show();
  //leds[53] = CRGB::White; FastLED.show();

  //leds[55] = CRGB::White; FastLED.show();
  leds[56] = CRGB::White; FastLED.show();
  //leds[57] = CRGB::White; FastLED.show();

  //leds[59] = CRGB::White; FastLED.show();
  leds[60] = CRGB::White; FastLED.show();
  //leds[61] = CRGB::White; FastLED.show();

  
  leds[64] = CRGB::White; FastLED.show();
  leds[65] = CRGB::White; FastLED.show();

  
  leds[67] = CRGB::White; FastLED.show();
  leds[68] = CRGB::White; FastLED.show();
  leds[69] = CRGB::White; FastLED.show();
}

void ZEHN()
{
  //leds[71] = CRGB::White; FastLED.show();
  leds[72] = CRGB::White; FastLED.show();
  //leds[73] = CRGB::White; FastLED.show();

  //leds[75] = CRGB::White; FastLED.show();
  leds[76] = CRGB::White; FastLED.show();
  //leds[77] = CRGB::White; FastLED.show();


  //leds[80] = CRGB::White; FastLED.show();
  leds[81] = CRGB::White; FastLED.show();

  //leds[84] = CRGB::White; FastLED.show();
  leds[85] = CRGB::White; FastLED.show();
  //leds[86] = CRGB::White; FastLED.show();
}

void DREI()
{
  //leds[88] = CRGB::White; FastLED.show();
  leds[89] = CRGB::White; FastLED.show();
  //leds[90] = CRGB::White; FastLED.show();

  //leds[92] = CRGB::White; FastLED.show();
  leds[93] = CRGB::White; FastLED.show();
  //leds[94] = CRGB::White; FastLED.show();


  //leds[96] = CRGB::White; FastLED.show();
  leds[97] = CRGB::White; FastLED.show();
  //leds[98] = CRGB::White; FastLED.show();
  
  leds[100] = CRGB::White; FastLED.show();
  //leds[101] = CRGB::White; FastLED.show();
  //leds[102] = CRGB::White; FastLED.show();
}

void VIERTEL()
{
  //leds[104] = CRGB::White; FastLED.show();
  leds[105] = CRGB::White; FastLED.show();
  //leds[106] = CRGB::White; FastLED.show();

  //leds[108] = CRGB::White; FastLED.show();
  leds[109] = CRGB::White; FastLED.show();
  //leds[110] = CRGB::White; FastLED.show();

  //leds[112] = CRGB::White; FastLED.show();
  leds[113] = CRGB::White; FastLED.show();
  //leds[114] = CRGB::White; FastLED.show();
  
  //leds[116] = CRGB::White; FastLED.show();
  leds[117] = CRGB::White; FastLED.show();
  //leds[118] = CRGB::White; FastLED.show();

  //leds[120] = CRGB::White; FastLED.show();
  leds[121] = CRGB::White; FastLED.show();
  //leds[122] = CRGB::White; FastLED.show();

  //leds[124] = CRGB::White; FastLED.show();
  leds[125] = CRGB::White; FastLED.show();
  //leds[125] = CRGB::White; FastLED.show();

  //leds[128] = CRGB::White; FastLED.show();
  leds[129] = CRGB::White; FastLED.show();
  //leds[130] = CRGB::White; FastLED.show();
}


void NACH()
{
  leds[133] = CRGB::White; FastLED.show();
  leds[134] = CRGB::White; FastLED.show();

  //leds[137] = CRGB::White; FastLED.show();
  leds[138] = CRGB::White; FastLED.show();
  //leds[139] = CRGB::White; FastLED.show();

  //leds[141] = CRGB::White; FastLED.show();
  leds[142] = CRGB::White; FastLED.show();
  
  //leds[145] = CRGB::White; FastLED.show();
  leds[146] = CRGB::White; FastLED.show();
  //leds[147] = CRGB::White; FastLED.show();
}


void VOR()
{
  //leds[165] = CRGB::White; FastLED.show();
  leds[166] = CRGB::White; FastLED.show();
  //leds[167] = CRGB::White; FastLED.show();
  
  leds[170] = CRGB::White; FastLED.show();
  //leds[171] = CRGB::White; FastLED.show();

  //leds[173] = CRGB::White; FastLED.show();
  leds[174] = CRGB::White; FastLED.show();
  //leds[175] = CRGB::White; FastLED.show();
}

void HALB()
{
  //leds[178] = CRGB::White; FastLED.show();
  leds[179] = CRGB::White; FastLED.show();
  //leds[180] = CRGB::White; FastLED.show();
  
  //leds[182] = CRGB::White; FastLED.show();
  leds[183] = CRGB::White; FastLED.show();
  //leds[184] = CRGB::White; FastLED.show();

  //leds[186] = CRGB::White; FastLED.show();
  leds[187] = CRGB::White; FastLED.show();
  //leds[188] = CRGB::White; FastLED.show();

  //leds[190] = CRGB::White; FastLED.show();
  leds[191] = CRGB::White; FastLED.show();
  //leds[192] = CRGB::White; FastLED.show();
}

void FUNF()
{
  //leds[206] = CRGB::White; FastLED.show();
  leds[207] = CRGB::White; FastLED.show();
  //leds[208] = CRGB::White; FastLED.show();
  
  //leds[210] = CRGB::White; FastLED.show();
  leds[211] = CRGB::White; FastLED.show();
  //leds[212] = CRGB::White; FastLED.show();
  
  //leds[214] = CRGB::White; FastLED.show();
  leds[215] = CRGB::White; FastLED.show();
  //leds[216] = CRGB::White; FastLED.show();

  leds[219] = CRGB::White; FastLED.show();
  //leds[220] = CRGB::White; FastLED.show();
}

void EINS()
{
  //leds[251] = CRGB::White; FastLED.show();
  leds[252] = CRGB::White; FastLED.show();

  //leds[255] = CRGB::White; FastLED.show();
  leds[256] = CRGB::White; FastLED.show();

  //leds[259] = CRGB::White; FastLED.show();
  leds[260] = CRGB::White; FastLED.show();

  //leds[263] = CRGB::White; FastLED.show();
  leds[264] = CRGB::White; FastLED.show();
}
