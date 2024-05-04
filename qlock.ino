#include <FastLED.h>
#include "Wire.h"
#define DS1307_I2C_ADDRESS 0x68  // This is the I2C address
// Arduino version compatibility Pre-Compiler Directives
#if defined(ARDUINO) && ARDUINO >= 100   // Arduino v1.0 and newer
  #define I2C_WRITE Wire.write 
  #define I2C_READ Wire.read
#else                                   // Arduino Prior to v1.0 
  #define I2C_WRITE Wire.send 
  #define I2C_READ Wire.receive
#endif
#define NUM_LEDS 449

CRGB leds[NUM_LEDS];

// Global Variables
int command = 0;       // This is the command char, in ascii form, sent from the serial port     
int i;
long previousMillis = 0;        // will store last time Temp was updated
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
byte test;
byte zero;
char  *Day[] = {"","Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
char  *Mon[] = {"","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

// Clock
int qs = 0; // Seconds
int qm = 0; // Minutes
int qh = 12; // Hours

bool showUhr = false; // Qlock bool
bool showNextHour = false;

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}
 
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}

// Gets the date and time from the ds1307 and prints result
void getDateDs1307()
{
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  I2C_WRITE(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
 
  // A few of these need masks because certain bits are control bits
  second     = bcdToDec(I2C_READ() & 0x7f);
  minute     = bcdToDec(I2C_READ());
  hour       = bcdToDec(I2C_READ() & 0x3f);  // Need to change this if 12 hour am/pm
  dayOfWeek  = bcdToDec(I2C_READ());
  dayOfMonth = bcdToDec(I2C_READ());
  month      = bcdToDec(I2C_READ());
  year       = bcdToDec(I2C_READ()); 
}
 

void setup() {
  // init LEDs
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
  Wire.begin();
  //Serial.begin(57600); 
  zero=0x00;
  // init pins
  delay(5000);
}

void loop() {
  // Display the Clock ***********************************************
  // Get time vars and convert them to mine
  getDateDs1307(); 
  qs = second; // Seconds
  qm = minute; // Minutes
  qh = hour;
  if(hour > 12)
  {
    qh = (hour - 12);
  }
  else
  {
    qh = hour; // Hours
  }
  //Serial.println(qs, DEC);
  //Serial.println(qm, DEC);
  //Serial.println(qh, DEC);



  showUhr = false; // Used to define if "Uhr" has to be shown
  FastLED.clear(); // Clear previous setting
  
  // Random show es-ist
  if(random(0,2))
  {
    ESIST();  
  }

  // If the hour is full, show "Uhr"
  if(qm >= 57 || qm < 3)
  {
    showUhr = true; 
  }
  else if(qm >= 3 && qm < 7)
  {
    FUNF_M();
    NACH();
  }
  else if(qm >= 7 && qm < 13)
  {
    ZEHN_M();
    NACH();
  }
  else if(qm >= 13 && qm < 17)
  {
    if(random(0,2)) { VIERTEL(); }
    else { FUNFZEHN(); }
    NACH();
  }
  else if(qm >= 17 && qm < 25)
  {
    ZWANZIG();
    NACH();
  }
  else if(qm >= 25 && qm < 37)
  {
    HALB();
    qh++;
    if(qh == 13) { qh = 1; }
  }
  else if(qm >= 37 && qm < 43)
  {
    ZWANZIG();
    VOR();
    qh++;
    if(qh == 13) { qh = 1; }
  }
  else if(qm >= 43 && qm < 47)
  {
    if(random(0,2)) { VIERTEL(); }
    else { FUNFZEHN(); } 
    VOR();
    qh++;
    if(qh == 13) { qh = 1; }
  }
  else if(qm >= 47 && qm < 53)
  {
    ZEHN_M();
    VOR();
    qh++;
    if(qh == 13) { qh = 1; }
  }
  else if(qm >= 53 && qm < 57)
  {
    FUNF_M();
    VOR();
    qh++;
    if(qh == 13) { qh = 1; }
  }

  // Show hour
  if(qh == 1) { EINS(); }
  else if(qh == 2) { ZWEI(); }
  else if(qh == 3) { DREI(); }
  else if(qh == 4) { VIER(); }
  else if(qh == 5) { FUNF(); }
  else if(qh == 6) { SECHS(); }
  else if(qh == 7) { SIEBEN(); }
  else if(qh == 8) { ACHT(); }
  else if(qh == 9) { NEUN(); }
  else if(qh == 10) { ZEHN(); }
  else if(qh == 11) { ELF(); }
  else if(qh == 12) { ZWOLF(); }

  if(showUhr)
  {
    UHR();
  } 
  
  delay(300000); // 5 min
}

// WORDS
void ESIST()
{
  leds[0] = CRGB::White; FastLED.show();
  leds[1] = CRGB::White; FastLED.show();
  leds[2] = CRGB::White; FastLED.show();

  leds[4] = CRGB::White; FastLED.show();
  leds[5] = CRGB::White; FastLED.show();


  leds[12] = CRGB::White; FastLED.show();
  leds[13] = CRGB::White; FastLED.show();

  leds[16] = CRGB::White; FastLED.show();
  leds[17] = CRGB::White; FastLED.show();

  leds[20] = CRGB::White; FastLED.show();
  leds[21] = CRGB::White; FastLED.show();
}

void FUNF_M() // _M for minutes
{
  leds[28] = CRGB::White; FastLED.show();
  leds[29] = CRGB::White; FastLED.show();

  leds[32] = CRGB::White; FastLED.show();
  leds[33] = CRGB::White; FastLED.show();
  leds[34] = CRGB::White; FastLED.show();

  leds[36] = CRGB::White; FastLED.show();
  leds[37] = CRGB::White; FastLED.show();
  leds[38] = CRGB::White; FastLED.show();

  leds[40] = CRGB::White; FastLED.show();
  leds[41] = CRGB::White; FastLED.show();
  leds[42] = CRGB::White; FastLED.show();
}

void FUNFZEHN()
{
  leds[28] = CRGB::White; FastLED.show();
  leds[29] = CRGB::White; FastLED.show();

  leds[32] = CRGB::White; FastLED.show();
  leds[33] = CRGB::White; FastLED.show();
  leds[34] = CRGB::White; FastLED.show();

  leds[36] = CRGB::White; FastLED.show();
  leds[37] = CRGB::White; FastLED.show();
  leds[38] = CRGB::White; FastLED.show();

  leds[41] = CRGB::White; FastLED.show();
  leds[42] = CRGB::White; FastLED.show();
  leds[43] = CRGB::White; FastLED.show();

  leds[71] = CRGB::White; FastLED.show();
  leds[72] = CRGB::White; FastLED.show();
  leds[73] = CRGB::White; FastLED.show();

  leds[75] = CRGB::White; FastLED.show();
  leds[76] = CRGB::White; FastLED.show();
  leds[77] = CRGB::White; FastLED.show();


  leds[80] = CRGB::White; FastLED.show();
  leds[81] = CRGB::White; FastLED.show();

  leds[84] = CRGB::White; FastLED.show();
  leds[85] = CRGB::White; FastLED.show();
  leds[86] = CRGB::White; FastLED.show();
}

void ZWANZIG()
{
  leds[43] = CRGB::White; FastLED.show();
  leds[44] = CRGB::White; FastLED.show();
  leds[45] = CRGB::White; FastLED.show();

  leds[47] = CRGB::White; FastLED.show();
  leds[48] = CRGB::White; FastLED.show();
  leds[49] = CRGB::White; FastLED.show();

  leds[51] = CRGB::White; FastLED.show();
  leds[52] = CRGB::White; FastLED.show();
  leds[53] = CRGB::White; FastLED.show();

  leds[55] = CRGB::White; FastLED.show();
  leds[56] = CRGB::White; FastLED.show();
  leds[57] = CRGB::White; FastLED.show();

  leds[59] = CRGB::White; FastLED.show();
  leds[60] = CRGB::White; FastLED.show();
  leds[61] = CRGB::White; FastLED.show();

  
  leds[64] = CRGB::White; FastLED.show();
  leds[65] = CRGB::White; FastLED.show();

  
  leds[67] = CRGB::White; FastLED.show();
  leds[68] = CRGB::White; FastLED.show();
  leds[69] = CRGB::White; FastLED.show();
}

void ZEHN_M() // for minutes
{
  leds[71] = CRGB::White; FastLED.show();
  leds[72] = CRGB::White; FastLED.show();
  leds[73] = CRGB::White; FastLED.show();

  leds[75] = CRGB::White; FastLED.show();
  leds[76] = CRGB::White; FastLED.show();
  leds[77] = CRGB::White; FastLED.show();


  leds[80] = CRGB::White; FastLED.show();
  leds[81] = CRGB::White; FastLED.show();

  leds[84] = CRGB::White; FastLED.show();
  leds[85] = CRGB::White; FastLED.show();
  leds[86] = CRGB::White; FastLED.show();
}

void DREI()
{
  leds[269] = CRGB::White; FastLED.show();
  leds[270] = CRGB::White; FastLED.show();

  leds[273] = CRGB::White; FastLED.show();
  leds[274] = CRGB::White; FastLED.show();
  
  leds[277] = CRGB::White; FastLED.show();
  leds[278] = CRGB::White; FastLED.show();

  leds[281] = CRGB::White; FastLED.show();
  leds[282] = CRGB::White; FastLED.show();
}

void VIERTEL()
{
  leds[106] = CRGB::White; FastLED.show();

  leds[108] = CRGB::White; FastLED.show();
  leds[109] = CRGB::White; FastLED.show();
  leds[110] = CRGB::White; FastLED.show();

  leds[112] = CRGB::White; FastLED.show();
  leds[113] = CRGB::White; FastLED.show();
  leds[114] = CRGB::White; FastLED.show();
  
  leds[116] = CRGB::White; FastLED.show();
  leds[117] = CRGB::White; FastLED.show();
  leds[118] = CRGB::White; FastLED.show();

  leds[120] = CRGB::White; FastLED.show();
  leds[121] = CRGB::White; FastLED.show();
  leds[122] = CRGB::White; FastLED.show();

  leds[124] = CRGB::White; FastLED.show();
  leds[125] = CRGB::White; FastLED.show();
  leds[125] = CRGB::White; FastLED.show();

  leds[128] = CRGB::White; FastLED.show();
  leds[129] = CRGB::White; FastLED.show();
  leds[130] = CRGB::White; FastLED.show();

  leds[131] = CRGB::White; FastLED.show();
  leds[132] = CRGB::White; FastLED.show();
}


void NACH()
{
  leds[133] = CRGB::White; FastLED.show();
  leds[134] = CRGB::White; FastLED.show();

  leds[137] = CRGB::White; FastLED.show();
  leds[138] = CRGB::White; FastLED.show();
  leds[139] = CRGB::White; FastLED.show();

  leds[141] = CRGB::White; FastLED.show();
  leds[142] = CRGB::White; FastLED.show();
  
  leds[145] = CRGB::White; FastLED.show();
  leds[146] = CRGB::White; FastLED.show();
  leds[147] = CRGB::White; FastLED.show();
}


void VOR()
{
  leds[168] = CRGB::White; FastLED.show();
  leds[169] = CRGB::White; FastLED.show();
  leds[170] = CRGB::White; FastLED.show();

  leds[172] = CRGB::White; FastLED.show();
  leds[173] = CRGB::White; FastLED.show();
  leds[174] = CRGB::White; FastLED.show();

  leds[175] = CRGB::White; FastLED.show();
  leds[176] = CRGB::White; FastLED.show();
  leds[177] = CRGB::White; FastLED.show();
}

void HALB()
{
  leds[179] = CRGB::White; FastLED.show();
  leds[180] = CRGB::White; FastLED.show();
  leds[181] = CRGB::White; FastLED.show();
  
  leds[182] = CRGB::White; FastLED.show();
  leds[183] = CRGB::White; FastLED.show();
  leds[184] = CRGB::White; FastLED.show();

  leds[186] = CRGB::White; FastLED.show();
  leds[187] = CRGB::White; FastLED.show();
  leds[188] = CRGB::White; FastLED.show();

  leds[191] = CRGB::White; FastLED.show();
  leds[192] = CRGB::White; FastLED.show();
  leds[193] = CRGB::White; FastLED.show();
}

void FUNF()
{
  leds[210] = CRGB::White; FastLED.show();
  leds[211] = CRGB::White; FastLED.show();
  leds[212] = CRGB::White; FastLED.show();

  leds[213] = CRGB::White; FastLED.show();
  leds[214] = CRGB::White; FastLED.show();

  leds[215] = CRGB::White; FastLED.show();
  leds[216] = CRGB::White; FastLED.show();

  leds[217] = CRGB::White; FastLED.show();
  leds[218] = CRGB::White; FastLED.show();

  leds[220] = CRGB::White; FastLED.show();
  leds[221] = CRGB::White; FastLED.show();
  leds[222] = CRGB::White; FastLED.show();
}

void EINS()
{
  leds[253] = CRGB::White; FastLED.show();
  leds[254] = CRGB::White; FastLED.show();

  leds[256] = CRGB::White; FastLED.show();
  leds[257] = CRGB::White; FastLED.show();

  leds[260] = CRGB::White; FastLED.show();
  leds[261] = CRGB::White; FastLED.show();

  leds[264] = CRGB::White; FastLED.show();
  leds[265] = CRGB::White; FastLED.show();
}

void SECHS()
{
  leds[339] = CRGB::White; FastLED.show();
  leds[340] = CRGB::White; FastLED.show();

  leds[341] = CRGB::White; FastLED.show();
  leds[342] = CRGB::White; FastLED.show();

  leds[345] = CRGB::White; FastLED.show();
  leds[346] = CRGB::White; FastLED.show();

  leds[349] = CRGB::White; FastLED.show();
  leds[350] = CRGB::White; FastLED.show();

  leds[354] = CRGB::White; FastLED.show();
  leds[355] = CRGB::White; FastLED.show();
}

void UHR()
{
  leds[405] = CRGB::White; FastLED.show();
  leds[406] = CRGB::White; FastLED.show();

  leds[408] = CRGB::White; FastLED.show();
  leds[409] = CRGB::White; FastLED.show();

  leds[411] = CRGB::White; FastLED.show();
  leds[412] = CRGB::White; FastLED.show();
  leds[413] = CRGB::White; FastLED.show();
}

void ZWEI()
{
  leds[225] = CRGB::White; FastLED.show();
  leds[226] = CRGB::White; FastLED.show();

  leds[228] = CRGB::White; FastLED.show();
  leds[229] = CRGB::White; FastLED.show();

  leds[231] = CRGB::White; FastLED.show();
  leds[232] = CRGB::White; FastLED.show();
  leds[233] = CRGB::White; FastLED.show();

  leds[235] = CRGB::White; FastLED.show();
  leds[236] = CRGB::White; FastLED.show();
  leds[237] = CRGB::White; FastLED.show();
}

void SIEBEN()
{
  leds[360] = CRGB::White; FastLED.show();
  leds[361] = CRGB::White; FastLED.show();
  leds[362] = CRGB::White; FastLED.show();

  leds[363] = CRGB::White; FastLED.show();
  leds[364] = CRGB::White; FastLED.show();
  leds[365] = CRGB::White; FastLED.show();

  leds[367] = CRGB::White; FastLED.show();
  leds[368] = CRGB::White; FastLED.show();
  leds[369] = CRGB::White; FastLED.show();

  leds[371] = CRGB::White; FastLED.show();
  leds[372] = CRGB::White; FastLED.show();
  leds[373] = CRGB::White; FastLED.show();

  leds[375] = CRGB::White; FastLED.show();
  leds[376] = CRGB::White; FastLED.show();
  leds[377] = CRGB::White; FastLED.show();

  leds[380] = CRGB::White; FastLED.show();
  leds[381] = CRGB::White; FastLED.show();
  leds[382] = CRGB::White; FastLED.show();
}

void ACHT()
{
  leds[314] = CRGB::White; FastLED.show();
  leds[315] = CRGB::White; FastLED.show();

  leds[317] = CRGB::White; FastLED.show();
  leds[318] = CRGB::White; FastLED.show();

  leds[320] = CRGB::White; FastLED.show();
  leds[321] = CRGB::White; FastLED.show();
  leds[322] = CRGB::White; FastLED.show();
  leds[323] = CRGB::White; FastLED.show();

  leds[325] = CRGB::White; FastLED.show();
  leds[326] = CRGB::White; FastLED.show();
  leds[327] = CRGB::White; FastLED.show();
}

void NEUN()
{
  leds[420] = CRGB::White; FastLED.show();
  leds[421] = CRGB::White; FastLED.show();
  leds[422] = CRGB::White; FastLED.show();

  leds[424] = CRGB::White; FastLED.show();
  leds[425] = CRGB::White; FastLED.show();
  leds[426] = CRGB::White; FastLED.show();

  leds[427] = CRGB::White; FastLED.show();
  leds[428] = CRGB::White; FastLED.show();
  leds[429] = CRGB::White; FastLED.show();

  leds[432] = CRGB::White; FastLED.show();
  leds[433] = CRGB::White; FastLED.show();
  leds[434] = CRGB::White; FastLED.show();
}

void ELF()
{
  leds[201] = CRGB::White; FastLED.show();
  leds[202] = CRGB::White; FastLED.show();
  leds[203] = CRGB::White; FastLED.show();

  leds[205] = CRGB::White; FastLED.show();
  leds[206] = CRGB::White; FastLED.show();
  leds[207] = CRGB::White; FastLED.show();

  leds[208] = CRGB::White; FastLED.show();
  leds[209] = CRGB::White; FastLED.show();
  leds[210] = CRGB::White; FastLED.show();
}

void ZWOLF()
{
  leds[385] = CRGB::White; FastLED.show();
  leds[386] = CRGB::White; FastLED.show();
  leds[387] = CRGB::White; FastLED.show();

  leds[390] = CRGB::White; FastLED.show();
  leds[391] = CRGB::White; FastLED.show();
  leds[392] = CRGB::White; FastLED.show();
  
  leds[394] = CRGB::White; FastLED.show();
  leds[395] = CRGB::White; FastLED.show();
  leds[396] = CRGB::White; FastLED.show();

  leds[397] = CRGB::White; FastLED.show();
  leds[398] = CRGB::White; FastLED.show();
  leds[399] = CRGB::White; FastLED.show();

  leds[401] = CRGB::White; FastLED.show();
  leds[402] = CRGB::White; FastLED.show();
  leds[403] = CRGB::White; FastLED.show();
}

void VIER()
{
  leds[299] = CRGB::White; FastLED.show();
  leds[300] = CRGB::White; FastLED.show();
  leds[301] = CRGB::White; FastLED.show();

  leds[303] = CRGB::White; FastLED.show();
  leds[304] = CRGB::White; FastLED.show();
  leds[305] = CRGB::White; FastLED.show();
  
  leds[307] = CRGB::White; FastLED.show();
  leds[308] = CRGB::White; FastLED.show();
  leds[309] = CRGB::White; FastLED.show();

  leds[311] = CRGB::White; FastLED.show();
  leds[312] = CRGB::White; FastLED.show();
  leds[313] = CRGB::White; FastLED.show();
}

void ZEHN()
{
  leds[432] = CRGB::White; FastLED.show();
  leds[433] = CRGB::White; FastLED.show();
  leds[434] = CRGB::White; FastLED.show();

  leds[436] = CRGB::White; FastLED.show();
  leds[437] = CRGB::White; FastLED.show();
  leds[438] = CRGB::White; FastLED.show();

  leds[440] = CRGB::White; FastLED.show();
  leds[441] = CRGB::White; FastLED.show();
  leds[442] = CRGB::White; FastLED.show();

  leds[444] = CRGB::White; FastLED.show();
  leds[445] = CRGB::White; FastLED.show();
  leds[446] = CRGB::White; FastLED.show();

  leds[447] = CRGB::White; FastLED.show();
  leds[448] = CRGB::White; FastLED.show();
  leds[449] = CRGB::White; FastLED.show();
}
