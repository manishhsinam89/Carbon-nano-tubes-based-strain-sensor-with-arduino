/*Group 21A,21B,21C
Tutor - M. Eng. Abdulkadir Sanli
The algorithm for this program is emapped_value_downplained below
(1) Setup baud rate 9600 & pin 9,pin 10, pin 11, pin 5 as an output
(2) Read the sensor value & get it as average value or smooth value, because we need stable reading--smoothing function
(3) Compare current value & start value
--- Calculate the difference
(i) if current value > start value --- 1st direction -- map the difference 0-255
(ii) -- 2nd direction -- map the difference 0-255
(iii) -- 3rd direction
(iv) -- 4th direction
(4) Compare the maximum value of current value if the current value is greater than the maximum value, set
current value as a maximum value
(5) Compare minimum value to current value if current value is less than maximum value , set current value
as a minimum value
(6) Now write the mapped value to pin
mapped_value_downed variables -- sensor dependent
float maximum_value = 0 ; // enter maximum_value = maximum sensor reading
float minimum_value = 1023 ; // enter minimum_value = minimum sensor reading
//define variables
*/ //mapped_value_downed variables -- sensor dependent
//define variables
//mapped_value_downed variables -- sensor dependent
float maximum_value1 = 0 ; // enter maximum_value = maximum sensor reading
float minimum_value1 = 1023 ; // enter minimum_value = minimum sensor reading
float maximum_value2 = 0 ; // enter maximum_value = maximum sensor reading
float minimum_value2 = 1023 ; // enter minimum_value = minimum sensor reading
float maximum_value3 = 0 ; // enter maximum_value = maximum sensor reading
float minimum_value3 = 1023 ; // enter minimum_value = minimum sensor reading
float maximum_value4 = 0 ; // enter maximum_value = maximum sensor reading
float minimum_value4 = 1023 ; // enter minimum_value = minimum sensor reading
//define variables
float start_value1 = 0 ; // sensor value at normal position
float start_value2 = 0 ;
float start_value3 = 0 ;
float start_value4 = 0 ;

float smooth_value1 = 0 ; // smoothed value will stored in this variable
float smooth_value2 = 0 ;
float smooth_value3 = 0 ;
float smooth_value4 = 0 ;

int thresold_1 = 40;      // depends on the strain sensor
int thresold_2 = 40;
int thresold_3 = 40;
int thresold_4 = 40;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);                            // initialize serial communications at 9600 bps:
pinMode(9,OUTPUT);                            // for DOWN motion
pinMode(10,OUTPUT);                           // for UP motion
pinMode(11,OUTPUT);                           // for right motion
pinMode(5,OUTPUT);                          // for left motion
smoothing();
start_value1= smooth_value1;
start_value2= smooth_value2;
start_value3= smooth_value3;
start_value4= smooth_value4;
}

