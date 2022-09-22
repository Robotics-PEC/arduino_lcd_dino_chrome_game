/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 7
 * LCD D5 pin to digital pin 6
 * LCD D6 pin to digital pin 5
 * LCD D7 pin to digital pin 4
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.
*/

// include the livrary code:
#include <LiquidCrystal.h>

// defined the pins for the LCD
#define RS 12
#define EN 11
#define D4 7
#define D5 6
#define D6 5
#define D7 4

// defined vutton pin for input
#define BTN_PIN 2

// defined dinasour position as 2
#define dinasour_position 2

int game_start = 0;

int tree0 = 0;
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
int game_speed = 300;

// initialize the library by assosicating any needed LCD interface pins
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);


// defined binaries for the tree
byte tree[8] = { 0B00100,
                 0B00101,
                 0B00101,
                 0B10101,
                 0B10110,
                 0B01100,
                 0B00100,
                 0B00100
               };

// defined binaries for dinasour animation
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

// defined a function to spawn a new tree 
void spawnTree(int &tree, int &tree_previous){
      randomSeed(analogRead(A0));
      tree = random(4,12) + tree_previous;
}

// defined a function to display the tree
void displayTree(int &tree){
  lcd.setCursor(tree , 1);
  lcd.write((uint8_t)0);
}

// 
void displayDinasour(){
  if(motion){
    lcd.write((uint8_t)1);
    motion--;
    }
    else{
      lcd.write((uint8_t)2);
      motion++;
    }
}

// function to read button input and initiate jum if game is running if not then start the game
void jump(){ 
  if (game_start){
    Jump = 1;
  } 
  else {
    game_start = 1;
    
    tree0 = 15;
    spawnTree(tree1,tree0);
    spawnTree(tree2,tree1);
    spawnTree(tree3,tree2);
  }
}


void setup() {
  // Create the character for the dinasour and tree
  lcd.createChar(0, tree);
  lcd.createChar(1, dina1);
  lcd.createChar(2, dina2);
  
  // initialised the LCD
  lcd.begin(16, 2);
  lcd.print("Press to start");
  
  // defined the button pin as input and set up an intrrupt on falling edge 
  pinMode(BTN_PIN , INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), jump,  FALLING);
}

void loop() {
  while (game_start) {
    if(tree0 < 0){
      spawnTree(tree0,tree3);
    }

    if(tree1 < 0){
      spawnTree(tree1,tree0);
    }

    if(tree2 < 0){
      spawnTree(tree2,tree1);
    }

    if(tree3 < 0){
      spawnTree(tree3,tree2);
    }
    did_jump = false;
    lcd.clear();
    
    if (Jump){
      lcd.setCursor(dinasour_position , 0);
      Jump = 0;
      did_jump = true;
    } 
    else{
      lcd.setCursor(dinasour_position , 1);
    }

    displayDinasour();

    if(tree0 <= 16){
      displayTree(tree0);
    }

    if(tree1 <= 16){
      displayTree(tree1);
    }

     if(tree2 <= 16){
      displayTree(tree2);
    }
    
    if(tree3 <= 16){
      displayTree(tree3);
    }


    if(((tree0 == dinasour_position) || (tree1 == dinasour_position) || (tree2 == dinasour_position)|| (tree3 == dinasour_position)) && !did_jump )
    {
      if(score>high_score){
        high_score=score;
      }

      if(tree0 == dinasour_position){
        collision_tree = tree0;
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
    else{
      // increment the score counter if collision did not occur
      score++;
    }
    
    // decrease the distance of all the trees by 1
    tree0 --;
    tree1 --;
    tree2 --;
    tree3 --;
    delay(game_speed);
  }
}
