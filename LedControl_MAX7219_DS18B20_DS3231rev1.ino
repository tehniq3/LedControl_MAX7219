// based on an orginal sketch by Arduino forum member "danigom"

// http://forum.arduino.cc/index.php?action=profile;u=188950

// http://tronixstuff.com/2013/10/11/tutorial-arduino-max7219-led-display-driver-ic/

// Nicu FLORICA change sketch for made Thermometer with DS18B20

// see more at http://www.tehnic.go.ro &

// http://www.arduinotehniq.com/

// The way PROGMEM is used has been changed.
//const  prog_uchar ---> const unsigned char


// for DS18B20 - http://arduinoprojects.ru/2014/08/%D0%BF%D1%80%D0%BE%D1%81%D1%82%D0%BE%D0%B9-%D1%82%D0%B5%D1%80%D0%BC%D0%BE%D1%81%D1%82%D0%B0%D1%82-%D0%BD%D0%B0-arduino-%D0%B8-%D1%86%D0%B8%D1%84%D1%80%D0%BE%D0%B2%D0%BE%D0%BC-%D1%82%D0%B5%D1%80%D0%BC/

#include <OneWire.h>

#include <DallasTemperature.h>

#define ONE_WIRE_BUS 13

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);



#include <avr/pgmspace.h>

#include <LedControl.h>

 

const int numDevices = 4;      // number of MAX7219s used

const long scrollDelay = 50;   // adjust scrolling speed

unsigned long bufferLong [14] = {0}; 

LedControl lc=LedControl(12,11,10,numDevices);



#include <Wire.h>

#include "RTClib.h" // from https://github.com/adafruit/RTClib

//#include <Encoder.h> // from http://www.pjrc.com/teensy/td_libs_Encoder.html

RTC_DS1307 RTC; // Tells the RTC library that we're using a DS1307 RTC

 

unsigned char logo[] PROGMEM ={

    "  Clock & Termomether on 32x8 led matrix with MAX7219 by niq_ro     \0"};



unsigned char guma[] PROGMEM ={

    "           \0"};

unsigned char temperatura[] PROGMEM ={

    "  temperatura: \0"};

unsigned char data[] PROGMEM ={

    "  data: \0"};

unsigned char ceas[] PROGMEM ={

    "  ceas: \0"};



  

void setup(){

    for (int x=0; x<numDevices; x++){

        lc.shutdown(x,false);       //The MAX72XX is in power-saving mode on startup

        lc.setIntensity(x,8);       // Set the brightness to default value

        lc.clearDisplay(x);         // and clear the display

    }

// for DS18B20 sensor

sensors.begin(); 



 // 11 bit resolution by default (9 - low, 10, 11 or 12 - best)

  // Note the programmer is responsible for the right delay

  // we could do something usefull here instead of the delay

  int resolution = 11;

  sensors.setResolution(resolution);

  delay(750/ (1 << (12-resolution)));

    

  Serial.begin(9600);  

  Wire.begin();

  RTC.begin();

  if (! RTC.isrunning()) {

    //Serial.println("RTC is NOT running!");

    // following line sets the RTC to the date & time this sketch was compiled

    RTC.adjust(DateTime(__DATE__, __TIME__));

  }

 //  RTC.adjust(DateTime(__DATE__, __TIME__));

}

 

 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 

