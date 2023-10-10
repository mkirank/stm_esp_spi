#include <ESP32SPISlave.h>

SPIClass * vspi = NULL;
const int VSPI_MISO = 19;
const int VSPI_MOSI = 23;
const int VSPI_SCLK = 18;
const int VSPI_CS = 5;  // You can change this if you're using a different pin for chip select

ESP32SPISlave slave(VSPI_HOST, VSPI_MISO, VSPI_MOSI, VSPI_SCLK, VSPI_CS); // Define SPI pins using renamed constants

void setup() {
    Serial.begin(115200);
    Serial.println("ESP32 SPI Slave");

    // Initialize the SPI slave interface
    slave.begin();

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

