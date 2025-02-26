#include <iostream>
#include <qrcodegen.hpp>
#include "stb_image_write.h"  // ใช้สำหรับเขียนไฟล์ภาพ
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


void saveQRCodeAsImage(const qrcodegen::QrCode &qr, const std::string &filename) {
    int size = qr.getSize();
    int width = size;  // ขนาดของ QR Code

    // สร้างภาพ (เช่น 1 พิกเซลต่อโมดูล QR Code)
    unsigned char* image = new unsigned char[width * width * 3];  // ใช้ 3 เพื่อ R, G, B (สี)

    // เติมสีขาว (255, 255, 255) สำหรับพื้นหลัง
    for (int i = 0; i < width * width * 3; ++i) {
        image[i] = 255;  // สีขาว
    }

    // เติมสีดำ (0, 0, 0) สำหรับโมดูล QR Code ที่เป็นสีดำ
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (qr.getModule(x, y)) {
                int offset = (y * width + x) * 3;
                image[offset] = 0;      // สีดำ (R)
                image[offset + 1] = 0;  // สีดำ (G)
                image[offset + 2] = 0;  // สีดำ (B)
            }
        }
    }

    // แสดงข้อความก่อนบันทึก
    std::cout << "Saving QR Code as " << filename << "..." << std::endl;

    // เขียนไฟล์ภาพ QR Code เป็นไฟล์ PNG
    if (stbi_write_png(filename.c_str(), width, width, 3, image, width * 3)) {
        std::cout << "QR Code saved successfully!" << std::endl;
    } else {
        std::cerr << "Failed to save QR Code!" << std::endl;
    }

    delete[] image;
}

int main() {
    // ข้อความที่ต้องการแปลงเป็น QR Code
    std::string data = "https://youtu.be/63OgGno9Jt0?si=-aginIHe0M_J_bGZ";

    // สร้าง QR Code
    const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(data.c_str(), qrcodegen::QrCode::Ecc::LOW);

    // แสดงข้อความว่าเริ่มบันทึก QR Code
    std::cout << "Generating QR Code..." << std::endl;

    // บันทึก QR Code เป็นไฟล์ PNG
    saveQRCodeAsImage(qr, "qrcode.png");

    std::cout << "QR Code saved as qrcode.png" << std::endl;

    return 0;
}
