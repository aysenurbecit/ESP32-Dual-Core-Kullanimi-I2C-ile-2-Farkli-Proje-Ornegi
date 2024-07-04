#include <Deneyap_SicaklikNemBasincOlcer.h>   
#include <Deneyap_OLED.h>              
#include <Deneyap_HareketAlgilama.h>            

Gesture Hareket; //sensörler için class tanımlamaları
OLED OLED;  
SHT4x TempHum;  

float sicaklik;
float nem;

// fonksiyonların prototipleri
void gorev1kodu(void * pvParameters);
void gorev2kodu(void * pvParameters);

// ESP32 Dual-Core kullanımı için görev atamaları
TaskHandle_t gorev1;
TaskHandle_t gorev2;

void setup() {
  Serial.begin(115200); // seri haberleşmenin başlatılması

  if (!OLED.begin(0X7A)) {                          
        Serial.println("OLED - I2C bağlantısı başarısız");     
        while (1);
  }

  if (!TempHum.begin(0X44)) {                          
        Serial.println("TempHum - I2C bağlantısı başarısız");     
        while (1);
  }

  if (!Hareket.begin(0x32)) {                         
        delay(3000);
        Serial.println("Hareket - I2C bağlantısı başarısız");    
        while (1);
  }

  // core 0 a gorev1kodu görevi ataması 
  xTaskCreatePinnedToCore(
                    gorev1kodu,   // Görevin çalışacağı fonksiyon
                    "gorev1",     // Görevin adı
                    10000,        // Görev stack boyutu
                    NULL,         // İlave parametreler
                    1,            // Görevin önceliği-> 1 veya 0 olabilir
                    &gorev1,      // Görevin pointer ı
                    0);           // Atamanın yapıldığı çekirdek numarası        
  delay(500); 

  // core 1 e gorev2kodu görevi ataması 
  xTaskCreatePinnedToCore(
                    gorev2kodu,   // Görevin çalışacağı fonksiyon
                    "gorev2",     // Görevin adı
                    10000,        // Görev stack boyutu
                    NULL,         // İlave parametreler
                    1,            // Görevin önceliği 
                    &gorev2,      // Görevin işaretçisi
                    1);           // Atamanın yapıldığı çekirdek numarası
    delay(500); 
}

// Görev 1 kodu: Sıcaklık ve nenm okuması yapıp OLED ekrana yaz
void gorev1kodu(void * pvParameters) { // ilave parametre almıyoruz
  Serial.print("gorev1'in Çalıştığı Çekirdek: ");
  Serial.println(xPortGetCoreID()); //çekirdek numarası al ve seri ekrana yaz

  for(;;) { // loop döngüsü ile aynı mantıkta çalışmakta
    TempHum.measure();                                   
    sicaklik = TempHum.TtoDegC();    // sıcaklık değeri alınır                   
    OLED.clearDisplay();                            
    OLED.setTextXY(1, 0);                           
    OLED.putString("sicaklik: ");
    OLED.putFloat(sicaklik); 

    nem = TempHum.RHtoPercent();     // nem değeri alınır
    OLED.setTextXY(3, 0);                     
    OLED.putString("Bağıl nem: ");
    OLED.putFloat(nem); 

    delay(1000);
  } 
}

// Görev 2 kodu: Hareket algılanırsa seri monitöre yaz
void gorev2kodu(void * pvParameters) { // ilave parametre almıyoruz
  Serial.print("gorev2'nin Çalıştığı Çekirdek: ");
  Serial.println(xPortGetCoreID());

  for(;;) { // sonsuz döngü
    bool gestureDurum = Hareket.readGesture();          
    if (gestureDurum == 1) { // hareket algılandıysa
        Serial.println("HAREKET ALGILANDI");            
    } else {
        Serial.println("#################");
    }
    delay(100);
  }
}

void loop() {
  // loop döngüsü yerine gorev1 ve gorev2 de for(;;){} döngüsünde çekirdeğe atanmış işlemler gerçekleştiğinden bu kısmı boş bıraktık
}
