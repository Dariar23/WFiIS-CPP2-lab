#include "Image.h"
#include <algorithm>
#include <cstring>


Image::Image(int w, int h):data(nullptr), weight(w), height(h){
    data = new Pixel[w*h];
}
Image::Image(const Image& other): data(nullptr), weight(other.weight), height(other.height){
    data=new Pixel[weight*height];
    std::copy(other.data, other.data+weight*height, data);
}

Image::Image(Image&& other) noexcept: data(nullptr), weight(other.weight), height(other.height){
    other.data=nullptr;
}

Image::~Image(){
    delete[] data;
}
Image& Image::operator=(const Image& other){
    if(this==&other){
        return *this;
    }
    delete[] data;
    weight=other.weight;
    height=other.height;
    data = new Pixel[weight*height];
    std::copy(other.data, other.data+weight*height, data);

    return *this;
}
///konstructor przenoszący

Image& Image::operator=( Image&& other) noexcept{
    if(&other==this){
        return *this;
    }
    delete[] data;
    weight=other.weight;
    height=other.height;
    data=other.data;

    other.data=nullptr;
    return *this;
}

//dostemp do pixela

Pixel& Image::operator()(int x, int y){
    return data[y*weight+x];
}

const Pixel& Image::operator()(int x, int y)const{
    return data[y*weight+x];
}

// ==
bool Image::operator==(const Image& other) const{
    if(weight!=other.weight || height!=other.height){
        return false;
    }
    for(int i=0; i <weight*height; i++){
        if(data[i].r != other.data[i].r ||
        data[i].g != other.data[i].g ||
        data[i].b != other.data[i].b ||
        data[i].a != other.data[i].a
        ){
            return false;
        }
        
    }
    return true;
}
bool Image::operator!=(const Image& other) const {
    return !(*this == other);
}
///+++
Image Image::operator+(const Image& other) const{
    Image result(weight, height);
    for( int i=0; i < weight*height; i++){
        result.data[i].r=std::min(255, other.data[i].r+ data[i].r);
        result.data[i].g=std::min(255, data[i].g+other.data[i].g);
        result.data[i].b=std::min(255,data[i].b+other.data[i].b);
        result.data[i].a=std::min(255,data[i].a+other.data[i].a);
    }
    return result;

}
Image& Image::operator+=(const Image& other){
    for( int i=0; i < weight*height;i++){
        data[i].r=std::min(255,data[i].r+other.data[i].r);
        data[i].g=std::min(255, data[i].g+other.data[i].g);
        data[i].b=std::min(255, data[i].b+other.data[i].b);
        data[i].a=std::min(255, data[i].a+other.data[i].a);
    }
    return *this;
}

///---

Image Image::operator-(const Image& other) const{
    Image result(weight, height);
    for( int i=0; i < weight*height; i++){
        result.data[i].r=std::max(0, data[i].r-other.data[i].r );
        result.data[i].g=std::max(0, data[i].g-other.data[i].g);
        result.data[i].b=std::max(0,data[i].b-other.data[i].b);
        result.data[i].a=std::max(0,data[i].a-other.data[i].a);
    }
    return *this;
}
Image& Image::operator-=(const Image& other){
    for( int i=0; i < weight*height;i++){
        data[i].r=std::max(0,data[i].r-other.data[i].r);
        data[i].g=std::max(0, data[i].g-other.data[i].g);
        data[i].b=std::max(0, data[i].b-other.data[i].b);
        data[i].a=std::max(0, data[i].a-other.data[i].a);
    }
    return *this;
}
/// ***

Image Image::operator*(double k) const {
    Image result(weight, height);
    for (int i = 0; i < weight * height; i++) {
        result.data[i].r = std::min(255, int(data[i].r * k));
        result.data[i].g = std::min(255, int(data[i].g * k));
        result.data[i].b = std::min(255, int(data[i].b * k));
        result.data[i].a = std::min(255, int(data[i].a * k));
    }
    return result;
}

Image& Image::operator*=(double k) {
    for (int i = 0; i < weight * height; i++) {
        data[i].r = std::min(255, int(data[i].r * k));
        data[i].g = std::min(255, int(data[i].g * k));
        data[i].b = std::min(255, int(data[i].b * k));
        data[i].a = std::min(255, int(data[i].a * k));
    }
    return *this;
}
Image Image::operator|(const Image& other) const {
    int newW = weight + other.weight;
    int newH = std::max(height, other.height);

    Image result(newW, newH);

    for (int y = 0; y < height; y++)
        for (int x = 0; x < weight; x++)
            result(x, y) = (*this)(x, y);

    for (int y = 0; y < other.height; y++)
        for (int x = 0; x < other.weight; x++)
            result(x + weight, y) = other(x, y);

    return result;
}

Image& Image::operator|=(const Image& other) {
    *this = (*this | other);
    return *this;
}
std::ostream& operator<<(std::ostream& os, const Image& img) {
    for(int y = 0; y < img.height; y++) {
        for(int x = 0; x < img.weight; x++) {
            const Pixel& p = img(x, y);
            os << "(" << int(p.r) << ", " << int(p.g) << ", "
               << int(p.b) << ", " << int(p.a) << ") ";
        }
        os << "\n";
    }
    return os;
}