#include "tiny.h"

#define SerialDebug

DigitalOut<PortB::pin3> pyro;
DigitalIn<PortB::pin4> servo;

#ifdef SerialDebug
TextOutStream<SoftwareSerialOut<DigitalOut<PortB::pin1>, 9600> > dbg;
const char *endl = "\r\n";
#endif

#define theshold 1600

unsingned long servoVal;

void setup() {
#ifdef SerialDebug  
  dbg << "BOOTING" <<endl;
#endif

}

void loop() {
  servoVal=pulseIn(inPin,);
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