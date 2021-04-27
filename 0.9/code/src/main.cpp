#include <Arduino.h>
#include <time.h>
#include <EEPROM.h>

int greenLed = 2;
int redLed = 3;

int fives = 0;
int tens = 0;
int twenties = 0;
int fifties = 0;
int hundreds = 0;

int registerAm = 0;
int amount = 0;

int five = 0, ten = 0, twenty = 0, fifty = 0, hundred = 0;

int customerAcc = 0;

int kopukle = 0, yika = 0, kurula = 0, cilala = 0;

//eeprom icin
int eeprom_Memory_address = 0;
int eeprom_size = 1024;
int fivesAddress = 10, tensAddress = 20, twentiesAddress = 30, fiftiesAddress = 40, hundredsAddress = 50;
int serviceBaslangicAddress = 60;

int step = 0;

struct service {
  int serviceID;
  char serviceName[10];
  int serviceLeft;
  int servicePrice;
  int btn;
} service1, service2, service3, service4;


void initVal() {
  fives = 20;
  tens = 20;
  twenties = 10;
  fifties = 30;
  hundreds = 5;
  //eeprom icin
  EEPROM.write(fivesAddress, fives);
  EEPROM.write(tensAddress, tens);
  EEPROM.write(twentiesAddress, twenties);
  EEPROM.write(fiftiesAddress, fifties);
  EEPROM.write(hundredsAddress, hundreds);


  fives = EEPROM.read(fivesAddress);
  tens = EEPROM.read(tensAddress);
  twenties = EEPROM.read(twentiesAddress);
  fifties = EEPROM.read(fiftiesAddress);
  hundreds = EEPROM.read(hundredsAddress);
  Serial.println("BANKNOT ADETLERİ");
  Serial.print(fives);
  Serial.print(",");
  Serial.print(tens);
  Serial.print(",");
  Serial.print(twenties);
  Serial.print(",");
  Serial.print(fifties);
  Serial.print(",");
  Serial.println(hundreds);





  registerAm = (hundreds * 100) + (fifties * 50) + (twenties * 20) + (tens * 10) + (fives * 5);

  service1.serviceID = 1;
  strcpy(service1.serviceName, "kopukleme");
  service1.serviceLeft = 30;
  service1.servicePrice = 15;
  //eepromda servisleri yazma okuma
  /*int tempAdress=serviceBaslangicAddress;
    EEPROM.put(tempAdress, service1);*/


  service2.serviceID = 2;
  strcpy(service2.serviceName, "yikama");
  service2.serviceLeft = 50;
  service2.servicePrice = 10;
  /*tempAdress += sizeof(service1);
    EEPROM.put(tempAdress, service2);*/

  service3.serviceID = 3;
  strcpy(service3.serviceName, "kurulama");
  service3.serviceLeft = 100;
  service3.servicePrice = 5;
  /*tempAdress += sizeof(service2);
    EEPROM.put(tempAdress, service3);*/

  service4.serviceID = 4;
  strcpy(service4.serviceName, "cilalama");
  service4.serviceLeft = 20;
  service4.servicePrice = 50;
  /*tempAdress += sizeof(service3);
    EEPROM.put(tempAdress, service4);*/

  /*tempAdress=serviceBaslangicAddress;
    EEPROM.get(serviceBaslangicAddress, service1);
    tempAdress += sizeof(service1);
    EEPROM.get(tempAdress, service2);
    tempAdress += sizeof(service2);
    EEPROM.get(tempAdress, service3);
    tempAdress += sizeof(service3);
    EEPROM.get(tempAdress, service4);*/
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Leds
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  initVal();
}

void reset(int btContiune, int btReset) {
  if (btContiune == HIGH) {
    step += 1;

    delay(500);

    Serial.println("Devam pressed");
  } else if (btReset == HIGH) {
    service1.serviceLeft += kopukle;
    service2.serviceLeft += yika;
    service3.serviceLeft += kurula;
    service4.serviceLeft += cilala;

    five = 0, ten = 0, twenty = 0, fifty = 0, hundred = 0;
    customerAcc = 0;
    kopukle = 0, yika = 0, kurula = 0, cilala = 0;
    amount = 0;
    step = 0;

    delay(500);

    Serial.println("Reset pressed");
  }
}

