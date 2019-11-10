/*
  SD card datalogger

 Card type:         SDHC
 Clusters:          121216
 Blocks x Cluster:  64
 Total Blocks:      7757824

 This example shows how to log data from three analog sensors
 to an SD card using the SD library.

 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10 (by Ismael)
 ATTENTION: The power supply is 5V because there is an internal regulator to 3,3V on MicroSD Card Adapter (by Ismael)

 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe
 modified 30 Dez 2017
 by Ismael Lopes

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;
unsigned int vloop = 0;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect))
  {
    Serial.println("\nCard failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("\ncard initialized.");
}

void loop()
{
  // make a string for assembling the data to log:
  String dataString = "";

  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 3; analogPin++)
  {
    unsigned int sensor = map(analogRead(analogPin),0,1023,0,5000);
    dataString += String(sensor);
    if (analogPin < 2)
    {
      dataString += ",";
    }
  }

  if (vloop==10)
  {
    delay(1000);
    exit(0);
  }
  vloop += 1;
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  if (vloop == 1)
  {
    dataFile.println("Tensão nas entradas A0, A1 e A2 em mV");
    Serial.println("Tensão nas entradas A0, A1 e A2 em mV");
  }
  
  // if the file is available, write to it:
  if (dataFile)
  {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else
  {
    Serial.println("error opening datalog.txt");
  }
}





