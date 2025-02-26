#include <iostream>
#include <string>
#include "qrcodegen.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using qrcodegen::QrCode;
using qrcodegen::QrSegment;

// ฟังก์ชันในการสร้าง QR Code สำหรับ PromptPay
void generatePromptPayQRCode(const std::string& promptPayData) {
    // สร้าง QR Code จากข้อมูลที่ได้รับ
    const QrCode qr = QrCode::encodeText(promptPayData.c_str(), QrCode::Ecc::HIGH);
    
    // ขนาดของ QR Code
    int size = qr.getSize();
    
    // สร้างภาพเพื่อเก็บข้อมูล QR Code
    unsigned char* image = new unsigned char[size * size];
    
    // เติมข้อมูล QR Code ในภาพ (0 = สีขาว, 255 = สีดำ)
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            image[y * size + x] = qr.getModule(x, y) ? 0 : 255; // 0 สำหรับสีดำ, 255 สำหรับสีขาว
        }
    }

    // บันทึกเป็นไฟล์ PNG
    if (stbi_write_png("qrcode.png", size, size, 1, image, size)) {
        std::cout << "QR Code saved successfully as qrcode.png!" << std::endl;
    } else {
        std::cout << "Failed to save QR Code." << std::endl;
    }
    
    // ลบภาพหลังจากใช้งาน
    delete[] image;
}

int main() {
    // ข้อมูล PromptPay สำหรับเบอร์ 0902726922
    std::string promptPayData = "00020101021129370016A00000067701011125100000370000503101100880000902726922";
    
    // สร้าง QR Code สำหรับ PromptPay
    generatePromptPayQRCode(promptPayData);
    
    return 0;
}