unsigned char font5x7 [] PROGMEM = {      //Numeric Font Matrix (Arranged as 7x font data + 1x kerning data)

    B00000000,  //Space (Char 0x20)

    B00000000,

    B00000000,

    B00000000,

    B00000000,

    B00000000,

    B00000000,

    6,

 

    B10000000,  //!

    B10000000,

    B10000000,

    B10000000,

    B00000000,

    B00000000,

    B10000000,

    2,

 

    B10100000,  //"

    B10100000,

    B10100000,

    B00000000,

    B00000000,

    B00000000,

    B00000000,

    4,

 

    B01010000,  //#

    B01010000,

    B11111000,

    B01010000,

    B11111000,

    B01010000,

    B01010000,

    6,

 

    B00100000,  //$

    B01111000,

    B10100000,

    B01110000,

    B00101000,

    B11110000,

    B00100000,

    6,

 

    B11000000,  //%

    B11001000,

    B00010000,

    B00100000,

    B01000000,

    B10011000,

    B00011000,

    6,

 

    B01100000,  //&

    B10010000,

    B10100000,

    B01000000,

    B10101000,

    B10010000,

    B01101000,

    6,

 

    B11000000,  //'

    B01000000,

    B10000000,

    B00000000,

    B00000000,

    B00000000,

    B00000000,

    3,

 

    B00100000,  //(

    B01000000,

    B10000000,

    B10000000,

    B10000000,

    B01000000,

    B00100000,

    4,

 

    B10000000,  //)

    B01000000,

    B00100000,

    B00100000,

    B00100000,

    B01000000,

    B10000000,

    4,

 

    B00000000,  //*

    B00100000,

    B10101000,

    B01110000,

    B10101000,

    B00100000,

    B00000000,

    6,

 

    B00000000,  //+

    B00100000,

    B00100000,

    B11111000,

    B00100000,

    B00100000,

    B00000000,

    6,

 

    B00000000,  //,

    B00000000,

    B00000000,

    B00000000,

    B11000000,

    B01000000,

    B10000000,

    3,

 

    B00000000,  //-

    B00000000,

    B11111000,

    B00000000,

    B00000000,

    B00000000,

    B00000000,

    6,

 

    B00000000,  //.

    B00000000,

    B00000000,

    B00000000,

    B00000000,

    B11000000,

    B11000000,

    3,

 

    B00000000,  ///

    B00001000,

    B00010000,

    B00100000,

    B01000000,

    B10000000,

    B00000000,

    6,

 

    B01110000,  //0

    B10001000,

    B10011000,

    B10101000,

    B11001000,

    B10001000,

    B01110000,

    6,

 

    B01000000,  //1

    B11000000,

    B01000000,

    B01000000,

    B01000000,

    B01000000,

    B11100000,

    4,

 

    B01110000,  //2

    B10001000,

    B00001000,

    B00010000,

    B00100000,

    B01000000,

    B11111000,

    6,

 

    B11111000,  //3

    B00010000,

    B00100000,

    B00010000,

    B00001000,

    B10001000,

    B01110000,

    6,

 

    B00010000,  //4

    B00110000,

    B01010000,

    B10010000,

    B11111000,

    B00010000,

    B00010000,

    6,

 

    B11111000,  //5

    B10000000,

    B11110000,

    B00001000,

    B00001000,

    B10001000,

    B01110000,

    6,

 

    B00110000,  //6

    B01000000,

    B10000000,

    B11110000,

    B10001000,

    B10001000,

    B01110000,

    6,

 

    B11111000,  //7

    B10001000,

    B00001000,

    B00010000,

    B00100000,

    B00100000,

    B00100000,

    6,

 

    B01110000,  //8

    B10001000,

    B10001000,

    B01110000,

    B10001000,

    B10001000,

    B01110000,

    6,

 

    B01110000,  //9

    B10001000,

    B10001000,

    B01111000,

    B00001000,

    B00010000,

    B01100000,

    6,

 

    B00000000,  //:

    B11000000,

    B11000000,

    B00000000,

    B11000000,

    B11000000,

    B00000000,

    3,

 

    B00000000,  //;

    B11000000,

    B11000000,

    B00000000,

    B11000000,

    B01000000,

    B10000000,

    3,

 

    B00010000,  //<

    B00100000,

    B01000000,

    B10000000,

    B01000000,

    B00100000,

    B00010000,

    5,

 

    B00000000,  //=

    B00000000,

    B11111000,

    B00000000,

    B11111000,

    B00000000,

    B00000000,

    6,

 

    B10000000,  //>

    B01000000,

    B00100000,

    B00010000,

    B00100000,

    B01000000,

    B10000000,

    5,

 

    B01110000,  //?

    B10001000,

    B00001000,

    B00010000,

    B00100000,

    B00000000,

    B00100000,

    6,

 

    B01110000,  //@

    B10001000,

    B00001000,

    B01101000,

    B10101000,

    B10101000,

    B01110000,

    6,

 

    B01110000,  //A

    B10001000,

    B10001000,

    B10001000,

    B11111000,

    B10001000,

    B10001000,

    6,

 

    B11110000,  //B

    B10001000,

    B10001000,

    B11110000,

    B10001000,

    B10001000,

    B11110000,

    6,

 

    B01110000,  //C

    B10001000,

    B10000000,

    B10000000,

    B10000000,

    B10001000,

    B01110000,

    6,

 

    B11100000,  //D

    B10010000,

    B10001000,

    B10001000,

    B10001000,

    B10010000,

    B11100000,

    6,

 

    B11111000,  //E

    B10000000,

    B10000000,

    B11110000,

    B10000000,

    B10000000,

    B11111000,

    6,

 

    B11111000,  //F

    B10000000,

    B10000000,

    B11110000,

    B10000000,

    B10000000,

    B10000000,

    6,

 

    B01110000,  //G

    B10001000,

    B10000000,

    B10111000,

    B10001000,

    B10001000,

    B01111000,

    6,

 

    B10001000,  //H

    B10001000,

    B10001000,

    B11111000,

    B10001000,

    B10001000,

    B10001000,

    6,

 

    B11100000,  //I

    B01000000,

    B01000000,

    B01000000,

    B01000000,

    B01000000,

    B11100000,

    4,

 

    B00111000,  //J

    B00010000,

    B00010000,

    B00010000,

    B00010000,

    B10010000,

    B01100000,

    6,

 

    B10001000,  //K

    B10010000,

    B10100000,

    B11000000,

    B10100000,

    B10010000,

    B10001000,

    6,

 

    B10000000,  //L

    B10000000,

    B10000000,

    B10000000,

    B10000000,

    B10000000,

    B11111000,

    6,

 

    B10001000,  //M

    B11011000,

    B10101000,

    B10101000,

    B10001000,

    B10001000,

    B10001000,

    6,

 

    B10001000,  //N

    B10001000,

    B11001000,

    B10101000,

    B10011000,

    B10001000,

    B10001000,

    6,

 

    B01110000,  //O

    B10001000,

    B10001000,

    B10001000,

    B10001000,

    B10001000,

    B01110000,

    6,

 

    B11110000,  //P

    B10001000,

    B10001000,

    B11110000,

    B10000000,

    B10000000,

    B10000000,

    6,

 

    B01110000,  //Q

    B10001000,

    B10001000,

    B10001000,

    B10101000,

    B10010000,

    B01101000,

    6,

 

    B11110000,  //R

    B10001000,

    B10001000,

    B11110000,

    B10100000,

    B10010000,

    B10001000,

    6,

 

    B01111000,  //S

    B10000000,

    B10000000,

    B01110000,

    B00001000,

    B00001000,

    B11110000,

    6,

 

    B11111000,  //T

    B00100000,

    B00100000,

    B00100000,

    B00100000,

    B00100000,

    B00100000,

    6,

 

    B10001000,  //U

    B10001000,

    B10001000,

    B10001000,

    B10001000,

    B10001000,

    B01110000,

    6,

 

    B10001000,  //V

    B10001000,

    B10001000,

    B10001000,

    B10001000,

    B01010000,

    B00100000,

    6,

 

    B10001000,  //W

    B10001000,

    B10001000,

    B10101000,

    B10101000,

    B10101000,

    B01010000,

    6,

 

    B10001000,  //X

    B10001000,

    B01010000,

    B00100000,

    B01010000,

    B10001000,

    B10001000,

    6,

 

    B10001000,  //Y

    B10001000,

    B10001000,

    B01010000,

    B00100000,

    B00100000,

    B00100000,

    6,

 

    B11111000,  //Z

    B00001000,

    B00010000,

    B00100000,

    B01000000,

    B10000000,

    B11111000,

    6,

 

    B11100000,  //[

    B10000000,

    B10000000,

    B10000000,

    B10000000,

    B10000000,

    B11100000,

    4,

 

    B00000000,  //(Backward Slash)

    B10000000,

    B01000000,

    B00100000,

    B00010000,

    B00001000,

    B00000000,

    6,

 

    B11100000,  //]

    B00100000,

    B00100000,

    B00100000,

    B00100000,

    B00100000,

    B11100000,

    4,

 

    B00100000,  //^

    B01010000,

    B10001000,

    B00000000,

    B00000000,

    B00000000,

    B00000000,

    6,

 

    B00000000,  //_

    B00000000,

    B00000000,

    B00000000,

    B00000000,

    B00000000,

    B11111000,

    6,

 

    B10000000,  //`

    B01000000,

    B00100000,

    B00000000,

    B00000000,

    B00000000,

    B00000000,

    4,

 

    B00000000,  //a

    B00000000,

    B01110000,

    B00001000,

    B01111000,

    B10001000,

    B01111000,

    6,

 

    B10000000,  //b

    B10000000,

    B10110000,

    B11001000,

    B10001000,

    B10001000,

    B11110000,

    6,

 

    B00000000,  //c

    B00000000,

    B01110000,

    B10001000,

    B10000000,

    B10001000,

    B01110000,

    6,

 

    B00001000,  //d

    B00001000,

    B01101000,

    B10011000,

    B10001000,

    B10001000,

    B01111000,

    6,

 

    B00000000,  //e

    B00000000,

    B01110000,

    B10001000,

    B11111000,

    B10000000,

    B01110000,

    6,

 

    B00110000,  //f

    B01001000,

    B01000000,

    B11100000,

    B01000000,

    B01000000,

    B01000000,

    6,

 

    B00000000,  //g

    B01111000,

    B10001000,

    B10001000,

    B01111000,

    B00001000,

    B01110000,

    6,

 

    B10000000,  //h

    B10000000,

    B10110000,

    B11001000,

    B10001000,

    B10001000,

    B10001000,

    6,

 

    B01000000,  //i

    B00000000,

    B11000000,

    B01000000,

    B01000000,

    B01000000,

    B11100000,

    4,

 

    B00010000,  //j

    B00000000,

    B00110000,

    B00010000,

    B00010000,

    B10010000,

    B01100000,

    5,

 

    B10000000,  //k

    B10000000,

    B10010000,

    B10100000,

    B11000000,

    B10100000,

    B10010000,

    5,

 

    B11000000,  //l

    B01000000,

    B01000000,

    B01000000,

    B01000000,

    B01000000,

    B11100000,

    4,

 

    B00000000,  //m

    B00000000,

    B11010000,

    B10101000,

    B10101000,

    B10001000,

    B10001000,

    6,

 

    B00000000,  //n

    B00000000,

    B10110000,

    B11001000,

    B10001000,

    B10001000,

    B10001000,

    6,

 

    B00000000,  //o

    B00000000,

    B01110000,

    B10001000,

    B10001000,

    B10001000,

    B01110000,

    6,

 

    B00000000,  //p

    B00000000,

    B11110000,

    B10001000,

    B11110000,

    B10000000,

    B10000000,

    6,

 

    B00000000,  //q

    B00000000,

    B01101000,

    B10011000,

    B01111000,

    B00001000,

    B00001000,

    6,

 

    B00000000,  //r

    B00000000,

    B10110000,

    B11001000,

    B10000000,

    B10000000,

    B10000000,

    6,

 

    B00000000,  //s

    B00000000,

    B01110000,

    B10000000,

    B01110000,

    B00001000,

    B11110000,

    6,

 

    B01000000,  //t

    B01000000,

    B11100000,

    B01000000,

    B01000000,

    B01001000,

    B00110000,

    6,

 

    B00000000,  //u

    B00000000,

    B10001000,

    B10001000,

    B10001000,

    B10011000,

    B01101000,

    6,

 

    B00000000,  //v

    B00000000,

    B10001000,

    B10001000,

    B10001000,

    B01010000,

    B00100000,

    6,

 

    B00000000,  //w

    B00000000,

    B10001000,

    B10101000,

    B10101000,

    B10101000,

    B01010000,

    6,

 

    B00000000,  //x

    B00000000,

    B10001000,

    B01010000,

    B00100000,

    B01010000,

    B10001000,

    6,

 

    B00000000,  //y

    B00000000,

    B10001000,

    B10001000,

    B01111000,

    B00001000,

    B01110000,

    6,

 

    B00000000,  //z

    B00000000,

    B11111000,

    B00010000,

    B00100000,

    B01000000,

    B11111000,

    6,

 

    B00100000,  //{

    B01000000,

    B01000000,

    B10000000,

    B01000000,

    B01000000,

    B00100000,

    4,

 

    B10000000,  //|

    B10000000,

    B10000000,

    B10000000,

    B10000000,

    B10000000,

    B10000000,

    2,

 

    B10000000,  //}

    B01000000,

    B01000000,

    B00100000,

    B01000000,

    B01000000,

    B10000000,

    4,

 

    B00000000,  //~

    B00000000,

    B00000000,

    B01101000,

    B10010000,

    B00000000,

    B00000000,

    6,

 

    B01100000,  // (Char 0x7F)

    B10010000,

    B10010000,

    B01100000,

    B00000000,

    B00000000,

    B00000000,

    5

 };

 

