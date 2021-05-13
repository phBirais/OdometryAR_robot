
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

int robotSpeed = 200;
int nospeed = 0;

// setting PWM properties
const int freq = 5000;
const int pwmChannelA = 0;
const int pwmChannelB = 0;
const int resolution = 8;


void setup()
{
    Serial.begin(9600);
    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(STBY, OUTPUT);
    pinMode(LED, OUTPUT);

    digitalWrite(STBY,HIGH);

  ledcSetup(pwmChannelA, freq, resolution);  
  ledcSetup(pwmChannelB, freq, resolution);  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(PWMA, pwmChannelA);
  ledcAttachPin(PWMB, pwmChannelB);
}


void loop()
{
  //Serial.println("FRENTE");
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  ledcWrite(pwmChannelA, robotSpeed);
  
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);       
  ledcWrite(pwmChannelB , robotSpeed);  

  /*
  digitalWrite(LED, HIGH);
  delay(1500);
  digitalWrite(LED, LOW);
  delay(1500); */
}


void moveControl(int x, int y)
{
//Move Forward
    if(y >= 650 && (x >= 450 && x<= 650))
    {
        Serial.println("FRENTE");
        digitalWrite(AIN1,LOW);
        digitalWrite(AIN2,HIGH);
        ledcWrite(PWMA, robotSpeed);
        
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2,HIGH);       
        ledcWrite(PWMB , robotSpeed);
    }


//Move  Right
    else if(x >= 650 && (y >= 450 && y<=650) )
    {
        Serial.println("DIREITA");
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);
        ledcWrite(PWMA,robotSpeed);
       
        
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2,HIGH);   
        ledcWrite(PWMB ,robotSpeed);
    }
//Move  Left
    else if(x <= 450 && (y >= 450 && y<=650))
    {
        Serial.println("ESQUERDA");
        digitalWrite(AIN1,LOW);
        digitalWrite(AIN2,HIGH);
        ledcWrite(PWMA,robotSpeed);
        
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2,LOW);      
        ledcWrite(PWMB ,robotSpeed);
    }
//Move Backward
    else if(y <= 450 && x >= 400 && x <= 600)
    {
        Serial.println("TRAS");
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2,LOW);
        ledcWrite(PWMA,robotSpeed);
        
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2,LOW);  
        ledcWrite(PWMB ,robotSpeed);
    }
    else{
        Serial.println("PARADO");
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);        
        ledcWrite(PWMA, nospeed);

        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, LOW); 
        ledcWrite(PWMB , nospeed);
    }
}
