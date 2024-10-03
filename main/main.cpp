#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#pragma pack(push, 1)

struct BMPFileHeader 
{
    uint16_t file_type{ 0x4D42 };          // Тип файла BMP, константа 0x4D42
    uint32_t file_size{ 0 };               // Размер файла в байтах
    uint16_t reserved1{ 0 };               // Зарезервировано, всегда 0
    uint16_t reserved2{ 0 };               // Зарезервировано, всегда 0
    uint32_t offset_data{ 0 };             // Начальная позиция пикселя (в байтах от начала файла)
};
#pragma pack(pop)

#pragma pack(push, 1)

struct BMPInfoHeader 
{
    uint32_t size{ 0 };                      // Размер заголовка в байтах
    int32_t width{ 0 };                      // Ширина изображения в пикселях
    int32_t height{ 0 };                     // Высота изображения в пикселях
    uint16_t planes{ 1 };                    // Метаданные изображения
    uint16_t bit_count{ 0 };                 // 
    uint32_t compression{ 0 };               // 
    uint32_t size_image{ 0 };                //
    int32_t x_pixels_per_meter{ 0 };         //
    int32_t y_pixels_per_meter{ 0 };         //
    uint32_t colors_used{ 0 };               // 
    uint32_t colors_important{ 0 };          //
};
#pragma pack(pop)

BMPFileHeader file_header;
BMPInfoHeader info;
vector<unsigned char> raw;

void set_pixel(int x, int y, int r, int g, int b) 
{
    raw[3 * (y * info.width + x) + 0] = b;
    raw[3 * (y * info.width + x) + 1] = g;
    raw[3 * (y * info.width + x) + 2] = r;
}

int get_red(int x, int y) 
{
    return raw[3 * (y * info.width + x) + 2];
}

int get_green(int x, int y) 
{
    return raw[3 * (y * info.width + x) + 1];
}

int get_blue(int x, int y) 
{
    return raw[3 * (y * info.width + x) + 0];
}

int main() 
{
    ifstream img("floppa.bmp", ios::in | ios::binary);
    img.read((char*)&file_header, sizeof(file_header));
    img.read((char*)&info, sizeof(info));

    img.seekg(file_header.offset_data, ios::beg);

    raw.resize(info.width * info.height * info.bit_count / 8);
    img.read((char*)raw.data(), raw.size());

    for (int y = 20; y < 400; y += 40)
    {
        for (int x = 20; x < 400; y += 40)
        {
            for (int i = x; i < i + 20; i++)
            {
                set_pixel(i, y, 0, 0, 255);
            }
        }
    }

    ofstream out("result.bmp", ios::binary);

    out.write((const char*)&file_header, sizeof(file_header));
    out.write((const char*)&info, sizeof(info));
    out.write((const char*)raw.data(), raw.size());

    out.close();

    return 0;
}