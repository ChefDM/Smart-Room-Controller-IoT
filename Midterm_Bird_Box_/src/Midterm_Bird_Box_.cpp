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
int trigPin(D10);
int echoPin(A2);
int buzzer = A5;

int pushups;
int prevDist;



void setup() {

  Serial.begin(9600);

  pinMode(trigPin,OUTPUT);    
  pinMode(echoPin,INPUT);    
  pinMode(buzzer,OUTPUT);    

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
  delay(10);
  digitalWrite(trigPin,HIGH);
  delay(10);
  digitalWrite(trigPin,LOW);

  
  duration = pulseIn(echoPin, HIGH);

  cm= (duration/2)*0.034;
  inch = (duration/2)*0.0135;

  if(inch < 3){
    // tone( A5, 440,200);
    // delay(500);
    // tone(A5,440,200);

digitalWrite(buzzer,HIGH);
delay(200);
digitalWrite(buzzer,LOW);

      }

  pushups = 0;
    

    if(inch == 3 || inch == 10 ){
      pushups ++;
  }

 prevDist = inch;

  testdrawchar();

  }
  





  

   // The core of your code will likely live here.

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!

void testdrawchar () {
  
  onscreen.setTextSize(2);
  onscreen.setTextColor(WHITE);
  onscreen.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  onscreen.clearDisplay();
  onscreen.printf("CM-%d \n IN-%d \n PUSHUPS-%d",cm,inch,pushups);
  onscreen.display();
  delay(10);
  onscreen.clearDisplay();

  Serial.printf("CM-%d \n IN-%d \n PU-%d",cm,inch,pushups);
  delay(10);
}

