#ifndef IMAGE_H_
#define IMAGE_H_
#include <cstddef>
#include <string>
#include <memory>
#include <Magick++.h>

class Image
{
    public:

        /// @brief constructor passing in width, height of the image
        /// and the depth of the color
        /// @param[in] _width width of the image
        /// @param[in] _height height of the image
        /// @param[in] _depth number of color component

        inline Image(std::size_t _width,
                     std::size_t _height,
                     std::size_t _depth = 3) :
            m_width(_width),
            m_height(_height),
            m_pixelDepth(_depth),
            m_data(new unsigned char[_width * _height * _depth]) {;}

        /// mutators
        /// @brief set the specified pixel to given r, g, b values
        /// @param[in] _x x index for pixel position
        /// @param[in] _y y index for pixel position
        /// @param[in] _r red component
        /// @param[in] _g green component
        /// @param[in] _b blue component

        void setPixel(std::size_t _x,
                      std::size_t _y,
                      unsigned char _r,
                      unsigned char _g,
                      unsigned char _b);        

        /// @brief set the whole image color according to given r, g, b values
        /// @param[in] _r red component
        /// @param[in] _g green component
        /// @param[in] _b blue component

        void clearScreen(unsigned char _r,
                         unsigned char _g,
                         unsigned char _b);

        /// @brief save image to output file
        /// @param[in] _fname name of the output file

        bool save(std::string _fname);

        /// @brief destructor

        inline ~Image() {;}

    private:

        std::size_t m_width;
        std::size_t m_height;
        std::size_t m_pixelDepth;
        std::unique_ptr<unsigned char[]> m_data;

        inline int getIndex (std::size_t _x,
                      std::size_t _y,
                      std::size_t _z) const
        {
            return (_x + m_width * _y) * m_pixelDepth + _z;
        }


};

#endif //IMAGE_H
