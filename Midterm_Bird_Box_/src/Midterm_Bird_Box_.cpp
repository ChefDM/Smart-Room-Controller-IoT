/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "Button.h"
#include "wemo.h"

// include "IoTClassroom_CNM".h


#include "Encoder.h"
#include "hue.h"


long duration;
int cm;
int inch;

// Encoder
const int CLK = D16;// white wire 
const int DT = D5; // blue wire  
const int SW = D6; //green wire // also button

#define OLED_RESET (D4)
Adafruit_SSD1306 onscreen(OLED_RESET);

//HC_SR04 sonar(TRIG,ECHO,MaxDist);

void testdrawchar(void);

// Ultrasonic Sensor

int trigPin = D10;
int echoPin = A2;

// Buzzer
int buzzer = A5;

int pushups;

bool inchDn;
bool inchUp;

// Wemo

// bool wemoOnOff = false;
// bool WEMO_STATE;
// const int WEM01 =1;



// Hue Lamps

int bulbQty[6]; // total number of bulbs in classroom 
int bulbId[] = {0,1,2,3,4,5};
bool onOff;

String ONOFF;
Button ENCODERBUTTON(SW);
Encoder myEnc (CLK,DT);

// Let Device OS manage the connection to the Particle Cloud

//Which mode do I use ?

//SYSTEM_MODE(SEMI_AUTOMATIC);

SYSTEM_MODE(MANUAL); 


// Run the application and system concurrently in separate threads
//SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
//SerialLogHandler logHandler(LOG_LEVEL_INFO);

// setup() runs once, when the device is first turned on

// Ultra Sonic Sensor


void setup() {

 // Put initialization like pinMode and begin functions here

  Serial.begin(9600);

  waitFor(Serial.isConnected,10000);


// Ultrasonic Sensor

  pinMode(trigPin,OUTPUT);    
  pinMode(echoPin,INPUT);    
  pinMode(buzzer,OUTPUT);  

//Encoder

  pinMode(SW,INPUT);

  onOff = true;
  WiFi.on();
  WiFi.setCredentials("IoTNetwork");
  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf("Connecting\n");
  }
  

  onscreen.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  onscreen.printf("CM_%d \n IN_%d",cm,inch);
  onscreen.display();
}
 
  

// loop() runs over and over again, as quickly as it can execute.
  void loop() {

  testdrawchar();

  // First run the Ultrasonic

  digitalWrite(trigPin,LOW);
  //delay(10);
  digitalWrite(trigPin,HIGH);
 // delay(10);
  digitalWrite(trigPin,LOW);

//delay slowed me down omitting eys me the process smoother !
  duration = pulseIn(echoPin, HIGH);

  cm= (duration/2)*0.034;
  inch = (duration/2)*0.0135;

  if(inch < 3){ // buzzer rings true for perfect dn position
    tone( buzzer, 500,500);
  }

   if( inch >=12 && inch <=22){ //buzzer rings true pefect up position
    //delay(500);
    tone(buzzer,400,200);
  }

//       delay(2000);
//       digitalWrite(buzzer,HIGH);   //Alternative
//       digitalWrite(buzzer,LOW);    // Alternative
// }
          
// if inch is 10 then true and doen is 3 then also true , once both up and down are true then count pushups, reset the 
// up and down to false to continue count, then use a button to reset pushups counter to zero.
    
    if ( inch == 3){
      inchDn = true;
    }

    if ( inch >=12 && inch <=20){ // register true for number between 12 and 18 including 12 and 18
      inchUp = true;
    }

    if(inchDn && inchUp){
      pushups ++; // reset T/F statements after count lets see if the count continues!
      inchUp = false;
      inchDn = false;
  }


  if (pushups == 3) {
    for ( int i = 0; i < 6; i++){
      setHue(bulbId[i], true, HueRed, 255, 55);
    }
  }

  if (pushups == 0) {
    for ( int i = 0; i < 6; i++){
      setHue(bulbId[i], false, HueRed, 255, 55);
    }
  }
// reset the count with button


  if (ENCODERBUTTON.isClicked()) {
     pushups = 0;  // also cut on wemo fan for 10 seconds !
  }
}

// THE SPEAKER "SPK" SEEMED LIKE AN EASY CONNECTION BUT FAILS TO EXECUTE AS WRITTEN IT IS PLUGGED DIRECTY INTO THE PIN AND A GROUND, 





  

   // The core of your code will likely live here.

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!

void testdrawchar () {
  
  onscreen.setTextSize(1);
  onscreen.setTextColor(WHITE);
  onscreen.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  onscreen.clearDisplay();
  onscreen.printf("CM-%d \n IN-%d \n PUSHUPS-%d",cm,inch,pushups);
  onscreen.display();
  onscreen.clearDisplay();

  //Serial.printf("CM-%d \n IN-%d \n PU-%d",cm,inch,pushups);
}

