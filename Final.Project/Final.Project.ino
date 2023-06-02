#include <Adafruit_CircuitPlayground.h>

#define DICE_COLOR          0xEA6292    // Dice digits color

int scoreA = 0;
int scoreB = 0;
int winningScore = 10;
bool isPlayerATurn = 1;
volatile bool rolling = 0;
volatile bool newRoll = 0;
volatile bool skipTurn = 0;
uint8_t rollNumber;

/*used the pixel pattern array down below and some of the bools up above from the dice code.
https://learn.adafruit.com/circuit-playground-d6-dice/d6-dice-code*/

uint8_t dicePixels[6][6] = 
{  // Pixel pattern for dice roll
  { 2, 0, 0, 0, 0, 0 } ,      // Roll = 1
  { 4, 9, 0, 0, 0, 0 } ,      //        2
  { 0, 4, 7, 0, 0, 0 } ,      //        3
  { 1, 3, 6, 8, 0, 0 } ,      //        4
  { 0, 2, 4, 5, 9, 0 } ,      //        5
  { 0, 2, 4, 5, 7, 9 } ,      //        6
};

const uint8_t spONE[]           PROGMEM = {0x66,0x4E,0xA8,0x7A,0x8D,0xED,0xC4,0xB5,0xCD,0x89,0xD4,0xBC,0xA2,0xDB,0xD1,0x27,0xBE,0x33,0x4C,0xD9,0x4F,0x9B,0x4D,0x57,0x8A,0x76,0xBE,0xF5,0xA9,0xAA,0x2E,0x4F,0xD5,0xCD,0xB7,0xD9,0x43,0x5B,0x87,0x13,0x4C,0x0D,0xA7,0x75,0xAB,0x7B,0x3E,0xE3,0x19,0x6F,0x7F,0xA7,0xA7,0xF9,0xD0,0x30,0x5B,0x1D,0x9E,0x9A,0x34,0x44,0xBC,0xB6,0x7D,0xFE,0x1F};
const uint8_t spTWO[]           PROGMEM = {0x06,0xB8,0x59,0x34,0x00,0x27,0xD6,0x38,0x60,0x58,0xD3,0x91,0x55,0x2D,0xAA,0x65,0x9D,0x4F,0xD1,0xB8,0x39,0x17,0x67,0xBF,0xC5,0xAE,0x5A,0x1D,0xB5,0x7A,0x06,0xF6,0xA9,0x7D,0x9D,0xD2,0x6C,0x55,0xA5,0x26,0x75,0xC9,0x9B,0xDF,0xFC,0x6E,0x0E,0x63,0x3A,0x34,0x70,0xAF,0x3E,0xFF,0x1F};
const uint8_t spTHREE[]         PROGMEM = {0x0C,0xE8,0x2E,0x94,0x01,0x4D,0xBA,0x4A,0x40,0x03,0x16,0x68,0x69,0x36,0x1C,0xE9,0xBA,0xB8,0xE5,0x39,0x70,0x72,0x84,0xDB,0x51,0xA4,0xA8,0x4E,0xA3,0xC9,0x77,0xB1,0xCA,0xD6,0x52,0xA8,0x71,0xED,0x2A,0x7B,0x4B,0xA6,0xE0,0x37,0xB7,0x5A,0xDD,0x48,0x8E,0x94,0xF1,0x64,0xCE,0x6D,0x19,0x55,0x91,0xBC,0x6E,0xD7,0xAD,0x1E,0xF5,0xAA,0x77,0x7A,0xC6,0x70,0x22,0xCD,0xC7,0xF9,0x89,0xCF,0xFF,0x03};
const uint8_t spFOUR[]          PROGMEM = {0x08,0x68,0x21,0x0D,0x03,0x04,0x28,0xCE,0x92,0x03,0x23,0x4A,0xCA,0xA6,0x1C,0xDA,0xAD,0xB4,0x70,0xED,0x19,0x64,0xB7,0xD3,0x91,0x45,0x51,0x35,0x89,0xEA,0x66,0xDE,0xEA,0xE0,0xAB,0xD3,0x29,0x4F,0x1F,0xFA,0x52,0xF6,0x90,0x52,0x3B,0x25,0x7F,0xDD,0xCB,0x9D,0x72,0x72,0x8C,0x79,0xCB,0x6F,0xFA,0xD2,0x10,0x9E,0xB4,0x2C,0xE1,0x4F,0x25,0x70,0x3A,0xDC,0xBA,0x2F,0x6F,0xC1,0x75,0xCB,0xF2,0xFF};
const uint8_t spFIVE[]          PROGMEM = {0x08,0x68,0x4E,0x9D,0x02,0x1C,0x60,0xC0,0x8C,0x69,0x12,0xB0,0xC0,0x28,0xAB,0x8C,0x9C,0xC0,0x2D,0xBB,0x38,0x79,0x31,0x15,0xA3,0xB6,0xE4,0x16,0xB7,0xDC,0xF5,0x6E,0x57,0xDF,0x54,0x5B,0x85,0xBE,0xD9,0xE3,0x5C,0xC6,0xD6,0x6D,0xB1,0xA5,0xBF,0x99,0x5B,0x3B,0x5A,0x30,0x09,0xAF,0x2F,0xED,0xEC,0x31,0xC4,0x5C,0xBE,0xD6,0x33,0xDD,0xAD,0x88,0x87,0xE2,0xD2,0xF2,0xF4,0xE0,0x16,0x2A,0xB2,0xE3,0x63,0x1F,0xF9,0xF0,0xE7,0xFF,0x01};
const uint8_t spSIX[]           PROGMEM = {0x04,0xF8,0xAD,0x4C,0x02,0x16,0xB0,0x80,0x06,0x56,0x35,0x5D,0xA8,0x2A,0x6D,0xB9,0xCD,0x69,0xBB,0x2B,0x55,0xB5,0x2D,0xB7,0xDB,0xFD,0x9C,0x0D,0xD8,0x32,0x8A,0x7B,0xBC,0x02,0x00,0x03,0x0C,0xB1,0x2E,0x80,0xDF,0xD2,0x35,0x20,0x01,0x0E,0x60,0xE0,0xFF,0x01};
const uint8_t spPASS[]          PROGMEM = {0x0A,0xC8,0x33,0x83,0x03,0xA3,0xEC,0x55,0x2D,0xD4,0x12,0xAF,0xAA,0x04,0xC9,0xD4,0x0E,0x7D,0xAA,0x16,0x4A,0x33,0x65,0xCE,0xAD,0x6F,0x7D,0x9A,0x9A,0xDC,0xDB,0x62,0xEE,0x6D,0x6E,0x73,0xC6,0x12,0xDD,0x5B,0x6B,0xEE,0x5D,0xF6,0x3A,0xCE,0xAA,0xD2,0x26,0xED,0x75,0xBB,0x9B,0x4D,0x6D,0xF1,0x25,0xFD,0x77,0x7F,0xEF,0xD2,0xCE,0x9D,0x46,0x00,0x4B,0x17,0x2B,0xE0,0x8F,0x52,0x0B,0x68,0x40,0x02,0x1C,0x90,0xC0,0xFF,0x03};
const uint8_t spBRAVO[]         PROGMEM = {0x61,0x5A,0xBA,0xC2,0xDD,0x62,0x85,0xD6,0xE8,0x15,0x59,0xB1,0x97,0x9A,0x30,0xD5,0xBC,0x85,0xDF,0xA8,0x63,0x0F,0xE9,0x50,0xE5,0xA7,0xCA,0x6E,0x22,0x5D,0x57,0xEF,0x72,0x97,0xB3,0x2A,0x6D,0x74,0x15,0xE9,0xBA,0x3A,0xF6,0x66,0xE8,0x3E,0xD4,0x5C,0x65,0xD7,0x31,0x2D,0x95,0x54,0xBB,0x8B,0xDF,0xD9,0xAE,0xB1,0xA1,0xAC,0x0E,0x51,0x3F,0xE7,0xB6,0x14,0xD2,0x35,0x4E,0xEE,0xFB,0x5E,0x77,0xB3,0x7B,0xDF,0x19,0x2C,0x7D,0xEC,0xE9,0x2F,0x73,0x05,0xDF,0x19,0x2C,0x7D,0xF8,0xF3,0xFF};


