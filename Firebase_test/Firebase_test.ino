#include <SoftwareSerial.h>
SoftwareSerial myserial(6, 7); // RX: 10, TX:11 

void setup()
{
  myserial.begin(9600);        // the GPRS baud rate
  Serial.begin(9600);
  Serial.println("Initializing..........");
}
 
void loop()
{
 /********************GSM Communication Starts********************/
 
  if (myserial.available())
  Serial.write(myserial.read());
 
  myserial.println("AT");
  delay(3000);
 
  myserial.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(6000);
  ShowSerialData();
 
  myserial.println("AT+SAPBR=3,1,\"APN\",\"web.gprs.mtnnigeria.net\"");//APN
  delay(6000);
  ShowSerialData();
 
  myserial.println("AT+SAPBR=1,1");
  delay(6000);
  ShowSerialData();
 
  myserial.println("AT+SAPBR=2,1");
  delay(6000);
  ShowSerialData();
 
 
  myserial.println("AT+HTTPINIT");
  delay(6000);
  ShowSerialData();
 
  myserial.println("AT+HTTPPARA=\"CID\",1");
  delay(6000);
  ShowSerialData();
 
  myserial.println("AT+HTTPPARA=\"URL\",\"http://https://us-central1-londonwarddata.cloudfunctions.net/helloWorld/addData\""); //Server address
  delay(4000);
  ShowSerialData();
 
  myserial.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  delay(4000);
  ShowSerialData();
 
 
  myserial.println("AT+HTTPDATA=" + String(7) + ",100000");
  delay(6000);
  ShowSerialData();
 
  myserial.println("Working");
  delay(6000);
  ShowSerialData;
 
  myserial.println("AT+HTTPACTION=1");
  delay(6000);
  ShowSerialData();
 
  myserial.println("AT+HTTPREAD");
  delay(6000);
  ShowSerialData();
 
  myserial.println("AT+HTTPTERM");
  delay(10000);
  ShowSerialData;
 
  /********************GSM Communication Stops********************/
 
}
 
 
void ShowSerialData()
{
  while (myserial.available() != 0)
    Serial.write(myserial.read());
  delay(1000);
 
}





