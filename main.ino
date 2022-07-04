/* Create : Thiago Yamamoto
 * Last Update: 04/07/2022
 */

/**********************************Defines Sensors**********************************/
#define sensorProt A0             //Nº Pin
#define correctionProt 0.014      //dimensionless

#define sensorAmb A1              //Nº Pin
#define correctionAmb 0.02         //dimensionless

/**********************************Defines Alarm**********************************/
#define buzzer 2                  //Nº Pin
#define lights8w 10               //Nº Pin
#define lights30C 8               //Nº Pin 

/**********************************Defines Datas**********************************/
#define samples 10                //dimensionless
#define tempOperation 30          //°C
#define tempLimitOperation 80     //ºC

#define OneSecond 1000                   //1000 miliseconds
#define seconds 10                //10 seconds
#define minute 5                  //5 minutes

typedef enum states{
  OFF, 
  ON
}sts;

/* 0V - 0
   5V - 1023
   1°C - 10mV
   tension sensor = 
   temp = (AO *5.0/1023)/0.01
*/
double average = 0 ;
double tempProt, tempAmb;
void setup()
{
  pinMode(sensorProt, INPUT);
  pinMode(sensorAmb, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(lights8w, OUTPUT);
  pinMode(lights30C, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL, Hora,Temp Amb, Temp Prototype");
  tempAmb =((((analogRead(sensorAmb))*5.0)/1023)/correctionAmb);
  tempProt =((((analogRead(sensorProt))*5.0)/1023)/correctionProt);
  
  Serial.print("DATA,TIME,");
  Serial.println(tempAmb);
  Serial.println(tempProt);

  digitalWrite(lights8w, ON);
  digitalWrite(lights30C, ON);
}
void loop()
{
  tempProt = 0;
  tempAmb = 0;
  
  //***********************************Temperature Stove/Ambience***********************************
  for(int i=0; i<samples; i++)
   tempAmb = tempAmb + ((((analogRead(sensorAmb))*5.0)/1023)/correctionAmb);
  tempAmb = tempAmb/samples;

  //***********************************Temperature Prototype***********************************
  for(int i=0; i<samples; i++)
    tempProt = tempProt+ ((((analogRead(sensorProt))*5.0)/1023)/correctionProt);
  tempProt= tempProt/samples;

  
  Serial.print("DATA,TIME,"); 
  Serial.print(tempAmb);
  Serial.println(tempProt);

  delay(OneSecond*seconds);

  if(tempAmb > tempOperation)
    digitalWrite(lights30C, OFF);
  else
    digitalWrite(lights30C, ON);

  if(tempProt >= tempLimitOperation) 
  {
    digitalWrite(lights8w, OFF);
    while(1)
    {
         digitalWrite(buzzer, ON);
         delay(200);
         digitalWrite(buzzer, OFF);
         delay(200); 
    }
  } 
}
