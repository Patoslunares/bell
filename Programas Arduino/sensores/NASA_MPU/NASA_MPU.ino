#include<Wire.h>
#include <ArduinoJson.h>
#define num 1

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265; 
int maxVal=402;

int i,k;
double prom[num + 1][3];

double x,Px;
double y,Py;
double z,Pz;

StaticJsonBuffer<200> jsonBuffer;

JsonObject& root = jsonBuffer.createObject();

JsonArray& sensores = root.createNestedArray("sensors");

JsonArray& ace = root.createNestedArray("aceletrometro");
  
void setup(){ 
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  Serial.begin(9600);
  sensores.add("mpu");
  

  ace.add(0);
  ace.add(1);
  ace.add(2);
 }

void loop(){
  i = 0;
 
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  prom[i][0] = x;
  prom[i][1] = y;
  prom[i][2] = z;
  
  if(i = num){
      Px = 0;
      Py = 0;
      Pz = 0;
      for(k = 0; k <= num ; k++){
        Px = Px + prom[k][0];
        Py = Py + prom[k][1];
        Pz = Pz + prom[k][2];
      }
        

        ace[0]=Px/num;
        ace[1]=Py/num;
        ace[2]=Pz/num;
      root.printTo(Serial);
     /* Serial.print("AngleX= ");
      Serial.println(Px/num);
      
      Serial.print("AngleY= ");
      Serial.println(Py/num);
      
      Serial.print("AngleZ= ");
      Serial.println(Pz/num);*/
      Serial.println("");
      
  }
}
