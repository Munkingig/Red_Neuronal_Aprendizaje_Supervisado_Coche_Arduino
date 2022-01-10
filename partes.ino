#include <string.h>
#include <stdio.h>


/******************************************************************
 *              Configuracion de los Motores                      *
 ******************************************************************/
//Motores left
//Trasero
int Pin_Enable_2 = 22;
int Pin_Input_4 = 24;
int Pin_Input_3 = 26;
//Delantero
int Pin_Enable_1 = 28;
int Pin_Input_1 = 30;
int Pin_Input_2 = 32;

//Motores Right
//Delantero
int Pin_Enable_3 = 34;
int Pin_Input_5 = 36;
int Pin_Input_6 = 38;
//Trasero
int Pin_Enable_4 = 40;
int Pin_Input_7 = 42;
int Pin_Input_8 = 44;
/******************************************************************
 *              Configuracion de los Sensores de proximidad       *
 ******************************************************************/
int EchoIzq = A4;  
int TrigIzq = A5; 

int EchoCen = A3;  
int TrigCen = A2; 

int EchoDer = A0;  
int TrigDer = A1; 

int EchoCenSup = A6;  
int TrigCenSup = A7;

int EchoLatIzq = A8;  
int TrigLatIzq = A9;

int EchoLatDer = A10;  
int TrigLatDer = A11;


double duracion, distancia;
double entrada1, entrada2, entrada3, entrada4, entrada5, entrada6 = 0.0; //entradas de datos para la NN
double ditanciaMaxima = 50.0;       // distancia de lejania desde la que empieza a actuar la NN
/******************************************************************
 *                                                                *
 ******************************************************************/


/******************************************************************
 *              Configuracion Red Neuronal                        *
 ******************************************************************/
const int InputNodes = 3; // incluye neurona de BIAS (3 datos + bias creo)
const int HiddenNodes = 6; //incluye neurona de BIAS
const int OutputNodes = 8; //Salidas Red Neuronal (2 por cada motor)
int i, j;
double Accum;
double Hidden[HiddenNodes];
double Output[OutputNodes]; //salidas de la red neuronal para dar ordenes a los motores.

float HiddenBias[6] = {-2.6609246,  -6.21766166,  0.6719238,  -1.91361643,  2.2715187,  -7.13369123};

float OutputBias[8] = { 1.09891189,  0.51677215,  0.5176923,  -0.05358793,  1.09891195,  0.51777866,  0.51615204, -0.05358793};


float HiddenWeights[3][6] = {{ -4.76060265,  -3.82800886,  -1.46388603, -10.52482004,  -1.48085581,  -4.96915681},
 { -1.38119297,  -1.09309423,  -2.88687046,  -4.24908356,   2.76399831,  2.1873772 },
 {  0.14264823,  -3.22309434,   8.64962958,  -3.48165854,  -9.3454453,  -2.98051136}};
                             

float OutputWeights[6][8] = {{ 0.02630783,  5.13696264,  5.11227514, -2.80382618,  0.02630783,  5.11013522,  5.15588299, -2.80382618},
 { 1.7111938,  -5.01162342, -4.98758049,  0.96023143,  1.7111939,  -4.98549652,  -5.03005081,  0.96023143},
 { 1.73185353, -4.90215991, -4.87880831, -0.04727425,  1.73185363, -4.87678458,  -4.9200616,  -0.04727425},
 {-0.02515359, -4.10509539, -4.0855204,   2.79325676, -0.02515359, -4.08382392,  -4.12010138,  2.79325676},
 { 1.73341113, -2.36087461, -2.352919,   -0.04506696,  1.73341122, -2.35223595,  -2.36705609, -0.04506696},
 {-0.60901439, -0.81515616, -0.8111343,  -1.00052274, -0.60901442, -0.81078545,  -0.81823547, -1.00052274}};
/******************************************************************
 *                                                                *
 ******************************************************************/

