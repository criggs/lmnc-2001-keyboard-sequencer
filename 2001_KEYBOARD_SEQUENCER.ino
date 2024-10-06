//LOOK MUM NO COMPUTER KEYBOARD SEQUENCER.
//VERSION 2.2
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


// this is the capacitive touch threshold for each pad
// go for a lower number for more sensitivity if you have fingers as dry as the sahara
int TOUCH_THRESHOLDS[] = {
  80,
  80,
  80,
  80,
  100,
  120,
  180,
  260,
};
int touchReadDelay = 0;  //a delay of zero! ooohllallaaa

int forwardInputValue = 0;
int zeroInputValue = 0;
int resetInputValue = 0;
int backInputValue = 0;

int activeFinger = -1;
int clockbypass = 0;
int fingerDetectionCountdown = 0;

int step = -1;

int row = 0;
int rowStep = 0;

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

  bool padTouchDetected = false;
  for (int i = 7; i >= 0; i--) {

    if (activeFinger > i) {
      // Ignore this touchpad, we have an active finger at a higher priority/position
      continue;
    }

    int touchValue = analogRead(i);
    if ((touchValue > TOUCH_THRESHOLDS[i])) {
      step = i;
      activeFinger = i;
      clockbypass = 1;
      fingerDetectionCountdown = 100;
      digitalWrite(TOUCHGATE, HIGH);
      delay(touchReadDelay);
      padTouchDetected = true;
    }
  }

  // We're no longer touching the pad, we just stopped.
  // We'll wait some additional cycles while acting like the pad is still being
  // pressed to smooth out any noise.
  if (!padTouchDetected && fingerDetectionCountdown > 0) {
    fingerDetectionCountdown--;

    // We've hit enough cycles of not seeing a finger. Let the clock tick away.
    if (fingerDetectionCountdown == 0) {
      clockbypass = 0;
      fingerDetectionCountdown = 0;
      activeFinger = -1;
      digitalWrite(TOUCHGATE, LOW);
    }
  }


}

/**
* Clock and control inputs
*/
void readControlInputs() {

  // A finger is being held down. No need to read the controls/clock inputs
  if (clockbypass) {
    return;
  }

  int newForwardInputValue = digitalRead(FORWARDS);
  int newBackInputValue = digitalRead(BACK);
  int newZeroInputValue = digitalRead(ZERO);
  int newResetInputValue = digitalRead(RESET);

  if ((newForwardInputValue == LOW) & (forwardInputValue == HIGH))  //FORWARD command
  {
    step++;
    if (step > 15) { step = 0; }
  }


  if ((newBackInputValue == LOW) & (backInputValue == HIGH))  //BACKWARD command
  {
    step--;
    if (step < 0) { step = 15; }
  }

  if ((newZeroInputValue == LOW) & (zeroInputValue == HIGH))  //zero this makes the sequencer have no step output, this is good for when you want the start clock to actually begin on step 1
  {
    step = -1;
  }

  if ((newResetInputValue == LOW) & (resetInputValue == HIGH))  //reset to 1
  {
    step = 0;
  }

  forwardInputValue = newForwardInputValue;
  zeroInputValue = newZeroInputValue;
  resetInputValue = newResetInputValue;
  backInputValue = newBackInputValue;
}

void updateStep() {
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
