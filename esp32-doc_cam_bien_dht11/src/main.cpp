#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// --- CẤU HÌNH CHO DHT11 ---
#define DHTPIN 23     // Chân kết nối dây DATA của DHT11
#define DHTTYPE DHT11 // Loại cảm biến là DHT11

// Khởi tạo đối tượng dht
DHT dht(DHTPIN, DHTTYPE);

// --- CẤU HÌNH CHO OLED ---
#define SCREEN_WIDTH 128 // Chiều rộng màn hình OLED, tính bằng pixel
#define SCREEN_HEIGHT 64 // Chiều cao màn hình OLED, tính bằng pixel
#define OLED_RESET    -1 // Chân Reset (nếu dùng I2C thì thường là -1 vì không dùng)
#define SCREEN_ADDRESS 0x3C // Địa chỉ I2C của OLED. Thường là 0x3C hoặc 0x3D.

// Khởi tạo đối tượng màn hình SSD1306 kết nối qua I2C (Wire)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Serial.println(F("ESP32 DHT11 OLED Test"));

  // 1. Khởi động cảm biến DHT
  dht.begin();

  // 2. Khởi động màn hình OLED
  // SSD1306_SWITCHCAPVCC để tạo điện áp màn hình từ nguồn 3.3V
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Khong tim thay man hinh OLED SSD1306, kiem tra lai day noi!"));
    for(;;); // Dừng chương trình tại đây nếu lỗi màn hình
  }

  // Xóa bộ đệm màn hình lần đầu
  display.clearDisplay();
  
  // Cài đặt font chữ và màu sắc
  display.setTextSize(1);      // Kích thước chữ bình thường
  display.setTextColor(SSD1306_WHITE); // Màu chữ trắng
  display.setCursor(0, 0);     // Đặt con trỏ tại góc trên trái
  display.println(F("Dang khoi dong..."));
  display.display(); // Lệnh bắt buộc để đẩy dữ liệu ra màn hình
  delay(2000); // Chờ 2 giây để cảm biến ổn định
}

void loop() {
  // Chờ một chút giữa các lần đo. DHT11 khá chậm, cần khoảng 2 giây.
  delay(2000);

  // Đọc độ ẩm
  float h = dht.readHumidity();
  // Đọc nhiệt độ C
  float t = dht.readTemperature();

  // Kiểm tra xem việc đọc có thành công hay không
  // isnan (Is Not a Number) là hàm kiểm tra xem giá trị có bị lỗi không
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Loi! Khong doc duoc du lieu tu DHT11"));
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println(F("Loi cam bien DHT11!"));
    display.display();
    return; // Thoát khỏi vòng lặp hiện tại, thử lại sau
  }

  // --- Hiển thị ra Serial Monitor để debug ---
  Serial.print(F("Do am: "));
  Serial.print(h);
  Serial.print(F("%  Nhiet do: "));
  Serial.print(t);
  Serial.println(F("°C"));

  // --- Hiển thị lên màn hình OLED ---
  display.clearDisplay(); // Xóa nội dung cũ

  

  // Hiển thị Nhiệt độ (chữ to hơn)
  display.setCursor(0, 15);
  display.setTextSize(1);
  display.print(F("Nhiet Do: "));
  display.setTextSize(2); // Chữ to lên
  display.print(t, 1);    // In nhiệt độ với 1 số thập phân
  display.setTextSize(1); // Chữ nhỏ lại để in ký hiệu độ C
  display.cp437(true);    // Sử dụng bảng mã CP437 để in được ký tự đặc biệt
  display.write(167);     // Ký tự hình tròn độ (°)
  display.println(F("C"));

  // Hiển thị Độ ẩm
  display.setCursor(0, 40);
  display.setTextSize(1);
  display.print(F("Do Am: "));
  display.setTextSize(2);
  display.print(h, 1);
  display.setTextSize(1);
  display.println(F(" %"));

  // CỰC KỲ QUAN TRỌNG: Phải gọi lệnh này thì nội dung mới hiện lên màn hình
  display.display(); 
}