# ESP32-Dual-Core-Kullanimi-I2C-ile-2-Farkli-Proje-Ornegi
Bu proje, ESP32'nin dual-core mimarisini kullanarak sıcaklık, nem ve hareket sensörlerinden veri okuyup, bu verileri OLED ekranda göstermek ve hareket algılama durumunu seri monitöre yazdırmayı amaçlar.
## Gereksinimler
- ESP32 Geliştirme Kartı - projede kullanılan Deneyap Kart 1A
- Deneyap Sıcaklık, Nem ve Basınç Ölçer Sensörü (SHT4x)
- Deneyap OLED Ekran
- Deneyap Hareket Algılama Sensörü
- Arduino IDE
## Gerekli Arduino Kütüphaneleri:
Deneyap_SicaklikNemBasincOlcer.h
Deneyap_OLED.h
Deneyap_HareketAlgilama.h
## Bağlantılar
SHT4x Sensörü ve OLED Ekran I2C protokolü ile ESP32'ye bağlanır.
Hareket Algılama Sensörü yine I2C üzerinden ESP32'ye bağlanır.
## Kurulum- Kullanım
1. Tüm bağlantıları yapın ve ESP32'yi bilgisayarınıza bağlayın.
2. Arduino IDE üzerinden doğru portu seçin.
3. Kodu ESP32'ye yükleyin.
4. Seri monitörü açarak sıcaklık, nem ve hareket verilerini gözlemleyin.

## Fonksiyonlar
gorev1kodu: Bu fonksiyon sıcaklık ve nem değerlerini okuyarak OLED ekranda görüntüler. Bu görev ESP32'nin çekirdek 0'ında çalışır.
gorev2kodu: Bu fonksiyon hareket sensöründen veri okur ve hareket algılandığında seri monitöre yazdırır. Bu görev ESP32'nin çekirdek 1'inde çalışır.

Bu özellik sayesinde aynı anda çok işlem yapmak mümkün hale geliyor. Bu iki projeyi tek çekirdek üzerinde aynı anda yapmak isteseydik düzgün çalışmayacaktı çünkü kod satır satır işlenecek ve aynı anda hem sıcaklık okuması yapıp yazamayacak hem de hareketi algılayamacaktı. Çekirdeklerde yapılabilecek işlemler genişletilip çekirdek özelliğiine ve kart kapasitesine göre çeşitlendirilebilir.
