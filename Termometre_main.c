#include <16F84A.h>
#device *=16
 
#use delay(CLOCK=4000000)         //Fosc=4Mhz
#FUSES NOWDT, XT, NOPUT, NOPROTECT
#include "ds18b20.c"
 
float sicaklik = 0;
char table[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
char i = 0, temp = 0,tmp=0;
char dig[2] = "";
 
///PROGRAM
#int_timer0
void timer0_kesme()
{
disable_interrupts(INT_TIMER0);
switch(i)
   {
      case 0:
         output_a(0x01+tmp);
         output_b(table[dig[1]]);
         break;
      case 1:
         output_a(0x02+tmp);
         output_b(table[dig[0]]);
         break;
      case 2:
         output_a(0x04+tmp);
         output_b(0xA7);//table[dig[0]]);//'C sembolü için
         break;
   }
  i++;
  i%=3;
  enable_interrupts(INT_TIMER0);
  set_timer0(50);
}
 
void main()
{
 
set_tris_b(0x00);
set_tris_a(0x00);
setup_timer_0(RTCC_DIV_32|RTCC_INTERNAL);
 
set_timer0(50);
 
enable_interrupts(INT_TIMER0);
enable_interrupts(GLOBAL);
 
while(1)
{
   sicaklik = ds1820_read();  //Sıcaklık bilgisi okunuyor ve çevriliyor
 
   temp = sicaklik;
 
   dig[0] = temp % 10;
   dig[1] = (temp / 10) % 10;
 
  if(temp > 90)
   tmp = 0x08;
  else
   tmp = 0;
 
   delay_ms(1000);
 
}
}
