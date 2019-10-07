/*
 * Siena Town - Gamebuino game
 * 
 * Created by Patryk Kuciński 'Kuciniak'
 * kucinskipatryk.site
 * 
 * 2019
 */


#include <Gamebuino.h>

//imports the SPI library (needed to communicate with Gamebuino's screen)
#include <SPI.h>
//imports the Gamebuino library
#include <Gamebuino.h>
//imports the Gamebuino library
#include <EEPROM.h>

Gamebuino gb;


PROGMEM const unsigned char Logo[] =
{
  64, 36,
  0x00, 0x00, 0x3F, 0xF8, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3F, 0xF8, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0xC0, 0x00,
  0x00, 0x00, 0x7F, 0xFC, 0x00, 0x00, 0x40, 0x00,
  0x00, 0x03, 0xFF, 0xFF, 0xFF, 0x00, 0x40, 0x00,
  0x00, 0x07, 0xFF, 0xFF, 0xFF, 0x80, 0xC0, 0x00,
  0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xE3, 0x80, 0x00,
  0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xF2, 0x00, 0x00,
  0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xF2, 0x00, 0x00,
  0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xF3, 0x00, 0x00,
  0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xF1, 0x80, 0x00,
  0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xF1, 0x80, 0x00,
  0x00, 0x0F, 0xF8, 0x7F, 0xB0, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x18, 0x00, 0x10, 0x07, 0x00, 0x00,
  0x00, 0x00, 0x10, 0x00, 0x18, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x13, 0xCF, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x19, 0x86, 0x08, 0x3E, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x00, 0x08, 0x12, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x20, 0x08, 0x12, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x30, 0x18, 0x12, 0x00, 0x00,
  0x00, 0x00, 0x1C, 0x00, 0x38, 0x12, 0xC0, 0x00,
  0x00, 0x00, 0x17, 0xFF, 0xF8, 0x13, 0x60, 0x00,
  0x00, 0x00, 0x18, 0x00, 0x08, 0x13, 0xE0, 0x00,
  0x00, 0x00, 0x08, 0x00, 0x08, 0x13, 0xF0, 0x00,
  0x00, 0x00, 0x0B, 0x24, 0x88, 0x17, 0x90, 0x00,
  0x00, 0x00, 0x08, 0x60, 0x88, 0x17, 0x90, 0x00,
  0x00, 0x00, 0x08, 0x00, 0x88, 0x1F, 0xF0, 0x00,
  0x00, 0x00, 0x0B, 0x02, 0x08, 0x0F, 0xC0, 0x00,
  0x00, 0x00, 0x09, 0x32, 0x0C, 0x0F, 0xC0, 0x00,
  0x00, 0x00, 0x08, 0x00, 0x44, 0x0F, 0xC0, 0x00,
  0x00, 0x00, 0xF8, 0x40, 0x6F, 0x8F, 0xC0, 0x00,
  0x00, 0x01, 0x8C, 0x64, 0x1C, 0xCF, 0xC0, 0x00,
  0x00, 0x03, 0x04, 0x06, 0x30, 0x7F, 0x80, 0x00,
  0x00, 0x06, 0x06, 0x00, 0xE0, 0x3F, 0x00, 0x00,
  0x00, 0x0C, 0x02, 0x01, 0x80, 0x7F, 0x80, 0x00,
};


const PROGMEM byte Sheriff[] {

  8, 8,
  0b01110000,
  0b11111000,
  0b01110000,
  0b00101110,
  0b00111000,
  0b00100000,
  0b01010000,
  0b01010000,
};

const PROGMEM byte Bandit[] {

  8, 8,

  0b00111000,
  0b00111000,
  0b00111000,
  0b00001000,
  0b11110000,
  0b01010000,
  0b00111000,
  0b01000100,
};

const PROGMEM byte Civilian[] {

  8, 8,
  0b00111000,
  0b10111010,
  0b10010010,
  0b01111100,
  0b00010000,
  0b00111000,
  0b01000100,
  0b01000100,
};

const PROGMEM byte Shoot[] {

  8, 8,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b01000000,
  0b00000000,
  0b00000000,
  0b00000000,
};

//Default Value
int SheriffPosY = 20;
int BanditPosY = 2, CivilianPosY;
int BanditPos;
bool BanditActive = false;
bool CivilianActive = false;
int Lives = 3;
int Points = 0;
int ShootPosY = 0;
int ShootPosX = 68;
bool Bullet = false;
int Choice = 0, Menu = 1;
int Topscore = EEPROM.read(0);
bool Record = false;

void setup()
{
  // initialize the Gamebuino object
  gb.begin();
  //display the main menu:
  gb.titleScreen(F("     Siena Town"), Logo);

}

