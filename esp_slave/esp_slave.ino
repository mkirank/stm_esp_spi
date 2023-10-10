#include <ESP32SPISlave.h>


ESP32SPISlave slave;


void setup() {
Serial.begin(9600);
Serial.println("ESP32 SPI Slave");


// Initialize the SPI slave interface
slave.setDataMode(SPI_MODE0);
slave.begin(VSPI);


// Set the callback when data is received
slave.setDataReceivedCallback(onDataReceived);
}


void loop() {
// Continuously poll the slave
slave.poll();
delay(10);
}


void onDataReceived(uint8_t * data, size_t len) {
// Print received data
Serial.print("Received: ");
for (size_t i = 0; i < len; i++) {
Serial.print(data[i], HEX);
Serial.print(" ");
}
Serial.println();
}
