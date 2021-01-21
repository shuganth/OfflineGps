
#define Sw4      PORTC.f0
#define Sw3      PORTC.f1
#define Det      PORTC.f2
#define Busy     PORTC.f3
#define GsmRly   PORTC.f4

#define Light    PORTB.f0
#define Alarm    PORTB.f1

unsigned int LgtCnt=0,Lt1=0,Lt2=0,Lt3=0,Lt4=0,SmLt1=0,SmLt3=0;
unsigned short y,ct,i,en,GPS[65],mt=0,Fcnt=0,F1,F2,F3,F4;
unsigned short d1,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d14,d15,d16,d17,d18,d19,d20,d21,d22,T3,T4,T5,T6,T7,T8;
unsigned long longCnt=0,d13,d2;



#define a          en.f0
#define b          en.f1
#define c          en.f2
#define Mob1En     en.f3
#define DetEn      en.f4


void Name(void){//LCD_Cmd(Lcd_CLEAR);LCD_Out(1,6,"S U G U S");LCD_Out(2,8,"G P S");Delay_ms(200);LCD_Out(3,4,"INITIALIZING");
  LCD_Cmd(Lcd_CLEAR);LCD_Out(1,1,"S U G U S  G P S");Delay_ms(200);LCD_Out(2,3,"INITIALIZING");}
void NxtEnt(void){USART_Write(0x0A),USART_Write(0x0D);}
void AT(void){USART_Write('A');USART_Write('T');USART_Write('+');}
void Store(void){
  //F1=Fcnt/100;F2=Fcnt%100;F3=F2/10;F4=F2%10;
  AT();USART_Write('W');USART_Write('F');USART_Write('I');USART_Write('L');USART_Write('E');USART_Write('=');
  USART_Write('/');USART_Write('G');USART_Write(0+48);USART_Write(0+48);USART_Write(1+48);
  USART_Write('.');USART_Write('C');USART_Write('S');USART_Write('V');USART_Write(0x0D);}