////include software serial
//#include <SoftwareSerial.h>
//
///******************Configuration Zone*****************/
////define pins for software serial
//SoftwareSerial SIM800(6, 7);
//
//const String APN  = "web.gprs.mtnnigeria.net";
//const String USER = "";
//const String PASS = "";
//
//void init_gsm();
//void gprs_connect();
//boolean gprs_disconnect();
//boolean is_gprs_connected();
//void post_to_firebase(String data);
//boolean waitResponse(String expected_answer="OK", unsigned int timeout=2000);
////
//const String FIREBASE_HOST  = "\"us-central1-londonwarddata.cloudfunctions.net/helloWorld/addData\"";
//const String FIREBASE_SECRET  = "AIzaSyCgkqfPvh47muosp88D4ZtONOHs-jQFGbA";
//
//#define USE_SSL false
//#define DELAY_MS 500
//
//void setup() 
//{
//  // put your setup code here, to run once:
//  SIM800.begin(9600);        // the gsm baud rate   
//  Serial.begin(9600);    // the baud rate
//  
//  Serial.println("Initializing SIM800...");
//  init_gsm();
//}
//
//void loop() 
//{
//  // put your main code here, to run repeatedly:
//  String data = "{\"data\":[";
//  data += "{\"pressure\":\"40.00\",\"flow_rate\":\"20.00\",\"id\":\"a\",\"index\":0},";
//  data += "{\"pressure\":\"30.00\",\"flow_rate\":\"15.00\",\"id\":\"b\",\"index\":1},";
//  data += "{\"pressure\":\"20.00\",\"flow_rate\":\"10.00\",\"id\":\"c\",\"index\":2},";
//  data += "{\"pressure\":\"10.00\",\"flow_rate\":\"5.00\",\"id\":\"d\",\"index\":3}";
//  data += "],\"readable_time\":";
//  data += "\""+String(millis())+"\"";
//  data += "}";
//  /****************DISPLAY RESULT**********/
//  /*
//   * Format for server
//   * {data:[{flow_rate:XXX, pressure:XXX, id: "a", index: 0},
//   *        {flow_rate:XXX, pressure:XXX, id: "b", index: 1},
//   *        {flow_rate:XXX, pressure:XXX, id: "c", index: 2},
//   *        {flow_rate:XXX, pressure:XXX, id: "d", index: 3}],
//   *  readable_time: "DateTime"}
//   *  
//   *  "AT+CCLK?" AT command to get time
//  */
//  Serial.print("Data = ");
//  Serial.println(data);
//
//  if(!is_gprs_connected())
//  {
//    gprs_connect();
//  }
//  
//  post_to_firebase(data);
//
//  delay(1000);
//}
//
//void gsm_send_serial(String command) 
//{
//  Serial.println("Send ->: " + command);
//  SIM800.println(command);
//  long wtimer = millis();
//  while (wtimer + 3000 > millis()) 
//  {
//    while (SIM800.available()) 
//    {
//      Serial.write(SIM800.read());
//    }
//  }
//  Serial.println();
//}
//
//void post_to_firebase(String data)
//{
//  
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Start HTTP connection
//  SIM800.println("AT+HTTPINIT");
//  waitResponse();
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Enabling SSL 1.0
//  if(USE_SSL == true){
//    SIM800.println("AT+HTTPSSL=1");
//    waitResponse();
//    delay(DELAY_MS);
//  }
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Setting up parameters for HTTP session
//  SIM800.println("AT+HTTPPARA=\"CID\",1");
//  waitResponse();
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Set the HTTP URL - Firebase URL and FIREBASE SECRET
//  //SIM800.println("AT+HTTPPARA=\"URL\","+FIREBASE_HOST+".json?auth="+FIREBASE_SECRET);
//  SIM800.println("AT+HTTPPARA=\"URL\","+FIREBASE_HOST);
//  waitResponse();
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Setting up re direct
////  SIM800.println("AT+HTTPPARA=\"REDIR\",1");
////  waitResponse();
////  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Setting up content type
//  SIM800.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
//  waitResponse();
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Setting up Data Size
//  //+HTTPACTION: 1,601,0 - error occurs if data length is not correct
//  SIM800.println("AT+HTTPDATA=" + String(data.length()) + ",10000");
//  waitResponse("DOWNLOAD");
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Sending Data
//  SIM800.println(data);
//  waitResponse();
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Sending HTTP POST request
//  SIM800.println("AT+HTTPACTION=1");
//  
//  for (uint32_t start = millis(); millis() - start < 20000;){
//    while(!SIM800.available());
//    String response = SIM800.readString();
//    if(response.indexOf("+HTTPACTION:") > 0)
//    {
//      Serial.println(response);
//      break;
//    }
//  }
//    
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //+HTTPACTION: 1,603,0 (POST to Firebase failed)
//  //+HTTPACTION: 0,200,0 (POST to Firebase successfull)
//  //Read the response
//  SIM800.println("AT+HTTPREAD");
//  waitResponse("OK");
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Stop HTTP connection
//  SIM800.println("AT+HTTPTERM");
//  waitResponse("OK",1000);
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//}
////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//// Initialize GSM Module
////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//void init_gsm()
//{
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Testing AT Command
//  SIM800.println("AT");
//  waitResponse();
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Checks if the SIM is ready
//  SIM800.println("AT+CPIN?");
//  waitResponse("+CPIN: READY");
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Turning ON full functionality
//  SIM800.println("AT+CFUN=1");
//  waitResponse();
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Turn ON verbose error codes
//  SIM800.println("AT+CMEE=2");
//  waitResponse();
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Enable battery checks
//  SIM800.println("AT+CBATCHK=1");
//  waitResponse();
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Register Network (+CREG: 0,1 or +CREG: 0,5 for valid network)
//  //+CREG: 0,1 or +CREG: 0,5 for valid network connection
//  SIM800.println("AT+CREG?");
//  waitResponse("+CREG: 0,");
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //setting SMS text mode
//  SIM800.print("AT+CMGF=1\r");
//  waitResponse("OK");
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//}
//
//
//
//
//
////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
////Connect to the internet
////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//void gprs_connect()
//{
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //DISABLE GPRS
//  SIM800.println("AT+SAPBR=0,1");
//  waitResponse("OK",60000);
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Connecting to GPRS: GPRS - bearer profile 1
//  SIM800.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
//  waitResponse();
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //sets the APN settings for your sim card network provider.
//  SIM800.println("AT+SAPBR=3,1,\"APN\","+APN);
//  waitResponse();
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //sets the user name settings for your sim card network provider.
//  if(USER != ""){
//    SIM800.println("AT+SAPBR=3,1,\"USER\","+USER);
//    waitResponse();
//    delay(DELAY_MS);
//  }
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //sets the password settings for your sim card network provider.
//  if(PASS != ""){
//    SIM800.println("AT+SAPBR=3,1,\"PASS\","+PASS);
//    waitResponse();
//    delay(DELAY_MS);
//  }
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //after executing the following command. the LED light of 
//  //sim800l blinks very fast (twice a second) 
//  //enable the GPRS: enable bearer 1
//  SIM800.println("AT+SAPBR=1,1");
//  waitResponse("OK", 30000);
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Get IP Address - Query the GPRS bearer context status
//  SIM800.println("AT+SAPBR=2,1");
//  waitResponse("OK");
//  delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//}
//
//
///*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//* Function: gprs_disconnect()
//* AT+CGATT = 1 modem is attached to GPRS to a network. 
//* AT+CGATT = 0 modem is not attached to GPRS to a network
////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//boolean gprs_disconnect()
//{
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //Disconnect GPRS
//  SIM800.println("AT+CGATT=0");
//  waitResponse("OK",60000);
//  //delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//  //DISABLE GPRS
//  //SIM800.println("AT+SAPBR=0,1");
//  //waitResponse("OK",60000);
//  //delay(DELAY_MS);
//  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//
//  return true;
//}
//
//
//
//
//
///*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//* Function: gprs_disconnect()
//* checks if the gprs connected.
//* AT+CGATT = 1 modem is attached to GPRS to a network. 
//* AT+CGATT = 0 modem is not attached to GPRS to a network
////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//boolean is_gprs_connected()
//{
//  SIM800.println("AT+CGATT?");
//  if(waitResponse("+CGATT: 1",6000) == 1) { return false; }
//
//  return true;
//}
//
//
//
//
//
////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
////Handling AT COMMANDS
////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
////boolean waitResponse(String expected_answer="OK", unsigned int timeout=2000) //uncomment if syntax error (arduino)
//boolean waitResponse(String expected_answer, unsigned int timeout) //uncomment if syntax error (esp8266)
//{
//  uint8_t x=0, answer=0;
//  String response;
//  unsigned long previous;
//    
//  //Clean the input buffer
//  while( SIM800.available() > 0) SIM800.read();
//  
//  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
//  previous = millis();
//  do{
//    //if data in UART INPUT BUFFER, reads it
//    if(SIM800.available() != 0){
//        char c = SIM800.read();
//        response.concat(c);
//        x++;
//        //checks if the (response == expected_answer)
//        if(response.indexOf(expected_answer) > 0){
//            answer = 1;
//        }
//    }
//  }while((answer == 0) && ((millis() - previous) < timeout));
//  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
//  
//  Serial.println(response);
//  return answer;
//}
