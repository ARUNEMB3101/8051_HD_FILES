#ifndef DS18B20_H
#define DS18B20_H

const char hex[23]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xA,0XB,0XC,0XD,0XE,0XF};

char buff[10];
char rom[9];

void timer_init()
{
 ET0=0;
 TR0=0;
 TMOD=(TMOD&0xF0)|0x02;
}

void time_slot(char us)
{
 TL0=255-(us-1);
 TH0=TL0;
 TR0=1;
 while(TF0==0)
 {}
 TR0=0;
 TF0=0;
}

void wire_reset()
{
__bit flag=0;
 while(flag==0)
 {
  WIRE=0;
  time_slot(250);
  time_slot(250);
  WIRE=1;
  time_slot(60);
  if(WIRE==0)
  {
   flag=1;
  }
  else
  {
  }
  time_slot(220);
  time_slot(220);
 }
}

void write_high()
{
 WIRE=0;
 time_slot(2);
 WIRE=1;
 time_slot(60);
}

void write_low()
{
 WIRE=0;
 time_slot(80);
 WIRE=1;
}

void write_byte(char c)
{
 char i;
 for(i=0;i<8;i++) 
 {
  if(((c>>i)&0x01)==0x01)
  {
   write_high();
  }
  else
  {
   write_low();
  }
  WIRE=1;
  time_slot(5);
 }
}

char read_byte()
{
 char r=0x00;
 char k;
 for(k=0;k<8;k++)
 {
  WIRE=1;
  time_slot(5);
  WIRE=0;
  time_slot(2);
  WIRE=1;
  if(WIRE==0)
  {
  }
  else
  {
   r=r|(0x01<<k);
  }
  time_slot(60);
 }
 return r;
}

void wire_busy()
{
 __bit busy=0;
 while(busy==0)
 {
  WIRE=1;
  time_slot(5);
  WIRE=0;
  time_slot(2);
  WIRE=1;
  busy=WIRE;
  time_slot(60);
 }
}

void read_rom()
{
 char n;
 wire_reset();
 write_byte(0x33);
 for(n=0;n<8;n++)
 {
  rom[n]=read_byte();
 }
}

void match_rom()
{
 char v;
 wire_reset();
 write_byte(0x55);
 for(v=0;v<8;v++)
 {
  write_byte(rom[v]);
 }
}

void skip_rom()
{
 wire_reset();
 write_byte(0xCC);
}

void set_rom(char *r)
{
 char n,v;
 for(n=0;n<8;n++)
 {
  v=hex[(*r)-0x30]<<4;
  *r++;
  v=v|hex[(*r)-0X30];
  *r++;
  rom[n]=v;
 }
}

void conv_temp()
{
 match_rom();
 write_byte(0x44);
 wire_busy();
}

void write_scratch(char TH,char TL,char CONF)
{
 match_rom();
 write_byte(0x4E);
 write_byte(TH);
 write_byte(TL);
 write_byte(CONF);
}

void read_scratch()
{
 char n;
 match_rom();
 write_byte(0xBE);
 for(n=0;n<9;n++)
 {
  buff[n]=read_byte();
 }
}

void copy_scratch()
{
 match_rom();
 write_byte(0x48);
 wire_busy();
}

void recall_eeprom()
{
 match_rom();
 write_byte(0xB8);
 wire_busy();
}

char read_temp()
{
 char temp;
 conv_temp();
 match_rom();
 write_byte(0xBE);
 temp=read_byte();
 temp=temp>>4;
 temp=temp|(read_byte()<<4);
 return temp;
}

#endif