void stop(){
  delantero_right_parado();
  delantero_letf_parado();
  trasero_right_parado();
  trasero_left_parado();
  }

//********************************************
//*--------------Acciones-------------*
//********************************************
void adelante(){
  delantero_right_adelante();
  trasero_right_adelante();
  delantero_left_adelante();
  trasero_left_adelante();
}

void atras(){
  delantero_right_atras();
  trasero_right_atras();
  delantero_left_atras();
  trasero_left_atras();
}

//********************************************
//*--------------Formas De Girar-------------*
//********************************************
void giro_derecha(){
  delantero_right_adelante();
  trasero_right_adelante();
  delantero_letf_parado();
  trasero_left_parado();
  }
  
void giro_izquierda(){
  delantero_right_parado();
  trasero_right_parado();
  delantero_left_adelante();
  trasero_left_adelante();
  }

//********************************************
//*--------------MOTORES RIGHT---------------*
//********************************************
void delantero_right_parado(){
  digitalWrite(Pin_Enable_3, LOW);
  digitalWrite(Pin_Input_5, LOW);  
  digitalWrite(Pin_Input_6, LOW); 
}

void delantero_right_adelante(){
  digitalWrite(Pin_Enable_3, HIGH);
  digitalWrite(Pin_Input_5, HIGH);  
  digitalWrite(Pin_Input_6, LOW); 
}

void delantero_right_atras(){
  digitalWrite(Pin_Enable_3, HIGH);
  digitalWrite(Pin_Input_5, LOW);  
  digitalWrite(Pin_Input_6, HIGH); 
}
//-------------------------------------------
void trasero_right_parado(){
  digitalWrite(Pin_Enable_4, HIGH);
  digitalWrite(Pin_Input_7, LOW);  
  digitalWrite(Pin_Input_8, LOW); 
}

void trasero_right_adelante(){
  digitalWrite(Pin_Enable_4, HIGH);
  digitalWrite(Pin_Input_7, HIGH);  
  digitalWrite(Pin_Input_8, LOW); 
}

void trasero_right_atras(){
  digitalWrite(Pin_Enable_4, HIGH);
  digitalWrite(Pin_Input_7, LOW);  
  digitalWrite(Pin_Input_8, HIGH); 
}
//********************************************
//*--------------MOTORES LEFT---------------*
//********************************************
void delantero_letf_parado(){
  digitalWrite(Pin_Enable_2, LOW);
  digitalWrite(Pin_Input_4, LOW);  
  digitalWrite(Pin_Input_3, LOW); 
}

void delantero_left_adelante(){
  digitalWrite(Pin_Enable_2, HIGH);
  digitalWrite(Pin_Input_4, HIGH);  
  digitalWrite(Pin_Input_3, LOW); 
}

void delantero_left_atras(){
  digitalWrite(Pin_Enable_2, HIGH);
  digitalWrite(Pin_Input_4, LOW);  
  digitalWrite(Pin_Input_3, HIGH); 
}
//-----------------------------------------
void trasero_left_parado(){
  digitalWrite(Pin_Enable_1, LOW);
  digitalWrite(Pin_Input_1, LOW);  
  digitalWrite(Pin_Input_2, LOW); 
}

void trasero_left_atras(){
  digitalWrite(Pin_Enable_1, HIGH);
  digitalWrite(Pin_Input_1, HIGH);  
  digitalWrite(Pin_Input_2, LOW); 
}

void trasero_left_adelante(){
  digitalWrite(Pin_Enable_1, HIGH);
  digitalWrite(Pin_Input_1, LOW);  
  digitalWrite(Pin_Input_2, HIGH); 
}

double Distancia_Izq(){
  double entrada = 0.0;
  digitalWrite(TrigIzq, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigIzq, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigIzq, LOW);

  duracion = pulseIn(EchoIzq, HIGH);
  distancia = (duracion/2) / 29;
  Serial.print("Distancia Izq ");
  Serial.println(distancia);
  entrada= ((-2.0/ditanciaMaxima)*double(distancia))+1.0;
  if (entrada <-1){
    return entrada = -1;
  }else{
    return entrada;
  }
}

