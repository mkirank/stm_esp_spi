#include <ESP32SPISlave.h>

ESP32SPISlave slave(VSPI_HOST);  // Use the VSPI host

static constexpr uint32_t BUFFER_SIZE {32};
uint8_t spi_slave_tx_buf[BUFFER_SIZE];
uint8_t spi_slave_rx_buf[BUFFER_SIZE];

void setup() {
    Serial.begin(115200);
    delay(2000);

    // Begin() with settings for VSPI
    // VSPI = CS:  5, CLK: 18, MOSI: 23, MISO: 19
    slave.setDataMode(SPI_MODE0);
    slave.begin();   // No need to specify VSPI here since it's already provided in the constructor

    // Clear buffers
    memset(spi_slave_tx_buf, 0, BUFFER_SIZE);
    memset(spi_slave_rx_buf, 0, BUFFER_SIZE);
}

void loop() {
    // Block until the transaction comes from master
    slave.wait(spi_slave_rx_buf, spi_slave_tx_buf, BUFFER_SIZE);

    // If transaction has completed from master,
    // available() returns size of results of transaction,
    // and buffer is automatically updated
    while (slave.available()) {
        // Show received data
        Serial.print("Command Received: ");
        Serial.println(spi_slave_rx_buf[0]);
        slave.pop();
    }

    // Additional delay or processing if needed
    delay(1000);  // Delay for a second to easily read the serial data
}

