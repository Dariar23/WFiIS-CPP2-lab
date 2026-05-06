#pragma once
#include <iostream>
#include <vector>


struct Tile {
    enum class Teren { Fields, Hills, Mountains };
    enum class Building { None, City, Farm, Lumbermill, Mine };
   

    Teren terrain = Teren::Fields;
    Building building = Building::None;

    bool near_river = false;
    bool sea_access = false;
    bool has_forest = false;
    bool has_road = false;

    bool operator==(const Tile& other) const;
};


std::ostream& operator<<(std::ostream& os, const Tile& t);

class TileMapView; 

class TileMap {
private:
    int _r;
    int _c;
    std::vector<Tile> tiles;

public:
    TileMap(int r, int c) : _r(r), _c(c), tiles(r * c) {}

    Tile& operator[](int rc);
    const Tile& operator[](int rc) const;

    Tile& operator()(int r, int c);
    const Tile& operator()(int r, int c) const;

    TileMapView createView();
    TileMapView createView(int s_r, int s_c, int f_r, int f_c);

    friend class TileMapView;
};
