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
#define TOUCH_TRIGGER_SENSITIVITY 90

/**
* This determines the allowed 'tightness' for detecting multiple fingers and prevents ghost fingers.
* 
* All sensed fingers must be above this percentage of the maximum finger value
*/
#define TOUCH_SENSITIVITY_GROUPING_FACTOR 0.6

/**
* The number of cycles until a missing finger is considered no longer pressed.
* This smooths out the finger presses.
*/
#define FINGER_SMOOTHING_CYCLES 10

/**
* The number of cycles that a finger needs to be above the threshold before we will start reading its value
*
* This removes a bit of possible noise that might trigger a finger accidentally
*/
#define MIN_THRESHOLD_CYCLES 10

/**
*
* DEPRECATED: Not currently using this setting. It was a hack. A dirty, disgusting hack....
*
* wtf, why does the previous analog read sometimes affect the next read?
* 
* This is the number of times A0 and A7 are pre-read each cycle before getting the used sample value
*
* This is done to prevent bounching between the first and last pad
*
*/
#define PAD_PREREAD_COUNT 0


/**
* Uncomment to enable debug mode
*
* When debugging, digital pins 0 and 1 will be used for serial communication. That means they cannot
* be used for BACK trigger input and TOUCHGATE ouput. Not a big deal as the purpose of debug mode is
* mostly to get the capacitive touch values for tuning the touch threshold settings.
*
* NOTE: IMPORTANT!!! The debugging setting will write data to serial out. This adds a bunch of extra
* overhead to each program cycle. Since most of our sampling and smoothing is cycle based, that means
* it won't work quite the same. If you're debugging and want "normal-ish" behavior, you'll need to
* tweak (i.e. lower) most of the cycle values. Debugging is really good to see what the values are
* under various levels of smoothing, though :)
* 
* Debugging output is formatted for live graphing with the TelePlot VS Code extension:
* https://marketplace.visualstudio.com/items?itemName=alexnesnes.teleplot
*/
//#define DEBUG

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

int forwardInputValue = 0;
int zeroInputValue = 0;
int resetInputValue = 0;
int backInputValue = 0;

int command = 0;

