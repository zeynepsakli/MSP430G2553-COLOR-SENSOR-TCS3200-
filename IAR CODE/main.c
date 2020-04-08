//LCD kütüphane kaynagi ==== www.github.com/kates/msp430-lcd
#include <msp430.h>
#include <stdint.h>
#include "lcd.h"
#include "in430.h"



/*Kullandigim Degiskenler*/
unsigned int Sayac_Degeri = 0;
unsigned int Saklanan_Deger = 0;
unsigned int Kirmizi = 0;
unsigned int Yesil = 0;
unsigned int Mavi = 0;


int main(void) {

    /*** Watchdog timer ve clocku ayarladim ***/
    WDTCTL = WDTPW + WDTHOLD;      // Watchdog timer durdu
    BCSCTL1 = CALBC1_8MHZ;          // 8 Mhzde dahili osilatörmüzün çalisacagini belirttim
    DCOCTL = CALDCO_8MHZ;           // SMCLK = DCO = 8MHz
    __delay_cycles(20000);
    
   P2DIR =0x1E;             // P2.0 i input yaptim sensörden çikan out pinini buraya bagladim 
   P2SEL |= BIT0;           //P2.1 den 2.4 e kadar çikis yaptim.

   
    TA0CCR0 = 20000;            // 20000*400 = 8000000 20ms
    TA0CCTL0 |= CCIE;           // Interrupti aktif hale getirdim
    TA0CTL |= TASSEL_2;         //SMCLK ile çalis

    TA1CCTL0 |= CCIE + CCIS_0 + CM_2 + CAP; // Interrupt, capture mod CCIxA,düsen kenar için sayma yap,capture modla çalis
    TA1CTL |= TASSEL_2;                     // SMCLK ile çalis
    //1. timerdan zaman tutulup 2. timerdan frekans saydirdim
    _BIS_SR(GIE);               
    lcd_init();                 // LCD Hazirlaniyor
    __delay_cycles(20000);
    lcd_go_line(1);
    lcd_writeln("HAZIR");
 
           
    while(1)
    {    
    
     
        while(1)                    //Kirmizi Degeri için
        {
        P2OUT=0x02;
        TA0CTL |= MC0;              // Timer_0 baslatiliyor
        TA1CTL |= MC1;              // Timer_1 baslatiliyor
        while(Sayac_Degeri != 400); // Sayac_Degeri 400 olana kadar bekle
        TA0CTL &= ~MC0;             // Timer_0 durduruluyor
        TA1CTL &= ~MC1;             // Timer_1 durduruluyor
        Kirmizi = Saklanan_Deger;   // Saklanan_Deger Kirmizi'ya atiliyor
        Sayac_Degeri = 0;           // Sayac_Degeri sifirlaniyor
        Saklanan_Deger = 0;         // Saklanan_Deger sifirlaniyor
        TA0R = 0;                   // Timer_A0 registeri sifirlaniyor
        TA1R = 0;                   // Timer_A1 registeri sifirlaniyor        
        break;
        }
        __delay_cycles(20000);    
        while(1)                    //Yesil Degeri için
        {
        P2OUT=0x1A;
        TA0CTL |= MC0;              // Timer_0 baslatiliyor
        TA1CTL |= MC1;              // Timer_1 baslatiliyor
        while(Sayac_Degeri != 400); // Sayac_Degeri 400 olana kadar bekle
        TA0CTL &= ~MC0;             // Timer_0 durduruluyor
        TA1CTL &= ~MC1;             // Timer_1 durduruluyor
        Yesil = Saklanan_Deger;     // Saklanan_Deger Yesil'e atiliyor
        Sayac_Degeri = 0;           // Sayac_Degeri sifirlaniyor
        Saklanan_Deger = 0;         // Saklanan_Deger sifirlaniyor
        TA0R = 0;                   // Timer_A0 registeri sifirlaniyor
        TA1R = 0;                   // Timer_A1 registeri sifirlaniyor         
        break;
        }
        __delay_cycles(20000);
        while(1)                    //Mavi Degeri için
        {
        P2OUT=0x12;
        TA0CTL |= MC0;              // Timer_0 baslatiliyor
        TA1CTL |= MC1;              // Timer_1 baslatiliyor
        while(Sayac_Degeri != 400); // Sayac_Degeri 400 olana kadar bekle
        TA0CTL &= ~MC0;             // Timer_0 durduruluyor
        TA1CTL &= ~MC1;             // Timer_1 durduruluyor
        Mavi = Saklanan_Deger;      // Saklanan_Deger Mavi'ye atiliyor
        Sayac_Degeri = 0;           // Sayac_Degeri sifirlaniyor
        Saklanan_Deger = 0;         // Saklanan_Deger sifirlaniyor
        TA0R = 0;                   // Timer_A0 registeri sifirlaniyor
        TA1R = 0;                   // Timer_A1 registeri sifirlaniyor        
        break;
        }
      
     
        //simdi de aldigim rgb degerlerini araliyip ekrana renkleri bastricam
       if(Kirmizi<1100&&Kirmizi>0)
        {
          if(Yesil<1100&&Yesil>0)
          {
            if(Mavi<1300&&Mavi>0)
            {
        
              lcd_go_line(1);
              lcd_writeln("SIYAH");
             
            }
          }         
        }
        else if(Kirmizi<7000&&Kirmizi>4500)
        {
          if(Yesil<7000&&Yesil>4600)
          {
            if(Mavi<8100&&Mavi>5800)
            {
          
              lcd_go_line(1);
              lcd_writeln("BEYAZ");
              
            }
          }         
        }
        else if(Kirmizi<5200&&Kirmizi>3400)
        {
          if(Yesil<2500&&Yesil>1100)
          {
            if(Mavi<3100&&Mavi>1700)
            {
           
              lcd_go_line(1);
              lcd_writeln("KIRMIZI");
             
            }
          }         
        }
        else if(Kirmizi<2800&&Kirmizi>1500)
        {
          if(Yesil<2900&&Yesil>1500)
          {
            if(Mavi<2700&&Mavi>1300)
            {
              
              lcd_go_line(1);
              lcd_writeln("YESIL");
             
            }
          }         
        }
         if(Kirmizi<3700&&Kirmizi>1700)
        {
          if(Yesil<3800&&Yesil>2200)
          {
            if(Mavi<6300&&Mavi>3800)
            {
              
              lcd_go_line(1);
              lcd_writeln("MAVI");
             
            }
          }         
        }
        if(Kirmizi<3600&&Kirmizi>1900)
        {
          if(Yesil<3100&&Yesil>1900)
          {
            if(Mavi<4300&&Mavi>2900)
            {
              
              lcd_go_line(1);
              lcd_writeln("MOR");
              
            }
          }         
        }
         if(Kirmizi<8000&&Kirmizi>5000)
        {
          if(Yesil<6000&&Yesil>3000)
          {
            if(Mavi<4500&&Mavi>2000)
            {
              
              lcd_go_line(1);
              lcd_writeln("SARI");
              
            }
          }         
        }
       
         if(Kirmizi<2400&&Kirmizi>1100)
        {
          if(Yesil<2400&&Yesil>1100)
          {
            if(Mavi<2400&&Mavi>1300)
            {
              
              lcd_go_line(1);
              lcd_writeln("KAHVERENGI");
            
            }
          }         
        }
        

       
          
        
    }  
}
//interruptlar
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{
    Sayac_Degeri++;
}


#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0(void)
{
    Saklanan_Deger++;
}

        