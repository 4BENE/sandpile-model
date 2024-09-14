#include <vector>
class Image
{
public:
    int width;
    int height;
    std::vector<uint8_t> colors;
    Image(int width, int height):width(width),height(height),colors(std::vector<uint8_t>(width*height)){};
    uint8_t GetColor(int x, int y) const;
    void SetColor(const uint8_t& color, int x , int y);
    void Export(const char* path) const;
};