void addCashMenu() {
  Serial.println("/////////////////////////////////////////////////");

  Serial.println("Enter amount of money for your account.");

  Serial.println("1. Buton : 5 TL Sayisi");
  Serial.println("2. Buton : 10 TL Sayisi");
  Serial.println("3. Buton : 20 TL Sayisi");
  Serial.println("4. Buton : 50 TL Sayisi");
  Serial.println("5. Buton : 100 TL Sayisi");
  Serial.println("6. Buton : Bitis");

  Serial.println("/////////////////////////////////////////////////");
}

void addCash(int btFive, int btTen, int btTwenty, int btFifty, int btHundred, int btFinish) {
  if (btFive == HIGH) {
    five += 1;

    delay(500);

    Serial.println("Button 1 pressed");
  } else if (btTen == HIGH) {
    ten += 1;

    delay(500);

    Serial.println("Button 2 pressed");
  } else if (btTwenty == HIGH) {
    twenty += 1;

    delay(500);

    Serial.println("Button 3 pressed");
  } else if (btFifty == HIGH) {
    fifty += 1;

    delay(500);

    Serial.println("Button 4 pressed");
  } else if (btHundred == HIGH) {
    hundred += 1;

    delay(500);

    Serial.println("Button 5 pressed");
  } else if (btFinish == HIGH) {
    Serial.println("Button 6 pressed");

    delay(500);

    customerAcc = 0;
    customerAcc += five * 5 + ten * 10 + twenty * 20 + fifty * 50 + hundred * 100;

    String Str = "Total cash in customer account : ";
    String StrD = Str + customerAcc ;

    Serial.println("");
    Serial.println("/////////////////////////////////////////////////");
    Serial.println(StrD);

    step += 1;
  }
}

void selectServiceMenu() {
  Serial.println("/////////////////////////////////////////////////");

  Serial.println("Select Services: ");

  // Serial.println("Kopukleme");
  Serial.print(service1.serviceID);
  Serial.print(",");
  Serial.print(service1.serviceName);
  Serial.print(",");
  Serial.print(service1.servicePrice);
  Serial.print(",");
  Serial.print("Kalan Hizmet:");
  Serial.println(+service1.serviceLeft);

  // Serial.println("Yikama");
  Serial.print(service2.serviceID);
  Serial.print(",");
  Serial.print(service2.serviceName);
  Serial.print(",");
  Serial.print(service2.servicePrice);
  Serial.print(",");
  Serial.print("Kalan Hizmet:");
  Serial.println(+service2.serviceLeft);
  // Serial.println("Kurulama");
  Serial.print(service3.serviceID);
  Serial.print(",");
  Serial.print(service3.serviceName);
  Serial.print(",");
  Serial.print(service3.servicePrice);
  Serial.print(",");
  Serial.print("Kalan Hizmet:");
  Serial.println(+service3.serviceLeft);
  //Serial.println("Cilalama");
  Serial.print(service4.serviceID);
  Serial.print(",");
  Serial.print(service4.serviceName);
  Serial.print(",");
  Serial.print(service4.servicePrice);
  Serial.print(",");
  Serial.print("Kalan Hizmet:");
  Serial.println(+service4.serviceLeft);
  Serial.println("Bitis");

  Serial.println("/////////////////////////////////////////////////");
}

