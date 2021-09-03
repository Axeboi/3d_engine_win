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

        //new_tri.v.push_back(tri.v[i] * (translate_camera * (rotate_x * rotate_y)) * projection);
        new_tri.v.push_back(tri.v[i] *  projection);
    }
   
    return new_tri;
};

class olcEngine3D : public olcConsoleGameEngine
{
public:
    olcEngine3D()
    {
        m_sAppName = L"3D Render";
    }

private:
    Vector4 camera;
    Mesh4 mesh_cube;

    bool OnUserCreate() override
    {
        camera = std::array{ 0.0, 0.0, -1.0, 1.0 };

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
                //vec.print();
                vec.v_data[0] += 1.0;
                vec.v_data[1] += 1.0;
                vec.v_data[2] += -10.0;
                vec.v_data[3] += 5.0;
                vec.v_data[0] *= (0.5 * (double)ScreenWidth());
                vec.v_data[1] *= (0.5 * (double)ScreenHeight());

                //vec.v_data[0] /= vec.v_data[3]; vec.v_data[1] /= vec.v_data[3]; vec.v_data[2] /= vec.v_data[3];
                if (vec.v_data[3] > 0.0001 || vec.v_data[3] < -0.0001)
                {
                    //std::cout << vec.v_data[3] << " " << vec.v_data[0] << " " << vec.v_data[1] << std::endl;
                    vec.v_data[0] /= vec.v_data[3]; vec.v_data[1] /= vec.v_data[3]; vec.v_data[2] /= vec.v_data[3];
                }
                    
            }

            //triangle.print();
        }

        for (Triangle4 tri : transformed_mesh.tris)
        {
            /*DrawLine(tri.v[0].x() / tri.v[0].w(), tri.v[1].y() / tri.v[1].w(), PIXEL_SOLID, FG_WHITE);
            DrawLine(tri.v[1].x() / tri.v[1].w(), tri.v[2].y() / tri.v[2].w(), PIXEL_SOLID, FG_WHITE);
            DrawLine(tri.v[2].x() / tri.v[2].w(), tri.v[0].y() / tri.v[0].w(), PIXEL_SOLID, FG_WHITE);*/
            //tri.print();
            DrawLine(tri.v[0].x(), tri.v[0].y(), tri.v[1].x(), tri.v[1].y(), PIXEL_SOLID, FG_WHITE);
            DrawLine(tri.v[1].x(), tri.v[1].y(), tri.v[2].x(), tri.v[2].y(), PIXEL_SOLID, FG_WHITE);
            DrawLine(tri.v[2].x(), tri.v[2].y(), tri.v[0].x(), tri.v[0].y(), PIXEL_SOLID, FG_WHITE);
        }

        //DrawLine(40, 40, ScreenWidth() - 40, ScreenHeight() - 40, PIXEL_SOLID, FG_WHITE);
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

