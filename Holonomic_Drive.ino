const int anglea=30;
const int angleb=150;
const int anglec= 270;
const int rpmmax = 300;
const int pinma = 1;
const int pinmb =2;
const int pinmc = 3;
const float r=1;
const float pi = 3.14;

void setmotion(int,int,int);

typedef struct wheels{
  float trans_rpm; //RPM for translational Velocity
  float ang_rpm; //RPM due to angular velocity
  int angle; //Position of tyre from x-axis
  float rpmmax; //Max RPM of wheel 
 } wheel;

char dir[4];
wheel wheela = {0,0,anglea,rpmmax},wheelb={0,0,angleb,rpmmax}, wheelc={0,0,anglec,rpmmax};
wheel *pwheela = &wheela, *pwheelb = &wheelb, *pwheelc=&wheelc;
void setup() {
  Serial.begin(9600); 
}

void loop() {
  int index=0;
  while( Serial.available() > 0 ){
     if(index<3){
     dir[index] = (int)Serial.read();
    }
  }
  int theta = dir[2]*100+dir[1]*10+dir[0];
  setmotion(0,theta,rpmmax); 
}

void setmotion(int omega, int angle, int transvel){
  pwheela->trans_rpm = transvel*sin(degtorad(pwheela->angle-angle)); //RPMtyre=RPM*sin(wheel angle- vel angle)
  pwheela->ang_rpm=omega*r;
  int pwma = rpmmax/(pwheela->trans_rpm+pwheela->ang_rpm)*255;
  pwheelb->trans_rpm = transvel*sin(degtorad(pwheelb->angle-angle)); //RPMtyre=RPM*sin(wheel angle- vel angle)
  pwheelb->ang_rpm=omega*r;
  int pwmb = rpmmax/(pwheelb->trans_rpm+pwheelb->ang_rpm)*255;
  pwheelc->trans_rpm = transvel*sin(degtorad(pwheelc->angle-angle)); //RPMtyre=RPM*sin(wheel angle- vel angle)
  pwheelc->ang_rpm=omega*r;
  int pwmc = rpmmax/(pwheelc->trans_rpm+pwheelc->ang_rpm)*255;
  analogWrite(pwma,pinma);
  analogWrite(pwmb,pinmb);
  analogWrite(pwmc,pinmc);
}

double degtorad(float degree){ 
  return (0.0174533*degree); //0.0174533 rad is 1 degree
}

