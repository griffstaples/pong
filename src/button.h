
#include <cstdint>
#include <string>

class Button
{
private:
    uint16_t width;
    uint16_t height;
    uint8_t borderRadius;
    uint8_t fontSize;
    uint8_t paddingX;
    uint8_t paddingY;
    std::string text;

public:
    Button(std::string text, uint8_t fontSize, uint8_t width, uint8_t height, uint8_t borderRadius, uint8_t paddingX, uint8_t paddingY);
    void updateButton(std::string text, uint8_t fontSize, uint8_t width, uint8_t height, uint8_t borderRadius, uint8_t paddingX, uint8_t paddingY);
    void render();
};