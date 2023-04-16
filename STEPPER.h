#ifndef STEPPER_H
#define STEPPER_H

#include <AT89S52.h>
#define STEPPER_MOTOR P0


void delay()
{
 int d;
 for(d=0;d<200;d++)
 {
 }
}

void rotate_anticlock(int angle)
{
 char val=0x88;
 int i,a;
 int step;
 P0=0xFF;
 step=(angle*64)/45;
 for(a=0;a<step;a++)
 {
  for(i=0;i<4;i++)
  {
   P0=~(val>>i);
   delay();
  }
 }
}

void rotate_clock(int angle)
{
 char val=0x11;
 int i,a;
 int step;
 P0=0xFF;
 step=(angle*64)/45;
 for(a=0;a<step;a++)
 {
  for(i=0;i<4;i++)
  {
   P0=~(val<<i);
   delay();
  }
 }
}

#endif