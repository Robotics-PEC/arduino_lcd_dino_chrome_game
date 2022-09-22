#include <LiquidCrystal.h>

#define RS 12
#define EN 11
#define D4 7
#define D5 6
#define D6 5
#define D7 4
#define BTN_PIN 2

#define dinasour_position 2

int game_start = 0;
int tree_4 = 0;
int tree1 = 0;
int tree2 = 0;
int tree3 = 0;
int collision_tree = 0;
int dinasour_line = 0;
int Jump = 0;
bool did_jump = false;
int score = 0;
int high_score = 0;
int motion = 0;
int delay_time = 300;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);


byte tree[8] = { 0B00100,
                 0B00101,
                 0B00101,
                 0B10101,
                 0B10110,
                 0B01100,
                 0B00100,
                 0B00100
               };

byte dina1[8] = { 0B00111,
                  0B00100,
                  0B00111,
                  0B00100,
                  0B00100,
                  0B01100,
                  0B10010,
                  0B10000
               };

byte dina2[8] = { 0B00111,
                  0B00100,
                  0B00111,
                  0B00100,
                  0B00100,
                  0B01100,
                  0B10010,
                  0B00010
               };

void jump(){ 
  if (game_start)
  {
    Jump = 1;
  } else {
    game_start = 1;
    tree_4 = 15;
    randomSeed(analogRead(A0));
    tree1 = random(4,12) + tree_4;
    randomSeed(analogRead(A0));
    tree2 = random(4,12) + tree1;
    randomSeed(analogRead(A0));
    tree3 = random(4,12) + tree2;
  }
}

void setup() {
  lcd.createChar(0, tree);
  lcd.createChar(1, dina1);
  lcd.createChar(2, dina2);
  
  lcd.begin(16, 2);
  lcd.print("Press to start");

  pinMode(BTN_PIN , INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), jump,  FALLING);
}

void loop() {
  while (game_start) {
    if (tree_4 < 0)
    {
      randomSeed(analogRead(A0));
      tree_4 = random(4,12) + tree3;
    }
    
    if (tree1 < 0)
    {
      randomSeed(analogRead(A0));
      tree1 = random(4,12) + tree_4;
    }

    if (tree2 < 0)
    {
      randomSeed(analogRead(A0));
      tree2 = random(4,12) + tree1;
    }
    if (tree3 < 0)
    {
      randomSeed(analogRead(A0));
      tree3 = random(4,12) + tree2;
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

    if(motion){
    lcd.write((uint8_t)1);
    motion--;
    }
    else{
      lcd.write((uint8_t)2);
      motion++;
    }

    if(tree_4 <= 16){
      lcd.setCursor(tree_4 , 1);
      lcd.write((uint8_t)0);
    }

    if(tree1 <= 16){
      lcd.setCursor(tree1 , 1);
      lcd.write((uint8_t)0);
    }

     if(tree2 <= 16){
      lcd.setCursor(tree2 , 1);
      lcd.write((uint8_t)0);
    }
    
    if(tree3 <= 16){
      lcd.setCursor(tree3 , 1);
      lcd.write((uint8_t)0);
    }


    if(((tree_4 == dinasour_position) || (tree1 == dinasour_position) || (tree2 == dinasour_position)|| (tree3 == dinasour_position)) && !did_jump )
    {
      if(score>high_score){
        high_score=score;
      }

      if(tree_4 == dinasour_position){
        collision_tree = tree_4;
      }
      else if(tree1 == dinasour_position){
        collision_tree = tree1;
      }
      else if(tree3 == dinasour_position){
        collision_tree = tree3;
      }
      else{
        collision_tree = tree2;
      }
      
      // collison
      did_jump = false;
      game_start = 0;
      lcd.clear();
      lcd.setCursor(collision_tree+1,1);
      lcd.write((uint8_t)0);
      lcd.setCursor(collision_tree,1);
      lcd.write((uint8_t)1);
      delay(300);
      lcd.clear();
      delay(600);
      lcd.setCursor(collision_tree+1,1);
      lcd.write((uint8_t)0);
      lcd.setCursor(dinasour_position,1);
      lcd.write((uint8_t)1);
      delay(600);
      lcd.clear();
      delay(500);
      lcd.setCursor(collision_tree+1,1);
      lcd.write((uint8_t)0);
      lcd.setCursor(dinasour_position,1);
      lcd.write((uint8_t)1);
      delay(600);
      lcd.clear();
      lcd.setCursor(0, 0);
      delay(600);
      lcd.clear();
      delay(600);
      lcd.setCursor(0, 0);
      lcd.print("High Score: ");
      lcd.print(high_score);
      lcd.setCursor(0, 1);
      lcd.print("Score: ");
      lcd.print(score);
      delay(1500);
      lcd.clear();
      delay(400);
      lcd.setCursor(0, 0);
      lcd.print("Press Again to");
      lcd.setCursor(0, 1);
      lcd.print("Play");
      score =0;
      break;
    }
    else if(((tree_4 == dinasour_position) || (tree1 == dinasour_position) || (tree2 == dinasour_position)|| (tree3 == dinasour_position)) && did_jump){
      score++;
    }
    tree_4 --;
    tree1 --;
    tree2 --;
    tree3 --;
    delay(delay_time);
  }
}
