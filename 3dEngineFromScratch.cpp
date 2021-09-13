#define OLC_PGE_APPLICATION

#include <tuple>
#include <functional>
#include <iostream>

#include "olc/olcPixelGameEngine.h"
#include "renderEngine.h"


int main()
{
	RenderEngine engine3d;
	if (engine3d.Construct(640, 480, 1, 1))
		engine3d.Start();

	return 0;
}
