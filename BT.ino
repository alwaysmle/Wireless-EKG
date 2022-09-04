/*
AUTHOR: Daniel Chou
DATE: Nov 1, 2021

ECG
0.5~1.5V

EMG
0.2~2V
*/

#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX for AT mode
int analoguePin = 3; // A3 pin for analogue reading
long long baudRate = 38400; //set using AT mode command: AT+UART=[baudrate],0,0
/*
 * HC-05 Rx > Arduino Pin 11
 * HC-05 Tx > Arduino Pin 10
 * HC-05 Vcc > Arduino 5V
 * HC-05 GND > Arduino GND
 * HC-05 KEY > Arduino Pin 9
 * EMG and ECG reading connect to A3
 */

void setup()
{
 Serial.begin(9600);  //baud rate of Arduino can go up to 115200, 9600 by default
 //Serial.println("Enter commands:");
 BTSerial.begin(baudRate); 
 pinMode(analoguePin, INPUT); 
 
 //pinMode(9, OUTPUT); // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
 //digitalWrite(9, HIGH);
 //Serial.println("Enter AT commands:"); 
 //BTSerial.begin(38400); // HC-05 default speed in AT command moe 
}



/*
 *BTSerial.write() converts whatever to be sent (eg. string, int, char, byte) into bytes or array of bytes to send
 *APP side: If it is hard-coded to receive as...
 *  1. Text, the bytes will be collected as unsigned char and then combined into a string
 *  2. Byte (1 unsigned Byte for me), each byte (value between 0 and 255) will be received.
 */ 
unsigned i = 0; unsigned val;
float Amp_scale = 1;
 
void loop()
{ 
 
 // Keep reading from HC-05 and send to Arduino Serial Monitor
 if (BTSerial.available()){
    Serial.println(BTSerial.readString());
 }

 
 // Keep reading from Arduino Serial Monitor and send to HC-05
 if (Serial.available()){
    
    //val = analogRead(analoguePin);
    //val = random(0,255);
    //BTSerial.write(val);
    
    //debug use
    //BTSerial.write(Serial.read());
    if(Serial.read()=='s')
    {
      for(i=0; i < 1023; i+=4)
      {
        val = (i/4)*Amp_scale; 
        //Serial.print("sent to BT: ");
        Serial.println(val);
        BTSerial.write(val);
      }
    }
    
  }
}
