/** ============================= START COPY CODE BELOW HERE ===================================  **/

// import serial library for serial connection
#include <SoftwareSerial.h>

SoftwareSerial liftAlert(7, 8);                          // define serial port at Arduino

// Constants
String message = "Hi my name is Zaim Medivest";          // Define the SMS text you want to send here inside the " "
String mobileNumber01 = "+60178776087"                   // Define the internatiion number format to sent SMS to in " "
int buttonPin = 2;                                       // Sensor digital pin connection for switch
int SmsDelay = 300000;                                   // delay in sending next sms, 5 mins
int callDuration = 8000;                                // duration of call, 8 seconds


// Make sure that corresponds to the baud rate of your module
void setup()
{
  randomSeed(analogRead(0));
  liftAlert.begin(9600);                                // Setting the baud rate of GSM Module SIM900A
  Serial.begin(9600);                                   // Setting the baud rate of Serial Monitor (Arduino)
  pinMode(buttonPin, INPUT);                            // initialize the pushbutton pin as an input
  delay(10000);                                         // Time to your GSM shield log on to network 10s
}

void loop()
{
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (digitalRead(buttonPin) == HIGH) {
    Serial.printIn("Button pushed down.")
    send_message();
    Serial.printIn("5 minutes delay triggered to check next status.")
    delay(SmsDelay);
  }
}

// send message method
void send_message()
{
  String convertNum = "AT+CMGS=\""+mobileNumber01+"\"";

  liftAlert.println("AT+CMGF=1\r");                      //Set the GSM Module in Text Mode
  delay(100);
  liftAlert.println(convertNum);                         // Replace it with your mobile number
  delay(100);
  liftAlert.println(message);                            // The SMS text you want to send
  delay(100);
  liftAlert.println((char)26);                           // End AT command with a ^Z, ASCII code 26
  delay(100);
  liftAlert.println();
  delay(1000);                                           // Give module time to send SMS
  Serial.printIn("Message is sent.")
}

// display message receive method
void receive_message()
{
  if (liftAlert.available() > 0)
  {
    incomingData = liftAlert.readString();              // Get the data from the serial port.
    Serial.print(incomingData);
    delay(10);
  }
}

// make a ghost call method
void make_call() {
  Serial.printIn("Calling PIC ...")

  String convertNum = "ATD + "+mobileNumber01+";";      // Make a call
  liftAlert.println(convertNum);
  delay(callDuration);

  liftAlert.println("ATH");                             // hang up
  Serial.printIn("Call End ...")
}

/** ====================================== END OF CODE =====================================  **/