#include "CoreMinimal.h"
using namespace cv;

int main()
{
	Flame t_flame(100, 100);
	
	imshow("test", t_flame.get_image());
	waitKey(0);
	return 0;
}