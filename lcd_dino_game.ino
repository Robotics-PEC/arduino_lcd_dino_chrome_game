#include <LiquidCrystal.h>

#define dinasour_position 2


int game_start = 0;
int nearest_tree = 15;
int dinasour_line = 0;
int Jump = 0;
bool did_jump = false;
int score = 0;
int high_score = 0;

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);


byte tree[8] = { 0B00100,
                 0B00101,
                 0B00101,
                 0B10101,
                 0B10110,
                 0B01100,
                 0B00100,
                 0B00100
               };

byte dina[8] = { 0B00111,
                 0B00100,
                 0B00111,
                 0B00100,
                 0B00100,
                 0B01100,
                 0B10010,
                 0B10010
               };
void jump()
{ if (game_start)
  {
    Jump = 1;

  } else {
    game_start = 1;
    lcd.clear();
    lcd.write((uint8_t)1);
    nearest_tree = 15;
  }

}

void setup() {


  lcd.createChar(0, tree);
  lcd.createChar(1, dina);
  lcd.begin(16, 2);
  lcd.print("Press to start");

  randomSeed(analogRead(A0));
  nearest_tree = random(4,17);


  pinMode(2 , INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), jump,  FALLING);
}



void loop() {





  while (game_start) {
    if (nearest_tree < 0)
    {
      randomSeed(analogRead(26));
      nearest_tree = random(6,17);
    }
    did_jump = false;
    lcd.clear();
    if (Jump) {
      lcd.setCursor(dinasour_position , 0);
      Jump = 0;
      did_jump = true;
    } else {
      lcd.setCursor(dinasour_position , 1);
    }

    lcd.write((uint8_t)1);

    lcd.setCursor(nearest_tree , 1);
    lcd.write((uint8_t)0);


    if (nearest_tree == dinasour_position && !did_jump )
    {
      if(score>high_score){
        high_score=score;
      }
      
      // collison
      did_jump = false;
      game_start = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game Over");
      delay(400);
      lcd.clear();
      delay(400);
      lcd.setCursor(0, 0);
      lcd.print("Game Over");
      delay(400);
      lcd.clear();
      delay(600);
      lcd.setCursor(0, 0);
      lcd.print("High Score: ");
      lcd.print(high_score);
      lcd.setCursor(0, 1);
      lcd.print("Score: ");
      lcd.print(score);
      delay(1000);
      lcd.clear();
      delay(400);
      lcd.setCursor(0, 0);
      lcd.print("High Score: ");
      lcd.print(high_score);
      lcd.setCursor(0, 1);
      lcd.print("Press Again");
      score =0;
      break;
    }
    else if(nearest_tree == dinasour_position && did_jump){
      score++;
    }

    nearest_tree --;
    delay(250);

  }


}
