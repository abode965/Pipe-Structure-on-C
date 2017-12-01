# Pipe-Structure-on-C
Project on OS course 
	Özet
Bu proje kapsamında pipe yapısı kullanılarak programlar arasında veri alışverişi sağlandı. Ana programdan açılan pipe kullanılarak diğer programlara her hangi bir veriyi taşıyarak iletişimi gerçekleştirdik . Aynı zamanda prosesler arası geçişler için frak ve exec sistemi çağrıları kullanılmıştır.
	
  Proje Konusu
              ∑_n^k 〖n^3+n〗
Bu projede dört adet program vardır.dört program aralarında haberleşerek yukarıdaki formülü kullanıcı tarafında girilen n ve k değerlerine göre hesaplanacaktır.
	Toplam sınıfı işlem sınıftan named pipe bağlantıyla gelen değerleri toplama işlemi yapılmakta
	İşlem sınıfı Nkup  ve Nkupplus sınıflarıyla pipe bağlantılarıyla haberleşerek  n^3 ve 〖(n〗^3+n) hesaplatarak sonucunu Toplam sınıfına gönderilmekte.
	Nkup sınıfı pipe bağlantı vasıtasıyla gelen n değer n^3  hesaplayıp işlem sınıfına geri gönderilmekte.
	Nkupplus sınıfı pipe bağlantı vasıtasıyla gelen n^3  〖(n〗^3+n) i hesaplayıp işlem sınıfına geri gönderilmekte 
	Proje Çıktıları ve Başarı Ölçütleri

	MakeFile 

Makefile dosyasında her zaman yaptığımız gibi , c dosyaları kullandığı kütüphaneleriyle compile ediyoruz ondan sonra programı çalıştırıyoruz.
Bu projede iki tane terminal ihtyacımızdan dolay xterm komutu kullandım 



	Toplam sınfı 
Bu sınıf işelm sınıfın tarafından gönderilen değerleri toplaması yapmak. Burada gördüğümüz gibi gelen mesajın integere çevirip sayıları dizisine saklayıp toplam değişkeni eklenmekte
Böylece gelen tüm sayıları sayılar dizinden ekrana yazdırabiliyoruz ve toplam sonucu toplam değişkeninde toplanmış olur.




	İşlem sınıfı
Bu projenin en büyük sınıfımızdır. Bu sınıf hem namepipe hem de pipe ile bağlıdır. Kullancı tarafından girilen n ve k değeri ile başlar .ondan sonra fork yaparak n^3 değeri hesaplamak için Nkup sınıfı çalıştırıyor o değeri sonuc değişkenine atılmak . n^3+n hesaplamak için yeni fork yaparak sonuc Nkupplusa gönderildikten sonra gelen n^3+n değeri sonuc1 atılıyor.ve bu sınıfın son işlemi ise sounc1 namepipe kullanarak toplam sınıfına gönderilmekte .Bu 3 işlevi while döngünün içinde k değeri sıfır oluncaya kadar devam edilmektir.
İşlem sınıfı bitiş sinyalı olarak whileden çıktıktan sonra toplam sınıfına 0 gönderilmektedir.

	Nkup sınıfı 
Nkup sınıfında İşlem sınıfından gönderilen n değeri n^3  hesaplanıp geri gönderilmekte.

	Nkupplus sınıfı 
Nkupplus  sınıfında İşlem sınıfından gönderilen n^3değeri n^3+n hesaplanıp geri gönderilmekte.
