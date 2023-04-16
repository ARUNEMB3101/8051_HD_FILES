#ifndef LCD_H
#define LCD_H

void lcd_busy(void)
{
 char lcd_status;
 DATABUS=0xFF;
 RS=0;
 RW=1;
 EN=1;
 EN=0;
 lcd_status=0x80;
 while(lcd_status!=0)
 {
  EN=1;
  lcd_status=DATABUS;
  EN=0;
  lcd_status=lcd_status & 0x80;
 }
 RW=0;
}

void lcd_cmd(char lcd_c)
{
 DATABUS=lcd_c;
 RS=0;
 RW=0;
 EN=1;
 EN=0;
 lcd_busy();
}

void lcd_data(char lcd_d)
{
 DATABUS=lcd_d;
 RS=1;
 RW=0;
 EN=1;
 EN=0;
 lcd_busy();
}  

void lcd_cmds(char inst[])
{
 int lcd_b=0;
 char lcd_t;
 lcd_t=inst[lcd_b];
 while(lcd_t!=0x00)
 {
  lcd_cmd(lcd_t);
  lcd_busy();
  lcd_b++;
  lcd_t=inst[lcd_b];
 }
}

void lcd_init(void)
{
 lcd_busy();
 lcd_cmd(0x38);
 lcd_cmd(0x01);
 lcd_cmd(0x0C);
 lcd_cmd(0x06);
 lcd_cmd(0x80);
}

void lcd_print(char *lcd_msg)
{
 char lcd_value;
 lcd_value=*lcd_msg;
 while(lcd_value!=0x00)
 {
  lcd_data(lcd_value);
  *lcd_msg++;
  lcd_value=*lcd_msg;
 }
}

void lcd_line(int lcd_l)
{
 lcd_l=((lcd_l-1)*0x40)|0x80;
 lcd_cmd(lcd_l);
}

void lcd_pos(int lcd_x,int lcd_y)
{
 lcd_x=(((lcd_x-1)*0x40)|0x80)+(lcd_y-1);
 lcd_cmd(lcd_x);
}

#endif