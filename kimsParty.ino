#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);




  const int upPB = 24;
  const int downPB = 22;
  const int selectPB = 26;
  int menu = 1;
  
  int rum = 49;
  int teq= 47;
  int soda = 45;
  int lime= 43;
  int lemonade= 41;
  int OJ = 39;
  int water = 51;

  
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();


  pinMode(upPB, INPUT_PULLUP);
  pinMode(downPB, INPUT_PULLUP);
  pinMode(selectPB, INPUT_PULLUP);
  updateMenu();

  pinMode(rum, OUTPUT);
  pinMode(teq, OUTPUT);
  pinMode(soda, OUTPUT);
  pinMode(lime, OUTPUT);
  pinMode(lemonade, OUTPUT);
  pinMode(OJ, OUTPUT);
  pinMode(water, OUTPUT);

  digitalWrite(rum, HIGH);
  digitalWrite(teq, HIGH);
  digitalWrite(soda, HIGH);
  digitalWrite(lime, HIGH);
  digitalWrite(lemonade, HIGH);
  digitalWrite(OJ, HIGH);
  digitalWrite(water, HIGH);

}

int pourTime(float volume)
{
  float mlPerSec = 360 / 10;              // These need to be changed depending on the chosen pumps
  float timeForOneOunce = mlPerSec / 30;  // These need to be changed depending on the chosen pumps
  return (int)(volume * timeForOneOunce * 1000);
}



void gosh1(float rumVol, float sodaVol, float limeVol)
{
  digitalWrite(rum,LOW);
  delay(pourTime(rumVol));
  digitalWrite(rum, HIGH);
  
  digitalWrite(soda, LOW);
  delay(pourTime(sodaVol));
  digitalWrite(soda, HIGH);

  digitalWrite(lime, LOW);
  delay(pourTime(limeVol));
  digitalWrite(lime, HIGH);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Top with");
  lcd.setCursor(0,1);
  lcd.print("Muddled Mint");
  delay(3000);
  //add muddled mint
}

void koopaTroopa(float rumVol, float lem)
{
  digitalWrite(rum,LOW);
  delay(pourTime(rumVol));
  digitalWrite(rum, HIGH);
  
  digitalWrite(lemonade, LOW);
  delay(pourTime(lem));
  digitalWrite(lemonade, HIGH);
 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Top with Mint");
  lcd.setCursor(0,1);
  lcd.print("Or Grenadine");
  delay(3000);
  //Tope with a splash of grenadine or mint
}
void daisy(float tequila, float OJuice)
{
  digitalWrite(teq,LOW);
  delay(pourTime(tequila));
  digitalWrite(teq, HIGH);
  digitalWrite(OJ, LOW);
  delay(pourTime(OJuice));
  digitalWrite(OJ, HIGH);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Top with");
  lcd.setCursor(0,1);
  lcd.print("Grenadine");
  delay(3000);
}

void clean()
{
  digitalWrite(water,LOW);
  delay(1500);
  digitalWrite(water, HIGH);
}


void updateMenu()
{
  switch (menu)
  {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Daisy");
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Yoshi");
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Koopa Troopa");
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Clean");
      break;
    case 5:
      menu = 4;
      break;
  }
}
void executeAction()
{
  switch(menu)
  {
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Making Your");
      lcd.setCursor(0,1);
      lcd.print("Daisy");
      daisy(2,4);
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Making Your");
      lcd.setCursor(0,1);
      lcd.print("Yoshi");
      gosh1(2,4,2);
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Making Your");
      lcd.setCursor(0,1);
      lcd.print("Koopa Troopa");
      koopaTroopa(2,4);
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cleaning Your");
      lcd.setCursor(0,1);
      lcd.print("System");
      clean();
      break;
  }
}
void loop() 
{
  if(!digitalRead(downPB))
  {
    menu++;
    updateMenu();
    delay(100);
    while(!digitalRead(downPB));
  }
  if(!digitalRead(upPB))
  {
    menu--;
    updateMenu();
    delay(100);
    while(!digitalRead(upPB));
  }
  if(!digitalRead(selectPB))
  {
    executeAction();
    updateMenu();
    delay(100);
    while(!digitalRead(selectPB));
  }

}
