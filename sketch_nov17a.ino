#include <TFT.h>  // 아두이노 LCD 라이브러리 포함
#include <SPI.h>  // 아두이노 SPI 라이브러리 포함
#include <SoftwareSerial.h> 

#include <SD.h>
#define cs   10   
#define dc   9    
#define rst  8    //핀,라이브러리 선언들
#define echo 6
#define trig 7
 
TFT TFTscreen = TFT(cs, dc, rst);    // TFT 클래스 생성
SoftwareSerial btSerial(2,3); 
 
void setup() { //반복을 시작하기전에 한번만 도는 문(준비단계)
  Serial.begin(9600);
  TFTscreen.begin();                 // TFT 클래스 시작
  btSerial.begin(9600); //시리얼 통신속도
  TFTscreen.background(0, 0, 0); //bleak
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
   TFTscreen.stroke(255,255,255); //폰트색깔 (글자가0~255까지 흰색)
 TFTscreen.setTextSize(3); //LCD 글자크기조절
 TFTscreen.setCursor(5,80);//위치
 TFTscreen.println("TEAM");
  TFTscreen.stroke(255,255,255); //폰트색깔 (글자가0~255까지 흰색)
 TFTscreen.setTextSize(5); //LCD 글자크기조절
 TFTscreen.setCursor(80,80);//위치
 TFTscreen.println("CL");

 
}
 String readSerial(){
  String str = "";
  char ch;
  while(btSerial.available()){
    ch = btSerial.read();
    str.concat(ch);
    delay(10);
  }
  return str;
 }

 

 
void loop() //반복문
{
 long duration, distance; //기본코드 걸린시간, 거리
  digitalWrite(trig, HIGH);  // trigPin에서 초음파 발생(echoPin도 HIGH)        
  delayMicroseconds(10); //초음파 지연시간
  digitalWrite(trig, LOW); //초음파 멈춤 
  duration = pulseIn(echo, HIGH);    // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance = ((float)(340 * duration) / 1000) / 2; //거리계산


if(distance<1000){ //distance가 100보다 작을 때
Serial.println("close"); // Serial close 출력
 btSerial.println("close"); //BTSerial로 가는 것
 btSerial.println(distance); //BTSerial로 distance가 가는 것
 TFTscreen.stroke(255,255,255); //폰트색깔 (글자가0~255까지 흰색)
 TFTscreen.setTextSize(1.5); //LCD 글자크기조절
 TFTscreen.setCursor(3,50);//위치
 TFTscreen.println("PUT YOUR HELMET");//전진x( 기본값x, 값이 적다)
 delay(1000);
 TFTscreen.fillRect(3,30,100,40,0x0000);


 
}
 else {
  Serial.println("FAR"); //Serial FAR 출력
  btSerial.println("FAR"); //BTSerial FAR로 가는 것
 btSerial.println(distance); //BTSerial로 distance가 가는 것

  TFTscreen.stroke(255,255,255); //폰트색깔 (글자가0~255까지 흰색)
  TFTscreen.setTextSize(2); //LCD 글자크기조절
  TFTscreen.setCursor(3,50);//위치
  TFTscreen.println("DRIVING");//전진x( 기본값x, 값이 적다)
  delay(1000);
  TFTscreen.fillRect(3,35,100,30,0x0000);

 
  
 }
  
  String msg;
  if (Serial.available()){
  btSerial.write(Serial.read());
  }

  if(btSerial.available()){
    msg = readSerial(); //사용자 정의 함수
 
  TFTscreen.stroke(255,255,255); //폰트색깔 (글자가0~255까지 흰색)
  TFTscreen.setTextSize(2); //LCD 글자크기조절
  TFTscreen.setCursor(2,27);//위치
  
  TFTscreen.println(msg+"00"+" won");//전진x( 기본값x, 값이 적다)
  delay(10000);
  TFTscreen.stroke(0,0,0); //이 문이없으면 글자가 겹침, 
  }
  
}
