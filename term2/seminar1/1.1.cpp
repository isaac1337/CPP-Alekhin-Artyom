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
    mipt::fefm::Point point = {10, 20};
    mipt::frtk::print(point);

}