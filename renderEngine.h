#pragma once

#include "matrix.h"
#include "vector.h"
#include "mesh.h"
#include <array>
#include <vector>
#include <tuple>
#include "olc/olcPixelGameEngine.h"

#ifndef PI
#define PI    3.14159265358979323846
#endif

double rotation_inc = 0.0;

typedef Vector<double, 4> Vector4;
typedef Matrix<double, 4, 4> Matrix4x4;
typedef Triangle<Vector<double, 4>> Triangle4;
typedef Mesh<Vector<double, 4>> Mesh4;

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
		sAppName = "3d engine";
	}

public:
	bool OnUserCreate() override
	{
		screenBuffer.resize(ScreenHeight());
		for (int i{ 0 }; i < ScreenHeight(); i++)
		{
			screenBuffer[i].resize(ScreenWidth());
			for (int j{ 0 }; j < ScreenWidth(); j++)
			{
				screenBuffer[i][j] = ScreenBuffer();
			}
		}

		mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {-0.5, -0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, -0.5, 1.0}} });
        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {-0.5, -0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, -0.5, -0.5, 1.0}} });

        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.5, -0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, 0.5, 1.0}} });
        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.5, -0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, -0.5, 0.5, 1.0}} });

        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, 0.5, 1.0}} });
        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, -0.5, 0.5, 1.0}} });

        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {-0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, -0.5, 1.0}} });
        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {-0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, -0.5, -0.5, 1.0}} });

        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {-0.5, 0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, 0.5, 1.0}} });
        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {-0.5, 0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, -0.5, 1.0}} });

        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, -0.5, -0.5, 1.0}} });
        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, -0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, -0.5, -0.5, 1.0}} });
        
    // Test triangle. Delete when loading actual tris.
		/*p0.x = -0.5;
		p0.y = -0.5;
		p0.z = -0.5;

		p2.x = 0.0;
		p2.y = 0.5;
		p2.z = -0.5;

		p1.x = 0.5;
		p1.y = -0.5;
		p1.z = -0.5;



		pb0.x = -0.8;
		pb0.y = -0.6;
		pb0.z = -0.7;

		pb2.x = 0.2;
		pb2.y = 0.6;
		pb2.z = -0.6;

		pb1.x = 0.7;
		pb1.y = -0.7;
		pb1.z = -0.6;*/
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        //Clear screen
		Clear(olc::BLACK);
		for (size_t i{ 0 }; i < ScreenHeight(); i++)
		{
			for (size_t j{ 0 }; j < ScreenWidth(); j++)
			{
				screenBuffer[i][j].r = 0;
				screenBuffer[i][j].g = 0;
				screenBuffer[i][j].b = 0;
				screenBuffer[i][j].z = -2;
			}
		}

		camera = std::array<double, 4> { 0.0, 0.0, -1.0, 1.0 }; // Thought I needed this but I don't yet.
        rotation_inc += 0.005;

        Mesh4 transformed_mesh;
        for (Triangle4 &triangle: mesh_cube.tris)
        {
            transformed_mesh.tris.push_back(to_image_space(triangle, camera));
        }

        double halfW = (double) ScreenWidth() / 2.0;
        double halfH = (double) (ScreenHeight() / 2.0);
        
        int counter = 0;
		for (Triangle4& tri : transformed_mesh.tris)
		{
			Vector4 normal = tri.normal();

			if (normal.z() * tri[0].z() > 0.0) // NOTE: This should be tri[0] - camera_position when there's a moving camera to worry about. Otherwise this will only calculate from origin
			{
				Vector4 light_direction{ std::array<double, 4> {0.0, 0.0, -1.0, 0.0} };

				float l = sqrtf(light_direction.x() * light_direction.x() + light_direction.y() * light_direction.y() + light_direction.z() * light_direction.z());
				light_direction[0] /= l; light_direction[1] /= l; light_direction[2] /= l;

				// How similar is normal to light direction
				float dp = normal.x() * light_direction.x() + normal.y() * light_direction.y() + normal.z() * light_direction.z();

				for (Vector4& vec : tri.v)
				{
					vec[0] /= vec[3];
					vec[1] /= vec[3];
					vec[2] /= vec[3];
				}
				drawTriangle(tri[0], tri[1], tri[2], dp);
				output();
			}
		}
		
		//drawTriangle(p0, p1, p2);
		//drawTriangle(pb0, pb1, pb2);
		//output();
		return true;
	}

	void drawTriangle(Vector4& input_p0, Vector4& input_p1, Vector4& input_p2, float col)
	{
		Point3d p0, p1, p2;

		// convert from image space (-1 to 1 x, -1 to 1 y) to screen space
		p0.x = (input_p0.x() + 1) * (0.5 * (ScreenWidth()-1) );
		p0.y = (input_p0.y() + 1) * (0.5 * (ScreenHeight() -1));
		p0.z = input_p0.z();

		p1.x = (input_p1.x() + 1) * (0.5 * (ScreenWidth() -1));
		p1.y = (input_p1.y() + 1) * (0.5 * (ScreenHeight() -1));
		p1.z = input_p0.z();

		p2.x = (input_p2.x() + 1) * (0.5 * (ScreenWidth() -1));
		p2.y = (input_p2.y()+ 1) * (0.5 * (ScreenHeight() -1));
		p2.z = input_p0.z();

		// AABB for triangle
		int minX = min3(p0.x, p1.x, p2.x);
		int minY = min3(p0.y, p1.y, p2.y);
		int maxX = max3(p0.x, p1.x, p2.x);
		int maxY = max3(p0.y, p1.y, p2.y);

		// Clip agains screen boundries
		minX = std::max(minX, 0);
		minY = std::max(minY, 0);
		maxX = std::min(maxX, ScreenWidth() - 1);
		maxY = std::min(maxY, ScreenHeight() - 1);

		Point2d p;
		for (p.y = minY; p.y < maxY; p.y++)
		{
			for (p.x = minX; p.x < maxX; p.x++)
			{
				int w0 = orient2d(p1, p0, p);
				int w1 = orient2d(p0, p2, p);
				int w2 = orient2d(p2, p1, p);
				if (w0 >= 0 && w1 >= 0 && w2 >= 0)
				{
					setImagePixel(p, w0, w1, w2, p0.z, p1.z, p2.z, col);
				}
			}
		}
	}

	void output()
	{
		for (int i = 0; i < ScreenHeight(); i++)
		{
			for (int j = 0; j < ScreenWidth(); j++)
			{
				if (screenBuffer[i][j].r > 0 || screenBuffer[i][j].g > 0 || screenBuffer[i][j].b > 0)
					this->Draw(j, i, olc::Pixel(screenBuffer[i][j].r, screenBuffer[i][j].g, screenBuffer[i][j].b, 255));
			}
		}
	}

	Triangle4 to_image_space(Triangle4 tri, const Vector4 camera)
	{
		Triangle4 new_tri;
		for (uint i{ 0 }; i < 3; i++)
		{
			// ANGLES FOR CAMERA TRANSFORM AND ROTATION TO -Z AXIS:
			//double theta = -std::atan2(tri.v[i].x(), tri.v[i].z());
			//double phi = std::atan2(tri.v[i].y(), std::sqrt((tri.v[i].x() * tri.v[i].x()) + (tri.v[i].y() * tri.v[i].y())));

			double theta = rotation_inc;// * (PI / 16.0);
			//double theta = PI / 4;
			double phi = PI / 128.0;

			double x_data[4 * 4]{
			  1.0, 0, 0, 0,
			  0, std::cos(phi),  std::sin(phi), 0,
			  0, -std::sin(phi), std::cos(phi), 0,
			  0, 0, 0, 1.0
			};

			double y_data[4 * 4]{
			  std::cos(theta),  0, -std::sin(theta), 0,
			  0, 1.0, 0, 0,
			  std::sin(theta), 0, std::cos(theta), 0,
			  0, 0, 0, 1.0
			};

			double z_data[4 * 4]{
			  std::cos(theta), std::sin(theta), 0, 0,
			  -std::sin(theta), std::cos(theta), 0, 0,
			  0, 0, 1.0, 0,
			  0, 0, 0, 1.0
			};

			// double translation[]{
			//   1.0, 0.0, 0.0, 0.0,
			//   0.0, 1.0, 0.0, 0.0,
			//   0.0, 0.0, 1.0, 0.0,
			//   -camera.x(), -camera.y(), -camera.z(), 1.0,
			// };

			double f = 0.1;
			double n = 100.0;
			double fov = PI / 2.0;

			double magic_nr1 = (f + n) / (f - n);
			double magic_nr2 = (2 * f * n) / (f - n);

			double proj[]{
			  (std::cos(fov/2) / std::sin(fov/2)), 0, 0, 0,
			  0, (std::cos(fov/2) / std::sin(fov/2)), 0, 0,
			  0, 0, magic_nr1, -1,
			  0, 0, magic_nr2, 0,
			};


			Matrix4x4 rotate_x{ x_data };
			Matrix4x4 rotate_y{ y_data };
			Matrix4x4 rotate_z{ z_data };
			// Matrix4x4 translate_camera{ translation };
			Matrix4x4 projection{ proj };

			double translation[]{
			  1.0, 0.0, 0.0, 0.0,
			  0.0, 1.0, 0.0, 0.0,
			  0.0, 0.0, 1.0, 0.0,
			  0.0, 0.0, 4.0, 1.0,
			};

			Matrix4x4 translate_matrix { translation };
			Vector4 point = tri[i];
			point[0] *= 2;
			point[1] *= 2;
			point[2] *= 2;

			Vector4 translated_point{ point * (rotate_y * translate_matrix) };

			new_tri[i] = (translated_point * projection);
			//new_tri[i] = (tri.v[i] * (translate_camera * (rotate_x * rotate_y)) * projection);
		}
   
		return new_tri;
	};

	std::vector<std::vector<ScreenBuffer>> screenBuffer;
	Vector4 camera;
    Mesh4 mesh_cube;
  ;

  private:

  void setImagePixel(const Point2d &p, int w0, int w1, int w2, float z0, float z1, float z2, float col)
  {
    float fw0 = (float) w0 / (float) (w0 + w1 + w2);
	float fw1 = (float) w1 / (float) ((w0 + w1 + w2));
	float fw2 = (float) w2 / (float) ((w0 + w1 + w2));

    float z = z0 + (w1 * (z1-z0)) + (w2 * (z2 - z0));

    //
    if (screenBuffer[p.y][p.x].z < z)
    {
		screenBuffer[p.y][p.x].z = z;
		screenBuffer[p.y][p.x].r = col * 255;
		screenBuffer[p.y][p.x].g = col * 255;
		screenBuffer[p.y][p.x].b = col * 255;
        //do Stuff
    }
  
  }

  int orient2d(const Point3d& a, const Point3d& b, const Point2d& c)
  {
    return ((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x));
  }

  int min3(int a, int b, int c) { return std::min(std::min(a, b), c); };
  int max3(int a, int b, int c) { return std::max(std::max(a, b), c); };
};
