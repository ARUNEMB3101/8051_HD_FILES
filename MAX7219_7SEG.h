#ifndef MAX7219_7SEG_H
#define MAX7219_7SEG_H

void clock(void)
{
 CLK=1;
 CLK=0;
}

void write_byte(char val)
{
 char i,t;
 for(i=0;i<8;i++)
 {
  t=val;
  t=t>>(7-i);
  t=t&0x01;
  if(t==0)
  {
   DIN=0;
   clock();
  }
  else
  {
   DIN=1;
   clock();
  }
 }
}

void load(void)
{
 CS=1;
 CS=0;
}

void write(char h,char l)
{
 write_byte(h);
 write_byte(l);
 load();
}

void clear(void)
{
 char f;
 for(f=1;f<=8;f++)
 {
  write(f,0x00);
 }
}

void init(void)
{
 DIN=0;CLK=0;CS=0;
 write(0X0C,0X01);
 write(0X0F,0X00);
 write(0X0B,0X07);
 write(0X09,0XFF);
 write(0X0A,0X01);
 clear();
}

void skip(char c)
{
 {
  write(c+1,0x00);
 }
}

void print(char *dig)
{
 char i;
 for(i=0;i<8;i++)
 {
  write(i+1,*dig);
  *dig++;
 }
}

#endif