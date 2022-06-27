#define seconds 1000
#define minute 60
#define temp 5

#define pin_Sensor A0
#define correction 0.02
#define samples 10

/* 0V - 0
   5V - 1023
   1°C - 10mV

   tension sensor = 
   temp = (AO *5.0/1023)/0.01
*/
double average = 0 ;
double tempActual = 0;
void setup()
{
  pinMode(pin_Sensor, INPUT);
  Serial.begin(9600);
  for(int i=0; i<samples; i++)
    tempActual = tempActual + (((((analogRead(pin_Sensor))*5.0)/1023)/correction)/samples;
  
  Serial.println("Temp:");
  Serial.println(tempActual);
}
void loop()
{
  for(int j = 0; j<temp; j++) // temp (5 minutes)
    for(int i = 0; i<minute; i++) // 1 minute
        delay(seconds); 
   
  for(int i=0; i<samples; i++)
    average = average + (((((analogRead(pin_Sensor))*5.0)/1023)/correction)/samples;
  
  Serial.println(average);
}
