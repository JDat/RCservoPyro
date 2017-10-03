#define treshold 1600
#define timeout 100000
#define SerialDebug

#define servoPin 4
#include "tiny.h"


DigitalOut<PortB::pin3> pyro;


#ifdef SerialDebug
TextOutStream<SoftwareSerialOut<DigitalOut<PortB::pin1>, 9600> > dbg;
const char *endl = "\r\n";
#endif



unsigned long servoVal;

void setup() {
#ifdef SerialDebug  
  dbg << "BOOTING" <<endl;
#endif

}

void loop() {
  servoVal=pulseIn(servoPin,HIGH, timeout);
#ifdef SerialDebug    
  dbg << "Val: " << servoVal << endl;
#endif
  if (servoVal > treshold) {
	pyro.high();

	#ifdef SerialDebug  	
	dbg << "ACTIVE" << endl;
#endif

	} else {
	pyro.low();

	#ifdef SerialDebug  
	dbg << "OFF" << endl;
#endif	
  
  }
  delay(1);
}
