#include <iostream>

class Complex {
public:
    double real, imag;
    //重载单目
    Complex operator + (const Complex &c){
        Complex temp;
        temp.real = this->real + c.real;
        temp.imag = imag + c.imag;
        return temp;
    }
    //重载双目
    friend Complex operator - (const Complex &c1, const Complex & c2);

    //友元重载
    friend std::ostream & operator << (std::ostream & out , const Complex& c);
};

Complex operator -(const Complex &c1, const Complex & c2){
    Complex temp;
    temp.real = c1.real - c2.real;
    temp.imag = c1.imag - c2.imag;
    return temp;
}

std::ostream & operator << (std::ostream & out , const Complex& c){
    out << "real is " << c.real << " imag is " << c.imag ;
    return out;
}

int main() {
    Complex c1, c2;
    c1.real = 3;
    c1.imag = 4;
    c2.real = 5;
    c2.imag = 6;

    auto result = c1+c2;
    std::cout << "result real is " << result.real << " result imag is " << result.imag << std::endl;

    auto result2 = c1-c2;
    std::cout << "result real is " << result2.real << " result imag is " << result2.imag << std::endl;

    std::cout << result << std::endl;
    return 0;
}