void loop()
{
  if (gb.update())
  {
    Topscore=0;
    //MENU Choice
    if (Choice == 0)
    {
      if (gb.buttons.pressed(BTN_UP))
      {
        Menu--;
        if (Menu < 1)
        {
          Menu = 4;
        }
      }
      if (gb.buttons.pressed(BTN_DOWN))
      {
        Menu++;
        if (Menu > 4)
        {
          Menu = 1;
        }
      }
      gb.display.println("        Menu");
      gb.display.println("");

      if (Menu == 1)
      {
        gb.display.println("  New Game");
        gb.display.println(" Instruction");
        gb.display.println(" Credits");
        gb.display.println(" Top Score");
      }

      if (Menu == 2)
      {
        gb.display.println(" New Game");
        gb.display.println("  Instruction");
        gb.display.println(" Credits");
        gb.display.println(" Top Score");
      }

      if (Menu == 3)
      {
        gb.display.println(" New Game");
        gb.display.println(" Instruction");
        gb.display.println("  Credits");
        gb.display.println(" Top Score");
      }

      if (Menu == 4)
      {
        gb.display.println(" New Game");
        gb.display.println(" Instruction");
        gb.display.println(" Credits");
        gb.display.println("  Top Score");
      }

      if (gb.buttons.pressed(BTN_A))
      {
        Choice = Menu;
      }
    }

    //Instruction
    if (Choice == 2)
    {
      gb.display.println("     Instruction");
      gb.display.println("");
      gb.display.println(" Kill bandits");
      gb.display.println(" Don't kill civilians");
      gb.display.println(" Earn points");
      gb.display.println(" Don't get killed");

      if (gb.buttons.pressed(BTN_B))
      {
        Choice = 0;
      }
    }

    //Credits
    if (Choice == 3)
    {
      gb.display.println("       Credits");
      gb.display.println("     Siena Town");
      gb.display.println("");
      gb.display.println(" Patryk Kucinski");
      gb.display.println(" 'Kuciniak'");
      gb.display.println(" 2019");

      if (gb.buttons.pressed(BTN_B))
      {
        Choice = 0;
      }
    }

    //Top Score
    if (Choice == 4)
    {
      gb.display.println("      Top Score");
      gb.display.println("");
      gb.display.print(" Score:");
      gb.display.print(Topscore);

      if (gb.buttons.pressed(BTN_B))
      {
        Choice = 0;
      }
    }

    //GAME
    if (Choice == 1)
    {

      gb.display.drawBitmap(2, SheriffPosY, Sheriff);

      gb.display.print( Points);
      gb.display.print("  ");

      //LIVES
      int draw = 0;
      while (draw < Lives)
      {
        gb.display.print("\3");
        draw++;
      }

      //Control
      if (gb.buttons.pressed(BTN_UP))

      {
        SheriffPosY -= 10;
        if (SheriffPosY < 10)
        {
          SheriffPosY = 10;
        }
      }

      if (gb.buttons.pressed(BTN_DOWN))

      {
        SheriffPosY += 10;
        if (SheriffPosY > 30)
        {
          SheriffPosY = 30;
        }
      }

      //Bandit move
      if (BanditActive == false)
      {
        BanditPos = BanditPosY;
        while (BanditPos == BanditPosY)
        {
          BanditPosY = rand() % 3 + 1;
        }
        BanditActive = true;
      }

      //Bandit draw
      gb.display.drawBitmap(72, BanditPosY * 10, Bandit);

      if (rand() % 30 == 1)
      {
        CivilianActive = false;
      }

      //Bullet move
      if (Bullet == false)
      {
        ShootPosY = BanditPosY;
        Bullet = true;
      }
      gb.display.drawBitmap(ShootPosX, ShootPosY * 10, Shoot);

      ShootPosX--;

      //Bullet detection
      if (ShootPosX == 6 && ShootPosY * 10 == SheriffPosY && Bullet == true)
      {
        Lives -= 1;
        Bullet = false;
        ShootPosX = 68;
      }

      if (ShootPosX == 0 && Bullet == true)
      {
        Bullet = false;
        ShootPosX = 68;
      }

      //Civil move
      if (CivilianActive == false)
      {
        CivilianPosY = rand() % 3 + 1;
        CivilianActive = true;
      }

      //Civil draw
      gb.display.drawBitmap(50, CivilianPosY * 10, Civilian);

      if (rand() % 24 == 2)
      {
        BanditActive = false;
      }

      //Shoot detection
      if (gb.buttons.pressed(BTN_A) && SheriffPosY == BanditPosY * 10 && SheriffPosY != CivilianPosY * 10)
      {
        gb.popup(F("Shoot!"), 20);
        Points = Points + 1;
        BanditActive = false;
        gb.sound.playTick();

      }
      if (gb.buttons.pressed(BTN_A) && SheriffPosY == CivilianPosY * 10)
      {
        gb.popup(F("Civilian down!"), 20);
        Lives -= 1;
      }

      if (Lives == 0)
      {
        Choice = 5;
      }
    }

    //Game Over
    else if (Choice == 5)
    {
      if (Points > Topscore || Record == true)
      {
        Topscore = Points;
        EEPROM.write(0, Topscore);
        Record = true;

        gb.display.println("      Game Over");
        gb.display.println("");
        gb.display.println(" New record!");
        gb.display.print(" Your score:");
      }
      else
      {
        gb.display.println("      Game Over");
        gb.display.println("");
        gb.display.print(" Your score:");
      }
      gb.display.println(Points);
      gb.display.println("");
      gb.display.println(" A-Menu");
      gb.display.println(" B-Restart");


      if (gb.buttons.pressed(BTN_A))
      {
        Choice = 0;
        Points = 0;
        Record = false;
      }

      if (gb.buttons.pressed(BTN_B))
      {
        Choice = 1;
        Points = 0;
        Record = false;
      }

    
      //Reset values
      SheriffPosY = 20;
      BanditPosY = 2;
      BanditActive = false;
      CivilianActive = false;
      Lives = 3;
    }
  }
}