void scrollFont() {

    for (int counter=0x20;counter<0x80;counter++){

        loadBufferLong(counter);

        delay(500);

    }

}

 

// Scroll Message

void scrollMessage(unsigned char * messageString) {

    int counter = 0;

    int myChar=0;

    do {

        // read back a char 

        myChar =  pgm_read_byte_near(messageString + counter); 

        if (myChar != 0){

            loadBufferLong(myChar);

        }

        counter++;

    } 

    while (myChar != 0);

}

// Load character into scroll buffer

void loadBufferLong(int ascii){

    if (ascii >= 0x20 && ascii <=0x7f){

        for (int a=0;a<7;a++){                      // Loop 7 times for a 5x7 font

            unsigned long c = pgm_read_byte_near(font5x7 + ((ascii - 0x20) * 8) + a);     // Index into character table to get row data

            unsigned long x = bufferLong [a*2];     // Load current scroll buffer

            x = x | c;                              // OR the new character onto end of current

            bufferLong [a*2] = x;                   // Store in buffer

        }

        byte count = pgm_read_byte_near(font5x7 +((ascii - 0x20) * 8) + 7);     // Index into character table for kerning data

        for (byte x=0; x<count;x++){

            rotateBufferLong();

            printBufferLong();

            delay(scrollDelay);

        }

    }

}

