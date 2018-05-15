#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 
#include <Servo.h> 
#include <Motor.h> 

Motor Omega(2,3,1);  // Gauche 1 
Motor Delta(4,5,1); // Droite 1 
Motor Teta(6,9,1);  // gauche 2 
Motor Zeta(10,5,1);  // droite 2 

int data[2]; 
char x[2]; 
//int Pos[2]; 

RF24 radio (7,8); 

const byte address[6]="00001"; 
//const byte addr[6]="00002"; 
//int Led=10; 
void setup() {
  Omega.begin(); 
  Delta.begin() ;
  Teta.begin(); 
  Zeta.begin();  
  //Alpha.attach(3); 
  //Beta.attach(5); 
 // pinMode(Led,OUTPUT); 
 

  Serial.begin(9600); 
radio.begin(); 
radio.openReadingPipe(0,address); 
radio.setPALevel(RF24_PA_MAX); 

}

void loop() {
delay(5); 
radio.startListening(); 

if(radio.available()) {
  while (radio.available()) 
  { 
  radio.read(x,sizeof(x));
  Serial.print(x[0]); Serial.print("\t"); Serial.println(x[1]);  
if (x[0]=='G' ) {
  Omega.rearward(100);  
  Teta.rearward(100); 

  Delta.forward(100); 
  Zeta.forward(100); 
}
else if (x[0] =='D' ) {
   Delta.rearward(100);  
   Zeta.rearward(100); 

  Omega.forward(100); 
  Teta.forward(100); 
}
 else if (x[0]== 'S' && x[1]=='S'){
     Delta.turnOff();  
   Zeta.turnOff(); 

  Omega.turnOff(); 
  Teta.turnOff(); 
 }

 if (x[1]=='F') {
  Omega.forward(100); 
  Teta.forward(100);
   Delta.forward(100); 
  Zeta.forward(100); 
 }
 else if (x[1]=='R') {
   Omega.rearward(100); 
  Teta.rearward(100);
   Delta.rearward(100); 
  Zeta.rearward(100);
 }
 else if (x[1]=='S' && x[0]=='S') {
     Delta.turnOff();  
   Zeta.turnOff(); 

  Omega.turnOff(); 
  Teta.turnOff();
 }
  
 }
}
}
