#include "DHT.h"
#include "Servo.h"
#include "time.h"
#include "WiFi.h"
#include "HTTPClient.h"
#include <ArduinoJson.h>
#define DHTTYPE DHT11

// WiFi
char ssid[] = "AndroidAP";
char password[] = "29102003";

// OM2M (HTTP)
String cse_ip = "192.168.219.207";
String cse_port = "8080";
String server = "http://" + cse_ip + ":" + cse_port + "/~/in-cse/in-name/";
String cnt = "node1";
String mode_ae = "Mode";

// DHT11
int DHTPIN = 22;
DHT dht(DHTPIN, DHTTYPE);
String Humidity_ae = "Humidity";
String Temperature_ae = "Temperature";

// Water Level Sensor
int water_power_pin = 32;
int water_signal_pin = 33;           //Analog input
String WaterLevel_ae = "WaterLevel";

// Buzzer
int buzzer_pin = 21;

// Servo Fan dial
Servo dial_fan;
int dial_fan_pin = 18;
String FanSpeed_ae = "FanSpeed";

// Servo Fan pump
Servo dial_pump;
int dial_pump_pin = 19;
String Pump_ae = "Pump";

// Thresholds
int humidity_threshold = 80;
String cnthumidity = "Humidity_Threshold";
float temp_low = 25;
String cntlow = "Temp_Low";
float temp_medium = 30;
String cntmedium = "Temp_Medium";
float temp_high = 35;
String cnthigh = "Temp_High";
int water_full = 40;
int water_empty = 3;
String pump = "F";
String fanspeed = "0";

void createCI(String ae, String cnt, String& val){
  HTTPClient http;
  http.begin(server + ae + "/" + cnt + "/");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");
  int code = http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(val) + "}}");
  Serial.println(code);
  if (code == -1) {
  Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  http.end();
}

String getlastCI(String ae, String cnt){
  HTTPClient http;
  http.begin(server + ae + "/" + cnt + "/la/");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");
  int code = http.GET();
  Serial.println(code);
  String json = http.getString();
  http.end();
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, json);
  String inp = doc["m2m:cin"]["con"];
  return inp;
}

void setup(){
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("Connecting...\n");
  }
  
  dht.begin();

  pinMode(water_power_pin, OUTPUT);
  digitalWrite(water_power_pin, LOW);

  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, HIGH);

  dial_fan.attach(dial_fan_pin);
  dial_fan.write(90);

  dial_pump.attach(dial_pump_pin);
  dial_pump.write(90);
}

void loop()
{
  delay(100);
  int pump_flag = 0;                                    // 0 -> ON, 1 -> OFF
  String modestr = "a";
  modestr = getlastCI(mode_ae, cnt);                        // a -> Automatic, m -> Manual
  Serial.println(modestr);
  digitalWrite(water_power_pin, HIGH);
  delay(10);
  int water_level = analogRead(water_signal_pin);
  digitalWrite(water_power_pin, LOW);
  water_level = water_level * 40/2182;
  String water_level_str = String(water_level);                  // convert to mm
  Serial.print("Water Level : ");
  Serial.println(water_level);
  String WaterLevel = String(water_level, 2);
  if(water_level < water_empty)
  {
    pump_flag = 1;
    pump = "F";
    Serial.println("Tank Empty !");
    digitalWrite(buzzer_pin, LOW);
    delay(500);
    digitalWrite(buzzer_pin, HIGH);
    delay(500);
    digitalWrite(buzzer_pin, LOW);
    delay(500);
    digitalWrite(buzzer_pin, HIGH);
  }
  else if(water_level >= water_full)
  {
    Serial.println("Tank Full !");
    digitalWrite(buzzer_pin, LOW);
    delay(500);
    digitalWrite(buzzer_pin, HIGH);
  }
  int mode_m = modestr.compareTo("a");
  if(mode_m == 0)
  {
    String hthresh = getlastCI(Humidity_ae, cnthumidity);
    String tlow = getlastCI(Temperature_ae, cntlow);
    String tmedium = getlastCI(Temperature_ae, cntmedium);
    String thigh = getlastCI(Temperature_ae, cnthigh);
    humidity_threshold = hthresh.toFloat();
    temp_low = tlow.toFloat();
    temp_medium = tmedium.toFloat();
    temp_high = thigh.toFloat();
    Serial.println(tlow);
    Serial.println(tmedium);
    Serial.println(thigh);
    delay(2000);
    float temperature = dht.readTemperature();
    delay(2000);
    float humidity = dht.readHumidity();
    while(isnan(temperature) || isnan(humidity))
    {
      delay(2000);
      temperature = dht.readTemperature();
      delay(2000);
      humidity = dht.readHumidity();
    }
    String temperature_str = String(temperature, 2);
    String humidity_str = String(humidity, 2);
    Serial.print("Humidity : ");
    Serial.println(humidity);
    Serial.print("Temperature : ");
    Serial.println(temperature);
    if(humidity > humidity_threshold || pump_flag == 1)
    {
      Serial.println("High Humidity !");
      dial_pump.write(0);
      pump = "F";
    }
    if(humidity <= humidity_threshold && pump_flag == 0)
    {
      Serial.println("Low Humidity !");
      dial_pump.write(180);
      pump = "T";
    }
    if(temperature > temp_low && temperature <= temp_medium)
    {
      Serial.println("Low Temperature !");
      dial_fan.write(60);
      fanspeed = "1";
    }
    else if(temperature > temp_medium && temperature <= temp_high)
    {
      dial_fan.write(120);
      Serial.println("Medium Temperature !");
      fanspeed = "2";
    }
    else if(temperature > temp_high)
    {
      Serial.println("High Temperature !");
      dial_fan.write(180);
      fanspeed = "3";
    }
    createCI(Temperature_ae, cnt, temperature_str);
    createCI(Humidity_ae, cnt, humidity_str);
    createCI(FanSpeed_ae, cnt, fanspeed);
    createCI(Pump_ae, cnt, pump);
  }
  else
  {
    fanspeed = getlastCI(FanSpeed_ae, cnt);
    pump = getlastCI(Pump_ae, cnt);
    Serial.print("Pump : ");
    Serial.println(pump); 
    Serial.print("Fan : ");
    Serial.println(fanspeed);
    int fanspeed_int = fanspeed.toInt();
    fanspeed_int = fanspeed_int % 4;
    fanspeed_int = fanspeed_int * 60;
    dial_fan.write(fanspeed_int);
    int pump_m = pump.compareTo("F");
    if(pump_m == 0 || pump_flag == 1)
    {
      dial_pump.write(0);
    }
    else
    {
      dial_pump.write(180);
    }
  }
  createCI(WaterLevel_ae, cnt, water_level_str);
}
