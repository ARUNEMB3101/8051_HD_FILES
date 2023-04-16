#ifndef KEYPAD_H
#define KEYPAD_H

void check_key()
{
 KEYPAD=0X0F;
 while(((KEYPAD|0XF0)^0XFF)==0)
 {
 }
}

void release_key()
{
 KEYPAD=0X0F;
 while(((KEYPAD|0XF0)^0XFF)!=0)
 {
 }
}

char col_value()
{
 char key_col;
 char key_c;
 KEYPAD=0X0F;
 key_c=((KEYPAD|0XF0)^0XFF)<<4;
 for(key_col=0;key_col<4;key_col++)
 {
  if((key_c&0x80)==0x80)
  {
   break;
  }
  key_c=key_c<<1;
 }
 return key_col;
}

char row_value()
{
 char key_row;
 char key_r;
 KEYPAD=0XF0;
 key_r=((KEYPAD|0X0F)^0XFF);
 for(key_row=0;key_row<4;key_row++)
 {
  if((key_r&0x80)==0x80)
  {
   break;
  }
  key_r=key_r<<1;
 }
 return key_row;
}

char read_key()
{
 char key_val;
 check_key();
 key_val=(4*row_value())+col_value();
 release_key();
 return key_val;
}

#endif