double Distancia_Cen(){
  double entrada = 0.0;
  digitalWrite(TrigCen, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigCen, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigCen, LOW);

  duracion = pulseIn(EchoCen, HIGH);
  distancia = (duracion/2) / 29;
  Serial.print("Distancia Cen ");
  Serial.println(distancia);
  entrada= ((-2.0/ditanciaMaxima)*double(distancia))+1.0;
  if (entrada <-1){
    return entrada = -1;
  }else{
    return entrada;
  }
}

double Distancia_Der(){
  double entrada = 0.0;
  digitalWrite(TrigDer, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigDer, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigDer, LOW);

  duracion = pulseIn(EchoDer, HIGH);
  distancia = (duracion/2) / 29;
  Serial.print("Distancia Der ");
  Serial.println(distancia);
  entrada= ((-2.0/ditanciaMaxima)*double(distancia))+1.0;
  if (entrada <-1){
    return entrada = -1;
  }else{
    return entrada;
  }
}

double Distancia_Cen_Sup(){
  double entrada = 0.0;
  digitalWrite(TrigCenSup, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigCenSup, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigCenSup, LOW);

  duracion = pulseIn(EchoCenSup, HIGH);
  distancia = (duracion/2) / 29;
  Serial.print("Distancia CenSup ");
  Serial.println(distancia);
  entrada= ((-2.0/ditanciaMaxima)*double(distancia))+1.0;
  if (entrada <-1){
    return entrada = -1;
  }else{
    return entrada;
  }
}

double Distancia_Lat_Izq(){
  double entrada = 0.0;
  digitalWrite(TrigLatIzq, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigLatIzq, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigLatIzq, LOW);

  duracion = pulseIn(EchoLatIzq, HIGH);
  distancia = (duracion/2) / 29;
  Serial.print("Distancia LatIzq ");
  Serial.println(distancia);
  entrada= ((-2.0/ditanciaMaxima)*double(distancia))+1.0;
  if (entrada <-1){
    return entrada = -1;
  }else{
    return entrada;
  }
}

