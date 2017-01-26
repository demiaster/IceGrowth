#ifndef VIEW_IMAGE_H_
#define VIEW_IMAGE_H_
#include <cstddef>
#include <string>
#include <memory>
#include <Magick++.h>

#include "grid.h"



namespace view
{
    class Image : public model::Grid<unsigned char, 3>
    {
        public:

            /// @brief constructor passing in width, height of the image
            /// and the depth of the color
            /// @param[in] _width width of the image
            /// @param[in] _height height of the image
            /// @param[in] _depth number of color component
            inline Image(const std::size_t _width,
                         const std::size_t _height,
                         std::size_t _depth = 3) :
                Grid(std::array<std::size_t, 3>{{_width, _height, _depth}}), m_width(_width), m_height(_height) {;}

            /// mutators
            /// @brief set the specified pixel to given r, g, b values
            /// @param[in] _x x index for pixel position
            /// @param[in] _y y index for pixel position
            /// @param[in] _r red component
            /// @param[in] _g green component
            /// @param[in] _b blue component
            void setPixel(const std::size_t _x,
                          const std::size_t _y,
                          const unsigned char _r,
                          const unsigned char _g,
                          const unsigned char _b);

            /// @brief set the whole image color according to given r, g, b values
            /// @param[in] _r red component
            /// @param[in] _g green component
            /// @param[in] _b blue component
            void clearScreen(const unsigned char _r,
                             const unsigned char _g,
                             const unsigned char _b);

            /// not mutators
            /// @brief save image to output file
            /// @param[in] _fname name of the output file
            /// @param[out] true if successfull
            bool save(const std::string _fname);

            /// @brief get array of data
            /// @param[out] array of data
            inline unsigned char* getData() const {return m_data.get();}

            /// @brief save default backgroudn color
            /// @param[in] _r red component
            /// @param[in] _g green component
            /// @param[in] _b blue component
            inline void setBackgroundColor(const unsigned char _r,
                                           const unsigned char _g,
                                           const unsigned char _b)
            {
                m_background.r = _r;
                m_background.g = _g;
                m_background.b = _b;
            }

            /// @brief set the specified pixel to given background color
            /// @param[in] _x x index for pixel position
            /// @param[in] _y y index for pixel position
            inline void resetPixelColor(const std::size_t _x,
                                        const std::size_t _y)
            {
                setPixel(_x, _y, m_background.r, m_background.g, m_background.b);
            }

            /// @brief destructor
            inline ~Image() {;}

            // http://stackoverflow.com/questions/702658/c-union-array-and-vars
            union Color {
              struct {
                unsigned char r;
                unsigned char g;
                unsigned char b;
              };
              unsigned char array[3];
            };

        private:
            std::size_t m_width, m_height;
            Color m_background;
    };
}
#endif // VIEW_IMAGE_H
