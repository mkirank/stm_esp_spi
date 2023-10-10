#include <SPI.h>

const int slaveSelectPin = 5;  // VSPI_CSO (Slave Select) pin

void setup() {
    //pinMode(slaveSelectPin, INPUT);
    pinMode(slaveSelectPin, INPUT_PULLUP);
    Serial.begin(9600);
    SPI.begin();  // Use default VSPI pins: SCK=18, MISO=19, MOSI=23, SS=5
}

void loop() {
    if (digitalRead(slaveSelectPin) == LOW) {
        Serial.println("Slave Selected!");
    } else {
      Serial.print("X");
    }
    delay(500);
}

void loop1() {
    if (digitalRead(slaveSelectPin) == LOW) {
        SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
        
        byte dataToSend = 0x00;  // Dummy byte
        byte dataReceived = SPI.transfer(dataToSend);

        Serial.print("Sent to master: ");
        Serial.print(dataToSend);
        Serial.print(", Received from master: ");
        Serial.println(dataReceived);

        byte response = 0x3a;  // Response byte
        SPI.transfer(response);

        SPI.endTransaction();
    }
    Serial.print(". ");
    delay(1000);
}

