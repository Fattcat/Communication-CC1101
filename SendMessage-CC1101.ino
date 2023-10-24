#include <SPI.h>
#include <CC1101.h> // Použite knižnicu pre CC1101

CC1101 radio;

void setup() {
  Serial.begin(9600);

  // Inicializujte komunikáciu s modulom CC1101
  radio.begin();
  radio.setFrequency(433.0); // Nastavte frekvenciu podľa vašich modulov
  radio.setOutputPower(10); // Nastavte výkon vysielania podľa vašich potrieb
  radio.setSyncWord(0xD391); // Nastavte synchronizačný word

  // Nastavte adresu odesielateľa a prijímateľa
  radio.setSenderAddress(0x01);
  radio.setReceiverAddress(0x02);
  radio.openTX();

  // Skontrolujte, či je modul pripravený na vysielanie
  if (radio.isTXFIFOEmpty()) {
    Serial.println("Modul je pripravený na vysielanie.");
  }
}

void loop() {
  // Čítajte správu zo sériového portu alebo inej zdrojovej správy
  String message = "Vaša správa";

  // Odošlite správu
  radio.sendString(message);

  // Skontrolujte, či bola správa úspešne odoslaná
  if (radio.sendFinished()) {
    Serial.println("Správa bola úspešne odoslaná.");
  }

  // Prijmite správu
  if (radio.receiveFinished()) {
    String receivedMessage = radio.receiveString();
    Serial.println("Prijatá správa: " + receivedMessage);
  }
}

