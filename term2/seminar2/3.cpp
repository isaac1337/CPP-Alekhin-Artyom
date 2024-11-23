#include <string>
#include <vector>

class Number 
{
public:
    std::vector<unsigned char> data;

    Number(): data(1, 0) {
    }

    Number(const Number& n): data(n.data){
    }

    Number(const std::string& str){
    for(size_t i = str.size(); i>0; i-=2)
    {
        unsigned char byte = 0;
        if(i > 1)
        {
             byte += static_cast<unsigned char>((str[i-2] - '0') * 10 );
        }
        byte += static_cast<unsigned char>((str[i-1] - '0'));
        data.push_back(byte);
        if (i == 0 || i == 1)
        {
            break;
        }
    }
    }
    Number& operator=(const Number& n)
    {
        data = n.data;
        return *this;
    }

};

int main(){

}