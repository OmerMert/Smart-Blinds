#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <EEPROM.h>

#define SP1 D1
#define SP2 D2
#define SP3 D3
#define SP4 D4
#define button D5

#define wait 2 //Delay Between Steps 2ms

char auth[] = "H63Ym13gHmJooMgNHKNHGHTznY-S-ELX";
char ssid[] = "SUPERONLINE_WiFi_8875";
char pass[] = "HPVATVJU77PA";

int pin_bits[4] = {0b0001, 0b0010, 0b0100, 0b1000};

bool can_turn_clockwise = true;
int turn_numb = 500; //number of turns to open(or close) blinds
int EEaddress = 0; //EEPROM Address

void ICACHE_RAM_ATTR ButtonControl();

BLYNK_WRITE(V1)
{
  if(param.asInt() == 1 && can_turn_clockwise)
  {
    //Turn On the Blinds
    Turn(turn_numb, true);
    can_turn_clockwise = false;
    EEPROM.write(EEaddress, can_turn_clockwise);
  }
  else if(param.asInt() == 0 && !can_turn_clockwise)
  {
    //Turn Off the Blinds
    Turn(turn_numb, false);
    can_turn_clockwise = true;
    EEPROM.write(EEaddress, can_turn_clockwise);  
  }
}

void setup() 
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
  pinMode(SP1, OUTPUT);
  pinMode(SP2, OUTPUT);
  pinMode(SP3, OUTPUT);
  pinMode(SP4, OUTPUT);
  
  can_turn_clockwise = EEPROM.read(EEaddress);

  attachInterrupt(digitalPinToInterrupt(button), ButtonControl, RISING);
  
  TurnOffMotor();
}

void loop() 
{
  Blynk.run();
}

void ButtonControl()
{
  noInterrupts(); // disable interrupts
  if(can_turn_clockwise)
  {
    Turn(turn_numb, true);
    can_turn_clockwise = false;
    EEPROM.write(EEaddress, can_turn_clockwise);
  }else{
    Turn(turn_numb, false);
    can_turn_clockwise = true;
    EEPROM.write(EEaddress, can_turn_clockwise);
  }
  Blynk.virtualWrite(V1, can_turn_clockwise);
  interrupts(); // enable interrupts
  
}

void Turn(unsigned int amount, bool clockwiseturn)
{
  if(clockwiseturn)
  {
    for(int i = 0; i < amount; i++)
      Clockwise();
  }else{
    for(int i = 0; i < amount; i++)
      Anticlockwise();
  }
  
  TurnOffMotor();
}

void Anticlockwise()
{
  for(int i = 0; i < 4; i++)
  {
    SetOutput(i);
    delay(wait);
  }
}

void Clockwise()
{
  for(int i = 3; i >= 0; i--)
  {
    SetOutput(i);
    delay(wait);
  }
}

void SetOutput(int out)
{
  digitalWrite(SP1, bitRead(pin_bits[out], 0));
  digitalWrite(SP2, bitRead(pin_bits[out], 1));
  digitalWrite(SP3, bitRead(pin_bits[out], 2));
  digitalWrite(SP4, bitRead(pin_bits[out], 3));
}

void TurnOffMotor()
{
  digitalWrite(SP1, LOW);
  digitalWrite(SP2, LOW);
  digitalWrite(SP3, LOW);
  digitalWrite(SP4, LOW);
  
}
