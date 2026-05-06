#pragma once


#include <iostream>

struct Pixel {
    unsigned char r, g, b, a;
   
};

class Image {
    private:
    Pixel* data;
    int weight, height;

    

    public:
    Image(int w, int h);//zwykly
    Image(const Image& other);//kopiujący
    Image(Image&& other) noexcept;//przenaszący
    ~Image();

    //operatory przypisania
    Image& operator=(const Image& other); //kopiujący
    Image& operator=(Image&& other) noexcept;//przenoszancy

    //dostemp do pixeli
    Pixel& operator()(int x, int y);
    const Pixel& operator()(int x, int y) const;

    //porwnanie
    bool operator==(const Image& other) const;
    bool operator!=(const Image& other) const;

    //dodanie/odejmowanie
    Image operator+(const Image& other)const;
    Image operator-(const Image& other)const;
    Image& operator+=(const Image& other);
    Image& operator-=(const Image& other);

    //*

    Image& operator*=(double k);
    Image operator*(double k) const;

    // |
    Image operator|(const Image& other) const;
    Image& operator|=(const Image& other);


    void pprint() const;

    int getWidth() const{
        return weight;
    }

    int getHeight() const{
        return height;
    }
    friend std::ostream& operator<<(std::ostream& os, const Image& img);

};   
inline std::ostream& operator<<(std::ostream& os, const Pixel& p) {
    os << "(" << int(p.r) << ", " << int(p.g) << ", " << int(p.b) << ", " << int(p.a) << ")";
    return os;
}
