#include <iostream>

namespace mipt
{
    namespace fefm
    {   
        struct Point
        {
            int x, y;
        };
    }

    namespace frtk
    {
        void print(fefm::Point p)
        {
            std::cout << p.x << " " << p.y << std::endl;
        }
    }
}

using namespace mipt;

int main()
{
    fefm::Point point = {10, 20};
    frtk::print(point);
    return 0;
}