void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(100);

  // Setup button interrupts and callback functions
  attachInterrupt(digitalPinToInterrupt(4), buttonAPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(5), skipTurnButton, FALLING);

  // Seed the random function with light sensor value
  randomSeed(CircuitPlayground.lightSensor());
}


void loop() {
  //code for skipping turns
  if (skipTurn){
    isPlayerATurn = !isPlayerATurn;
    skipTurn = 0;
    CircuitPlayground.clearPixels();
    delay(1000);
  }

  // Check if a new roll is requested
  if (newRoll) {
    spinAnimation(); // Play the spinning animation and tone
    rollNumber = random(1, 7);  // Compute a random number from 1 to 6
    CircuitPlayground.clearPixels(); // Display the dice roll number
    for (int p = 0; p < rollNumber; p++) 
    {
      CircuitPlayground.setPixelColor(dicePixels[rollNumber - 1][p], DICE_COLOR);
    }

    speakNumber(rollNumber); // Speak the number rolled
    applyRules(); //applyrules

    //check for winning condition
    if (scoreA == winningScore || scoreB == winningScore){
      if (scoreA == winningScore){
        Serial.println("PLAYER A WINS!");
        for (int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i, 0, 255, 0);  // Green color (R, G, B)
      }
        delay(50);
        CircuitPlayground.speaker.say(spBRAVO);
      }
      else {
        Serial.println("PLAYER B WINS!");
        for (int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i, 0, 255, 0);  // Green color (R, G, B)
      }
        delay(50);
        CircuitPlayground.speaker.say(spBRAVO);
      }

    // Reset the scores and game state
      scoreA = 0;
      scoreB = 0;
      isPlayerATurn = 1;
  }

    // Reset the score if a player goes over the target number
    if (scoreA > winningScore) {
      scoreA = 0;
    }
    if (scoreB > winningScore) {
      scoreB = 0;
    }

 // Print the current scores of both players after resetting
  Serial.print(" Player A score: ");
  Serial.print(scoreA);
  Serial.print(" Player B score: ");
  Serial.print(scoreB);
  Serial.println();

  // Delay for a short period to show the result
  delay(2000);

  // Reset the roll state
    CircuitPlayground.clearPixels();
    newRoll = false;
    rolling = false;
    isPlayerATurn = !isPlayerATurn;
  }
}

