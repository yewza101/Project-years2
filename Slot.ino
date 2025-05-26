int betAmount = 1;
int coins = 10;
int buttonPin = 10;
int buttonState = 0;
int lastButtonState = 0;
int ledPins[] = {2,11,12};
int slotStore[3] = {0,0,0};
byte segmentPins[] = {3,4,5,6,7,8,9};

void displayValue(int num);
void ledWinning777();

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(buttonPin, INPUT_PULLUP);

    lastButtonState = digitalRead(buttonPin);4
  
    for(int i =0; i<7; i++){
      pinMode(segmentPins[i], OUTPUT);
    }

    for(int i =0; i<3; i++){
      pinMode(ledPins[i], OUTPUT);
    }
    randomSeed(analogRead(A0));
}

void loop() {
    if (Serial.available()>0){
      int newBet = Serial.parseInt();
      if (newBet > 0 && newBet <= coins){
        betAmount = newBet;
        Serial.print("Bet amount set to: ");
        Serial.println(betAmount);
      }else if(newBet < 0 || newBet > coins){
        Serial.println("Invalid bet. Must be more than 0 and less or equal than your coin balance");
      }
    }
  // put your main code here, to run repeatedly:
    buttonState = digitalRead(buttonPin);
    
    if(buttonState == HIGH && lastButtonState == LOW){
      
      delay(50);
      if (coins <= 0){
        Serial.println("No coins left! Please insert more coins");
      }
      else{
      coins -= betAmount;
      Serial.print("Spin Started. Coins left: ");
      Serial.println(coins);
      for(int i = 0; i < 3; i++){
        slotStore[i] = random(0,10);
        displayValue(slotStore[i]);
        delay(1000); 

        }
      
      //end of the spin
      displayValue(slotStore[2]);
      delay(1500);

      if (slotStore[0]==slotStore[1] && slotStore[1]==slotStore[2]){
        ledJackpotWinning777();
        coins += 5* betAmount;
        Serial.print("Jackpot!!!!! +");
        Serial.print(5 * betAmount);
        Serial.println(" coins");
      }
      else if (slotStore[0]==slotStore[1] || slotStore[1]==slotStore[2] || slotStore[0]==slotStore[2]){
        ledMinorWinning777();
        coins += 2*betAmount;
        Serial.print("Minor win! +");
        Serial.print(2 * betAmount);
        Serial.println(" coins");
      }else{
        Serial.println("No match. Better luck next time!");
      }
      Serial.print("Current coins: ");
      Serial.println(coins);
      delay(500);
      }
    }
    lastButtonState = buttonState;
}

void displayValue(int rnum){
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], LOW);
  }
  
   switch (rnum) {
    case 0:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[4], HIGH); // e
      digitalWrite(segmentPins[5], HIGH); // f
      break;
    case 1:
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      break;
    case 2:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[4], HIGH); // e
      digitalWrite(segmentPins[6], HIGH); // g
      break;
    case 3:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[6], HIGH); // g
      break;
    case 4:
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[5], HIGH); // f
      digitalWrite(segmentPins[6], HIGH); // g
      break;
    case 5:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[5], HIGH); // f
      digitalWrite(segmentPins[6], HIGH); // g
      break;
    case 6:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[4], HIGH); // e
      digitalWrite(segmentPins[5], HIGH); // f
      digitalWrite(segmentPins[6], HIGH); // g
      break;
    case 7:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      break;
    case 8:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[4], HIGH); // e
      digitalWrite(segmentPins[5], HIGH); // f
      digitalWrite(segmentPins[6], HIGH); // g
      break;
    case 9:
      digitalWrite(segmentPins[0], HIGH); // a
      digitalWrite(segmentPins[1], HIGH); // b
      digitalWrite(segmentPins[2], HIGH); // c
      digitalWrite(segmentPins[3], HIGH); // d
      digitalWrite(segmentPins[5], HIGH); // f
      digitalWrite(segmentPins[6], HIGH); // g
      break;
    default:
      break;
  }
}

void ledJackpotWinning777(){
  for(int i = 0; i<6; i++){
    digitalWrite (ledPins[0], 1);
    digitalWrite (ledPins[1], 0);
    digitalWrite (ledPins[2], 0);
    delay(500);

    digitalWrite (ledPins[0], 0);
    digitalWrite (ledPins[1], 1);
    digitalWrite (ledPins[2], 0);
    delay(500);

    digitalWrite (ledPins[0], 0);
    digitalWrite (ledPins[1], 0);
    digitalWrite (ledPins[2], 1);
    delay(500);

  }

    digitalWrite (ledPins[0], 0);
    digitalWrite (ledPins[1], 0);
    digitalWrite (ledPins[2], 0);
    delay(500);
}

void ledMinorWinning777(){
   for(int i = 0; i<6; i++){
    digitalWrite (ledPins[0], 1);
    delay(500);

    digitalWrite (ledPins[0], 0);
    digitalWrite (ledPins[1], 0);
    delay(500);

  }

    digitalWrite (ledPins[0], 0);
    digitalWrite (ledPins[1], 0);
    digitalWrite (ledPins[2], 0);
    delay(500);
}