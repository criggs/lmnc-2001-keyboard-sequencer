//LOOK MUM NO COMPUTER KEYBOARD SEQUENCER.

//VERSION 2.3 - Adds ARP feature

//VERSION 2.2 flips from reading pads high to reading pads low (if you have the kosmo format sequencer board from 2021-2024 you need to modify it to use this code, mod info on
//the look mum no computer website on the sequencer page in projects). it also is much more stable in function. and quicker!
//A SIMPLE DESIGN TO MAKE A 4017 STYLE SEQUENCER WITH MORE ADDED FUNCTIONS.
//MORE INFO CHECK LOOKMUMNOCOMPUTER.COM
//JOIN FORUM IF YOU HAVE ANY QUESTIONS
//ANY MODIFICATIONS PLEASE SHARE ON FORUM PEOPLE MAY ENJOY YOUR TAKE ON THIS
//SAM BATTLE 2021-2024
//BOOM

//In Look Mum No Computer Arduino Project Style Its been written in the purest plonker form.
//triple distilled plonker code.

// The distilled plonker code has been further refined by Chris Riggs to make it easier to add new features


/////////////////////////////////////////////////////////
//
// Settings you might want to tweak
//

/**
* This is the minimum sensitivity to sense a touch
*/
#define TOUCH_TRIGGER_SENSITIVITY 80 

/**
* This determines the allowed 'tightness' for detecting multiple fingers and prevents ghost fingers.
* 
* All sensed fingers must be no further than this amount below the maximum sensed finger value.
*/
#define TOUCH_SENSITIVITY_GROUPING 40

/**
* The number of cycles until a missing finger is considered no longer pressed.
* This smooths out the finger presses.
*/
#define FINGER_SMOOTHING_CYCLES 25



/////////////////////////////////////////////////////////
//
// Other Settings/Configuration
//

#define STEP1 2        //step 1 output
#define STEP2 3        //step 2 output
#define STEP3 4        //step 3 output
#define STEP4 5        //step 4 output
#define STEP5 6        //step 5 output
#define STEP6 7        //step 6 output
#define STEP7 8        //step 7 output
#define STEP8 9        //step 8 output
#define STEPBUTTON1 0  //these are the capacitive touch pads
#define STEPBUTTON2 1  //these are the capacitive touch pads
#define STEPBUTTON3 2  //these are the capacitive touch pads
#define STEPBUTTON4 3  //these are the capacitive touch pads
#define STEPBUTTON5 4  //these are the capacitive touch pads
#define STEPBUTTON6 5  //these are the capacitive touch pads
#define STEPBUTTON7 6  //these are the capacitive touch pads
#define STEPBUTTON8 7  //these are the capacitive touch pads

#define FORWARDS 12    //this is the pin that the forwards button (and coupled jack input) connects to
#define RESET 11       //this is the pin that the reset button (and coupled jack input) connects to
#define BACK 0         //this is the pin that the backwards button (and coupled jack input) connects to
#define ZERO 10        //this is the pin that the zero button (and coupled jack input) connects to
#define TOUCHGATE 1    //this is the gate output jack that turns on when a touch pad is being pressed
#define ROW_SELECT 13  //this is the pin that sets which row the "merge" jack is listenning to. HIGH is row A, LOW is row B

//Commands
#define CMD_FORWARD 1
#define CMD_BACKWARD 2
#define CMD_ZERO 3
#define CMD_RESET 4


int touchReadDelay = 0;  //a delay of zero! ooohllallaaa

int forwardInputValue = 0;
int zeroInputValue = 0;
int resetInputValue = 0;
int backInputValue = 0;

int command = 0;

int fingerDetectionCountdown[] = {0,0,0,0,0,0,0,0};
int fingerCount = 0;

int step = -1;

int row = 0;
int rowStep = 0;

int arpStep = 0;
bool arpModeActive = false;

void setup() {
  pinMode(ROW_SELECT, OUTPUT);
  pinMode(STEP1, OUTPUT);
  pinMode(STEP2, OUTPUT);
  pinMode(STEP3, OUTPUT);
  pinMode(STEP4, OUTPUT);
  pinMode(STEP5, OUTPUT);
  pinMode(STEP6, OUTPUT);
  pinMode(STEP7, OUTPUT);
  pinMode(STEP8, OUTPUT);
  pinMode(FORWARDS, INPUT);
  pinMode(BACK, INPUT);
  pinMode(RESET, INPUT);
  pinMode(ZERO, INPUT);
  pinMode(TOUCHGATE, OUTPUT);
}

