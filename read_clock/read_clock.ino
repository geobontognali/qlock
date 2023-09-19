/* RTC Control v1.00 
 * by <http://www.combustory.com> John Vaughters
 *
 * THIS CODE IS FREE FOR ANYTHING  - There is no Rocket Science here. No need to create some long GPL statement.
 *
 * Credit to:
 * Maurice Ribble - http://www.glacialwanderer.com/hobbyrobotics for RTC DS1307 code
 * BB Riley - Underhill Center, VT  <brianbr@wulfden.org> For simplification of the Day of Week and month
 *                                                        and updating to Arduino 1.0 
 * peep rada - from Arduino Forum - Found that only 32 registers per I2C connection was possible 
 * 
 * With this code you can set the date/time, retreive the date/time and use the extra memory of an RTC DS1307 chip.  
 * The program also sets all the extra memory space to 0xff.
 * Serial Communication method with the Arduino that utilizes a leading CHAR for each command described below. 
 *
 * Commands:
 * T(00-59)(00-59)(00-23)(1-7)(01-31)(01-12)(00-99) - T(sec)(min)(hour)(dayOfWeek)(dayOfMonth)(month)(year) -
 * T - Sets the date of the RTC DS1307 Chip. 
 * Example to set the time for 25-Jan-2012 @ 19:57:11 for the 4 day of the week, use this command - T1157194250112
 * Q(1-2) - (Q1) Memory initialization  (Q2) RTC - Memory Dump  
 * R - Read/display the time, day and date
 *
 * ---------------------------------------------------------
 * Notes:
 * Version 1.0
 *    Moving this code to Version 1.0 because this code has been updated to Arduino v1.0 and the features have
 *    been well tested and improved in a collaborative effort.
 *    - Fixed the issue of not being able to access all the registers - JWV
 *    - Added initialization for all non-time registers - JWV
 *    - Added Dump of all 64 registers - JWV
 *    - Some Date/Time reformatting and cleanup of display, added Day/Month texts - BBR
 *    - Made compatible with Arduino 1.0 - BBR
 *    - Added Rr command for reading date/time - BBR
 *    - Made commands case insensitive - BBR
 *    - Create #define varibles to support pre Arduino v1.0 - JWV
 * Version 0.01
 *    Inital code with basics of setting time and the first 37 registers and dumping the first 32 registers. 
 *    The code was based on Maurice Ribble's original code.
 * 
 */
 
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
// Global Variables
int command = 0;       // This is the command char, in ascii form, sent from the serial port     
int i;
long previousMillis = 0;        // will store last time Temp was updated
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
byte test;
byte zero;
char  *Day[] = {"","Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
char  *Mon[] = {"","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
 
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
  Wire.begin();
  Serial.begin(57600); 
  zero=0x00;
}
 
void loop() 
{
  getDateDs1307();
    Serial.print(hour, DEC);
    Serial.print(":");
    Serial.print(minute, DEC);
    Serial.print(":");
    Serial.print(second, DEC);
    Serial.print("  ");
    Serial.print(Day[dayOfWeek]);
    Serial.print(", ");
    Serial.print(dayOfMonth, DEC);
    Serial.print(" ");
    Serial.print(Mon[month]);
    Serial.print(" 20");
    Serial.println(year, DEC);

    delay(3000);
}
//*****************************************************The End***********************