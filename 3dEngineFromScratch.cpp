#include "matrix.h"
#include "vector.h"
#include "mesh.h"
#include "olc/olcConsoleGameEngine.h"
#include <iostream>
#include <cmath>
#include <vector>

#ifndef PI
#define PI    3.14159265358979323846
#endif


typedef Vector<double, 4> Vector4;
typedef Matrix<double, 4, 4> Matrix4x4;
typedef Triangle<Vector<double, 4>> Triangle4;
typedef Mesh<Vector<double, 4>> Mesh4;

Triangle4 to_image_space(Triangle4 tri, const Vector4 camera)
{
    Triangle4 new_tri;
    for (uint i{ 0 }; i < 3; i++)
    {
        //Vector4 vertex = tri.v[i];
        double theta = -std::atan2(tri.v[i].x(), tri.v[i].z());
        double phi = std::atan2(tri.v[i].y(), std::sqrt((tri.v[i].x() * tri.v[i].x()) + (tri.v[i].y() * tri.v[i].y())));

        double x_data[4 * 4]{
          1.0, 0, 0, 0,
          0, std::cos(phi),  std::sin(phi), 0,
          0, -std::sin(phi), std::cos(phi), 0,
          0, 0, 0, 1.0
        };

        double y_data[4 * 4]{
          std::cos(theta),  0, -std::sin(theta), 0,
          0, 1.0, 0, 0,
          std::sin(theta), std::cos(theta), 0, 0,
          0, 0, 0, 1.0
        };

        double z_data[4 * 4]{
          std::cos(theta), std::sin(theta), 0, 0,
          -std::sin(theta), std::cos(theta), 0, 0,
          0, 0, 1.0, 0,
          0, 0, 0, 1.0
        };

        double translation[]{
          1.0, 0.0, 0.0, 0.0,
          0.0, 1.0, 0.0, 0.0,
          0.0, 0.0, 1.0, 0.0,
          -camera.x(), -camera.y(), -camera.z(), 1.0,
        };

        double f = 0.1;
        double n = 1000.0;
        double fov = PI / 4;

        double magic_nr1 = (f + n) / (f - n);
        double magic_nr2 = (2 * f * n) / (f - n);

        double proj[]{
          std::cos(fov) / std::sin(fov), 0, 0, 0,
          0, std::cos(fov) / std::sin(fov), 0, 0,
          0, 0, magic_nr1, -1,
          0, 0, magic_nr2, 0,
        };

        Matrix4x4 rotate_x{ x_data };
        Matrix4x4 rotate_y{ y_data };
        Matrix4x4 rotate_z{ z_data };
        Matrix4x4 translate_camera{ translation };
        Matrix4x4 projection{ proj };

        //new_tri[i] = (tri.v[i] * (translate_camera * (rotate_x * rotate_y)) * projection);
        new_tri[i] = (tri[i] *  projection);
    }
   
    return new_tri;
};

class olcEngine3D : public olcConsoleGameEngine
{
public:
    olcEngine3D() { m_sAppName = L"3D Render"; }

private:
    Vector4 camera;
    Mesh4 mesh_cube;

