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

            /// @brief destructor
            inline ~Image() {;}

        private:
            std::size_t m_width, m_height;
    };
}
#endif // VIEW_IMAGE_H
