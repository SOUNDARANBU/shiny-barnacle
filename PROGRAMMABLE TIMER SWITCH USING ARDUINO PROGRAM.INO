/*Please download the library files in the web. This program works on arduino platform when the libraries are added correctly and the ports are assigned properly*/



#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <RTClib.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
RTC_DS3231 rtc;
char a[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const int back=13;
const int inc=12;
const int dec=11;
const int set=10;

int setting=0;
int menu=0;

int i=0;
int d=0;

int device=0;
int screen=0;

DateTime ondate;
DateTime offdate;

void setup() {
   pinMode(back,INPUT);
   pinMode(inc,INPUT);
   pinMode(dec,INPUT);
   pinMode(set,INPUT);
 
  Serial.begin(9600);

  
  display.begin();
  display.setContrast(50);
  display.clearDisplay(); 
  display.display();

if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  
  
}

void loop() {
  DateTime now = rtc.now();
  display.display();
  
  if(digitalRead(set)==HIGH)
  {
    delay(200);
    setting++;
    d=0;
    
  }
 
  if(digitalRead(inc)==HIGH)
  {
    delay(200);
    d++;

   
  }
  if(digitalRead(dec)==HIGH)
  {
    delay(200);
    d--;
  
  }
  if(digitalRead(back)==HIGH)
  {
    delay(200);
    setting=0;
  }

  if(setting==1)
  { 
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Setting");
   display.drawFastHLine(0,10,83,BLACK);
   display.setCursor(0, 12);
   display.print("Set ON Date");
   DateTime future (now+TimeSpan(d,0,0,0));
   display.setCursor(0, 21);
   display.print(future.day(), DEC);
   display.print('/');
   display.print(future.month(), DEC);
   display.print('/');
   display.print(future.year(), DEC);
   ondate=future;
  }
   if(setting==2)
   {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Setting");
     display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(0, 12);
   display.print("Set ON Time");
    DateTime future (ondate+TimeSpan(0,0,d,0));
   display.setCursor(0, 21);
   display.print(future.hour(), DEC);
   display.print(':');
   display.print(future.minute(), DEC);
   display.print(':');
   display.print("00");
  ondate=future;
   }
   if(setting==3)
  {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Setting");
     display.drawFastHLine(0,10,83,BLACK);
       display.setCursor(0, 12);
   display.print("Set OFF Date");
   DateTime future (now+TimeSpan(d,0,0,0));
   display.setCursor(0, 21);
   display.print(future.day(), DEC);
   display.print('/');
   display.print(future.month(), DEC);
   display.print('/');
   display.print(future.year(), DEC);
   offdate=future;
  }
  
   if(setting==4)
   {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Setting");
     display.drawFastHLine(0,10,83,BLACK);
       display.setCursor(0, 12);
   display.print("Set OFF Time");
   DateTime future (offdate+TimeSpan(0,0,d,0));
   display.setCursor(0,21);
   display.print(future.hour(), DEC);
   display.print(':');
   display.print(future.minute(), DEC);
   display.print(':');
   display.print("00");
   offdate=future;
   }
   if(setting>=5)
   {   
     
     display.clearDisplay();
     display.setCursor(5, 20);
     display.print("Device Set!");
    
   }
   
   if(setting==0)
   {  
     display.clearDisplay();
     display.setCursor(0, 0);
     display.print(now.hour(), DEC);
     display.print(':');
     display.print(now.minute(), DEC);
     display.print(':');
     display.print(now.second(), DEC);
     display.drawFastHLine(0,10,83,BLACK);
     display.setCursor(65,0);
           if(device==0)
           {
             display.print("OFF");
           }
            if(device==1)
           {
             display.print("ON");
           }
     
      if((now.day()==ondate.day()) && (now.month()==ondate.month()) 
  && (now.year()==ondate.year())&& (now.hour()==ondate.hour())
  && (now.minute()==ondate.minute())&& (now.second()==ondate.second()))
  {
    device=1;
   
  }

    if((now.day()==offdate.day()) && (now.month()==offdate.month()) 
  && (now.year()==offdate.year())&& (now.hour()==offdate.hour())
  && (now.minute()==offdate.minute())&& (now.second()==offdate.second()))
  {
    device=0;
  }
            
        display.setCursor(0,12);
        display.print("ON:");
        display.print(ondate.day(), DEC);
        display.print('/');
        display.print(ondate.month(), DEC);
        display.print('/');
        display.print(ondate.year(), DEC);
        display.setCursor(0,21);
        display.print(ondate.hour(), DEC);
        display.print(':');
        display.print(ondate.minute(), DEC);
        display.print(':');
        display.print(ondate.second(), DEC);

        display.setCursor(0,30);
        display.print("OFF:");
        display.print(offdate.day(), DEC);
        display.print('/');
        display.print(offdate.month(), DEC);
        display.print('/');
        display.print(offdate.year(), DEC);
        display.print('-');
        display.setCursor(0,39);
        display.print(offdate.hour(), DEC);
        display.print(':');
        display.print(offdate.minute(), DEC);
        display.print(':');
        display.print(offdate.second(), DEC);
   }
   }
