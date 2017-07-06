/* This is my B.E. third year project 
This working arduino program is designed to count number of whistles from the cooker and to shut down the electric induction cooker*/

#define MIC A1
float sig = 0;
const int segment[] = {4, 5, 6, 7, 8, 9, 10};
const byte states[] = {B0000001, B0110111, B1000010, B0010010, B0110100, B0011000, B0001000, B0110011, B0000000, B0010000, B1111111,B1111110};
const int inc=11;
const int dec=12;
const int set=13;
const int trigger=2;
int count=1;
int whistle=0;
float b=0;
int stop=1;
void setup()
{
  for (int i = 0; i < 8; i++)
    pinMode(segment[i], OUTPUT);
  pinMode(inc,INPUT);
  pinMode(dec,INPUT);
  pinMode(set,INPUT);
  pinMode(trigger,OUTPUT);
   Serial.begin(9600);
   setcount();
}
void loop()
{
mike();
}
 
 void setcount()
 {
  digit(count);
  if(digitalRead(set)==HIGH)
 {
   delay(1000);
   while(digitalRead(set)==LOW&&stop==1)
   {
     if(digitalRead(set)==HIGH)
       stop=0;
     if(digitalRead(inc)==HIGH&&count<11)
     {
       count++;
       digit(count);
       delay(500);
     }
    if(digitalRead(dec)==HIGH&&count>0)
    {
       count--;
       digit(count);
       delay(500);
    }
   }
 }
 }
 void digit(int num)
{
  if(num>10||num<0)
  num=11;
  boolean bits;
  for (int i = 0; i < 7; i++)
  {
    bits = bitRead(states[num], i);
    digitalWrite(segment[i], bits);
  }
}

void mike()
{
 if(count!=0)
{
 sig=analogRead(MIC)/10;
  if(sig>56)
  { b=0;
    delay(250);
    if(sig>56)
     {
      float a[12];
      for(int i=0;i<12;i++)
         { 
         a[i]=sig;
         delay(250);
         sig=analogRead(MIC)/10;
         }
     for(int j=0;j<12;j++)
      {
        b=b+a[j];
       }
     b=b/12;
     for(int j=0;j<12;j++){Serial.println(a[j]);};
     Serial.println(b);
   
       if(b>55.45)
       digit(count--);  
    }
  }

}
if(count=0)
{
   digitalWrite(trigger,HIGH);
  
}
}

