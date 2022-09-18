void setup(){
  DDRB=B001000;//set PIN3 to output
  PORTB=B001000;//set ZZHZZZ

  OCR1C=146;//MAX
  OCR1B=73;//threshold

  //タイマー1制御レジスタ2
  // 7    6     5      4      3    2     1    0
  // CTC1 PWM1A COM1A1 COM1A0 CS13 CCS12 CS11 CS10
  //-----
  // 0    CTC PWM使うので無関係
  // 000  PWM1A使わん
  // 1001 16500k/CS/OCR1C=Hz
  TCCR1=B00001001;

  //一般タイマ―制御レジスタ という名の タイマー1制御レジスタ サブ
  // TSM PWM1B COM1B1 COM1B0 FOC1B FOC1A PSR1 PSR0
  //-----
  // 0   ようわからんけど無関係
  // 101 PWM1B使う /OC1B(PIN3)使うのでCOM1B=01
  // 00  PWM1B=1なので無関係 Aは使わないので無関係
  // 00  ここへの書き込みは無意味
  GTCCR=B01010000;


  TCNT1=0;//timer1 reset
}
void loop(){
  OCR1B=millis()%1000<50?73:OCR1C;
}