void skipTurnButton()
{
  skipTurn = 1;
  for (int i = 0; i < 10; i++) {
  CircuitPlayground.setPixelColor(i, 255, 0, 0);  // Green color (R, G, B)
  }
  CircuitPlayground.speaker.say(spPASS);
}

void buttonAPressed() {
  if (!rolling) {
    newRoll = 1;
    rolling = 1;
  }
}


void applyRules()
{
 //rule: rolling a 1 gives you an extra point
 if (rollNumber==1 || rollNumber==4 || rollNumber == 5){
   if (isPlayerATurn){
     scoreA += (rollNumber + 1);
   } else {
     scoreB += (rollNumber + 1);
   }
   return;
 }

//rule: rolling a 2 or 3 just adds that number to score
if (rollNumber == 2 || rollNumber == 3){
  if (isPlayerATurn){
    scoreA += rollNumber;
  } else {
    scoreB += rollNumber;
  }
  return;
}
 //rule: rolling a 6 makes you lose a point
 if (rollNumber==6){
   if (isPlayerATurn){
     scoreA--;
   }else{
     scoreB--;
   }
   return;
 }
}

void spinAnimation() {
  int numSteps = 10;

  for (int i = 0; i < numSteps; i++) {
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(i, DICE_COLOR);
    CircuitPlayground.speaker.set(200);
    CircuitPlayground.playTone(i * 200 + 200, 50);
    delay(50);
  }

  for (int i = numSteps - 2; i >= 1; i--) {
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(i, DICE_COLOR);
    delay(50);
  }
}

void speakNumber(uint8_t number) {
  CircuitPlayground.speaker.set(255);
switch (number) {
    case 1:
      CircuitPlayground.speaker.say(spONE);
      break;
    case 2:
      CircuitPlayground.speaker.say(spTWO);
      break;
    case 3:
      CircuitPlayground.speaker.say(spTHREE);
      break;
    case 4:
      CircuitPlayground.speaker.say(spFOUR);
      break;
    case 5:
      CircuitPlayground.speaker.say(spFIVE);
      break;
    case 6:
      CircuitPlayground.speaker.say(spSIX);
      break;
    default:
      return;
  }
}