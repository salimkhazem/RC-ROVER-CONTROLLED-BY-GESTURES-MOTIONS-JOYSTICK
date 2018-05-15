
#include <SPI.h> 
#include <RF24.h> 
#include <nRF24L01.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"


RF24 radio(7,8); 
const byte address[6]= "00001"; 
int posX=A2;
int posY=A3;  
int Button=6; 
boolean etat=0; 
int Pos[2]; 
int data[2]; 
char x[2];

/*struct package
{
int pos; 
int dir;
};
typedef struct package Package; 
Package data;  */ 
//Motor Alpha(8,12,9) ;  // (pin1,pin2,pinP)
//Motor Beta(7,4,10);  //(pin1,pin2,pinP) 

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 mpu;
#define OUTPUT_READABLE_YAWPITCHROLL
#define LED_PIN 13 

bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {

    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    //put on the output the pins of motors 
   // Alpha.begin();
  //  Beta.begin(); 
   // vw_set_tx_pin(12); 
    //vw_setup(2000); 

    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
    Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately
    mpu.initialize();
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        //Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        //Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

    radio.begin(); 
radio.openWritingPipe(address); 
radio.setPALevel(RF24_PA_MAX); 
radio.stopListening();
pinMode(posX,INPUT); 
pinMode(posY,INPUT); 
pinMode(Button,INPUT_PULLUP); 
    

    // configure LED for output

}

// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
    // if programming failed, don't try to do anything
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
 
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        //Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

    

 

       #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

         /* 
         Serial.print("Phi: ");
         Serial.print(ypr[2] * 180/M_PI);
         Serial.print("\t Theta: ");
         Serial.print(" "); 
           Serial.print(ypr[1] * 180/M_PI);
          Serial.print("\t Psi: ");
           Serial.print(" ");
         Serial.println(ypr[0] * 180/M_PI);
        
         */
            //delay(100);
             #endif
            //int valeurSW=!digitalRead(Button);
            //if(valeurSW==1) {delay(250); etat=!etat;}
            if (!digitalRead(Button)) {delay(250); etat=!etat; delay(200);} 
            if (etat==1) {
             delay(150); 
             int X = ypr[1] * 180/M_PI; 
             int Y = ypr[2] * 180/M_PI; 
             //int Z= ypr[0] * 180/M_PI; 
             data[0]=map(X,-85,85,0,180);
             data[1]=map(Y,-90,90,0,180);
             //data[2]=map(Z,-90,90,0,255); 

            //  if(data[2]<0) {data[2]=0;}
             // else if (data[2]>255) {data[2]=255;}
             if (data[1]<0) {data[1]=0;}
             else if (data[1]>180) {data[1]=180; } 
             if (data[0]<0) {data[0]=0;}
             else if (data[0]>180) {data[0]=180;}

             if (data[0]<60) {
              x[1]='F';
              radio.write(x,sizeof(x)); 
             }
             else if(data[0]>103){
              x[1]='R';
              radio.write(x,sizeof(x));  
             }
             else if (data[0]>60 && data[0] <103) {
              x[1]='S';
              radio.write(x,sizeof(x)); 
             }

             if (data[1] > 103) {
              x[0]='D'; 
              radio.write(x,sizeof(x)); 
             }
             else if (data[1] <60) {
              x[0]='G'; 
              radio.write(x,sizeof(x)); 
             }
             else if (data[1]<103 && data[1] >60) {
              x[0]='S'; 
              radio.write(x,sizeof(x)); 
             }
            // radio.write(data,sizeof(data));
             Serial.print("Axe X :") ; Serial.print("\t");    Serial.print(x[0]); Serial.print("\t"); 
              Serial.print("Axe Y :") ; Serial.print("\t");   Serial.print(x[1]); Serial.println("\t"); 
           //   Serial.print("Axe Z :"); Serial.print("\t");    Serial.println(data[2]);
             
            }
            else if(etat ==0) {
              delay(150); 
           char x[2]; 
           
            data[0]=map(analogRead(posX),0,1023,0,180); 
            data[1]=map(analogRead(posY),0,1023,0,180); 
            
            if (data[0]>100) {
              x[0]='D'; 
              radio.write(x,sizeof(x));
            }
            else if (data[0]<80) {
              x[0]='G'; 
              radio.write(x,sizeof(x)); 
            }
            else if (data[0]==91) {
              x[0]='S';
              radio.write(x,sizeof(x)); 
            }
            
            if (data[1]>100) {
              x[1]='F'; 
              radio.write(x,sizeof(x)); 
            }
            else if (data[1]<80) {
              x[1]='R';
              radio.write(x,sizeof(x)); 
            }
            else if (data[1]>80 && data[1] <100 ) {
              x[1]='S';
              radio.write(x,sizeof(x)); 
            }
          
           // radio.write(data,sizeof(data)); 
             Serial.print("Joy X :") ; Serial.print("\t");    Serial.print(data[0]); Serial.print("\t"); Serial.print(x[0]); Serial.print("\t"); 
              Serial.print("Joy Y :") ; Serial.print("\t");   Serial.print(data[1]); Serial.print("\t"); Serial.println(x[1]);  

              
            }



    }
}