// Rotate the buffer

void rotateBufferLong(){

    for (int a=0;a<7;a++){                      // Loop 7 times for a 5x7 font

        unsigned long x = bufferLong [a*2];     // Get low buffer entry

        byte b = bitRead(x,31);                 // Copy high order bit that gets lost in rotation

        x = x<<1;                               // Rotate left one bit

        bufferLong [a*2] = x;                   // Store new low buffer

        x = bufferLong [a*2+1];                 // Get high buffer entry

        x = x<<1;                               // Rotate left one bit

        bitWrite(x,0,b);                        // Store saved bit

        bufferLong [a*2+1] = x;                 // Store new high buffer

    }

}  

// Display Buffer on LED matrix

void printBufferLong(){

  for (int a=0;a<7;a++){                    // Loop 7 times for a 5x7 font

    unsigned long x = bufferLong [a*2+1];   // Get high buffer entry

    byte y = x;                             // Mask off first character

    lc.setRow(3,a,y);                       // Send row to relevent MAX7219 chip

    x = bufferLong [a*2];                   // Get low buffer entry

    y = (x>>24);                            // Mask off second character

    lc.setRow(2,a,y);                       // Send row to relevent MAX7219 chip

    y = (x>>16);                            // Mask off third character

    lc.setRow(1,a,y);                       // Send row to relevent MAX7219 chip

    y = (x>>8);                             // Mask off forth character

    lc.setRow(0,a,y);                       // Send row to relevent MAX7219 chip

  }

}