double Distancia_Lat_Der(){
  double entrada = 0.0;
  digitalWrite(TrigLatDer, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigLatDer, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigLatDer, LOW);

  duracion = pulseIn(EchoLatDer, HIGH);
  distancia = (duracion/2) / 29;
  Serial.print("Distancia LatDer ");
  Serial.println(distancia);
  entrada= ((-2.0/ditanciaMaxima)*double(distancia))+1.0;
  if (entrada <-1){
    return entrada = -1;
  }else{
    return entrada;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(EchoDer, INPUT);
  pinMode(TrigDer, OUTPUT);
  pinMode(EchoCen, INPUT);
  pinMode(TrigCen, OUTPUT);
  pinMode(EchoIzq, INPUT);
  pinMode(TrigIzq, OUTPUT);
  pinMode(EchoCenSup, INPUT);
  pinMode(TrigCenSup, OUTPUT);
  pinMode(EchoLatIzq, INPUT);
  pinMode(TrigLatIzq, OUTPUT);
  pinMode(EchoLatDer, INPUT);
  pinMode(TrigLatDer, OUTPUT);

 //Preparamos Motor Delantero_Left
  pinMode(Pin_Enable_1, OUTPUT); 
  pinMode(Pin_Input_1, OUTPUT); 
  pinMode(Pin_Input_2, OUTPUT); 
  //Preparamos Motor Trasero_Left
  pinMode(Pin_Enable_2, OUTPUT); 
  pinMode(Pin_Input_4, OUTPUT); 
  pinMode(Pin_Input_3, OUTPUT); 


  
  //Preparamos Motor Delantero_Right
  pinMode(Pin_Enable_3, OUTPUT); 
  pinMode(Pin_Input_5, OUTPUT); 
  pinMode(Pin_Input_6, OUTPUT); 
//Preparamos Motor Trasero_Right
  pinMode(Pin_Enable_4, OUTPUT); 
  pinMode(Pin_Input_7, OUTPUT); 
  pinMode(Pin_Input_8, OUTPUT); 
  
}

void loop() {

  entrada6 = round(Distancia_Cen_Sup());
  if(entrada6 == 1){
    atras();
  }
  else if(entrada6 < 1){ 

  
    // put your main code here, to run repeatedly:
    double In1 = 1.0;
    //double In2 = -1.0;
    //double In3 = -1.0;
    //double In4 = -1.0;
    //[-1, -1, -1], # Avanzar. => [1,0,0,1,1,0,0,1], # Avanzar. 

    //entrada3 = Distancia_Der();
    //entrada2 = Distancia_Cen();
    //entrada1 = Distancia_Izq();


    //entrada3 = -1;
    //entrada2 = -1;
    //entrada1 = 1;

    //Serial.print(entrada1);
    //Serial.print("  ");
    //Serial.print(entrada2);
    //Serial.print("  ");
   // Serial.println(entrada3);

    entrada5 = round(Distancia_Lat_Der());
    entrada4 = round(Distancia_Lat_Izq());
    entrada3 = round(Distancia_Der());
    entrada2 = round(Distancia_Cen());
    entrada1 = round(Distancia_Izq());
    Serial.print(entrada1);
    Serial.print("  ");
    Serial.print(entrada2);
    Serial.print("  ");
    Serial.println(entrada3);
    
    //InputToOutput(In1, entrada1, entrada2, entrada3);
    predic(entrada1, entrada2, entrada3);
  
    //InputToOutput(In1, -1, entrada2, -1);
    //int accion[8] = {1,0,0,1,1,0,0,1};//Adelante
    //int accion[8] = {0,1,1,0,0,1,1,0};//Atras
    //int accion[8] = {1,0,0,0,1,0,0,0};//Girar Izquierda
    //int accion[8] = {0,0,0,1,0,0,0,1};//Girar Derecha
  
    int acciones [4][8] = {{1,0,0,1,1,0,0,1},//Adelante
                        {0,1,1,0,0,1,1,0}, //Atras
                        {1,0,0,0,1,0,0,0},//Girar Izquierda 
                        {0,0,0,1,0,0,0,1}};//Girar Derecha
  
  
    int accion[8];
    accion [0] = round(abs(Output[0]));
    accion [1] = round(abs(Output[1]));
    accion [2] = round(abs(Output[2]));
    accion [3] = round(abs(Output[3]));
    accion [4] = round(abs(Output[4]));
    accion [5] = round(abs(Output[5]));
    accion [6] = round(abs(Output[6]));
    accion [7] = round(abs(Output[7]));
  
  
     /*Serial.println("Valor de comparacion");
     int val = memcmp(accion, acciones[0],sizeof(accion));
     Serial.println(val);
     val = memcmp(accion, acciones[1],sizeof(accion));
     Serial.println(val);
     val = memcmp(accion, acciones[2],sizeof(accion));
     Serial.println(val);
     val = memcmp(accion, acciones[3],sizeof(accion));
     Serial.println(val);
     Serial.println("Valor de comparacion");
     Serial.println(val);*/
  
  
  
  
    Serial.println("Se muestra la accion en binario: ");
    Serial.print(accion[0]);
    Serial.print(accion[1]);
    Serial.print(accion[2]);
    Serial.print(accion[3]);
    Serial.print(accion[4]);
    Serial.print(accion[5]);
    Serial.print(accion[6]);
    Serial.println(accion[7]);
  
  
  
    Serial.println("Empiezan las comparaciones.");
    if( 0 == memcmp(accion, acciones[0],sizeof(accion)) ){
      if(entrada4 == 1){
        giro_derecha();
      }
      else if(entrada5 == 1){
        giro_izquierda();
      }
      else{
        Serial.println("Adelante");
        adelante();
      }
    }
    else if( 0 == memcmp(accion, acciones[1],sizeof(accion)) ){
      Serial.println("Atras");
      atras();
    }
    else if( 0 == memcmp(accion, acciones[2],sizeof(accion)) ){
      Serial.println("Izquierda");
      giro_izquierda();
    }
    else if( 0 == memcmp(accion, acciones[3],sizeof(accion)) ){
      Serial.println("Girar Derecha");
      giro_derecha();
    }
  
  
  
    //int acciones[8] = {1,0,0,1,1,0,0,1};
  
    //marchar(acciones);
  
    //marchar(accion);
  
    /*int out1 = round(abs(Output[0]));
    int out2 = round(abs(Output[1]));
    int out3 = round(abs(Output[2]));
    int out4 = round(abs(Output[3]));
    int out5 = round(abs(Output[4]));
    int out6 = round(abs(Output[5]));
    int out7 = round(abs(Output[6]));
    int out8 = round(abs(Output[7]));
    
  
    Serial.print(out1);
    Serial.print(out2);
    Serial.print(out3);
    Serial.print(out4);
    Serial.print(out5);
    Serial.print(out6);
    Serial.print(out7);
    Serial.println(out8);*/
    Serial.println("Hello Word");
  }
  delay(10);

}




void predic(double In2, double In3, double In4){
  double TestInput[] = {0, 0, 0};
  TestInput[0] = In2;
  TestInput[1] = In3;
  TestInput[2] = In4;
  //Serial.println("Estamos Dentro");

  double matriz[6] = {0,0,0,0,0,0};
  double output[8] = {0,0,0,0,0,0,0,0};
  
  for(i=0; i < HiddenNodes; i++){
    for(j=0; j < InputNodes; j++){
      //Serial.println(TestInput[j] * HiddenWeights[j][i]);
      matriz[i] += (TestInput[j] * HiddenWeights[j][i]);// + HiddenBias[j];
      }
      matriz[i] = matriz[i] + HiddenBias[i];
      matriz[i] = tanh(matriz[i]);
     //Serial.print("activacion: ");
     //Serial.println(matriz[i]);
  }
  
  //Serial.print("Fin primer Ciclo");
  for(i=0; i < OutputNodes; i++){
    for(j=0; j < HiddenNodes; j++){
      output[i] += (matriz[j] * OutputWeights[j][i]);
    }
    output[i] = output[i] + OutputBias[i];
    output[i] = tanh(output[i]);
    Output[i] = output[i] ;
  }
}




/*void InputToOutput(double In1, double In2, double In3, double In4){
  double TestInput[] = {0, 0, 0, 0, 0};
  TestInput[0] = In1;
  TestInput[1] = In2;
  TestInput[2] = In3;
  TestInput[3] = In4;
 
 
 /******************************************************************
  *        Calcular las activaciones en las capas ocultas          *
  ******************************************************************/
 
  /*for ( i = 0 ; i < HiddenNodes ; i++ ) {
    Accum = 0;//HiddenWeights[InputNodes][i] ;
    for ( j = 0 ; j < InputNodes ; j++ ) {
      Accum += TestInput[j] * HiddenWeights[j][i] ;
    }
    //Hidden[i] = 1.0 / (1.0 + exp(-Accum)) ; //Sigmoid
    Hidden[i] = tanh(Accum) ; //tanh
  }
 
 /******************************************************************
  *        Calcular activacion y error en la capa de Salida        *
  ******************************************************************/
 
  /*for ( i = 0 ; i < OutputNodes ; i++ ) {
    Accum = 0;//OutputWeights[HiddenNodes][i];
    for ( j = 0 ; j < HiddenNodes ; j++ ) {
        Accum += Hidden[j] * OutputWeights[j][i] ;
    }
    Output[i] = tanh(Accum) ;//tanh
  }
 
}*/
