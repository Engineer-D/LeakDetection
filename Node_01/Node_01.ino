// Node01
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

RF24 radio(9, 10); // nRF24L01 (CE,CSN)
RF24Network network(radio); // Include the radio in the network
LiquidCrystal_I2C lcd(0x27, 16, 2);

const uint16_t this_node = 01; // Address of this node in Octal format
const uint16_t node00 = 00; 
unsigned long data[3]; // number of sensors

void setup() 
{
  // Initialize I2C LCD and Setup
  lcd.init();
  lcd.backlight(); 
  
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  analogReference(INTERNAL); // Set internal reference to 1.1V
  Serial.begin(9600);    // the baud rate
  
  /*******Welcome Command after Successful Setup******/ 
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("WELCOME!");
  delay(2000);
  lcd.clear();
}
void loop() 
{
  network.update();
  // put your main code here, to run repeatedly:
  float pressure = getPressure(A0);
  float flowRate = getFlow(A1);
  
  /****************DISPLAY RESULT**********/
  lcd.print("Pressure: ");
  Serial.print("pressure = ");
  lcd.setCursor(10,0);
  lcd.print(pressure);
  Serial.println(pressure);

  lcd.setCursor(0,1);
  lcd.print("Flow Rate: ");
  Serial.print("Flow Rate = ");
  lcd.setCursor(11,1);
  lcd.print(flowRate);
  Serial.println(flowRate);
  
  data[0] = pressure;
  data[1] = flowRate; 
  
  RF24NetworkHeader header7(node00);
  bool ok = network.write(header7, &data, sizeof(data)); // Send the data
}

float readVoltage(int pin)
{
    long sum = 0;        // sum of samples taken
    float analogVoltage = 0.0; // calculated voltage
    float voltage = 0.0;
    
    for (int i = 0; i < 500; i++)
    {
        sum = sum + analogRead(pin);
        delayMicroseconds(1000);
    }
  
    analogVoltage = sum / (float)500;
    analogVoltage = (analogVoltage * 1.1) / 1023.0; //for internal 1.1v reference
    analogVoltage = (analogVoltage * 100) / 100; //round value by two precision

    return analogVoltage;
}

float getPressure(int pin)
{
  float pressure = 0.0;

  pressure = (readVoltage(pin) * 100)-2;

  if (pressure < 10.50 || pressure > 500)
  {
    pressure = 0;
  }
  
  return pressure;
  
}
float getFlow(int pin)
{
  uint8_t maxFlow = 5;
  float voltageAtMaxFlow = 4.33;
  float flow = 0.0;
  
  flow = ((maxFlow * readVoltage(pin))/ voltageAtMaxFlow);

  if(flow < 0.1 || flow > 5)
  {
    flow = 0;
  }

  return flow;// in cubic meter per hour
  
}
