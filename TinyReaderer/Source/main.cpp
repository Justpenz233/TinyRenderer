#include "Engine/CoreMinimal.h"
using namespace cv;

int main()
{
	Flame t_flame(100, 100);
	for(int i = 1;i <= 10;i ++)
	{
		for(int j = 1;j <= 30;j ++)
		{
			t_flame.set(Point2d(i, j), COLOR_PURPLE);
		}
	}
	imshow("test", t_flame.get_image());
	waitKey(0);
	return 0;
}