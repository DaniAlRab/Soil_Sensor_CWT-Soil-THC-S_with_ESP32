#include <ModbusMaster.h>

#define RE_DE_PIN 4  // RE and DE pins from MAX3485
#define MAX485_DE 4
#define MAX485_RE 4

ModbusMaster node;

// Function to handle the transmission mode
void preTransmission() {
  digitalWrite(MAX485_DE, 1);
  digitalWrite(MAX485_RE, 1);
}

// Function to handle the reception mode
void postTransmission() {
  digitalWrite(MAX485_DE, 0);
  digitalWrite(MAX485_RE, 0);
}

void setup() {
  Serial.begin(115200);

  // Initialize RS-485 serial communication
  Serial1.begin(4800, SERIAL_8N1, 17, 16); // RX, TX pins

  // Initialize ModbusMaster instance
  node.begin(1, Serial1); // 1 is the default device address
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  // Initialize RE and DE pins
  pinMode(MAX485_DE, OUTPUT);
  pinMode(MAX485_RE, OUTPUT);
  digitalWrite(MAX485_DE, 0);
  digitalWrite(MAX485_RE, 0);
}

void readParameter(uint16_t registerAddress, const char* name, float conversionFactor) {
  uint8_t result;
  
  // Read data from the specified register address
  result = node.readHoldingRegisters(registerAddress, 2);

  if (result == node.ku8MBSuccess) {
    // Convert and print the received data
    float value = node.getResponseBuffer(0) * conversionFactor;
    Serial.print(name);
    Serial.print(": ");
    Serial.println(value);
  } else {
    Serial.print("Error reading ");
    Serial.print(name);
    Serial.print(": ");
    Serial.println(result);
  }
}

void loop() {
  // Read and print each parameter
  readParameter(0x0000, "Humidity", 0.1); // 0.1%RH
  readParameter(0x0001, "Temperature", 0.1); // 0.1°C
  readParameter(0x0002, "Conductivity", 1); // 1 unit
  readParameter(0x0003, "Salinity", 1); // 1 unit
  readParameter(0x0004, "TDS", 1); // 1 unit

  delay(1000); // Delay between reads
}
