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

#define STEP1 2  //step 1 output
#define STEP2 3  //step 2 output
#define STEP3 4  //step 3 output
#define STEP4 5  //step 4 output
#define STEP5 6  //step 5 output
#define STEP6 7  //step 6 output
#define STEP7 8  //step 7 output
#define STEP8 9  //step 8 output
#define STEPBUTTON1   0 //these are the capacitive touch pads
#define STEPBUTTON2   1 //these are the capacitive touch pads
#define STEPBUTTON3   2 //these are the capacitive touch pads
#define STEPBUTTON4   3 //these are the capacitive touch pads
#define STEPBUTTON5   4 //these are the capacitive touch pads
#define STEPBUTTON6   5 //these are the capacitive touch pads
#define STEPBUTTON7   6 //these are the capacitive touch pads
#define STEPBUTTON8   7 //these are the capacitive touch pads

#define FORWARDS 12   //this is the pin that the forwards button (and coupled jack input) connects to
#define RESET 11      //this is the pin that the reset button (and coupled jack input) connects to
#define BACK 0        //this is the pin that the backwards button (and coupled jack input) connects to
#define ZERO 10       //this is the pin that the zero button (and coupled jack input) connects to
#define TOUCHGATE 1   //this is the gate output jack that turns on when a touch pad is being pressed
#define STEPSET1 13   //this is the pin that sets which row the "merge" jack is listenning to. HIGH is row A, LOW is row B


int touchthreshold = 50;  //this is the capacitive touch threshold, go for a higher number for more sensitivity if you have fingers as dry as the sahara
int gate = 50; //this is the gate threshold. to be honest it could be ommited as matches the touch threshold but heyho!
int touchdelay = 0; //a delay of zero! ooohllallaaa



int val = 0;
int old_val = 0;
int val1 = 0;
int old_val1 = 0;
int val2 = 0;
int old_val2 = 0;
int val3 = 0;
int old_val3 = 0;
int val4 = 0;
int old_val4 = 0;

int vals1 = 0;
int vals2 = 0;
int vals3 = 0;
int vals4 = 0;
int vals5 = 0;
int vals6 = 0;
int vals7 = 0;
int vals8 = 0;

int clockbypass = 0;
int count = 0;
int steppriority = 0;
int stepcount = 0;
int bypass = 0;

int state = 0;
int led = 17;
int newled = 1;


void setup ()
{
  pinMode (STEPSET1, OUTPUT);
  pinMode (STEP1, OUTPUT);
  pinMode (STEP1, OUTPUT);
  pinMode (STEP2, OUTPUT);
  pinMode (STEP3, OUTPUT);
  pinMode (STEP4, OUTPUT);
  pinMode (STEP5, OUTPUT);
  pinMode (STEP6, OUTPUT);
  pinMode (STEP7, OUTPUT);
  pinMode (STEP8, OUTPUT);
  pinMode (FORWARDS, INPUT);
  pinMode (BACK, INPUT);
  pinMode (RESET, INPUT);
  pinMode (ZERO, INPUT);
  pinMode (TOUCHGATE, OUTPUT);
}


