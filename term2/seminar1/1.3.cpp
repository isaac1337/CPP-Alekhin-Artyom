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
int main()
{
    using mipt::fefm::Point, mipt::frtk::print;
    Point point = {10, 20};
    print(point);
}