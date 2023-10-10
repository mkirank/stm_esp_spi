#include <SPI.h>

const int slaveSelectPin = PA4; // SS (Slave Select) pin
byte dataToSend = 0x3a;

void setup()
{
    Serial.begin(9600);

    pinMode(slaveSelectPin, OUTPUT);
    digitalWrite(slaveSelectPin, HIGH); // Deselect the slave device initially

    SPI.begin();
}
void loop()
{
    Serial.print('x');
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    digitalWrite(slaveSelectPin, LOW); // Select the slave device

    byte dataReceived = SPI.transfer(dataToSend);

    digitalWrite(slaveSelectPin, HIGH); // Deselect the slave device
    SPI.endTransaction();

    Serial.print("Sent to slave: ");
    Serial.print(dataToSend);
    Serial.print(", Received from slave: ");
    Serial.println(dataReceived);

    dataToSend = dataReceived + 1;

    delay(1000);
}
