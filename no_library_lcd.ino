// Datenblatt https://www.displayfuture.com/Display/datasheet/alphanumeric/LCM1602A.pdf

int delay_time = 300;         // damit das schreiben cooler aussieht

byte pins_all[] = {2,3,4,5,6,7,8,9,10,11,12};
byte pins_data[] = {12,11,10,9,8,7,6,5};
byte pins_data_reverse[] = {5,6,7,8,9,10,11,12};

void data_stream(String data){       
  for(int i=0; i<8; i++){
    digitalWrite(pins_data[i], bitRead(data.charAt(i),0)); 
  }
}

void rs_rw_stream(int rs, int rw){
  digitalWrite(2,rs);
  digitalWrite(3,rw);
}

void enable(){
  digitalWrite(4,1);
  digitalWrite(4,0);
}

void clear(){
  data_stream("00000001");
  rs_rw_stream(0,0);
  enable();
}

void print(String text) {
  for(int i=0; i<text.length(); i++) {
    char Char = text.charAt(i);
    for(int i=7; i>=0; i--) {
      digitalWrite(pins_data_reverse[i], bitRead(Char,i));
    }
    rs_rw_stream(1,0);
    enable();
    delay(delay_time);
  }
}

void cursor(int line, int pos){
  byte pins_data_ddram[] = {5,6,7,8,9,10,11};
  if(line == 1){
    pos -= 1;
    digitalWrite(12,1);
    for(int i=0; i<7; i++){
      digitalWrite(pins_data_ddram[i], bitRead(pos,i));
    }
    rs_rw_stream(0,0);
    enable();
    delay(2);
  }else if(line == 2){
    pos +=63;
    digitalWrite(12,1);
    for(int i=0; i<7; i++){
      digitalWrite(pins_data_ddram[i], bitRead(pos,i));
    }
    rs_rw_stream(0,0);
    enable();
    delay(2);
  }
}

void printCustomChar(int custom){
  custom -= 1;
  for(int i=0; i<8; i++){
    digitalWrite(pins_data_reverse[i], bitRead(custom,i));
  }
  rs_rw_stream(1,0);
  enable();
  delay(delay_time);
}

void setCGRAM(String adress){
  data_stream("01" + adress);
  rs_rw_stream(0,0);
  enable();
  delay(2);
}

void writeCGRAM(String data){
  data_stream("000" + data);
  rs_rw_stream(1,0);
  enable();
  delay(2);
}

/*
benutzen von eigenen Charactären:
  1. Dot-Matrix bearbeiten:
    - zur jehweiligen Dot-Matrix begeben z.B. Nr.1 (0x00-0x07)
    - 1 für leuchtende Pixel, 0 für nichtleuchtende Pixel
    - letzte Reihe für Cursor auf 00000 lassen
  2. eigene Charctäre an das Display senden:
    - Character in CGRAM laden --> createCustomChar(xyz), xyz steht für jehweiligen Character (1-8)
    - Cusrsorposition setzen --> cursor(Zeile, Position), an jener Stelle wird der eigene Character erscheinen
    - eigenen Character senden --> printCustomChar(xyz, xyz steht für jehweiligen Character (1-8)
*/

void createCustomChar(int custom){    
  if(custom==1){
    setCGRAM("000000");      // start 0x00, ende 0x07
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("01010");     // ⬛⬜⬛⬜⬛
    writeCGRAM("01010");     // ⬛⬜⬛⬜⬛
    writeCGRAM("01010");     // ⬛⬜⬛⬜⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("10001");     // ⬜⬛⬛⬛⬜
    writeCGRAM("01110");     // ⬛⬜⬜⬜⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
  }else if(custom==2){
    setCGRAM("001000");     // start 0x08, ende 0x0F
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
  }else if(custom==3){
    setCGRAM("010000");     // start 0x10, ende 0x17
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
  }else if(custom==4){
    setCGRAM("011000");     // start 0x18, ende 0x1F
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
  }else if(custom==5){
    setCGRAM("100000");     // start 0x20, ende 0x27
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
  }else if(custom==6){
    setCGRAM("101000");     // start 0x28, ende 0x2F
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
  }else if(custom==7){
    setCGRAM("110000");     // start 0x30, ende 0x37
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
  }else if(custom==8){
    setCGRAM("111000");     // start 0x38, ende 0x3F
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
    writeCGRAM("00000");     // ⬛⬛⬛⬛⬛
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(13, INPUT);                   // reset Knopf; eigentlich Nutzlos; für Notfälle

  for(int i=0; i<11; i++){              // setzt pins 2-12 auf OUTPUT
    pinMode(pins_all[i],OUTPUT);
  }
  
  clear();                              // um nach jedem reset das Display zu clearen und DDRAM Adresse 00 zu setzen 
  delay(10);                            // dieses Delay ist wichtig; mindestens 1,55ms
  
  data_stream("00111000");              // 8-bit Modus; 2 Zeilen; 5x8 Schrift
  rs_rw_stream(0,0);
  enable();
  
  data_stream("00001110");              // aktiviert den Cursor (kein blinken)
  rs_rw_stream(0,0);
  enable();
  
  data_stream("00000110");              // verschiebe die Register Adresse jedes mal +1
  rs_rw_stream(0,0);
  enable();
  
  print("Hello World!");
  print(" ");
  
  createCustomChar(1);
  cursor(1,14);
  printCustomChar(1);
  
  cursor(2,1);
  print("Ohne Bibliothek!");
}

void loop() {
  if (digitalRead(13) == LOW) {
    clear();
  }
}
