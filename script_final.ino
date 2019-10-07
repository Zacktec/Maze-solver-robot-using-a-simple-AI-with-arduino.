
#define in1 6 
#define in2 11
#define in3 9
#define in4 10
#define IR0 4
#define IR1 5
#define IR2 12
#define LED 11
#define en1 45
#define en2 50
#define turn_right 700
#define turn_left  700
#define one_inch_for   1100
#define one_inch_back   500
#define turn_u 1371
#define sped 13
int IRS[3] = {0,0,0};
int a;
int b;
int c;
int l = 1;
int h = 1;
int k = 1;
int time1;
int time2;
int deltaTime = 0 ; 

void setup() {
 pinMode(in1,OUTPUT);
 pinMode(in2,OUTPUT);
 pinMode(in3,OUTPUT);
 pinMode(in4,OUTPUT);
 pinMode(en1,OUTPUT);
 pinMode(en2,OUTPUT);
 pinMode(IR0,INPUT);
 pinMode(IR1,INPUT);
 pinMode(IR2,INPUT);
 digitalWrite(en1,HIGH);
 digitalWrite(en2,HIGH);   
Serial.begin(9600);

a=digitalRead(4);
b=digitalRead(5);
c=digitalRead(12);
Serial.println(a);
Serial.println(b);
Serial.println(c);
Serial.println("+++++++++++++++++++++++++++++++++++");
delay(200);
}

void loop() {
  if(l){
  
  if(h == 1) delay(4000); // a delay at the begining to help when testing
  h = 2;
 

 check();
//+++++++++++++++++++++++++++++++++  line following  ++++++++++++++++++++++++++++++++++++++++++++++++++ 
  if( IRS[0] == 0 && IRS[1] == 1 && IRS[2] == 0 ) forward();
  if( IRS[0] == 1 && IRS[1] == 0 && IRS[2] == 0 ) {
    k = 1 ;
    forward_more_right();
    }
  if( IRS[0] == 0 && IRS[1] == 0 && IRS[2] == 1 ) {
    k = 1 ;
    forward_more_left();
    }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  if( IRS[0] == 0 && IRS[1] == 1 && IRS[2] == 1 ) turnleft();
  if( IRS[0] == 1 && IRS[1] == 1 && IRS[2] == 1 ) condition_2();

  else if( IRS[0] == 1 && IRS[1] == 1 && IRS[2] == 0 ) condition_1();
  
  else if( IRS[0] == 0 && IRS[1] == 0 && IRS[2] == 0 ){
  if (k == 1)   time1 = millis();
  k = 2;
  if( k == 2) time2 = millis();
  deltaTime = time2 - time1;
  if ( deltaTime > 1000) turnU();
  }
}}
void check(){
  IRS[0] = digitalRead(IR0);
  IRS[1] = digitalRead(IR1);
  IRS[2] = digitalRead(IR2);
 
}
void forward(){
  k = 1 ;
  digitalWrite(in2,HIGH);
  digitalWrite(in4,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in3,LOW);
}
void forward_more_right(){
  analogWrite(in2,sped);
  digitalWrite(in4,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in3,LOW);
}
void forward_more_left(){
  digitalWrite(in2,HIGH);
  analogWrite(in4,sped);
  digitalWrite(in1,LOW);
  digitalWrite(in3,LOW);
}
void backward(){
  digitalWrite(in1,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in4,LOW);
}
void stop_cart(){
  k = 1 ;
  digitalWrite(in2,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in3,LOW);
}
void turnright (){
  k = 1 ;
  digitalWrite(in1,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in4,HIGH);
  delay(turn_right);
  stop_cart();
}
void turnleft (){
  k = 1 ;
  forward_inch();
  digitalWrite(in1,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in2,HIGH);
  digitalWrite(in4,LOW);
  delay(turn_left);
  stop_cart();
}
void turnU (){
  digitalWrite(in1,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in2,HIGH);
  digitalWrite(in4,LOW);
  delay(turn_u);
  k = 1;
  stop_cart();
}
void forward_inch(){
  forward();
  delay(one_inch_for);
  stop_cart();
}
void backward_inch(){
  backward();
  delay(one_inch_back);
  stop_cart();
}
void condition_1(){
  forward_inch();
  check();
  
  if( IRS[0] == 0 && IRS[1] == 1 && IRS[2] == 0 ){
   
    forward();
  }

  
  if( IRS[0] == 0 && IRS[1] == 0 && IRS[2] == 0 ){
    turnright();
  }
}
void condition_2(){
  forward_inch();
  check();
  

  if( IRS[0] == 1 && IRS[1] == 1 && IRS[2] == 1){
    stop_cart();
    l = 0;
    //digitalWrite(LED,HIGH);
  }
  else{
    turnleft();
  } 
}
void Affichage(){
Serial.println(IRS[0]);
Serial.println(IRS[1]);
Serial.println(IRS[2]);
Serial.println("+++++++++++++++++++++++++++++++++++");
}
void Testing(){
  check();
 Affichage();}
