char audiopin = A0;
int audio = 0;
int schwelle = 50;
int arrayLength = 1024;
String audioString = "";

boolean toggle1 = 0; //storage variable

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  
  cli();//stop interrupts

  /*//set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);// Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);*/
  
  // set timer1 interrupt at 1Hz
  TCCR1A = 0;             // set entire TCCR1A register to 0
  TCCR1B = 0;             // same for TCCR1B
  TCNT1  = 0;             // initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;                          // = (16*10^6) / (1*1024) - 1 (must be <65536)  
  TCCR1B |= (1 << WGM12);                 // turn on CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10);    // Set CS10 and CS12 bits for 1024 prescaler
  TIMSK1 |= (1 << OCIE1A);                // enable timer compare interrupt

  //DDRC = DDRC | B11111110; // Set Pin A0 input
  sei();                                  // allow interrupts
}

// Interrupt-handler timer1
ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  if (toggle1){
    digitalWrite(13,HIGH);
    toggle1 = 0;
  }
  else{
    digitalWrite(13,LOW);
    toggle1 = 1;
  }
}
                                                                                                                                                         
void loop() {
  /*Serial.print("\nCS00 = ");
  Serial.print(CS00);
  Serial.print(", CS01 = ");
  Serial.print(CS01);
  delay(1000);*/
  audio = analogRead(audiopin);
  audioString = "";
  int i = 0;
  while (i < audio/6){
    audioString.concat("|");
    i++;
    }
  if (audio > schwelle){
    digitalWrite(2,HIGH);
  }
  else{
    digitalWrite(2,LOW);
  }
  Serial.println(audioString);
}
