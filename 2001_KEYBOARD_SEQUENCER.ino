//LOOK MUM NO COMPUTER KEYBOARD SEQUENCER.
//VERSION 2.1 (keep an eye out for 2.2 with fixes and extra functions).
//A SIMPLE DESIGN TO MAKE A 4017 STYLE SEQUENCER WITH MORE ADDED FUNCTIONS.
//MORE INFO CHECK LOOKMUMNOCOMPUTER.COM
//JOIN FORUM IF YOU HAVE ANY QUESTIONS
//ANY MODIFICATIONS PLEASE SHARE ON FORUM PEOPLE MAY ENJOY YOUR TAKE ON THIS
//SAM BATTLE 2021
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
#define STEPBUTTON1   14   //these are the capacitive touch pads
#define STEPBUTTON2   15 //these are the capacitive touch pads
#define STEPBUTTON3   16 //these are the capacitive touch pads
#define STEPBUTTON4   17 //these are the capacitive touch pads
#define STEPBUTTON5   18 //these are the capacitive touch pads
#define STEPBUTTON6   19 //these are the capacitive touch pads
#define STEPBUTTON7   20 //these are the capacitive touch pads
#define STEPBUTTON8   21 //these are the capacitive touch pads

#define FORWARDS 12   //this is the pin that the forwards button (and coupled jack input) connects to
#define RESET 11      //this is the pin that the reset button (and coupled jack input) connects to
#define BACK 0        //this is the pin that the backwards button (and coupled jack input) connects to
#define ZERO 10       //this is the pin that the zero button (and coupled jack input) connects to
#define TOUCHGATE 1   //this is the gate output jack that turns on when a touch pad is being pressed
#define STEPSET1 13   //this is the pin that sets which row the "merge" jack is listenning to. HIGH is row A, LOW is row B


int touchthreshold = 800;  //this is the capacitive touch threshold, go for a higher number for more sensitivity if you have fingers as dry as the sahara
int Gthrshld = 1000;      //this is the capacitive theshold the gate output will go high
int capacitivedelay = 0; //delay to smooth the capacitive touch this will change in version 2.2 of the code

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
int old_vals1 = 0;
int vals2 = 0;
int old_vals2 = 0;
int vals3 = 0;
int old_vals3 = 0;
int vals4 = 0;
int old_vals4 = 0;
int vals5 = 0;
int old_vals5 = 0;
int vals6 = 0;
int old_vals6 = 0;
int vals7 = 0;
int old_vals7 = 0;
int vals8 = 0;
int old_vals8 = 0;


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


  //SET THE PINS TO IN OR OUT
  

}


void loop ()
{  




  
  val1 = digitalRead (FORWARDS);
   if((val1 == LOW) && (old_val1 == HIGH))
   
   {
    newled = led - 1; 
     if (newled <=0) { newled = 16; } 
    led = newled;
   
   }

//THIS IS THE THING THAT MAKES IT GO FORWARDS, IT SAYS -1 YOULL SEE ALL OF THE NUMBERS AND WHAT THEY DO BELOW
   
       val2 = digitalRead (ZERO);
   if((val2 == LOW) && (old_val2 == HIGH))
   
   {
    newled = led = 17;
    led = newled;
   }
  
//THIS MAKES THE ZERO COMMAND WORK. 17 IS WHEN NO LIGHTS ARE ON 
   
    val3 = digitalRead (RESET);
   if((val3 == LOW) && (old_val3 == HIGH))
   
   {
    newled = led = 16;
    led = newled;
   }

//RESET BACK TO STEP 1

     val4 = digitalRead (BACK);
   if((val4 == LOW) && (old_val4 == HIGH))
   
   {
    newled = led + 1; 
     if (newled >= 17 ) { newled = 9; } 
    led = newled;
   
   }

//GO BACKWARDS

//BELOW ARE ALL OF THE STEP BUTTONS AND WHAT THEY DO. BASICALLY WHEN THEY ARE HIT THE LED NUMBER GOES TO THE RIGHT NUMBER

     vals1 = analogRead (STEPBUTTON1);
   if((vals1 <= touchthreshold)) 
   
   {
    newled = led = 16;
    digitalWrite(TOUCHGATE, HIGH);
    delay(capacitivedelay);
   
   }
    
     vals2 = analogRead (STEPBUTTON2);
   if((vals2 <= touchthreshold))
   
   {
    newled = led = 15;
   digitalWrite(TOUCHGATE, HIGH);
   delay(capacitivedelay);
   }

     vals3 = analogRead (STEPBUTTON3);
   if((vals3 <= touchthreshold))
   
   {
    newled = led = 14;
   digitalWrite(TOUCHGATE, HIGH);
   delay(capacitivedelay);
   }

     vals4 = analogRead (STEPBUTTON4);
   if((vals4 <= touchthreshold))
   
   {
    newled = led = 13;
   digitalWrite(TOUCHGATE, HIGH);
   delay(capacitivedelay);
   }
   

     vals5 = analogRead (STEPBUTTON5);
   if((vals5 <= touchthreshold))
   
   {
    newled = led = 12;
   digitalWrite(TOUCHGATE, HIGH);
   delay(capacitivedelay);
   }
   
     vals6 = analogRead (STEPBUTTON6);
   if((vals6 <= touchthreshold))
   
   {
    newled = led = 11;
   digitalWrite(TOUCHGATE, HIGH);
   delay(capacitivedelay);
   }

     vals7 = analogRead (STEPBUTTON7);
   if((vals7 <= touchthreshold))
   
   {
    newled = led = 10;
   digitalWrite(TOUCHGATE, HIGH);
   delay(capacitivedelay);
   }
  
      vals8 = analogRead (STEPBUTTON8);
   if((vals8 <= touchthreshold))
   
   {
    newled = led = 9;
   digitalWrite(TOUCHGATE, HIGH);
   delay(capacitivedelay);
   }
   
   

   if((vals1 >=Gthrshld,vals2 >=Gthrshld,vals3 >=Gthrshld,vals4 >=Gthrshld,vals5 >=Gthrshld,vals6 >=Gthrshld,vals7 >=Gthrshld,vals8 >=Gthrshld))
   {
   digitalWrite(TOUCHGATE, LOW);
   }
   

  
  old_val = val;
  old_val1 = val1;
  old_val2 = val2;
  old_val3 = val3;
  old_val4 = val4;


  if (newled >=17 ) { newled = 1; } 
  if (newled <=1 ) { newled = 16; } 
  
      

  
 //BELOW ARE ALL OF THE NU<BERS AND WHAT THEY DO!
 
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
 
  if (led == 16)
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
 if (led == 15)
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
 if (led == 14)
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
 if (led == 13)
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
   if (led == 12)
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
   if (led == 11)
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
     if (led == 10)
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
       if (led == 9)
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
   if (led == 0)
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

  if (led == 8)
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
 if (led == 7)
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
 if (led == 6)
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
 if (led == 5)
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
   if (led == 4)
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
   if (led == 3)
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
     if (led == 2)
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
       if (led == 1)
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