void applyService() {
  // service1
  if (strcmp("kopukleme", service1.serviceName)) {
    if (service1.serviceLeft > 0) {
      service1.serviceLeft -= 1 * kopukle;

    } else {
      kopukle -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }

  } else if (strcmp("yikama", service1.serviceName)) {
    if (service1.serviceLeft > 0) {
      service1.serviceLeft -= 1 * yika;

    } else {
      yika -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }
  } else if (strcmp("kurulama", service1.serviceName)) {
    if (service1.serviceLeft > 0) {
      service1.serviceLeft -= 1 * kurula;

    } else {
      kurula -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }

  } else if (strcmp("cilalama", service1.serviceName)) {
    if (service1.serviceLeft > 0) {
      service1.serviceLeft -= 1 * cilala;

    } else {
      cilala -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }
  }

  // service2
  if (strcmp("kopukleme", service2.serviceName)) {
    if (service2.serviceLeft > 0) {
      service2.serviceLeft -= 1 * kopukle;

    } else {
      kopukle -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }

  } else if (strcmp("yikama", service2.serviceName)) {
    if (service2.serviceLeft > 0) {
      service2.serviceLeft -= 1 * yika;

    } else {
      yika -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }
  } else if (strcmp("kurulama", service2.serviceName)) {
    if (service2.serviceLeft > 0) {
      service2.serviceLeft -= 1 * kurula;

    } else {
      kurula -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }

  } else if (strcmp("cilalama", service2.serviceName)) {
    if (service2.serviceLeft > 0) {
      service2.serviceLeft -= 1 * cilala;

    } else {
      cilala -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }
  }

  // service3
  if (strcmp("kopukleme", service3.serviceName)) {
    if (service3.serviceLeft > 0) {
      service3.serviceLeft -= 1 * kopukle;

    } else {
      kopukle -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }

  } else if (strcmp("yikama", service3.serviceName)) {
    if (service3.serviceLeft > 0) {
      service3.serviceLeft -= 1 * yika;

    } else {
      yika -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }
  } else if (strcmp("kurulama", service3.serviceName)) {
    if (service3.serviceLeft > 0) {
      service3.serviceLeft -= 1 * kurula;

    } else {
      kurula -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }

  } else if (strcmp("cilalama", service3.serviceName)) {
    if (service3.serviceLeft > 0) {
      service3.serviceLeft -= 1 * cilala;

    } else {
      cilala -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }
  }

  // service4
  if (strcmp("kopukleme", service4.serviceName)) {
    if (service4.serviceLeft > 0) {
      service4.serviceLeft -= 1 * kopukle;

    } else {
      kopukle -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }

  } else if (strcmp("yikama", service4.serviceName)) {
    if (service4.serviceLeft > 0) {
      service4.serviceLeft -= 1 * yika;

    } else {
      yika -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }
  } else if (strcmp("kurulama", service4.serviceName)) {
    if (service4.serviceLeft > 0) {
      service4.serviceLeft -= 1 * kurula;

    } else {
      kurula -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }

  } else if (strcmp("cilalama", service4.serviceName)) {
    if (service4.serviceLeft > 0) {
      service4.serviceLeft -= 1 * cilala;

    } else {
      cilala -= 1;
      Serial.println("Yeterli hizmet kalmadi!");
    }
  }
}

void selectService(int btKopukle, int btYika, int btKurula, int btCilala, int btFinish) {

  if (btKopukle == HIGH) {
    kopukle += 1;
    delay(500);

    Serial.println("Kopukle pressed");
  } else if (btYika == HIGH) {
    yika += 1;
    delay(500);

    Serial.println("Yika pressed");
  } else if (btKurula == HIGH) {
    kurula += 1;
    delay(500);

    Serial.println("Kurula pressed");
  } else if (btCilala == HIGH) {
    cilala += 1;
    delay(500);

    Serial.println("Cilala pressed");
  } else if (btFinish == HIGH) {
    Serial.println("Bitis pressed");

    delay(500);

    amount = 0;
    amount = kopukle * 15 + yika * 10 + kurula * 5 + cilala * 50;

    if (amount <= customerAcc) {
      applyService();

      String Str = "Total price of selected services : ";
      String StrD = Str + amount;

      Serial.println("");
      Serial.println("/////////////////////////////////////////////////");
      Serial.println(StrD);

      step += 1;
    } else {
      String Str = "Customer account is insufficient resetting steps: ";

      Serial.println("");
      Serial.println("/////////////////////////////////////////////////");
      Serial.println(Str);

      reset(LOW, HIGH);
    }
  }
}

void resetMenu() {
  Serial.println("/////////////////////////////////////////////////");
  Serial.println("Yanlis secim yaptiysaniz Resetleyebilirsiniz(Tum secimler iptal edilir!).");
  Serial.println("6. Buton: Devam");
  Serial.println("7. Buton: Reset");
  Serial.println("/////////////////////////////////////////////////");
}


void isStuct() {
  int isStuck = (rand() % 4) + 1;
  if (isStuck == 2) {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    Serial.println("Money Stuct\n");
    Serial.println("Returning Money...\n");
    reset(LOW, HIGH);
  }
  else {
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    Serial.println("Money Processed\n");
    Serial.println("Calculating Change...\n");
    reset(HIGH, LOW);
  }
}