/**
* Touchpad inputs
*/
void readTouchpads() {
  fingerCount = 0;


  int maxFingerValue = 0;
  int minFingerValue = 1000000;

  int fingerValues[8]; 

  //Read all of the pads/finger values and find the min/max
  for (int i = 7; i >= 0; i--) {
    int val = analogRead(i);
    fingerValues[i] = val;
    minFingerValue = min(minFingerValue, val);
    maxFingerValue = max(maxFingerValue, val);
  }

  // Dynamically set the threshold based on the max value we got. We need at least TOUCH_TRIGGER_SENSITIVITY
  int threshold = max(TOUCH_TRIGGER_SENSITIVITY, maxFingerValue - TOUCH_SENSITIVITY_GROUPING);

  for (int i = 7; i >= 0; i--) {
    int touchValue = fingerValues[i];

    if (touchValue > threshold) {
      fingerCount++;
      fingerDetectionCountdown[i] = FINGER_SMOOTHING_CYCLES; // Reset the cooldown
      digitalWrite(TOUCHGATE, HIGH);
      delay(touchReadDelay);
    } else if(fingerDetectionCountdown[i] > 0){
      // We still have an active cooldown
      if(--fingerDetectionCountdown[i] > 0){
        fingerCount++;
      }
    }
  }

  // We're no longer touching any pads, we just stopped.
  // We'll wait some additional cycles while acting like the pad is still being
  // pressed to smooth out any noise.
  if (fingerCount == 0) {
    digitalWrite(TOUCHGATE, LOW);
  }
}

/**
* Clock and control inputs
*/
void readControlInputs() {

  command = 0;

  // A finger is being held down. No need to read the controls/clock inputs

  int newForwardInputValue = digitalRead(FORWARDS);
  int newBackInputValue = digitalRead(BACK);
  int newZeroInputValue = digitalRead(ZERO);
  int newResetInputValue = digitalRead(RESET);

  // We can only read in a single command per iteration. Set the priority based on the order of the conditionals (if/else statemenst)
  if ((newResetInputValue == LOW) & (resetInputValue == HIGH))  //reset to 1
  {
    command = CMD_RESET;
  } else if((newZeroInputValue == LOW) & (zeroInputValue == HIGH)){
    command = CMD_ZERO;
  } else if((newBackInputValue == LOW) & (backInputValue == HIGH)){
    command = CMD_BACKWARD;
  } else if((newForwardInputValue == LOW) & (forwardInputValue == HIGH)){
    command = CMD_FORWARD;
  }

  forwardInputValue = newForwardInputValue;
  zeroInputValue = newZeroInputValue;
  resetInputValue = newResetInputValue;
  backInputValue = newBackInputValue;
}


int getStepForFingerNum(int n){
  n = n % fingerCount;
    for(int i = 0; i < 8; i++){
      if(fingerDetectionCountdown[i] > 0){
        if(n == 0){
          return i;
        } else {
          n--;
        }
      }
    }
    return -1;
}

void updateStep() {
  if(fingerCount == 0){
    arpModeActive = false; // No fingers, no arp
  }

  if(fingerCount > 0){
    // //Highest pad/step wins, by default
    if(!arpModeActive){
      for(int i = 0; i < 8; i++){
          if(fingerDetectionCountdown[i] > 0){
            step = i;
          }
      }
    }

    // Multiple fingers and we got a step command?!?! Time to ARP!!!
    if(command == CMD_FORWARD){
      step = getStepForFingerNum(arpStep++);
      arpModeActive = true; 
    } else if(command == CMD_BACKWARD) {
      step = getStepForFingerNum(arpStep--);
      arpModeActive = true;
    }
    if(arpStep < 0){
      arpStep = fingerCount - 1;
    }
    arpStep = arpStep % fingerCount;

  } else if(command != 0){
    //Handle the current command
    if(command == CMD_FORWARD){
      step = (step + 1) % 16;
    } else if(command == CMD_BACKWARD){
      step = (step - 1);
      if(step < 0){
        step = 15;
      }
    } else if(command == CMD_ZERO){
      step = -1;
    } else if(command == CMD_RESET){
      step = 0;
    }
  }

  if (step == -1) {  // We don't have an active step
    rowStep = -1;
    row = 0;
  } else {
    row = step / 8;
    rowStep = step % 8;
  }

  //Set the right step.
  for (int i = 0; i < 8; i++) {
    digitalWrite(STEP1 + i, i == rowStep ? HIGH : LOW);
    digitalWrite(ROW_SELECT, row == 1 ? LOW : HIGH);
  }
}

void loop() {
  readTouchpads();
  readControlInputs();
  updateStep();
}