int fingerDetectionCountdown[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int fingerOverThresholdCount[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int fingerCount = 0;



struct SampleQueue{
  int currentIndex;
  int size;
  int *samples;
};


// Initialize the sample data structures
#define THRESHOLD_SAMPLE_SIZE 3
int _thresholdSamples[THRESHOLD_SAMPLE_SIZE];
SampleQueue thresholdSamples = {0,THRESHOLD_SAMPLE_SIZE, _thresholdSamples};

#define FINGER_SAMPLE_SIZE 10
int _fingerSamples[8][FINGER_SAMPLE_SIZE];

SampleQueue fingerSamples[8] = {
  {0, FINGER_SAMPLE_SIZE, _fingerSamples[0]},
  {0, FINGER_SAMPLE_SIZE, _fingerSamples[1]},
  {0, FINGER_SAMPLE_SIZE, _fingerSamples[2]},
  {0, FINGER_SAMPLE_SIZE, _fingerSamples[3]},
  {0, FINGER_SAMPLE_SIZE, _fingerSamples[4]},
  {0, FINGER_SAMPLE_SIZE, _fingerSamples[5]},
  {0, FINGER_SAMPLE_SIZE, _fingerSamples[6]},
  {0, FINGER_SAMPLE_SIZE, _fingerSamples[7]},
};


int step = -1;

int row = 0;
int rowStep = 0;

int arpStep = 0;
bool arpModeActive = false;

void setup() {

#ifdef DEBUG
  //Setup serial. We won't be able to use BACK/TOUCHGATE pins while debugging
  Serial.begin(115200);
  Serial.print("LMNC 2001 KEYBOARD SEQUENCER\n");
  Serial.print("Debug mode activated...\n");
#endif

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
#ifndef DEBUG
  pinMode(BACK, INPUT);
#endif
  pinMode(RESET, INPUT);
  pinMode(ZERO, INPUT);
#ifndef DEBUG
  pinMode(TOUCHGATE, OUTPUT);
#endif
}

int getSlidingMaxSample(int newSample, int minValue, SampleQueue &queue) {
  queue.samples[queue.currentIndex] = newSample;
  queue.currentIndex = (queue.currentIndex + 1) % queue.size;

  // There's absolutely a better algorithm for this.
  // We should be able to keep a pointer to the current max
  // and compare that with the new sample. If the previous max
  // was being aged off, then we would have to scan the full list.
  // Alternatively, we could keep a heap of the values in addition
  // to a queue. But for a sample size of 10.... not worth the effort when
  // it's after midnight and I need to grab another beer.
  int newMax = minValue;
  //use the lazy brute force way to get the max
  for(int i=0; i < queue.size; i++){
    newMax = max(newMax, queue.samples[i]);
  }
  return newMax;
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
  for (int i = 0; i < 8; i++) {

    // Preread the first and last value

    // You might ask why we're doing this.
    // What possible reason would we have to read the values
    // throw them away and then read them again.
    // My answer to you is this: Sometimes the first read value in
    // the loop is effected by the last read value. ¯\_(ツ)_/¯
    if (i == 0 || i == 7) {
      for (int j = 0; j < PAD_PREREAD_COUNT; j++) {
        analogRead(i);
      }
    }
    int val = analogRead(i);

    // Ceiling for values so nothing gets too crazy.
    // The max on the lower digital pins seems to be about 600 for a normal pad, but the top 3 can go from 800-1000
    // No need to let them mess with thresholds by getting that high
    if(val > 600){
      val = 600;
    }

    val = getSlidingMaxSample(val, 0, fingerSamples[i]);
    fingerValues[i] = val;

#ifdef DEBUG
    Serial.print(">p_");
    Serial.print(i);
    Serial.print(":");
    Serial.print(val);
    Serial.print("\n");
#endif

    minFingerValue = min(minFingerValue, val);
    maxFingerValue = max(maxFingerValue, val);
  }

  // Dynamically set the threshold based on the max value we got. We need at least TOUCH_TRIGGER_SENSITIVITY
  int threshold = max(TOUCH_TRIGGER_SENSITIVITY, (int) (maxFingerValue * TOUCH_SENSITIVITY_GROUPING_FACTOR));
  threshold = getSlidingMaxSample(threshold, TOUCH_TRIGGER_SENSITIVITY, thresholdSamples);

#ifdef DEBUG
  Serial.print(">t:");
  Serial.print(threshold);
  Serial.print("\n");
#endif

  for (int i = 0; i < 8; i++) {
    int touchValue = fingerValues[i];

    if (touchValue > threshold) {

      // Smooth new fingers to make sure it isn't noise from an adjacent finger
      // This mostly happens between the first and last pad
      fingerOverThresholdCount[i]++;
      if (fingerOverThresholdCount[i] < MIN_THRESHOLD_CYCLES) {
        continue;
      }

      fingerCount++;
      fingerDetectionCountdown[i] = FINGER_SMOOTHING_CYCLES;  // Reset the cooldown
      digitalWrite(TOUCHGATE, HIGH);
    } else if (fingerDetectionCountdown[i] > 0) {
      // We still have an active cooldown
      if (--fingerDetectionCountdown[i] > 0) {
        fingerCount++;
      } else {
        fingerOverThresholdCount[i] = 0;
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
  } else if ((newZeroInputValue == LOW) & (zeroInputValue == HIGH)) {
    command = CMD_ZERO;
  } else if ((newBackInputValue == LOW) & (backInputValue == HIGH)) {
    command = CMD_BACKWARD;
  } else if ((newForwardInputValue == LOW) & (forwardInputValue == HIGH)) {
    command = CMD_FORWARD;
  }

  forwardInputValue = newForwardInputValue;
  zeroInputValue = newZeroInputValue;
  resetInputValue = newResetInputValue;
  backInputValue = newBackInputValue;
}


int getStepForFingerNum(int n) {
  n = n % fingerCount;
  for (int i = 0; i < 8; i++) {
    if (fingerDetectionCountdown[i] > 0) {
      if (n == 0) {
        return i;
      } else {
        n--;
      }
    }
  }
  return -1;
}

void updateStep() {
  if (fingerCount == 0) {
    arpModeActive = false;  // No fingers, no arp
  }

  if (fingerCount > 0) {
    // //Highest pad/step wins, by default
    if (!arpModeActive) {
      for (int i = 0; i < 8; i++) {
        if (fingerDetectionCountdown[i] > 0) {
          step = i;
        }
      }
    }

    // Multiple fingers and we got a step command?!?! Time to ARP!!!
    if (command == CMD_FORWARD) {
      step = getStepForFingerNum(arpStep++);
      arpModeActive = true;
    } else if (command == CMD_BACKWARD) {
      step = getStepForFingerNum(arpStep--);
      arpModeActive = true;
    }
    if (arpStep < 0) {
      arpStep = fingerCount - 1;
    }
    arpStep = arpStep % fingerCount;

  } else if (command != 0) {
    //Handle the current command
    if (command == CMD_FORWARD) {
      step = (step + 1) % 16;
    } else if (command == CMD_BACKWARD) {
      step = (step - 1);
      if (step < 0) {
        step = 15;
      }
    } else if (command == CMD_ZERO) {
      step = -1;
    } else if (command == CMD_RESET) {
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
