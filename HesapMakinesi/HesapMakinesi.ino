//#include<Keypad.h>
//const byte ROWS = 4;  //4 satır olucak
//const byte COLS = 4;  //4 sütun olucak
//char keys[[ROWS][COLS]] = {
  //{'1','2','3','A'},
  //{'4','5','6','B'},
  //{'7','8','9','C'},
  //{'*','0','#','D'}
  //}
//byte rowPin[ROWS] = {2,3,4,5};  //Satırların bağlı olduğu pinler
//byte rowPin[COLS] = {6,7,8,9};  //Satırların bağlı olduğu pinler

//Keypad keypad

#include <LiquidCrystal.h>
#include <math.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int okunan;
byte full[] = {31,31,31,31,31,31,31,31};

#define sag 0
#define ust 1
#define alt 2
#define sol 3
#define secim 4
#define yok 5

int tus_oku() {
  okunan = analogRead(0);
  if (okunan > 1000) return yok;
  if (okunan < 50) return sag;
  if (okunan < 195) return ust;
  if (okunan < 380) return alt;
  if (okunan < 555) return sol;
  if (okunan < 790) return secim;
  return yok;
}

void setup() {
  lcd.begin(16,2);  //lcd yi tanıtmak için
  lcd.createChar(0,full);
  lcd.setCursor(0,0);
  lcd.print("-HESAP MAKINESI-"); //İlk satırda
  lcd.setCursor(0,1);
  lcd.print("  HOS GELDINIZ  ");
  delay(1000);
  for(int i=0;i<16;i++){  //Animasyonnn için
      lcd.setCursor(i,1);
      lcd.write(byte(0));
      delay(200);
      lcd.print(" ");    
    }
    //for(int i=16;i>1;i--){  //Ters animasyonnn için
      //lcd.setCursor(i,1);
      //lcd.write(byte(0));
      //delay(200);
      //lcd.print(" "); 
    //}
    
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("ISLEM SECINIZ");

  int menuSecim = 1; // Varsayılan seçim Temel İşlemler

  while (true) {
    int tus = tus_oku();
    if (tus == ust) {
      menuSecim = 1;    // Temel İşlemler
    } 
    else if (tus == alt) {
      menuSecim = 2;    // Geometri
    } 
    else if (tus == secim) {
      break;
    }

    lcd.setCursor(0, 1);
    if (menuSecim == 1) {
      lcd.print(">TEMEL ISLEMLER  ");
    } else {
      lcd.print(">GEOMETRI        ");
    }
    delay(200);
  }

  if (menuSecim == 1) {
    temelIslemlerMenu();
  }
  else {
    geometriMenu();
  }
}

void temelIslemlerMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEMEL ISLEMLER");
  delay(1000);
  lcd.clear();

  int islemSecim = 1; // Varsayılan seçim Toplama

  while (true) {
    int tus = tus_oku();
    if (tus == ust) {
      islemSecim = (islemSecim == 1) ? 10 : islemSecim - 1;
    } 
    else if (tus == alt) {
      islemSecim = (islemSecim == 10) ? 1 : islemSecim + 1;
    } 
    else if (tus == secim) {
      break;
    }
    else if (tus == sag) {
      return; // Sağ tuşuna basıldığında ana menüye dön
    }

    lcd.setCursor(0, 0);
    lcd.print("TEMEL ISLEMLER   ");
    lcd.setCursor(0, 1);
    switch (islemSecim) {
      case 1:
        lcd.print(">TOPLAMA         ");
        break;
      case 2:
        lcd.print(">CIKARMA         ");
        break;
      case 3:
        lcd.print(">CARPMA          ");
        break;
      case 4:
        lcd.print(">BOLME           ");
        break;
      case 5:
        lcd.print(">UST ALMA        ");
        break;
      case 6:
        lcd.print(">KAREKOK         ");
        break;
      case 7:
        lcd.print(">SINUS           ");
        break;
      case 8:
        lcd.print(">COSINUS         ");
        break;
      case 9:
        lcd.print(">TANJANT         ");
        break;
      case 10:
        lcd.print(">KOTANJANT       ");
        break;
    }
    delay(200);
  }

  int sayi1 = sayiGir("1. SAYIYI");
  int sayi2 = 0;
  if (islemSecim == 1 || islemSecim == 2 || islemSecim == 3 || islemSecim == 4 || islemSecim == 5) {
    sayi2 = sayiGir("2. SAYIYI");
  }

  lcd.clear();
  lcd.setCursor(0, 0);

  switch (islemSecim) {
    case 1:
      lcd.print("TOPLAMA: ");
      lcd.print(sayi1 + sayi2);
      break;
    case 2:
      lcd.print("CIKARMA: ");
      lcd.print(sayi1 - sayi2);
      break;
    case 3:
      lcd.print("CARPMA: ");
      lcd.print(sayi1 * sayi2);
      break;
    case 4:
      if (sayi2 != 0) {
        lcd.print("BOLME: ");
        lcd.print(sayi1 / sayi2);
      } else {
        lcd.print("SIFIRA BOLUNMEZ");
      }
      break;
    case 5:
      lcd.print("UST ALMA: ");
      lcd.print(pow(sayi1, sayi2));
      break;
    case 6:
      lcd.print("KAREKOK: ");
      lcd.print(sqrt(sayi1));
      break;
    case 7:
      lcd.print("SINUS: ");
      lcd.print(sin(radians(sayi1)));
      break;
    case 8:
      lcd.print("COSINUS: ");
      lcd.print(cos(radians(sayi1)));
      break;
    case 9:
      lcd.print("TANJANT: ");
      lcd.print(tan(radians(sayi1)));
      break;
    case 10:
      lcd.print("KOTANJANT: ");
      lcd.print(1 / tan(radians(sayi1)));
      break;
  }

  delay(3000);
  lcd.clear();
}

void geometriMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GEOMETRI        ");
  delay(1000);
  lcd.clear();

  int geometriSecim = 1; // Varsayılan seçim Üçgen

  while (true) {
    int tus = tus_oku();
    if (tus == ust) {
      geometriSecim = (geometriSecim == 1) ? 4 : geometriSecim - 1;
    } 
    else if (tus == alt) {
      geometriSecim = (geometriSecim == 4) ? 1 : geometriSecim + 1;
    } 
    else if (tus == secim) {
      break;
    }
    else if (tus == sag) {
      return; // Sağ tuşuna basıldığında ana menüye dön
    }

    lcd.setCursor(0, 0);
    lcd.print("GEOMETRI        ");
    lcd.setCursor(0, 1);
    switch (geometriSecim) {
      case 1:
        lcd.print(">UCGEN           ");
        break;
      case 2:
        lcd.print(">KARE            ");
        break;
      case 3:
        lcd.print(">DIKDORTGEN      ");
        break;
      case 4:
        lcd.print(">DAIRE           ");
        break;
    }
    delay(200);
  }

  switch (geometriSecim) {
    case 1:
      ucgenIslemleri();
      break;
    case 2:
      kareIslemleri();
      break;
    case 3:
      dikdortgenIslemleri();
      break;
    case 4:
      daireIslemleri();
      break;
  }
}

int sayiGir(String sayiSirasi) {
  int sayi;
  do {
    sayi = map(analogRead(A1), 0, 1023, 0, 100); // sayıyı oku
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(sayiSirasi + " GIRIN");
    lcd.setCursor(0, 1);
    lcd.print("SAYI: ");
    lcd.print(sayi);
    delay(300);
  } while (tus_oku() != secim);
  return sayi;
}

void ucgenIslemleri() {
  int taban = sayiGir("TABAN");
  int yukseklik = sayiGir("YUKSEKLIK");
  int kenar1 = sayiGir("KENAR1");
  int kenar2 = sayiGir("KENAR2");

  int alan = (taban * yukseklik) / 2;
  int cevre = taban + kenar1 + kenar2;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALAN: ");
  lcd.print(alan);
  lcd.setCursor(0, 1);
  lcd.print("CEVRE: ");
  lcd.print(cevre);
  delay(3000);
  lcd.clear();
}

void kareIslemleri() {
  int kenar = sayiGir("KENAR");

  int alan = kenar * kenar;
  int cevre = 4 * kenar;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALAN: ");
  lcd.print(alan);
  lcd.setCursor(0, 1);
  lcd.print("CEVRE: ");
  lcd.print(cevre);
  delay(3000);
  lcd.clear();
}

void dikdortgenIslemleri() {
  int uzunKenar = sayiGir("UZUN KENAR");
  int kisaKenar = sayiGir("KISA KENAR");

  int alan = uzunKenar * kisaKenar;
  int cevre = 2 * (uzunKenar + kisaKenar);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALAN: ");
  lcd.print(alan);
  lcd.setCursor(0, 1);
  lcd.print("CEVRE: ");
  lcd.print(cevre);
  delay(3000);
  lcd.clear();
}

void daireIslemleri() {
  int yaricap = sayiGir("YARICAP");

  float alan = M_PI * yaricap * yaricap;
  float cevre = 2 * M_PI * yaricap;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALAN: ");
  lcd.print(alan);
  lcd.setCursor(0, 1);
  lcd.print("CEVRE: ");
  lcd.print(cevre);
  delay(3000);
  lcd.clear();
}
