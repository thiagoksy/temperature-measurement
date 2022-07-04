#define seconds 1000
#define minute 30
#define temp 1
#define luz 10
#define buzzer 2
#define pin_Sensor A0
#define correction 0.014
#define samples 10
#define limit 80


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
  pinMode(buzzer, OUTPUT);
  pinMode(luz, OUTPUT);
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL, Hora,Temperatura");
  tempActual =((((analogRead(pin_Sensor))*5.0)/1023)/correction);
  Serial.print("DATA,TIME,");
  Serial.println(tempActual);
}
void loop()
{

  digitalWrite(luz, HIGH);
  //for(int j = 0; j<temp; j++) // temp (5 minutes)
   for(int i = 0; i<minute; i++) // 1 minute
     delay(seconds);    
  average = 0;
  for(int i=0; i<samples; i++)
   average = average + ((((analogRead(pin_Sensor))*5.0)/1023)/correction);
  average = average/samples;
  Serial.print("DATA,TIME,"); 
  Serial.println(average);
   if(average >= limit) 
  {
    digitalWrite(luz, LOW);
    while(1)
    {
         digitalWrite(buzzer, HIGH);
         delay(200);
         digitalWrite(buzzer, HIGH);
         delay(200);
         
    }
  }
 
}
