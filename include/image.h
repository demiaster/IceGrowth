#ifndef VIEW_IMAGE_H_
#define VIEW_IMAGE_H_
/// @file image.h
/// @brief this class produces png, jpg ... images

#include <cstddef>
#include <string>
#include <memory>
#include <Magick++.h>

#include "grid.h"
#include "color.h"

namespace view
{

///----------------------------------------------------------------------------
/// @class Image "include/image.h"
/// @author Marta Feriani
/// @brief inherits from base class Grid, implements method to set, or
/// change colours on an image, as well as save it on disk
///----------------------------------------------------------------------------
class Image : public model::Grid<unsigned char, 3>
{
public:

    ///------------------------------------------------------------------------
    /// @brief constructor passing in width, height of the image
    /// and the depth of the color
    /// @param[in] _width width of the image
    /// @param[in] _height height of the image
    /// @param[in] _depth number of color component
    ///------------------------------------------------------------------------
    inline Image(const std::size_t _width,
                 const std::size_t _height,
                 std::size_t _depth = 4) :
                                Grid(std::array<std::size_t, 3>{{_width,
                                                                 _height,
                                                                 _depth}}),
                                m_width(_width),
                                m_height(_height) {;}

    /// mutators
    /// -----------------------------------------------------------------------
    /// @brief set the specified pixel to given r, g, b values
    /// @param[in] _x x index for pixel position
    /// @param[in] _y y index for pixel position
    /// @param[in] _r red component
    /// @param[in] _g green component
    /// @param[in] _b blue component
    /// @param[in] _a alpha channel
    /// -----------------------------------------------------------------------
    void setPixel(const std::size_t _x,
                  const std::size_t _y,
                  const unsigned char _r,
                  const unsigned char _g,
                  const unsigned char _b,
                  const unsigned char _a);

    ///------------------------------------------------------------------------
    /// @brief set the whole image color according to given r, g, b values
    /// @param[in] _r red component
    /// @param[in] _g green component
    /// @param[in] _b blue component
    /// @param[in] _a alpha channel
    /// -----------------------------------------------------------------------
    void clearScreen(const unsigned char _r,
                     const unsigned char _g,
                     const unsigned char _b,
                     const unsigned char _a);

    /// non mutators
    /// -----------------------------------------------------------------------
    /// @brief save image to output file
    /// @param[in] _fname name of the output file
    /// @param[out] true if successfull
    /// -----------------------------------------------------------------------
    bool save(const std::string _fname);

    /// @brief get array of data
    /// @param[out] array of data
    inline unsigned char* getData() const {return m_data.get();}

    ///------------------------------------------------------------------------
    /// @brief save default backgroudn color
    /// @param[in] _r red component
    /// @param[in] _g green component
    /// @param[in] _b blue component
    /// @param[in] _a alpha channel
    ///------------------------------------------------------------------------
    inline void setBackgroundColor(const unsigned char _r,
                                   const unsigned char _g,
                                   const unsigned char _b,
                                   const unsigned char _a)
    {
        m_background.r = _r;
        m_background.g = _g;
        m_background.b = _b;
        m_background.a = _a;
    }

    ///------------------------------------------------------------------------
    /// @brief set the specified pixel to given background color
    /// @param[in] _x x index for pixel position
    /// @param[in] _y y index for pixel position
    /// -----------------------------------------------------------------------
    inline void resetPixelColor(const std::size_t _x,
                                const std::size_t _y)
    {
        setPixel(_x, _y, m_background.r, m_background.g,
                 m_background.b, m_background.a);
    }

    ///------------------------------------------------------------------------
    /// @brief destructor
    ///------------------------------------------------------------------------
    inline ~Image() {;}

private:

    /// -----------------------------------------------------------------------
    /// @brief width of the grid
    /// -----------------------------------------------------------------------
    std::size_t m_width;

    /// -----------------------------------------------------------------------
    /// @brief height of the grid
    /// -----------------------------------------------------------------------
    std::size_t m_height;

    /// -----------------------------------------------------------------------
    /// @brief color for the background
    /// -----------------------------------------------------------------------
    Color m_background;
};
} // end namespace view
#endif // VIEW_IMAGE_H
