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

long duration;
int cm;
int inch;



#define OLED_RESET (D4)
Adafruit_SSD1306 onscreen(OLED_RESET);

//HC_SR04 sonar(TRIG,ECHO,MaxDist);

void testdrawchar(void);

//int pushups;

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

// Run the application and system concurrently in separate threads
//SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
//SerialLogHandler logHandler(LOG_LEVEL_INFO);

// setup() runs once, when the device is first turned on
int trigPin = D10;
int echoPin = A2;
int buzzer = A5;
int spkr = D3;

int pushups;

bool inchDn;
bool inchUp;




void setup() {

  Serial.begin(9600);

  pinMode(trigPin,OUTPUT);    
  pinMode(echoPin,INPUT);    
  pinMode(buzzer,OUTPUT);  
  pinMode(spkr,OUTPUT);  

  onscreen.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  onscreen.printf("CM_%d \n IN_%d",cm,inch);
  onscreen.display();
  delay(5000);
  //testdrawchar();


  
  
  // Put initialization like pinMode and begin functions here
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

  digitalWrite(trigPin,LOW);
  //delay(10);
  digitalWrite(trigPin,HIGH);
 // delay(10);
  digitalWrite(trigPin,LOW);

  
  duration = pulseIn(echoPin, HIGH);

  cm= (duration/2)*0.034;
  inch = (duration/2)*0.0135;

  if(inch < 3){ // buzzer rings true for perfect dn position
    tone( buzzer, 200,200);
    //delay(500);
    tone(buzzer,200,200);
  }

   if( inch >=12 && inch <=22){ //buzzer rings true pefect up position
    tone( buzzer, 400,200);
    //delay(500);
    tone(buzzer,400,200);
  }

//      if(inch > 22){
//       digitalWrite(buzzer,HIGH);
//       delay(2000);
//       digitalWrite(buzzer,LOW);
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

    if(pushups < 3){
      tone(spkr,523,300);
      //delay(2000);
      noTone(spkr);
   }
  

 // reset the count with button

  testdrawchar();

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