void Header(void){
  AT();USART_Write('W');USART_Write('B');USART_Write('U');USART_Write('F');USART_Write('F');USART_Write('=');
  USART_Write('D');USART_Write('A');USART_Write('T');USART_Write('E');USART_Write(',');USART_Write('T');USART_Write('I');
  USART_Write('M');USART_Write('E');USART_Write(',');USART_Write('L');USART_Write('A');USART_Write('T');USART_Write('I');
  USART_Write('T');USART_Write('U');USART_Write('D');USART_Write('E');USART_Write(',');USART_Write('L');USART_Write('O');
  USART_Write('N');USART_Write('G');USART_Write('I');USART_Write('T');USART_Write('U');USART_Write('D');USART_Write('E');
  NxtEnt();Delay_ms(100);Store();
}
void Wdata(void){
  AT();USART_Write('W');USART_Write('B');USART_Write('U');USART_Write('F');USART_Write('F');USART_Write('=');
  USART_Write(GPS[52]);USART_Write(GPS[53]);USART_Write(':');USART_Write(GPS[54]);USART_Write(GPS[55]);USART_Write(':');
  USART_Write(GPS[56]);USART_Write(GPS[57]);USART_Write(','); //Date
  USART_Write(T7/10+48);USART_Write(T7%10+48);USART_Write(':');USART_Write(T8/10+48);USART_Write(T8%10+48);USART_Write(',');//Time
  //USART_Write(GPS[15]);USART_Write(GPS[16]);USART_Write('.');
  //USART_Write(d7+48);USART_Write(d8+48);USART_Write(d9+48);USART_Write(d10+48);USART_Write(',');//Latitude
  //USART_Write(GPS[28]);USART_Write(GPS[29]);USART_Write('.');
  //USART_Write(d18+48);USART_Write(d19+48);USART_Write(d20+48);USART_Write(d21+48);//Longitude
  
  

  USART_Write(',');USART_Write(GPS[15]);USART_Write(GPS[16]);USART_Write(',');USART_Write(GPS[17]);
  USART_Write(GPS[18]);USART_Write(GPS[19]);USART_Write(GPS[20]);USART_Write(GPS[21]);USART_Write(GPS[22]);
  USART_Write(GPS[23]);

  USART_Write(',');USART_Write(GPS[28]);USART_Write(GPS[29]);USART_Write(',');USART_Write(GPS[30]);
  USART_Write(GPS[31]);USART_Write(GPS[32]);USART_Write(GPS[33]);USART_Write(GPS[34]);USART_Write(GPS[35]);
  USART_Write(GPS[36]);
  
  NxtEnt();Delay_ms(100);Store();
}
void Recall(void){
  Fcnt=EEPROM_Read(1);Fcnt++;if(Fcnt>200)Fcnt=0;EEprom_Write(1,Fcnt);
  F1=Fcnt/100;F2=Fcnt%100;F3=F2/10;F4=F2%10;F1=1;F3=2;F4=3;
}
void main() {
  ADCON1=0X00;PORTC=0;TRISC=0x0F;PORTB=0;TRISB=0x00;
  LCD_Config(&PORTD,2,3,0,7,6,5,4);
  LCD_Cmd(LCD_CURSOR_OFF);Light=1;en=0xff; Light=1;
  USART_init(9600);if(Det==0)Recall();
  Name();b=c=d1=d2=d3=d4=d5=d6=d7=d8=d9=d10=d11=d12=d13=d14=d15=d16=d17=d18=d19=d20=d21=d22=Lt1=Lt3=0;
/******************************************************************************************************************************
PROG
******************************************************************************************************************************/

  while(1){
   if(Mob1En==0&&Det==0){if(USART_Data_Ready()){y=USART_Read();if(y==0x43&&a==1)a=i=0;if(a==0){GPS[i]=y;i++;if(i>60)a=Mob1En=b=1;}}}//
   if(Mob1En==0&&Det==1&&DetEn==1)LCD_Cmd(Lcd_CLEAR),LCD_Out(1,2,"PLEASE INSERT"),LCD_Out(2,5,"PENDRIVE"),Mob1En=1,c=DetEn=0;
   if(Det==0&&DetEn==0)DetEn=1,Recall();
   if(Mob1En==1){longCnt++;if(longcnt>10000)Mob1En=longcnt=0;}

   if(b==1){for(ct=0;ct<60;ct++){y=GPS[ct];}
     if(GPS[13]==0x41){if(c==0)LCD_Cmd(Lcd_CLEAR),Header(),c=1;
       /*
       d1=GPS[17]-48;d2=GPS[18]-48;d3=GPS[20]-48;d4=GPS[21]-48;d5=GPS[22]-48;d6=GPS[23]-48;
       Lt1=(d1*100000+d2*10000+d3*1000+d4*100+d5*10+d6)/60; //Lt1=6947;
       d7=Lt1/1000;Lt2=Lt1%1000;d8=Lt2/100;d11=Lt2%100;d9=d11/10;d10=d11%10;
       LCD_Out(1,1,"LATI:");LCD_Chr(1,6,GPS[15]);LCD_Chr(1,7,GPS[16]);LCD_Chr(1,8,'.');
       LCD_Chr(1,9,d7+48);LCD_Chr(1,10,d8+48);LCD_Chr(1,11,d9+48);LCD_Chr(1,12,d10+48);
       
       d12=GPS[30]-48;d13=GPS[31]-48;d14=GPS[33]-48;d15=GPS[34]-48;d16=GPS[35]-48;d17=GPS[36]-48;
       Lt3=(d12*100000+d13*10000+d14*1000+d15*100+d16*10+d17)/60;//Lt3=1747;
       d18=Lt3/1000;Lt4=Lt3%1000;d19=Lt4/100;d22=Lt4%100;d20=d22/10;d21=d22%10;
       LCD_Out(2,1,"LONG:");LCD_Chr(2,6,GPS[28]);LCD_Chr(2,7,GPS[29]);LCD_Chr(2,8,'.');
       LCD_Chr(2,9,d18+48);LCD_Chr(2,10,d19+48);LCD_Chr(2,11,d20+48);LCD_Chr(2,12,d21+48);
       */
       
       T3=GPS[2]-48;T4=GPS[3]-48;T5=GPS[4]-48;T6=GPS[5]-48;T7=T3*10+T4+5;
       T8=T5*10+T6+30;if(T8>59)T8=T8-60,T7=T7+1; if(T7>23)T7=T7-24;
       LCD_Out(4,1,"TIME:");LCD_Chr(4,6,T7/10+48);LCD_Chr(4,7,T7%10+48);LCD_Chr(4,8,':');LCD_Chr(4,9,T8/10+48);
       LCD_Chr(4,10,T8%10+48);

       LCD_Out(1,1,"LAT:");LCD_Chr(1,6,GPS[15]);LCD_Chr(1,7,GPS[16]);LCD_Chr(1,8,GPS[17]);
       LCD_Chr(1,9,GPS[18]);LCD_Chr(1,10,GPS[19]);LCD_Chr(1,11,GPS[20]);LCD_Chr(1,12,GPS[21]);LCD_Chr(1,13,GPS[22]);
       LCD_Chr(1,14,GPS[23]);
       
       LCD_Out(2,1,"LON:");LCD_Chr(2,6,GPS[28]);LCD_Chr(2,7,GPS[29]);LCD_Chr(2,8,GPS[30]);
       LCD_Chr(2,9,GPS[31]);LCD_Chr(2,10,GPS[32]);LCD_Chr(2,11,GPS[33]);LCD_Chr(2,12,GPS[34]);LCD_Chr(2,13,GPS[35]);
       LCD_Chr(2,14,GPS[36]);

       LCD_Out(3,1,"DATE:");LCD_Chr(3,6,GPS[52]);LCD_Chr(3,7,GPS[53]);LCD_Chr(3,8,':');LCD_Chr(3,9,GPS[54]);LCD_Chr(3,10,GPS[55]);
       LCD_Chr(3,11,':');LCD_Chr(3,12,GPS[56]);LCD_Chr(3,13,GPS[57]);
       //if(Lt1!=SmLt1||Lt3!=SmLt3){Wdata();SmLt1=Lt1;SmLt3=Lt3;}
       Wdata();
     }
    b=mt=0;
   }

  }
}
/******************************************************************************************************************************
END
******************************************************************************************************************************/