    bool OnUserCreate() override
    {
        camera = std::array<double, 4> { 0.0, 0.0, -1.0, 1.0 };

        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.0f, 0.0f, 0.0f, 1.0f}}, Vector4 { std::array<double, 4> {0.0f, 1.0f, 0.0f, 1.0f}}, Vector4 { std::array<double, 4> {1.0f, 1.0f, 0.0f, 1.0f}} });
        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.0f, 0.0f, 0.0f, 1.0f}}, Vector4 { std::array<double, 4> {0.0f, 1.0f, 0.0f, 1.0f}}, Vector4 { std::array<double, 4> {1.0f, 1.0f, 0.0f, 1.0f}} });

        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.0f, 0.0f, 0.0f, 1.0f}}, Vector4 { std::array<double, 4> {1.0f, 1.0f, 0.0f, 1.0f}}, Vector4 { std::array<double, 4> {1.0f, 0.0f, 0.0f, 1.0f}} });
        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {1.0f, 0.0f, 0.0f, 1.0f}}, Vector4 { std::array<double, 4> {1.0f, 1.0f, 1.0f, 1.0f}}, Vector4 { std::array<double, 4> {1.0f, 0.0f, 1.0f, 1.0f}} });

        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {1.0f, 0.0f, 1.0f, 1.0f}}, Vector4 { std::array<double, 4> {1.0f, 1.0f, 1.0f, 1.0f}}, Vector4 { std::array<double, 4> {0.0f, 1.0f, 1.0f, 1.0f}} });
        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {1.0f, 0.0f, 1.0f, 1.0f}}, Vector4 { std::array<double, 4> {0.0f, 1.0f, 1.0f, 1.0f}}, Vector4 { std::array<double, 4> {0.0f, 0.0f, 1.0f, 1.0f}} });

        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.0f, 0.0f, 1.0f, 1.0f}}, Vector4 { std::array<double, 4> {0.0f, 1.0f, 1.0f, 1.0f}}, Vector4 { std::array<double, 4> {0.0f, 1.0f, 0.0f, 1.0f}} });
        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.0f, 0.0f, 1.0f, 1.0f}}, Vector4 { std::array<double, 4> {0.0f, 1.0f, 0.0f, 1.0f}}, Vector4 { std::array<double, 4> {0.0f, 0.0f, 0.0f, 1.0f}} });

        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.0f, 1.0f, 0.0f, 1.0f}}, Vector4 { std::array<double, 4> {0.0f, 1.0f, 1.0f, 1.0f}}, Vector4 { std::array<double, 4> {1.0f, 1.0f, 1.0f, 1.0f}} });
        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {0.0f, 1.0f, 0.0f, 1.0f}}, Vector4 { std::array<double, 4> {1.0f, 1.0f, 1.0f, 1.0f}}, Vector4 { std::array<double, 4> {1.0f, 1.0f, 0.0f, 1.0f}} });

        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {1.0f, 0.0f, 1.0f, 1.0f}}, Vector4 { std::array<double, 4> {0.0f, 0.0f, 1.0f, 1.0f}}, Vector4 { std::array<double, 4> {0.0f, 0.0f, 0.0f, 1.0f}} });
        mesh_cube.tris.push_back(Triangle4{ Vector4 { std::array<double, 4> {1.0f, 0.0f, 1.0f, 1.0f}}, Vector4 { std::array<double, 4> {0.0f, 0.0f, 0.0f, 1.0f}}, Vector4 { std::array<double, 4> {1.0f, 0.0f, 0.0f, 1.0f}} });

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        //Clear screen
        Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

        Mesh4 transformed_mesh;
        for (Triangle4 triangle: mesh_cube.tris)
        {
            transformed_mesh.tris.push_back(to_image_space(triangle, camera));
        }

        for (Triangle4& triangle : transformed_mesh.tris)
        {
            for (Vector4& vec : triangle.v)
            {
                vec[0] += 1.0;
                vec[1] += 1.0;
                vec[2] += -10.0;
                vec[3] += 5.0;
                vec[0] *= (0.5 * (double)ScreenWidth());
                vec[1] *= (0.5 * (double)ScreenHeight());

                if (vec[3] > 0.0001 || vec[3] < -0.0001)
                {
                    vec[0] /= vec[3]; vec[1] /= vec[3]; vec[2] /= vec[3];
                }
            }
        }

        for (Triangle4 tri : transformed_mesh.tris)
        {
            DrawLine(tri[0].x(), tri[0].y(), tri[1].x(), tri[1].y(), PIXEL_SOLID, FG_WHITE);
            DrawLine(tri[1].x(), tri[1].y(), tri[2].x(), tri[2].y(), PIXEL_SOLID, FG_WHITE);
            DrawLine(tri[2].x(), tri[2].y(), tri[0].x(), tri[0].y(), PIXEL_SOLID, FG_WHITE);
        }

        return true;
    }
};

int main()
{
    olcEngine3D app;
    if (app.ConstructConsole(200, 200, 4, 4))
        app.Start();
    else
        return -1;
    return 0;
}

