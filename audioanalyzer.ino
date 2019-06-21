//Audioanalyzer 

  
bool toggle1 = false; //storage variable
bool blink_red = false;
char audiopin = A0;
char potpin = A1;
int audio = 0;
int pot = 0;
int schwelle = 0;
int rgb[] = {0,0,0};
//int arrayLength = 1024;
//String audioString = "";


  void setup(){
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  
  // SRC: https://www.instructables.com/id/Arduino-Timer-Interrupts/
  cli();                                  //stop interrupts

  /*//set timer0 interrupt at 40kHz
  TCCR0A = 0;                             // set entire TCCR0A register to 0
  TCCR0B = 0;                             // same for TCCR0B
  TCNT0  = 0;                             //initialize counter value to 0
  // set compare match register for 40khz increments
  OCR0A = 49;                             // = (16*10^6) / (40000*8) - 1 (must be <256)
  TCCR0A |= (1 << WGM01);                 // turn on CTC mode
  TCCR0B |= (1 << CS01);    // Set CS01(=1) bit for 8 prescaler
  TIMSK0 |= (1 << OCIE0A);                // enable timer compare interrupt
  */
  // set timer1 interrupt at 1Hz
  TCCR1A = 0;                             // set entire TCCR1A register to 0
  TCCR1B = 0;                             // same for TCCR1B
  TCNT1  = 0;                             // initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;                          // = (16*10^6) / (1*1024) - 1 (must be <65536)  
  TCCR1B |= (1 << WGM12);                 // turn on CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10);    // Set CS10(=0) and CS12(=2) bits for 1024 prescaler 
  TIMSK1 |= (1 << OCIE1A);                // enable timer compare interrupt

  //DDRC = DDRC | B11111110; // Set Pin A0 input
  sei();                                  // allow interrupts
  }
//*************************Cyclic*Code******************                  
void loop(){                                                                                                                                   
  while(1) { 
    //==================================
    // Get Inputs
    //==================================
    audio = analogRead(audiopin);
    pot = analogRead(potpin);
    
    //==================================
    // Logic
    //==================================
    schwelle = 255 - pot;
    /*audioString = "";
    int i = 0;
    while (i < audio/6){
      audioString.concat("|");
      i++;
      }*/
    if (audio > schwelle){
      blink_red = true;
      rgb[0]= 200;
      
    }
    else{
      blink_red = false;
      rgb[0]= 0;
    }
    //==================================
    // Write Outputs
    //==================================
    //Serial.println(audioString);
    digitalWrite(13,toggle1);
    digitalWrite(2,blink_red); // Red LED
    analogWrite(A3, rgb[0]); // Rgb
    analogWrite(A4, 0); // rGb
    analogWrite(A5, audio); // rgB
  }
}

//*************************ISRs**************************

// Interrupt-handler timer0 @40kHz
ISR(TIMER0_COMPA_vect){
// Read A1
}

// Interrupt-handler timer1 @1Hz
ISR(TIMER1_COMPA_vect){
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  if (toggle1){
    toggle1 = false;
  }
  else{
    toggle1 = true;
  }
}
