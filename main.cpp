#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "font8x8.h"

using namespace std;

const string ASCII_CHARS = "@%#*+=-:. ";

void imageInput(unsigned char* &imgData, int &width, int &height, int &channels){
    string imagePath;
    cout<<"Nhap duong dan file anh: ";
    cin>>imagePath;
    imgData = stbi_load(imagePath.c_str(), &width, &height, &channels, 3);
    if (imgData == nullptr) {
        cout << "Loi: Khong the mo file anh! Kiem tra lai ten file." << endl;
        exit(1);
    }
}

vector<vector<char>> turnToAsciiImage(int width, int height, unsigned char* imgData){
    vector<vector<char>> asciiImage(height, vector<char>(width));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pixelIndex = (y * width + x) * 3;
            int r = imgData[pixelIndex];
            int g = imgData[pixelIndex + 1];
            int b = imgData[pixelIndex + 2];
            float brightness = (r + g + b) / 3.0f;
            int mapIndex = (brightness / 255.0f) * (ASCII_CHARS.length() - 1);
            asciiImage[y][x] = ASCII_CHARS[mapIndex];
        }
    }
    return asciiImage;
}

void outputAsciiImage(vector<vector<char>> asciiImage){
    for (int y = 0; y < asciiImage.size(); y++) {
        for (int x = 0; x < asciiImage[y].size(); x++) {
            cout << asciiImage[y][x];
        }
        cout << endl;
    }
}

void saveToFile(vector<vector<char>> asciiImage, string filename){
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the tao file output!" << endl;
        return;
    }

    for (int y = 0; y < asciiImage.size(); y++) {
        for (int x = 0; x < asciiImage[y].size(); x++) {
            file << asciiImage[y][x];
        }
        file << endl;
    }
    
    file.close();
    cout << "Da luu ket qua vao file: " << filename << endl;
}

void saveAsciiToImage(vector<vector<char>> asciiImage, string filename) {
    int height = asciiImage.size();
    if (height == 0) return;
    int width = asciiImage[0].size();

    int imgWidth = width * 8;
    int imgHeight = height * 8;
    int channels = 1; // Grayscale

    // Allocate memory for the image (initially all black)
    unsigned char* pixels = (unsigned char*)calloc(imgWidth * imgHeight * channels, sizeof(unsigned char));

    if (!pixels) {
        cout << "Loi: Khong du bo nho de tao anh!" << endl;
        return;
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char c = asciiImage[y][x];
            const unsigned char* fontChar = font8x8_basic[(unsigned char)c];
            for (int fy = 0; fy < 8; fy++) {
                for (int fx = 0; fx < 8; fx++) {
                    if (fontChar[fy] & (1 << fx)) {
                        int px = x * 8 + fx;
                        int py = y * 8 + fy;
                        int index = (py * imgWidth + px) * channels;
                        pixels[index] = 255;
                    }
                }
            }
        }
    }

    stbi_write_jpg(filename.c_str(), imgWidth, imgHeight, channels, pixels, 100);
    free(pixels);
    cout << "Da luu anh JPG vao file: " << filename << endl;
}

int main() {
    int width, height, channels;
    unsigned char* imgData;
    
    imageInput(imgData, width, height, channels);
    
    cout << "Da load anh thanh cong! Kich thuoc: " << width << "x" << height << endl;
    cout << "Dang chuyen doi..." << endl << endl;
    
    vector<vector<char>> asciiImage = turnToAsciiImage(width, height, imgData);
    string output;
    cout<<"Nhap duong dan file output: ";
    cin>>output;
    saveToFile(asciiImage, output);
    saveAsciiToImage(asciiImage, output);
    stbi_image_free(imgData);
    return 0;
}