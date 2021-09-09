#define OLC_PGE_APPLICATION

#include <tuple>
#include <functional>
#include <iostream>

#include "olc/olcPixelGameEngine.h"

//const int SCREEN_WIDTH = 320;
//const int SCREEN_HEIGHT = 240;


struct Point2d
{
	int x, y;

	void print() { std::cout << x << " " << y << std::endl; };
};

struct Point3d
{
	float x, y, z;
};

int orient2d(const Point2d& a, const Point2d& b, const Point2d& c)
{
	int ret = ((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x));
	return ret;
}

class Engine;
//void drawTriangle(const Engine*, Point3d, Point3d, Point3d);

int min3(int a, int b, int c) { return std::min(std::min(a, b), c); };
int max3(int a, int b, int c) { return std::max(std::max(a, b), c); };


class Engine : public olc::PixelGameEngine
{
public:
	Engine()
	{
		sAppName = "3d engine";
	}

public:
	bool OnUserCreate() override
	{
		// Counter clockwise triangle
		/*p0.x = -0.5;
		p0.y = -0.5;

		p1.x = 0.5;
		p1.y = -0.5;

		p2.x = 0.25;
		p2.y = 0.0;*/

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
		drawTriangle(p0, p1, p2);
		return true;
	}

	void drawTriangle(Point3d input_p1, Point3d input_p2, Point3d input_p3)
	{
		// convert from image space (-1 to 1 x, -1 to 1 y) to screen space
		// (coordinate + 1)* (0.5 * screenspace)
		Point2d a, b, c;

		/*a.x = input_p1.x;
		a.y = input_p1.y;

		b.x = input_p2.x;
		b.y = input_p2.y;

		c.x = input_p3.x;
		c.y = input_p3.y;*/
		a.x = (input_p1.x + 1) * (0.5 * (ScreenWidth()-1) );
		a.y = (input_p1.y + 1) * (0.5 * (ScreenHeight() -1));

		b.x = (input_p2.x + 1) * (0.5 * (ScreenWidth() -1));
		b.y = (input_p2.y + 1) * (0.5 * (ScreenHeight() -1));

		c.x = (input_p3.x + 1) * (0.5 * (ScreenWidth() -1));
		c.y = (input_p3.y + 1) * (0.5 * (ScreenHeight() -1));

		// AABB for triangle
		int minX = min3(a.x, b.x, c.x);
		int minY = min3(a.y, b.y, c.y);
		int maxX = max3(a.x, b.x, c.x);
		int maxY = max3(a.y, b.y, c.y);

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
				int w0 = orient2d(b, c, p);
				int w1 = orient2d(c, a, p);
				int w2 = orient2d(a, b, p);
				if (w0 >= 0 && w1 >= 0 && w2 >= 0)
				{
					//renderPixel(p, w0, w1, w2);
					
					float fw0 = (float) w0 / (float) (w0 + w1 + w2);
					float fw1 = (float) w1 / (float) ((w0 + w1 + w2));
					float fw2 = (float) w2 / (float) ((w0 + w1 + w2));

					float red = fw0*255;
					float green = fw1 * 255;
					float blue = fw2 * 255;
					
					//Draw(p.x, p.y, olc::Pixel(100, 100, 100, 0));
					this->Draw(p.x, p.y, olc::Pixel(red, green, blue, 255));
				}
			}
		}

		// a.print();
		// b.print();
		// c.print();
		// std::cout << minX << " " << minY << " " << maxX << " " << maxY << std::endl;
	}

	Point3d p0, p1, p2;
};









int main()
{
	Engine demo;
	if (demo.Construct(640, 480, 1, 1))
		demo.Start();

	return 0;
}








