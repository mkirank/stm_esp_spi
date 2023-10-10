#include <SPI.h>

const int slaveSelectPin = PA4;  // SS (Slave Select) pin

void setup() {
    Serial.begin(9600);
    
    pinMode(slaveSelectPin, OUTPUT);
    digitalWrite(slaveSelectPin, HIGH); // Deselect the slave device initially

    SPI.begin();
}
void loop() {
    digitalWrite(slaveSelectPin, LOW);
    delay(1000);
    digitalWrite(slaveSelectPin, HIGH);
    delay(1000);
}

void loop1() {
    Serial.print('x');
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    digitalWrite(slaveSelectPin, LOW); // Select the slave device
    delay(10); // small delay to ensure slave is ready

    byte dataToSend = 0x3a; 
    byte dataReceived = SPI.transfer(dataToSend);
    
    digitalWrite(slaveSelectPin, HIGH); // Deselect the slave device
    SPI.endTransaction();

    Serial.print("Sent to slave: ");
    Serial.print(dataToSend);
    Serial.print(", Received from slave: ");
    Serial.println(dataReceived);

    delay(1000);
}