void UpdateEepromCacheAmount() {
  EEPROM.write(fivesAddress, fives);
  EEPROM.write(tensAddress, tens);
  EEPROM.write(twentiesAddress, twenties);
  EEPROM.write(fiftiesAddress, fifties);
  EEPROM.write(hundredsAddress, hundreds);

  Serial.println("Kalan Banknot Adetleri(5,10,20,50,100 degerinde banknotlar)");

  int fives2 = EEPROM.read(fivesAddress);
  int tens2 = EEPROM.read(tensAddress);
  int twenties2 = EEPROM.read(twentiesAddress);
  int fifties2 = EEPROM.read(fiftiesAddress);
  int hundreds2 = EEPROM.read(hundredsAddress);

  Serial.print(fives2);
  Serial.print(",");
  Serial.print(tens2);
  Serial.print(",");
  Serial.print(twenties2);
  Serial.print(",");
  Serial.print(fifties2);
  Serial.print(",");
  Serial.println(hundreds2);
}

void giveChange() {
  int change = customerAcc - amount;
  if (registerAm < change) {
    Serial.println("insufficient amount in register Resetting steps.");
    reset(LOW, HIGH);
  } else {
    int f = 0, t = 0, tw = 0, ft = 0, h = 0;
    h = change / 100;
    change -= h * 100;
    ft = change / 50;
    change -= ft * 50;
    tw = change / 20;
    change -= tw * 20;
    t = change / 10;
    change -= t * 10;
    f = change / 5;
    change -= f * 5;

    String Strf = "Fives : ";
    String StrF = Strf + f;

    String Strt = "Tens : ";
    String StrT = Strt + t;

    String Strtw = "Twenties : ";
    String StrTw = Strtw + tw;

    String Strft = "Fifties : ";
    String StrFt = Strft + ft;

    String Strh = "Hundreds : ";
    String StrH = Strh + h;
    //eeprom icin
    fives -= f;
    tens -= t;
    twenties -= tw;
    fifties -= ft;
    hundreds -= h;
    registerAm -= amount;

    UpdateEepromCacheAmount();



    Serial.println("");
    Serial.println("/////////////////////////////////////////////////");
    Serial.print("Total change : ");
    Serial.println(customerAcc - amount);
    Serial.println(StrF);
    Serial.println(StrT);
    Serial.println(StrTw);
    Serial.println(StrFt);
    Serial.println(StrH);


     step += 1;
    //step = 0;

  }
}

void serviceLeft() {
  Serial.println("/////////////////////////////////////////////////");
  Serial.println("");
  Serial.print("Kalan ");
  Serial.print(service1.serviceName);
  Serial.print(": ");
  Serial.println(service1.serviceLeft);

  Serial.print("Kalan ");
  Serial.print(service2.serviceName);
  Serial.print(": ");
  Serial.println(service2.serviceLeft);

  Serial.print("Kalan ");
  Serial.print(service3.serviceName);
  Serial.print(": ");
  Serial.println(service3.serviceLeft);

  Serial.print("Kalan ");
  Serial.print(service4.serviceName);
  Serial.print(": ");
  Serial.println(service4.serviceLeft);

  Serial.println("");
}

void contiuneService() {
    five = 0, ten = 0, twenty = 0, fifty = 0, hundred = 0;
    kopukle = 0, yika = 0, kurula = 0, cilala = 0;
    customerAcc = 0;
    amount = 0;
    step = 0;

    delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Reset Finish Buttons
  int btReset = digitalRead(4);
  int btFinish = digitalRead(5);

  if (step == 0) {
    //Serial.println(step);

    Serial.println("/////////////////////////////////////////////////");
    Serial.println("Welcome To Car Wash!");

    addCashMenu();

    step += 1;
  } else if (step == 1) {
    //Serial.println(step);

    // addCash Buttons
    int btFive = digitalRead(13);
    int btTen = digitalRead(12);
    int btTwenty = digitalRead(11);
    int btFifty = digitalRead(10);
    int btHundred = digitalRead(9);

    addCash(btFive, btTen, btTwenty, btFifty, btHundred, btFinish);

    if (btFinish == HIGH) {
      selectServiceMenu();
    }

  } else if (step == 2) {
    //Serial.println(step);

    // selectService Buttons
    int btKopukle = digitalRead(13);
    int btYika = digitalRead(12);
    int btKurula = digitalRead(11);
    int btCilala = digitalRead(10);

    amount = 0;

    selectService(btKopukle, btYika, btKurula, btCilala, btFinish);

    if (btFinish == HIGH) {
      resetMenu();
    }
  } else if (step == 3) {
    //Serial.println(step);

    reset(btFinish, btReset);
  } else if (step == 4) {
    //Serial.println(step);

    isStuct();
  } else if (step == 5) {
    //Serial.println(step);

    giveChange();
    serviceLeft();
  } else if( step == 6){
    //Serial.println(step);

    contiuneService();
  }
}