void smoothing()
{ 
float temp1=0,temp2=0,temp3=0,temp4=0;
float sum1 = 0,sum2 = 0,sum3 = 0,sum4 = 0;
                                           // --------read the analog input value for smoothing-------------//
for(int i=0;i<10;i++)
{
temp1 = analogRead(A0);
sum1 = sum1 + temp1; 
temp2 = analogRead(A2);
sum2 = sum2 + temp2; 
temp3 = analogRead(A4);
sum3 = sum3 + temp3;
temp4 = analogRead(A5);
sum4 = sum4 + temp4; 
}
smooth_value1 =sum1/10;
smooth_value2 =sum2/10;
smooth_value3 =sum3/10;
smooth_value4 =sum4/10;
}
void loop() {
                                                // put your main code here, to run repeatedly:
smoothing();                                  // calling function smoothing to get smooth_value
float current_value1 = smooth_value1;         // current_value will get difference with normal position or start_value
float current_value2 = smooth_value2;
float current_value3 = smooth_value3;
float current_value4 = smooth_value4;

float mapped_value_1 = 0 ;                    // for mapping the range of differnce
float mapped_value_2 = 0 ; 
float mapped_value_3 = 0 ;
float mapped_value_4 = 0 ;
                                               //-------------------self calebration for maximum & minimum value------------//
  
  if(current_value1 > maximum_value1)// if we have a larger value than the maximum value, maximum value will updated
    { maximum_value1 = current_value1;}
  else if(current_value1 < minimum_value1) // if we have a smaller value than the minimum value, minimum value will updated
    { minimum_value1 = current_value1;}
  else
    {}  
  if(current_value2 > maximum_value2)
    { maximum_value2 = current_value2;}
  else if(current_value2 < minimum_value2) // if we have a smaller value than the minimum value, minimum
    { minimum_value2 = current_value2;}
  else
    {}  
  if(current_value3 > maximum_value3)
    { maximum_value3 = current_value3;}
  else if(current_value3 < minimum_value3) // if we have a smaller value than the minimum value, minimum
    { minimum_value3 = current_value3;}  
  else
    {}  
  if(current_value4 > maximum_value4) 
    { maximum_value4 = current_value4;}
  else if(current_value4 < minimum_value4) // if we have a smaller value than the minimum value, minimum
    { minimum_value4 = current_value4;}  
  else
    {}  
    
//-------------------condition for 1st direction---------------------//
if(current_value1 - start_value1 > thresold_1)              //set threshold value for down leds
{mapped_value_1=map(current_value1-start_value1-thresold_1,0,maximum_value1-start_value1-thresold_1,0,255);} // mapping difference to 0-255
else if(start_value1 - current_value1 > thresold_1) 
{mapped_value_1=map(start_value1-current_value1-thresold_1,0,start_value1-minimum_value1-thresold_1,0,255);} // mapping difference to 0-255
//--------------------condition for 2nd direction-----------------------//
if(current_value2 -start_value2 > thresold_2) //set thresold value for up leds
{mapped_value_2=map(current_value2-start_value2-thresold_2,0,maximum_value2-start_value2-thresold_2,0,255);}
else if(start_value2 - current_value2 > thresold_2) 
{mapped_value_2=map(start_value2-current_value2-thresold_2,0,start_value2-minimum_value2-thresold_2,0,255);}
//-------------------condition for 3rd direction---------------------//
if(current_value3 - start_value3 > thresold_3) //set threshold value for right leds
{mapped_value_3=map(current_value3-start_value3-thresold_3,0,maximum_value3-start_value3-thresold_3,0,255);} // mapping difference to 0-255
else if(start_value3 - current_value3 > thresold_3) 
{mapped_value_3=map(start_value3-current_value3-thresold_3,0,start_value3-minimum_value3-thresold_3,0,255);}
//--------------------condition for 4th direction-----------------------//
if(current_value4 - start_value4>thresold_4) //set thresold value for left leds
{mapped_value_4=map(current_value4-start_value4-thresold_4,0,maximum_value4-start_value4-thresold_4,0,255);}
else if(start_value4 - current_value4 > thresold_4) 
{mapped_value_4=map(start_value4-current_value4-thresold_4,0,start_value4-minimum_value4-thresold_4,0,255);}

{
analogWrite(9,mapped_value_1);// no LED will glow
analogWrite(10,mapped_value_2); // no LED will glow
analogWrite(11,mapped_value_3);
analogWrite(5,mapped_value_4);
}
/*if(mapped_value_1 > mapped_value_2 && mapped_value_1 > mapped_value_3 && mapped_value_1 > mapped_value_4 )
{
analogWrite(10,0);
analogWrite(11,0);
analogWrite(12,0);
analogWrite(9,mapped_value_1);}
else if (mapped_value_2 > mapped_value_1 && mapped_value_2 > mapped_value_3 && mapped_value_2 > mapped_value_4)
{
analogWrite(9,0);
analogWrite(11,0);
analogWrite(12,0);
analogWrite(10,mapped_value_2);}
else if (mapped_value_3 > mapped_value_1 && mapped_value_3 > mapped_value_2 && mapped_value_3 > mapped_value_4)
{
analogWrite(9,0);
analogWrite(10,0);
analogWrite(12,0);
analogWrite(11,mapped_value_3);}
else if (mapped_value_4 > mapped_value_1 && mapped_value_4 > mapped_value_2 && mapped_value_4 > mapped_value_3)
{
analogWrite(9,0);
analogWrite(10,0); 
analogWrite(11,0);
analogWrite(12,mapped_value_4);}

else
{
analogWrite(9,0);// no LED will glow
analogWrite(10,0); // no LED will glow
analogWrite(11,0);
analogWrite(12,0);
}*/

Serial.print("\n sv1= ");
Serial.print(start_value1);
Serial.print("\t m1=");
Serial.print(mapped_value_1);
Serial.print("\t cv1=");
Serial.print(current_value1);
Serial.print("\t sv2=");
Serial.print(start_value2);
Serial.print("\t m2=");
Serial.print(mapped_value_2);
Serial.print("\t cv2=");
Serial.print(current_value2);
Serial.print("\t sv3=");
Serial.print(start_value3);
Serial.print("\t m3=");
Serial.print(mapped_value_3);
Serial.print("\t cv3=");
Serial.print(current_value3);
Serial.print("\t sv4=");
Serial.print(start_value4);
Serial.print("\t m4=");
Serial.print(mapped_value_4);
Serial.print("\t cv4=");
Serial.print(current_value4);
delay(100);
}

