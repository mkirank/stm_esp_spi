#include <ESP32SPISlave.h>


ESP32SPISlave slave;


static constexpr uint32_t BUFFER_SIZE {32};
uint8_t spi_slave_tx_buf[BUFFER_SIZE];
uint8_t spi_slave_rx_buf[BUFFER_SIZE];


void setup() {
Serial.begin(9600);
delay(2000);
slave.setDataMode(SPI_MODE0);
slave.begin(VSPI); // VSPI is not the default for slave mode


// clear buffers
memset(spi_slave_tx_buf, 0, BUFFER_SIZE);
memset(spi_slave_rx_buf, 0, BUFFER_SIZE);
}


void loop() {
// block until the transaction comes from master
slave.wait(spi_slave_rx_buf, spi_slave_tx_buf, BUFFER_SIZE);


// if transaction has completed from master,
// available() returns size of results of transaction,
// and buffer is automatically updated
char data;
while (slave.available()) {
Serial.print("Sent to master: ");
Serial.print(spi_slave_tx_buf[0]);
Serial.print(", Received from master: ");
Serial.println(spi_slave_rx_buf[0]);
data = spi_slave_rx_buf[0];
slave.pop();
}
Serial.println(". ");
delay(1000);
}
