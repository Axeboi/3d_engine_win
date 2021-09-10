#pragma once

#include <array>
#include <vector>
#include <tuple>
#include "olc/olcPixelGameEngine.h"

struct Point2d
{
	int x, y;

	void print() { std::cout << x << " " << y << std::endl; };
};

struct Point3d
{
	float x, y, z;
};

struct ScreenBuffer
{
  unsigned int r, g, b;
  float z;
};


class RenderEngine : public olc::PixelGameEngine
{
public:
	RenderEngine()
	{
    screenBuffer[ScreenHeight() * ScreenWidth()];
		sAppName = "3d engine";
	}

public:
	bool OnUserCreate() override
	{
    // Test triangle. Delete when loading actual tris.
		p0.x = -0.5;
		p0.y = -0.5;

		p2.x = 0.0;
		p2.y = 0.5;

		p1.x = 0.5;
		p1.y = -0.5;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
    screenBuffer[ScreenHeight()][ScreenWidth()];

    for (size_t i {0}; i < ScreenHeight(); i++)
    {
      for (size_t j {0}; j < ScreenWidth(); j++)
      {
        screenBuffer[i][j].r = 0;
        screenBuffer[i][j].g = 0;
        screenBuffer[i][j].b = 0;
        screenBuffer[i][j].z = -2; // Setting this to a value that is beyond far plane in image space. Might cause bug.
      }
    }
    
		drawTriangle(p0, p1, p2);
		return true;
	}

	void drawTriangle(Point3d input_p0, Point3d input_p1, Point3d input_p2)
	{
		Point2d a, b, c;

		// convert from image space (-1 to 1 x, -1 to 1 y) to screen space
		p0.x = (input_p0.x + 1) * (0.5 * (ScreenWidth()-1) );
		p0.y = (input_p0.y + 1) * (0.5 * (ScreenHeight() -1));

		p1.x = (input_p1.x + 1) * (0.5 * (ScreenWidth() -1));
		p1.y = (input_p1.y + 1) * (0.5 * (ScreenHeight() -1));

		p2.x = (input_p2.x + 1) * (0.5 * (ScreenWidth() -1));
		p2.y = (input_p2.y + 1) * (0.5 * (ScreenHeight() -1));

		// AABB for triangle
		int minX = min3(p0.x, p1.x, p2.x);
		int minY = min3(p0.y, p1.y, p2.y);
		int maxX = max3(p0.x, p1.x, p2.x);
		int maxY = max3(p0.y, p1.y, p2.y);

		// Clip agains screen boundries
		minX = std::max(minX, 0);
		minY = std::max(minY, 0);
		maxX = std::min(maxX, ScreenHeight() - 1);
		maxY = std::min(maxY, ScreenWidth() - 1);

		Point2d p;
		for (p.y = minY; p.y < maxY; p.y++)
		{
			for (p.x = minX; p.x < maxX; p.x++)
			{
				int w0 = orient2d(p1, p2, p);
				int w1 = orient2d(p2, p0, p);
				int w2 = orient2d(p0, p1, p);
				if (w0 >= 0 && w1 >= 0 && w2 >= 0)
				{
					setImagePixel(p, w0, w1, w2, p0.z, p1.z, p2.z);
					
					// float red = fw0*255;
					// float green = fw1 * 255;
					// float blue = fw2 * 255;
					
					//Draw(p.x, p.y, olc::Pixel(100, 100, 100, 0));
					//this->Draw(p.x, p.y, olc::Pixel(red, green, blue, 255));
				}
			}
		}

		// a.print();
		// b.print();
		// c.print();
		// std::cout << minX << " " << minY << " " << maxX << " " << maxY << std::endl;
	}

	void draw()
	{
		for (int i = 0; i < ScreenHeight(); i++)
		{
			for (int j = 0; j < ScreenWidth(); j++)
			{
				this->Draw(i, j, olc::Pixel(screenBuffer[i][j].r, screenBuffer[i][j].b, screenBuffer[i][j].b, 255));

			}
		}
	}

	Point3d p0, p1, p2;
  std::vector<std::vector<ScreenBuffer> > screenBuffer
  ;

  private:

  void setImagePixel(const Point2d &p, int w0, int w1, int w2, float z0, float z1, float z2)
  {
    float fw0 = (float) w0 / (float) (w0 + w1 + w2);
		float fw1 = (float) w1 / (float) ((w0 + w1 + w2));
		float fw2 = (float) w2 / (float) ((w0 + w1 + w2));

    float z = z0 + (w1 * (z1-z0)) + (w2 * (z2 - z0));

    for (size_t height {0}; height < ScreenHeight(); height++)
    {
      for (size_t width {0}; width < ScreenWidth(); width++)
      {
        if (screenBuffer[height][width].z < z)
        {
          screenBuffer[height][width].z = z;
          screenBuffer[height][width].r = w0*255;
          screenBuffer[height][width].b = w1*255;
          screenBuffer[height][width].g = w2*255;
          //do Stuff
        }
      }
    }
  }

  int orient2d(const Point3d& a, const Point3d& b, const Point2d& c)
  {
    return ((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x));
  }

  int min3(int a, int b, int c) { return std::min(std::min(a, b), c); };
  int max3(int a, int b, int c) { return std::max(std::max(a, b), c); };
};
