
#include <ctime>

#include "kd_tree.h"

int main()
{
    srand((unsigned int)time(NULL));
    const int test_len = 10;
    BasicPoint* points = new BasicPoint[test_len];
    for (int i = 0; i < 10; ++i) {
        points[i].set_x(rand() % 101 - 50);
        points[i].set_y(rand() % 101 - 50);
        points[i].set_z(rand() % 101 - 50);
    }

    kd_tree<BasicPoint, int> kd(points, test_len);
    kd.print();
    std::cout << "Hello World!\n";
}
