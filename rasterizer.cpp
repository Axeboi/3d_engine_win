#include <tuple>
#include <functional>
#include <iostream>

#include "olc/olcPixelGameEngine.h"

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;

int min3(int a, int b, int c) { return std::min(std::min(a, b), c); };
int max3(int a, int b, int c) { return std::max(std::max(a, b), c); };

struct Point2d
{
  int x, y;

  void print() { std::cout << x << " " << y << std::endl; };
};

struct Point3d
{
  float x, y, z;
};

int orient2d(const Point2d &a, const Point2d &b, const Point2d &c)
{
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

void drawTriangle(const auto &engine, Point3d input_p1, Point3d input_p2, Point3d input_p3)
{
  // convert from image space (-1 to 1 x, -1 to 1 y) to screen space
  // (coordinate + 1)* (0.5 * screenspace)
  Point2d a, b, c;

  a.x = (input_p1.x + 1) * (0.5 * SCREEN_WIDTH);
  a.y = (input_p1.y + 1) * (0.5 * SCREEN_HEIGHT);

  b.x = (input_p2.x + 1) * (0.5 * SCREEN_WIDTH);
  b.y = (input_p2.y + 1) * (0.5 * SCREEN_HEIGHT);

  c.x = (input_p3.x + 1) * (0.5 * SCREEN_WIDTH);
  c.y = (input_p3.y + 1) * (0.5 * SCREEN_HEIGHT);

  // AABB for triangle
  int minX = min3(a.x, b.x, c.x);
  int minY = min3(a.y, b.y, c.y);
  int maxX = max3(a.x, b.x, c.x);
  int maxY = max3(a.y, b.y, c.y);

  // Clip agains screen boundries
  minX = std::max(minX, 0);
  minY = std::max(minY, 0);
  maxX = std::min(maxX, SCREEN_WIDTH - 1);
  maxY = std::min(maxY, SCREEN_HEIGHT -1);

  Point2d p;
  for (p.x = minX; p.x < maxX; p.x++)
  {
    for (p.y = minY; p.y < maxY; p.y++)
    {
      int w0 = orient2d(b, c, p);
      int w1 = orient2d(c, a, p);
      int w2 = orient2d(a, b, p);
      if (w0 >= 0 && w1 >= 0 && w2 >= 0)
      {
        //renderPixel(p, w0, w1, w2);
        engine.draw(p.x, p.y, olc::Pixel(100, 100, 100, 0));
      }
    }
  }

  // a.print();
  // b.print();
  // c.print();
  // std::cout << minX << " " << minY << " " << maxX << " " << maxY << std::endl;
}


class Engine : public olc::PixelGameEngine
{
public:
	Engine()
	{
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
    a.x = -0.5;
    a.y = -0.5;

    b.x = 0.0;
    b.y = 0.0;

    c.x = 0.5;
    c.y = 0.5;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		// for (int x = 0; x < ScreenWidth(); x++)
		// 	for (int y = 0; y < ScreenHeight(); y++)
		// 		Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));
		return true;
	}

  Point3d a, b, c;
};


int main()
{
	Engine demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}

// int main()
// {
//

//   drawTriangle(a, b, c);
// }







// struct point
// {
//   float x, y;

//   void print() { std::cout << x << " " << y << std::endl; };
//   static std::tuple<float, float> getXY(point p)
//   {
//     return std::make_tuple(p.x, p.y);
//   }
// };


// template <typename P>
// void raster(P &p0, P &p1, P &p2, std::function<std::tuple<float, float> (point)> &&getXY)
// {
//   auto [x0, y0, x1, y1, x2, y2] = std::tuple_cat(getXY(p0), getXY(p1), getXY(p2));

//   // Sort netword to bubble point with smallest y value on top
//   if(std::tie(y1, x1) < std::tie(y0, x0))
//   {
//     std::swap(x0, x1);
//     std::swap(y0, y1);
//     std::swap(p0, p1);
//   }

//   if(std::tie(y2, x2) < std::tie(y0, x0))
//   {
//     std::swap(x2, x0);
//     std::swap(y2, y0);
//     std::swap(p2, p0);
//   }

//   if(std::tie(y2, x2) < std::tie(y1, x1))
//   {
//     std::swap(x2, x1);
//     std::swap(y2, y1);
//     std::swap(p2, p1);
//   }

//   // calculate slope and get short and long slope
// }

// int main()
// {
//   point p0 { 5.0, 6.0 };
//   point p1 { 8.0, 4.0 };
//   point p2 { 10.0, 8.0 };

//   raster(p0, p1, p2, &point::getXY);

// }
