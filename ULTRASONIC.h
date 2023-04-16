#ifndef ULTRASONIC_H
#define ULTRASONIC_H

int get_distance(void)
{
 int ultra_dist;
 char ultra_q;
 TRIG=0;
 ECHO=1;
 TR1=0;
 TMOD=(TMOD&0x0F)|(0x10);
 TH1=0x00;
 TL1=0x00;

 TRIG=1;
 for(ultra_q=0;ultra_q<10;ultra_q++)
 {}
 TRIG=0;
 while(ECHO==0)
 {
 }
 TR1=1;
 while(ECHO==1)
 {
 }
 TR1=0;
 ultra_dist=((TH1*256)+TL1)/54;
 return ultra_dist;
}
#endif