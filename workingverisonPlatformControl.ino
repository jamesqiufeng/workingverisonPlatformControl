#define ADC_ref 2.56
#define zero_x 1.569
#define zero_y 1.569
#define zero_z 1.569
#define sensitivity_x 0.3
#define sensitivity_y 0.3
#define sensitivity_z 0.3

//define ports for sensor
unsigned int value_x;
unsigned int value_y;
unsigned int value_z;
signed int Xset;
signed int Yset;
signed int Zset;


// IN 1,3 goes to POS, 2,4 goes to NEG
//driverA
// left control
int enA = 13;
int APOS1 = 22;
int ANEG1 = 24;
// right control
int enB = 12;
int BPOS1 = 26;
int BNEG1 = 28;


//robot movement signal
int ControlSignal = 52;

void setup()
{
  analogReference(INTERNAL2V56);
  Serial.begin(256000);

  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(APOS1, OUTPUT);
  pinMode(ANEG1, OUTPUT);
  pinMode(BPOS1, OUTPUT);
  pinMode(BNEG1, OUTPUT);
  pinMode(ControlSignal, INPUT);
}

void moveAup() 
{
  digitalWrite(APOS1, HIGH); 
  digitalWrite(ANEG1, LOW);
}

void moveBup() 
{
  digitalWrite(BPOS1, HIGH);
  digitalWrite(BNEG1, LOW);
}

void moveAdown() 
{
  digitalWrite(APOS1, LOW);
  digitalWrite(ANEG1, HIGH);
}

void moveBdown() 
{
  digitalWrite(BPOS1, LOW);
  digitalWrite(BNEG1, HIGH);
}

void StopA()
{
  digitalWrite(APOS1, HIGH);
  digitalWrite(ANEG1, HIGH); 
}

void StopB()
{
  digitalWrite(BPOS1, HIGH);
  digitalWrite(BNEG1, HIGH); 
}

void CoastA()            //test purpose, might need it for initial state.
{
  digitalWrite(APOS1, LOW);
  digitalWrite(ANEG1, LOW);
}

void CoastB()            //test purpose, might need it for initial state.
{
  digitalWrite(BPOS1, LOW);
  digitalWrite(BNEG1, LOW); 
}

void Aenable()
{
  digitalWrite(enA, HIGH);
}

void Adisable()
{
  digitalWrite(enA, LOW);
}

void Benable()
{
  digitalWrite(enB, HIGH);
}

void Bdisable()
{
  digitalWrite(enB, LOW);
}

//movement fcns

void AUpSlow(int duration)
{
  moveAup();
  delay(duration);
}

void ADownSlow(int duration) 
{
  moveAdown();
  delay(duration);
}

void BUpSlow(int duration)
{
  moveBup();
  delay(duration);
}

void BDownSlow(int duration)
{
  moveBdown();
  delay(duration);
}

void HoldA(int duration)
{
  StopA();
  delay(duration);
}

void HoldB(int duration)
{
  StopB();
  delay(duration);
}


void loop()  //test main
{
  //sensor readings
  value_x = analogRead(0);
  value_y = analogRead(1);
  value_z = analogRead(2);
  
  //readings and serial scopes
  Xset = value_x - 651; 
  Serial.print ("x= ");
  Serial.print(Xset);
  
  Yset = value_y - 638;
  Serial.print (" y= ");
  Serial.print(Yset);
 
  Zset = value_z - 788;
  Serial.print (" z= ");
  Serial.print(Zset);
  Serial.print("\n");

 /* if (ControlSignal == 0)
  {  
    // we should initial the position of the actuators, needs to be discuessed.
    Aenable();
    Benable();
    AUpSlow(1000); //set it to move up for 1s.
    BUpSlow(1000);
    Adisable;
    Bdisable;
  }
  */
//  else if (ControlSignal == 1)
//  {
    
    if (Xset < -2)
    {
      Aenable();
      AUpSlow(25);
      HoldA(100); 
      Adisable;
    }
    else if (Xset > 2)
    {
      Aenable();
      ADownSlow(25); 
      HoldA(100);
      Adisable;
    }
    if (Yset < -3)
    {
      Benable();
      BUpSlow(25); 
      HoldB(100);
      Bdisable;
    }
    else if(Yset > 3)
    {
      Benable();
      BDownSlow(25); 
      HoldB(100);
      Bdisable;
    }
    
//  }
   
}
