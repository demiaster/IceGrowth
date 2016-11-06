#include "Image.h"
#include "lineyielder.h"
#include <cstdlib>
#include <iostream>

// random shits
#include <random>
#include <algorithm>
#include <sstream>

//line things
#define NDEBUG
#include <cassert>

constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;
constexpr int DEPTH = 3;
constexpr float PI = 3.1415926535897;

void rnd(int);

void line(Image &image,
          const int _startX, const int _startY,
          const int _endX, const int _endY,
          const unsigned char _r, const unsigned char _g, const unsigned char _b);

void bhm_line(const Image& image,
              int _x1, int _y1, int _x2, int _y2,
              const unsigned char _r, const unsigned char _g, const unsigned char _b);

void rainbowWheel(const int _line_Number,
                  const int unsigned _x_center, const unsigned int _y_center,
                  const int unsigned _x_end, const unsigned int _y_end);

int main()
{
    std::cout<<"Need to write an Image Class\n";
    Image image(WIDTH, HEIGHT, DEPTH);
    image.clearScreen(67, 189, 242);
    image.save("picture.png");

    //for (int i = 0; i < 50; ++i)
    //    rnd(i);
    // Create a video with: ffmpeg -i picture-$DISTRIBUTION-%d.png output.gif

    //line(100, 100, 800, 800, 255, 0, 0);

    rainbowWheel(200, WIDTH / 2, HEIGHT / 2, 1360, 540);

    return EXIT_SUCCESS;
}

#define NORMAL 1
#ifdef NORMAL
#define DISTRIBUTION std::normal_distribution<double> distribution(128,128)
#define NORMALIZE (unsigned int)distribution(generator) % 255
#define DSTRING "normal"
#elif GAMMA
#define DISTRIBUTION std::gamma_distribution<char> distribution(2.0,2.0)
#define DSTRING "gamma"
#endif //GAMMA

void rnd(const int output)
{
    static std::knuth_b generator;
    DISTRIBUTION;
    Image image(WIDTH, HEIGHT, DEPTH);
    for (unsigned int i = 0; i < WIDTH; ++i)
    {
        for (unsigned int j = 0; j < HEIGHT; ++j)
        {
            //just to get a more blue-ish result :)
            //maybe it gets things much slower
            std::vector<unsigned char> vec;
            vec.push_back(NORMALIZE);
            vec.push_back(NORMALIZE);
            vec.push_back(NORMALIZE);
            std::sort(vec.begin(), vec.begin());

            image.setPixel(i, j, vec.at(0),
                           vec.at(1),
                           vec.at(2));
        }
    }
    std::stringstream ss;
    ss << "picture-" << DSTRING << "-" << output << ".png";
    image.save(ss.str().c_str());
}

/* Breseham's line algorithm
 *  function line(x0, y0, _x1, _y1)
 *    real deltax := _x1 - x0
 *    real deltay := _y1 - y0
 *    real error := -1.0
 *    real deltaerr := abs(deltay / deltax)
 *
 *    // Assume deltax != 0 (line is not vertical),
 *    // note that this division needs to be done
 *    //in a way that preserves the fractional part
 *
 *    int y := y0
 *    for x from x0 to _x1-1
 *        plot(x,y)
 *        error := error + deltaerr
 *        if error ≥ 0.0 then
 *            y := y + 1
 *            error := error - 1.0
 */

//line apparently does not work properly
void line(Image& image,
          const int _startX, const int _startY,
          const int _endX, const int _endY,
          const unsigned char _r,
          const unsigned char _g,
          const unsigned char _b)
{
    //check input validity
    assert(0 < _startX && _startX < WIDTH);
    assert(0 < _endX && _endX < WIDTH);
    assert(0 < _startY && _startY < HEIGHT);
    assert(0 < _endY && _endY < HEIGHT);

    float deltaX = _endX - _startX;
    float deltaY = _endY - _startY;
    float error = -1.0;

    //this algorithm only works for deltaX not zero
    assert(deltaX != 0);
    float deltaErr = std::fabs(deltaY / deltaX);
    int y = _startY;
    for (int x = _startX; x < _endX; ++x)
    {
        image.setPixel(x, y, _r, _g, _b);
        error += deltaErr;
        if (error >= 0.0)
        {
            ++y;
            error -= 1.0;
         }
    }

    return;
}

//same algorithm from
//http://www.etechplanet.com/codesnippets/computer-graphics-draw-a-line-using-bresenham-algorithm.aspx
void bhm_line(Image& image,
              int _x1, int _y1, int _x2, int _y2,
              const unsigned char _r,
              const unsigned char _g,
              const unsigned char _b)
{
     int x, y;
     int dx, dy;
     int d_x1, d_y1;
     int px, py;
     int xe, ye;

     dx = _x2 - _x1;
     dy = _y2 - _y1;
     d_x1 = std::fabs(dx);
     d_y1 = std::fabs(dy);
     px = 2 * d_y1 - d_x1;
     py = 2 * d_x1 - d_y1;

     if (d_y1 <= d_x1)
     {
         if (dx >= 0)
          {
               x = _x1;
               y = _y1;
               xe = _x2;
          }
          else
          {
               x = _x2;
               y = _y2;
               xe = _x1;
          }
          image.setPixel(x, y, _r, _g, _b);

          for (int i = 0; x < xe; ++i)
          {
               ++x;
               if (px < 0)
               {
                    px += 2 * d_y1;
               }
               else
               {
                    if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    {
                        ++y;
                    }
                    else
                    {
                        --y;
                    }
                    px += 2 * (d_y1 - d_x1);
               }
               image.setPixel(x, y, _r, _g, _b);
          }
     }
     else
     {
          if(dy >= 0)
          {
               x = _x1;
               y = _y1;
               ye = _y2;
          }
          else
          {
               x = _x2;
               y = _y2;
               ye = _y1;
          }
          image.setPixel(x, y, _r, _g, _b);

          for (int i = 0; y < ye; ++i)
          {
               ++y;
               if(py <= 0)
               {
                    py += 2 * d_x1;
               }
               else
               {
                   //((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) ? x++ : x--;
                   if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    {
                        ++x;
                    }
                    else
                    {
                        --x;
                    }
                    py += 2 * (d_x1 - d_y1);
               }
               image.setPixel(x, y, _r, _g, _b);
          }
     }
}

void rainbowWheel(const int _line_Number,
                  const int unsigned _x_center, const unsigned int _y_center,
                  const int unsigned _x_end, const unsigned int _y_end)
{
    Image image(WIDTH, HEIGHT);

    //cleaning background
    image.clearScreen(0, 0, 0);

    Point center = Point{_x_center, _y_center};
    Point end_point = Point{_x_end, _y_end};

    float _deg_angle = float(360) / _line_Number;
    float _rad_angle = _deg_angle * PI / 180;

    LineYielder yielder(center, end_point);

    for (int i = 0; i < _line_Number; ++i)
    {
        Point next = yielder.nextLine(_rad_angle);
        bhm_line(image, center.x, center.y, next.x, next.y, 255, 255, 255);
        std::stringstream ss;
        ss << "picture-rainbowlines" << "-" << i << ".png";
        image.save(ss.str().c_str());
    }
    //string path = "$HOME/workspace/lecture4/ImageMagick/";
    system("ffmpeg -i picture-rainbowlines-%d.png rainbowlines.gif");
    system("rm picture-rainbowlines-*");
    system("animate rainbowlines.gif");

}

/* Investigate the use of fmod to create repeating patterns
 *  such as a sphere
 */
void repeatingPatterns()
{

}
