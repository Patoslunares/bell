#include <ArduinoJson.h>

boolean anterior[3];    
boolean actual[3]; 
int contador[3]; 

int i = 0;
int initSeting = 7, cantidadPin = 3;
int pin[3];

char car;

StaticJsonBuffer<200> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();

JsonArray& sensores = root.createNestedArray("sensores");
JsonArray& pasos = root.createNestedArray("pasos");

boolean debounce(boolean dato_anterior, int pin) 
{
 boolean dato_actual = digitalRead(pin);
   if (dato_anterior != dato_actual)
     {
       //delay(5);
       dato_actual = digitalRead(pin);
     }
   return dato_actual;
}  

void setup() 
{
  Serial.begin(9600);
  sensores.add("pasos");
  
  for(i = initSeting; i <= initSeting + (cantidadPin-1); i++)
  {
      pin[i - initSeting] = i;
      pinMode(pin[i - initSeting],INPUT);
      pasos.add(i - initSeting);   
  }
  
}



void loop() 
{           

  
  for(i = initSeting; i <= initSeting + (cantidadPin-1); i++)
  {
    //Serial.println(i - initSeting);
    actual[i - initSeting] = debounce(anterior[i - initSeting], pin[i - initSeting]); 
    
  
    if ( anterior[i - initSeting] == 0 && actual[i - initSeting] == 1) 
    {
           contador[i - initSeting]++;              
           
           //delay(50);          
           //Serial.println(contador[i - initSeting]);
    }
    
      anterior[i - initSeting] = actual[i - initSeting];
  }
  
   //Serial.print(Serial.read());
    if (Serial.available()){
      // read the incoming byte:
      car = Serial.read();
      
      for(i = initSeting; i <= initSeting + (cantidadPin-1); i++)
      {
          pasos[i - initSeting] = contador[i - initSeting];
          contador[i - initSeting] = 0;
      }
      root.printTo(Serial);    
      Serial.println("");

    }
  
}
