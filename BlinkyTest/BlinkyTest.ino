//Viral Science www.youtube.com/c/viralscience  www.viralsciencecreativity.com
//ESP8266 Blynk Joystick Car
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Motor A
 
#define PWMA 5//D4
#define AIN1 16 //
#define AIN2 17 //
 
// Motor B
 
#define PWMB 27 //d6
#define BIN1 25 //d13
#define BIN2 26 //d7

#define STBY 4//d8

#define LED 2


char auth[] = "Eq26uSyEbXxD2yKs9zqwaHcuTsSsSkT3";  //Blynk Authentication Token
char ssid[] = "BiraisNokia";           //WIFI Name
char pass[] = "birais2020";           //WIFI Password

//int minRange = 312;
//int maxRange = 712;

int robotSpeed = 200;
int nospeed = 0;


void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);

    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(STBY, OUTPUT);
    pinMode(GUN, OUTPUT);

    digitalWrite(STBY,HIGH);
}


void loop()
{
    Blynk.run();
}


void moveControl(int x, int y)
{
//Move Forward
    if(y >= 650 && (x >= 450 && x<= 650))
    {
        Serial.println("FRENTE");
        digitalWrite(AIN1,LOW);
        digitalWrite(AIN2,HIGH);
        analogWrite(PWMA, robotSpeed);
        
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2,HIGH);       
        analogWrite(PWMB , robotSpeed);
    }


//Move  Right
    else if(x >= 650 && (y >= 450 && y<=650) )
    {
        Serial.println("DIREITA");
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);
        analogWrite(PWMA,robotSpeed);
       
        
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2,HIGH);   
        analogWrite(PWMB ,robotSpeed);
    }
//Move  Left
    else if(x <= 450 && (y >= 450 && y<=650))
    {
        Serial.println("ESQUERDA");
        digitalWrite(AIN1,LOW);
        digitalWrite(AIN2,HIGH);
        analogWrite(PWMA,robotSpeed);
        
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2,LOW);      
        analogWrite(PWMB ,robotSpeed);
    }
//Move Backward
    else if(y <= 450 && x >= 400 && x <= 600)
    {
        Serial.println("TRAS");
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2,LOW);
        analogWrite(PWMA,robotSpeed);
        
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2,LOW);  
        analogWrite(PWMB ,robotSpeed);
    }
    else{
        Serial.println("PARADO");
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);        
        analogWrite(PWMA,nospeed);

        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, LOW); 
        analogWrite(PWMB , nospeed);
    }
}

BLYNK_WRITE(V2){  // 
  robotSpeed = param.asInt();  //
  Serial.print("Speed Slider: ");
  Serial.println(robotSpeed); // 
}

BLYNK_WRITE(V3){  /
  int isTurned = param.asInt();  //
  if(isTurned==1){
    analogWrite(GUN, 950);
     Serial.print("LIGAR ARMA ");
  }else{
    analogWrite(GUN, 0);
  }
}
 

BLYNK_WRITE(V1)
{
    int x = param[0].asInt();
    int y = param[1].asInt();
    moveControl(x,y);
    Serial.print(x);
    Serial.print(" y: ");
    Serial.println(y);
}
