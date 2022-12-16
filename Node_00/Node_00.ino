// Node00
#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include <Wire.h>
#include <SimpleTimer.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  //0x27 is the i2c address, while 16 = columns, and 2 = rows. 

SimpleTimer timer;

RF24 radio(9, 10); // nRF24L01 (CE,CSN)
RF24Network network(radio); // Include the radio in the network
const uint16_t this_node = 00; // Address of our node in Octal format
unsigned long data[3]; // number of sensors

unsigned long data1P;
unsigned long data1F; 
unsigned long data2P;
unsigned long data2F;
unsigned long data3P;
unsigned long data3F;

const String SERVER  = "api.thingspeak.com";
const String TOKEN  = "A7KTR5NT5B2N4SDF";

void setup() 
{
  // Pin settings to read supply voltage
  analogReference(INTERNAL); // Set internal reference to 1.1V
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  lcd.init();                 //Init the LCD
  lcd.backlight();            //Activate backlight     
  lcd.home();

  timer.setInterval(200L, lcdDisplay);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("WELCOME!");
  delay(2000);
  lcd.clear();
}
void loop() 
{
  timer.run(); 
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
  
  while ( network.available() ) 
  { // Is there any incoming data?
    RF24NetworkHeader header;
  
    network.read(header, &data, sizeof(data)); // Read the incoming data
    
    if (header.from_node == 1) 
    { // If data comes from Node 01
      data1P = data[0]; 
      data1F = data[1]; 
    }
  
    if (header.from_node == 2) 
    { // If data comes from Node 02
      data2P = data[0];
      data2F = data[1]; 
    }

    if (header.from_node == 3) 
    { // If data comes from Node 03
      data3P = data[0];
      data3F = data[1]; 
    }
  }

}

void lcdDisplay()
{

lcd.clear();
lcd.setCursor(0,0); 
lcd.print("T1_D1:"); 
lcd.print(data1);

lcd.setCursor(0,1); 
lcd.print("T2_D2:"); 
lcd.print(data2);
  
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
