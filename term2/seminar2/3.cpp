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
        
        Number operator+(const Number& other) const
        {
        Number result;
        result.data.clear(); // Очищаем результат перед применением сложения
        size_t maxLength = std::max(data.size(), other.data.size());
        unsigned char carry = 0;
        
        for (size_t i = 0; i < maxLength || carry > 0; ++i)
        {
            unsigned char left = 0;
            unsigned char right = 0;

            if (i < data.size()) {
                left = data[i];
            } else {
                left = 0;
            }

            if (i < other.data.size()) {
                right = other.data[i];
            } else {
                right = 0;
            }

            unsigned char sum = left + right + carry;
            carry = sum / 100;
            result.data.push_back(sum % 100);
        }

        return result;
    }
    Number& operator+=(const Number& other)
    {
        *this = *this + other; // Используем оператор + для реализации +=
        return *this;
    }



};

    int main(){

    }