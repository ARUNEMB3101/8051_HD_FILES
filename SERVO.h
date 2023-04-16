#ifndef SERVO_H
#define SERVO_H

#define SERVO_FOSC 11059200
#define SERVO_CLK SERVO_FOSC/12
#define SERVO_PERIOD SERVO_CLK/50
#define SERVO_PWM SERVO_PERIOD/80
#define L 9
#define M 4
#define R 1

__sbit servo_c,servo_b;
char servo_TON,servo_TOFF;
char servo_n;
int servo_n0,servo_n1;

void run_servo(char);
void servo_init(void);

void servo_init()
{
 servo_c=0;
 servo_n=0;
 PULSE=0;
 TMOD=(TMOD&0XF0)|0x02;
 ET0=1;
 EA=1;
}

void timer0_int() __interrupt(1)
{
 if(servo_n==25)
 {
  servo_n=0;
  servo_c=0;
  servo_b=1;
 }
 else if(servo_c==0)
 {
  if(servo_n1==servo_TON)
  {
   servo_n1=0;
   servo_c=1;
  }
  else
  {
   PULSE=1;
   servo_n1=servo_n1+1;
  }
 }
 else if(servo_c==1)
 {
  if(servo_n0==servo_TOFF)
  {
   servo_n0=0;
   servo_c=0;
   servo_n=servo_n+1;
  }
  else
  {
   PULSE=0;
   servo_n0=servo_n0+1;
  }
 }
 else
 {}
}

void run_servo(char servo_ang)
{
  servo_b=0;
  servo_TON=servo_ang;
  servo_TOFF=80-servo_TON;
  TR0=0;
  TH0=(0xFF-SERVO_PWM)+1;
  TL0=(0xFF-SERVO_PWM)+1;
  TR0=1;
  while(servo_b==0)
  {}
  servo_b=0;
  TR0=0;
}

#endif