//#include "matrix.h"
//#include "vector.h"
//#include "mesh.h"
//#include "olc/olcConsoleGameEngine.h"
//#include <iostream>
//#include <cmath>
//#include <vector>
//
//#ifndef PI
//#define PI    3.14159265358979323846
//#endif
//
//double rotation_inc = 0.0;
//
//typedef Vector<double, 4> Vector4;
//typedef Matrix<double, 4, 4> Matrix4x4;
//typedef Triangle<Vector<double, 4>> Triangle4;
//typedef Mesh<Vector<double, 4>> Mesh4;
//
//Triangle4 to_image_space(Triangle4 tri, const Vector4 camera)
//{
//    Triangle4 new_tri;
//    for (uint i{ 0 }; i < 3; i++)
//    {
//        // ANGLES FOR CAMERA TRANSFORM AND ROTATION TO -Z AXIS:
//        //double theta = -std::atan2(tri.v[i].x(), tri.v[i].z());
//        //double phi = std::atan2(tri.v[i].y(), std::sqrt((tri.v[i].x() * tri.v[i].x()) + (tri.v[i].y() * tri.v[i].y())));
//
//        double theta = rotation_inc;// * (PI / 16.0);
//        //double theta = PI / 4;
//        double phi = PI / 128.0;
//
//        double x_data[4 * 4]{
//          1.0, 0, 0, 0,
//          0, std::cos(phi),  std::sin(phi), 0,
//          0, -std::sin(phi), std::cos(phi), 0,
//          0, 0, 0, 1.0
//        };
//
//        double y_data[4 * 4]{
//          std::cos(theta),  0, -std::sin(theta), 0,
//          0, 1.0, 0, 0,
//          std::sin(theta), 0, std::cos(theta), 0,
//          0, 0, 0, 1.0
//        };
//
//        double z_data[4 * 4]{
//          std::cos(theta), std::sin(theta), 0, 0,
//          -std::sin(theta), std::cos(theta), 0, 0,
//          0, 0, 1.0, 0,
//          0, 0, 0, 1.0
//        };
//
//        // double translation[]{
//        //   1.0, 0.0, 0.0, 0.0,
//        //   0.0, 1.0, 0.0, 0.0,
//        //   0.0, 0.0, 1.0, 0.0,
//        //   -camera.x(), -camera.y(), -camera.z(), 1.0,
//        // };
//
//        double f = 0.1;
//        double n = 100.0;
//        double fov = PI / 2.0;
//
//        double magic_nr1 = (f + n) / (f - n);
//        double magic_nr2 = (2 * f * n) / (f - n);
//
//        double proj[]{
//          (std::cos(fov/2) / std::sin(fov/2)), 0, 0, 0,
//          0, (std::cos(fov/2) / std::sin(fov/2)), 0, 0,
//          0, 0, magic_nr1, -1,
//          0, 0, magic_nr2, 0,
//        };
//
//
//        Matrix4x4 rotate_x{ x_data };
//        Matrix4x4 rotate_y{ y_data };
//        Matrix4x4 rotate_z{ z_data };
//        // Matrix4x4 translate_camera{ translation };
//        Matrix4x4 projection{ proj };
//
//        double translation[]{
//          1.0, 0.0, 0.0, 0.0,
//          0.0, 1.0, 0.0, 0.0,
//          0.0, 0.0, 1.0, 0.0,
//          0.0, 0.0, 4.0, 1.0,
//        };
//
//        Matrix4x4 translate_matrix { translation };
//        Vector4 point = tri[i];
//        point[0] *= 2;
//        point[1] *= 2;
//        point[2] *= 2;
//
//        Vector4 translated_point{ point * (rotate_y * translate_matrix) };
//
//        new_tri[i] = (translated_point * projection);
//        //new_tri[i] = (tri.v[i] * (translate_camera * (rotate_x * rotate_y)) * projection);
//    }
//   
//    return new_tri;
//};
//
//class olcEngine3D : public olcConsoleGameEngine
//{
//public:
//    olcEngine3D() { m_sAppName = L"3D Render"; }
//
//private:
//    Vector4 camera;
//    Mesh4 mesh_cube;
//
//    bool OnUserCreate() override
//    {
//        camera = std::array<double, 4> { 0.0, 0.0, -1.0, 1.0 };
//
//        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {-0.5, -0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, -0.5, 1.0}} });
//        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {-0.5, -0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, -0.5, -0.5, 1.0}} });
//
//        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.5, -0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, 0.5, 1.0}} });
//        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.5, -0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, -0.5, 0.5, 1.0}} });
//
//        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, 0.5, 1.0}} });
//        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, -0.5, 0.5, 1.0}} });
//
//        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {-0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, -0.5, 1.0}} });
//        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {-0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, -0.5, -0.5, 1.0}} });
//
//        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {-0.5, 0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, 0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, 0.5, 1.0}} });
//        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {-0.5, 0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, 0.5, -0.5, 1.0}} });
//
//        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, -0.5, -0.5, 1.0}} });
//        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.5, -0.5, 0.5, 1.0}}, Vector4 { std::array<double, 4> {-0.5, -0.5, -0.5, 1.0}}, Vector4 { std::array<double, 4> {0.5, -0.5, -0.5, 1.0}} });
//        
//        return true;
//    }
//
//    CHAR_INFO GetColour(float lum)
//    {
//        short bg_col, fg_col;
//        wchar_t sym;
//        int pixel_bw = (int)(13.0f * lum);
//        switch (pixel_bw)
//        {
//        case 0: bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID; break;
//
//        case 1: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_QUARTER; break;
//        case 2: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_HALF; break;
//        case 3: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_THREEQUARTERS; break;
//        case 4: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_SOLID; break;
//
//        case 5: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_QUARTER; break;
//        case 6: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_HALF; break;
//        case 7: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_THREEQUARTERS; break;
//        case 8: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_SOLID; break;
//
//        case 9:  bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_QUARTER; break;
//        case 10: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_HALF; break;
//        case 11: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_THREEQUARTERS; break;
//        case 12: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_SOLID; break;
//        default:
//            bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID;
//        }
//
//        CHAR_INFO c;
//        c.Attributes = bg_col | fg_col;
//        c.Char.UnicodeChar = sym;
//        return c;
//    }
//
//    bool OnUserUpdate(float fElapsedTime) override
//    {
//        //Clear screen
//        Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);
//
//        rotation_inc += 0.01;
//
//        Mesh4 transformed_mesh;
//        for (Triangle4 &triangle: mesh_cube.tris)
//        {
//            transformed_mesh.tris.push_back(to_image_space(triangle, camera));
//        }
//
//        double halfW = (double) ScreenWidth() / 2.0;
//        double halfH = (double) (ScreenHeight() / 2.0);
//        
//        int counter = 0;
//        for (Triangle4 &tri : transformed_mesh.tris)
//        {
//            Vector4 normal = tri.normal();
//             
//            if (normal.z() * tri[0].z() > 0.0) // NOTE: This should be tri[0] - camera_position when there's a moving camera to worry about. Otherwise this will only calculate from origin
//            {
//                Vector4 light_direction{ std::array<double, 4> {0.0, 0.0, -1.0, 0.0} };
//
//                float l = sqrtf(light_direction.x() * light_direction.x() + light_direction.y() * light_direction.y() + light_direction.z() * light_direction.z());
//                light_direction[0] /= l; light_direction[1] /= l; light_direction[2] /= l;
//
//                // How similar is normal to light direction
//                float dp = normal.x() * light_direction.x() + normal.y() * light_direction.y() + normal.z() * light_direction.z();
//
//                CHAR_INFO c = GetColour(dp);
//                tri.col = c.Attributes;
//                tri.sym = c.Char.UnicodeChar;
//
//                for (Vector4& vec : tri.v)
//                {
//                    double temp = 0.0;
//                    temp = vec[0] / vec[3];
//                    vec[0] = temp;
//                    temp = vec[1] / vec[3];
//                    vec[1] = temp;
//                    temp = vec[2] / vec[3];
//                    vec[2] = temp;
//
//                }
//
//                FillTriangle((tri[0].x() * halfW) + halfW, (tri[0].y() * halfH) + halfH,
//                    (tri[1].x() * halfW) + halfW, (tri[1].y() * halfH) + halfH,
//                    (tri[2].x() * halfW) + halfW, (tri[2].y() * halfH) + halfH,
//                    tri.sym,
//                    tri.col
//                );
//
//                //DrawLine((tri[0].x() * halfW) + halfW, (tri[0].y() * halfH) + halfH, (normal_x * halfW) + halfW, (normal_y*halfH) + halfH, PIXEL_SOLID, FG_RED);
//                //DrawLine((tri[0].x() * halfW) + halfW, (tri[0].y() * halfH) + halfH, (tri[1].x() * halfW) + halfW, (tri[1].y() * halfH) + halfH, PIXEL_SOLID, FG_WHITE);
//                //DrawLine((tri[1].x() * halfW) + halfW, (tri[1].y() * halfH) + halfH, (tri[2].x() * halfW) + halfW, (tri[2].y() * halfH) + halfH, PIXEL_SOLID, FG_WHITE);
//                //DrawLine((tri[2].x() * halfW) + halfW, (tri[2].y() * halfH) + halfH, (tri[0].x() * halfW) + halfW, (tri[0].y() * halfH) + halfH, PIXEL_SOLID, FG_WHITE);
//            }
//        }
//
//        return true;
//    }
//};
//
//int main()
//{
//    olcEngine3D app;
//    if (app.ConstructConsole(320, 240, 2, 2))
//        app.Start();
//    else
//        return -1;
//    return 0;
//}
//