void loop(){ 

//    scrollMessage(scrollText);

//    scrollFont();



// using DS18B20 ( http://arduinoprojects.ru/2014/08/%D0%BF%D1%80%D0%BE%D1%81%D1%82%D0%BE%D0%B9-%D1%82%D0%B5%D1%80%D0%BC%D0%BE%D1%81%D1%82%D0%B0%D1%82-%D0%BD%D0%B0-arduino-%D0%B8-%D1%86%D0%B8%D1%84%D1%80%D0%BE%D0%B2%D0%BE%D0%BC-%D1%82%D0%B5%D1%80%D0%BC/ )

sensors.requestTemperatures(); // запрос на получение температуры

float te=(sensors.getTempCByIndex(0)); 

Serial.println(te);

 delay(250);



 int t2 = 10*te; 

// value for test display:

// t2 = 297;

//t2 = 14;

// t2 = 0;

// t2 = -15;

// t2 = -123;



int tz = t2/100;

t2 = t2-tz*100;

int tu = t2/10;

int ts = t2%10;



Serial.print("=");

Serial.print(tz);

Serial.print(tu);

Serial.print(",");

Serial.print(ts);

Serial.println("?");



        scrollMessage(temperatura);

        if (t2 > 0)

       {

         loadBufferLong(43);  // +

       }  

        else

       {

         loadBufferLong(45);  // +

        t2 = -t2; 

       }  

        loadBufferLong(48+tz);  // 2

        loadBufferLong(48+tu);  // 1

        loadBufferLong(44);  // ,

        loadBufferLong(48+ts);  // 7

        loadBufferLong(0x7F);  // degree sign

        loadBufferLong(67);  // C

delay(2000);



DateTime now = RTC.now();

int ora = now.hour();

int minut = now.minute();

int anul = now.year() - 2000;

Serial.print(anul);

int luna = now.month();

int ziua = now.day();



// scrollMessage(guma);  // clear screen with scrool text



int zz = ziua/10;

int zu = ziua%10;

int lz = luna/10;

int lu = luna%10;

int az = anul/10;

int au = anul%10;



Serial.print(" =  20");

Serial.print(az);

Serial.println(au);



 scrollMessage(data);  // clear screen with scrool text 

loadBufferLong(48+zz);  // tens of day

loadBufferLong(48+zu);  // units of day

loadBufferLong(47);  // sign /

loadBufferLong(48+lz);  // tensf of month

loadBufferLong(48+lu);  // units of month

loadBufferLong(47);  // sign /

loadBufferLong(48+2);  // 2

loadBufferLong(48+0);  // 0

loadBufferLong(48+az);  // tensf of year

loadBufferLong(48+au);  // units of year



// scrollMessage(guma);  // clear screen with scrool text 



int oz = ora/10;

int ou = ora%10;

int mz = minut/10;

int mu = minut%10;

 scrollMessage(ceas);  // clear screen with scrool text 

loadBufferLong(48+oz);  // tens of hour

loadBufferLong(48+ou);  // units of hour

loadBufferLong(58);  // sign :

loadBufferLong(48+mz);  // tensf of minute

loadBufferLong(48+mu);  // units of minute

delay(2000);

}
