# ENGR103-Final-Project
OBJECTIVE: Be the first player to get to 10 points.

RULES: This is a two player dice game to play on the Circuit PLayground Express board. First player to get to 10 points wins and you can choose to either press button A to roll the dice or press button B to skip your turn. If you go over 10 points, your score gets reset back to 0. 

SCORING SYSTEM: Rolling a 1, 4, or 5 gets you your roll plus 1 extra point. Rolling a 2 or 3 just gets you the points from your dice roll and rolling a 6 loses you a point.

INPUTS: 
  Button A: Interrupt driven and is triggered when button is pressed.
  Button B: Interrupt driven and is triggered when button is pressed.
  Light Sensor Value: Uses light sensor value to seed the random number generator.

OUTPUTS: 
  Dice Roll Animation: Uses the LEDs to display a spinning animaton pattern when a new roll is requested.
  Dice Roll Number: Determines a random number from 1 to 6 and displays the corresponding dots on the LEDs.
  Speaker: Uses the speaker to speak the dice number that is rolled. It also says "Bravo" when a player wins and "pass" when a player skips their turns.
  Winning Condition: Checks the winning condition (when the score is = 10 points). When a player wins it displays an LED pattern and the speaker says "Bravo".
  Serial Monitor: After each role, the updated player scores are printed in the serial monitor. When someone wins, it also prints "Player A wins!" or "Player B     wins!" into the serial monitor.
  



