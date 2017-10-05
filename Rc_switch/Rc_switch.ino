//-U lfuse:w:0xe2:m -U hfuse:w:0xd7:m -U efuse:w:0xff:m 

// nostrades slieksnis pie kura jabutt OK
#define treshold 1600

//pulseIn timeout mikrosekundes. Skatit Arduino reference manual
#define pulseTimeout 50000

#define relejs 3
#define servoIn 4
#define statusLedPin 1


const uint8_t kTIMER1_DIV4096 = 0b1101;

unsigned long  ins; 

void setup() {
  //varbut vajag INPUT un pielodet 100K pretestibu pret GND
  pinMode(servoIn,INPUT_PULLUP);
  pinMode(relejs,OUTPUT);
  pinMode(statusLedPin,OUTPUT);

  cli();
  TCCR1 = _BV(CTC1) | kTIMER1_DIV4096;
  //TCCR1 = kTIMER1_DIV512;
  OCR1C = 193;
  OCR1A = OCR1C;
  TIMSK |= _BV(OCIE1A);
  sei();

  //Uz atTiny85 nav seriala porta, izmetam ara
  //Serial.begin(9600);
}

void loop() {  
  ins = pulseIn(servoIn, HIGH, pulseTimeout); 
  if (ins > treshold) {
    digitalWrite(relejs,HIGH);
  }
  else {
    digitalWrite(relejs,LOW);
  }

//Serial.println(ins, DEC);
//Serial.println(relejs, BIN);

// mums vairs nevajag pauzi, visam jastrada nepartraukti.
// Ja ir sudi tad pieliekam delay 10 50 vai cik vajag
  //delay(100);
}

ISR(TIMER1_COMPA_vect) {
  static bool ledState;
  static uint8_t cnt1;
  
  if (++cnt1 >= 30) {
    cnt1 = 0;
  }
  if (ins==0) {
    ledState=!ledState;
    if (ledState){
          digitalWrite(statusLedPin,HIGH);
    } else {
      digitalWrite(statusLedPin,LOW);
    }
  } else {
    //if (cnt1 < 2 || (cnt1 > 8 && cnt1 < 15)) digitalWrite(statusLedPin,HIGH);
    if ((cnt1 > 8 && cnt1 < 15)) digitalWrite(statusLedPin,HIGH);
    else digitalWrite(statusLedPin,LOW);
  }
}