void loop ()
{  
  vals8 = analogRead(STEPBUTTON8);
  vals7 = analogRead(STEPBUTTON7);
  vals6 = analogRead(STEPBUTTON6);
  vals5 = analogRead(STEPBUTTON5);
  vals4 = analogRead(STEPBUTTON4);
  vals3 = analogRead(STEPBUTTON3);
  vals2 = analogRead(STEPBUTTON2);
  vals1 = analogRead(STEPBUTTON1);
  val1 = digitalRead (FORWARDS);
  val4 = digitalRead (BACK);
  val2 = digitalRead (ZERO);
  val3 = digitalRead (RESET);



  

   if ((vals8 > 280) & (stepcount > 1))//Step 8 touchpad
   {  
   led = 9;
   clockbypass = 1;
   count = 0;
   bypass = 1;
   digitalWrite(TOUCHGATE, HIGH);
   delay(touchdelay);
   stepcount = 0;
   }
   

   else if((vals7 > 280) & (stepcount > 2))//Step 7 touchpad
   {  
   led = 10;
   clockbypass = 1;
   bypass = 1;
   count = 0;
   digitalWrite(TOUCHGATE, HIGH);
   delay(touchdelay);
   stepcount = 0;
   }
   
   else if((vals6 > 60) & (stepcount > 3))//Step 6 touchpad
   {led = 11;
   clockbypass = 1;
   bypass = 1;
   count = 0;
   digitalWrite(TOUCHGATE, HIGH);
   delay(touchdelay);
   stepcount = 0;
   }
   
   else if((vals5 > touchthreshold) & (stepcount > 4))//Step 5 touchpad
   {  
   led = 12;
   clockbypass = 1;
   bypass = 1;
   count = 0;
   digitalWrite(TOUCHGATE, HIGH);
   delay(touchdelay);
   stepcount = 0;
   }
   
   else if((vals4 > touchthreshold) & (stepcount > 5))//Step 4 touchpad
   {  
   led = 13;
   clockbypass = 1;
   bypass = 1;
   count = 0;
   digitalWrite(TOUCHGATE, HIGH);
   delay(touchdelay);
   stepcount = 0;
   }
   
   else if((vals3 > touchthreshold) & (stepcount > 6))//Step 3 touchpad
   {  
   led = 14;
   clockbypass = 1;
   bypass = 1;
   count = 0;
   digitalWrite(TOUCHGATE, HIGH);
   delay(touchdelay);
   stepcount = 0;
   }

   else if((vals2 > touchthreshold) & (stepcount > 7))//Step 2 touchpad
   {
   led = 15;
   clockbypass = 1;
   bypass = 1;
   count = 0;
   digitalWrite(TOUCHGATE, HIGH);
   delay(touchdelay);
   stepcount = 0;

   }


   else if((vals1 > touchthreshold) & (stepcount > 8))//Step 1 touchpad
   {
   led = 16;
   clockbypass = 1;
   bypass = 1;
   count = 0;
   digitalWrite(TOUCHGATE, HIGH);
   delay(touchdelay);
   stepcount = 0;

   }




   if ((vals1 < gate) & (vals2 < gate) & (vals3 < gate) & (vals4 < gate) & (vals5 < gate) & (vals6 < gate) & (vals7 < gate) & (vals8 < gate) & (bypass == 1)) //this smooths out the gate output
   {
    count = count + 1;
    delay (5);
   }


   if (count >= 10) //this counter solves finget noise
   {
   clockbypass = 0;
   count = 0;
   bypass = 0;
   digitalWrite(TOUCHGATE, LOW);
   }



  if ((vals1 > touchthreshold) | (vals2 > touchthreshold) | (vals3 >  touchthreshold) | (vals4 >  touchthreshold) | (vals5 >  touchthreshold) | (vals6 >  touchthreshold) | (vals7 >  touchthreshold) | (vals8 > touchthreshold))
   {
    delay (2);
    stepcount = stepcount + 1;
//this means when your fingers ar eon the pads itll ignore steps
   }



   if((val1 == LOW) & (old_val1 == HIGH) & (clockbypass == 0))  //FORWARD command
   {
    newled = led - 1; 
     if (newled <=0) { newled = 16; } 
    led = newled;
   
   }


   if((val4 == LOW) & (old_val4 == HIGH) & (clockbypass == 0))  //BACKWARD command
   {
    newled = led + 1; 
     if (newled >16) { newled = 1; } 
    led = newled;
   
   }

   

   if((val2 == LOW) & (old_val2 == HIGH) & (clockbypass == 0)) //zero this makes the sequencer have no step output, this is good for when you want the start clock to actually begin on step 1
   
   {
    led = 17;

   }
  

   
   if((val3 == LOW) & (old_val3 == HIGH) & (clockbypass == 0)) //reset to 1
   
   {
    led = 16;

   }


  old_val  = val;
  old_val1 = val1;
  old_val2 = val2;
  old_val3 = val3;
  old_val4 = val4;

 // if (newled >= 17 ) { newled = 1; } 
 // if (newled < 1 ) { newled = 16; } 
 // if (stepcount >9) {stepcount = 0; }



 //BELOW ARE ALL OF THE NUMBERS FOR WHAT LIGHT TO GO WHERE FOR WHICH STEP
 
  if (led == 17)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
    digitalWrite(STEPSET1, HIGH);

  }
 
  else if (led == 16)
  {
    digitalWrite(STEP1, HIGH);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
    digitalWrite(STEPSET1, HIGH);
    
  }
 else if (led == 15)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, HIGH);
    digitalWrite(STEP3, LOW);
     digitalWrite(STEP4, LOW);
     digitalWrite(STEP5, LOW);
     digitalWrite(STEP6, LOW);
     digitalWrite(STEP7, LOW);
     digitalWrite(STEP8, LOW);
    digitalWrite(STEPSET1, HIGH);

         }
 else if (led == 14)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, HIGH);
     digitalWrite(STEP4, LOW);
     digitalWrite(STEP5, LOW);
     digitalWrite(STEP6, LOW);
     digitalWrite(STEP7, LOW);
     digitalWrite(STEP8, LOW);
    digitalWrite(STEPSET1, HIGH);


  
  } 
 else if (led == 13)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
     digitalWrite(STEP4, HIGH);
     digitalWrite(STEP5, LOW);
     digitalWrite(STEP6, LOW);
     digitalWrite(STEP7, LOW);
     digitalWrite(STEP8, LOW);
      digitalWrite(STEPSET1, HIGH);
   

  } 
   else if (led == 12)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
     digitalWrite(STEP4, LOW);
     digitalWrite(STEP5, HIGH);
     digitalWrite(STEP6, LOW);
     digitalWrite(STEP7, LOW);
     digitalWrite(STEP8, LOW);
       digitalWrite(STEPSET1, HIGH);


  } 
   else if (led == 11)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
     digitalWrite(STEP4, LOW);
     digitalWrite(STEP5, LOW);
     digitalWrite(STEP6, HIGH);
     digitalWrite(STEP7, LOW);
     digitalWrite(STEP8, LOW);
       digitalWrite(STEPSET1, HIGH);


  } 
  else if (led == 10)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
     digitalWrite(STEP4, LOW);
     digitalWrite(STEP5, LOW);
     digitalWrite(STEP6, LOW);
     digitalWrite(STEP7, HIGH);
     digitalWrite(STEP8, LOW);
       digitalWrite(STEPSET1, HIGH);


  } 
  else if (led == 9)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
     digitalWrite(STEP4, LOW);
     digitalWrite(STEP5, LOW);
     digitalWrite(STEP6, LOW);
     digitalWrite(STEP7, LOW);
     digitalWrite(STEP8, HIGH);
       digitalWrite(STEPSET1, HIGH);


  } 
  else if (led == 0)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
    digitalWrite(STEPSET1, HIGH);


  } 

  else if (led == 8)
  {
    digitalWrite(STEP1, HIGH);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
     digitalWrite(STEPSET1, LOW);
    
  }
 else if (led == 7)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, HIGH);
    digitalWrite(STEP3, LOW);
   digitalWrite(STEP4, LOW);
   digitalWrite(STEP5, LOW);
   digitalWrite(STEP6, LOW);
   digitalWrite(STEP7, LOW);
   digitalWrite(STEP8, LOW);
   digitalWrite(STEPSET1, LOW);

         }
 else if (led == 6)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, HIGH);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
    digitalWrite(STEPSET1, LOW);


  
  } 
 else if (led == 5)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, HIGH);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
    digitalWrite(STEPSET1, LOW);


  } 
else if (led == 4)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, HIGH);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
    digitalWrite(STEPSET1, LOW);


  } 
   else if (led == 3)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, HIGH);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
    digitalWrite(STEPSET1, LOW);


  } 
  else if (led == 2)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, HIGH);
    digitalWrite(STEP8, LOW);
    digitalWrite(STEPSET1, LOW);


  } 
  else if (led == 1)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, HIGH);
    digitalWrite(STEPSET1, LOW);
   

  } 


}
