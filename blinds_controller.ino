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

char auth[] = "********************";  //Blynk Token
char ssid[] = "********************";  //WiFi Name
char pass[] = "********************";  //WiFi Password

int pin_bits[4] = {0b0001, 0b0010, 0b0100, 0b1000};


int turn_numb = 500; //number of turns to open(or close) blinds
int current_pos;
int EEaddress_direction = 0; //EEPROM Address
int EEaddress_position = 1; //EEPROM Address
bool can_turn_clockwise = true;
bool button_pressed = false;

void ICACHE_RAM_ATTR ButtonStatus();

/****** Open-Close Button ******/
BLYNK_WRITE(V1)
{
  if(param.asInt() == 1 && can_turn_clockwise)
  {
    //Turn On the Blinds
    Turn(current_pos, true);
    current_pos = 0;
    can_turn_clockwise = false;
    EEPROM.write(EEaddress_direction, can_turn_clockwise);
    EEPROM.write(EEaddress_position, current_pos);
    Blynk.virtualWrite(V2, current_pos);
  }
  else if(param.asInt() == 0 && !can_turn_clockwise)
  {
    //Turn Off the Blinds
    Turn(turn_numb - current_pos, false);
    current_pos = turn_numb;
    can_turn_clockwise = true;
    EEPROM.write(EEaddress_direction, can_turn_clockwise);  
    EEPROM.write(EEaddress_position, current_pos);
    Blynk.virtualWrite(V2, current_pos);
  }
}

/****** Vertical Slider ******/
BLYNK_WRITE(V2)
{
  if(param.asInt() > current_pos)
  {
    if(param.asInt() == turn_numb)
    {
      can_turn_clockwise = true;
      EEPROM.write(EEaddress_direction, can_turn_clockwise);
      Blynk.virtualWrite(V1, !can_turn_clockwise);
    }
    Turn(param.asInt() - current_pos, false);
    current_pos = param.asInt();
    EEPROM.write(EEaddress_position, current_pos);
  }
  else if(param.asInt() < current_pos)
  {
    if(param.asInt() == 0)
    {
      can_turn_clockwise = false;
      EEPROM.write(EEaddress_direction, can_turn_clockwise);
      Blynk.virtualWrite(V1, !can_turn_clockwise);
    }
    Turn(current_pos - param.asInt(), true);
    current_pos = param.asInt();
    EEPROM.write(EEaddress_position, current_pos);
  }
  
}

void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  
  pinMode(SP1, OUTPUT);
  pinMode(SP2, OUTPUT);
  pinMode(SP3, OUTPUT);
  pinMode(SP4, OUTPUT);
  
  current_pos = turn_numb;
  can_turn_clockwise = EEPROM.read(EEaddress_direction);
  current_pos = EEPROM.read(EEaddress_position);
  
  attachInterrupt(digitalPinToInterrupt(button), ButtonStatus, RISING);
  
  TurnOffMotor();
}

void loop() 
{
  Blynk.run();

  ButtonControl();
}

void ButtonStatus()
{
  button_pressed = true;
}

/****** Push Button Control ******/
void ButtonControl()
{
  if(button_pressed)
  {
    if(can_turn_clockwise)
    {
      Turn(current_pos, true);
      can_turn_clockwise = false;
      current_pos = 0;
    }else{
      Turn(turn_numb - current_pos, false);
      can_turn_clockwise = true;
      current_pos = turn_numb;
    }
    EEPROM.write(EEaddress_direction, can_turn_clockwise);
    EEPROM.write(EEaddress_position, current_pos);
    Blynk.virtualWrite(V1, !can_turn_clockwise);
    Blynk.virtualWrite(V2, current_pos);
    button_pressed = false;
  }
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
