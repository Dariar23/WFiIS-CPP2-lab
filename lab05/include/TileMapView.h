#pragma once
#include "TileMap.h"

class TileMapView {
private:
    TileMap& map;
    int s_r, s_c;
    int e_r, e_c;

public:
    TileMapView(TileMap& m, int sr, int er, int sc, int ec): map(m), s_r(sr), s_c(sc), e_r(er), e_c(ec) {}

    Tile& operator()(int r, int c);
    const Tile& operator()(int r, int c) const;

    Tile& operator[](int index);
    const Tile& operator[](int index) const;

    class Iterator {
    private:
        TileMapView& view;
        int index;

    public:
        Iterator(TileMapView& v, int i) : view(v), index(i) {}

        Tile& operator*();
        Iterator& operator++();
        Iterator& operator--();  
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin();
    Iterator end();
};
