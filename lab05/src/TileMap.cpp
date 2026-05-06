#include "TileMap.h"
#include "TileMapView.h"

Tile& TileMap::operator[](int rc){
    return tiles[rc] ;
}
const Tile& TileMap::operator[](int rc) const{
    return tiles[rc] ;
}

Tile& TileMap::operator()(int r, int c){
    return tiles[r*_c+c];
}
const Tile& TileMap::operator()(int r, int c) const{
    return tiles[r*_c+c];
}
bool Tile::operator==(const Tile& other) const{
    return terrain == other.terrain&&
            building== other.building&&
            near_river==other.near_river&&
            sea_access==other.sea_access&&
            has_forest==other.has_forest&&
            has_road==other.has_road;
}

std::ostream& operator<<(std::ostream& os, const Tile& t) {
    os << "Tile("
       << "terrain=" << static_cast<int>(t.terrain) << ", "
       << "building=" << static_cast<int>(t.building) << ", "
       << "near_river=" << t.near_river << ", "
       << "sea_access=" << t.sea_access << ", "
       << "has_forest=" << t.has_forest << ", "
       << "has_road=" << t.has_road
       << ")";
    return os;
}

TileMapView TileMap::createView() {
    return TileMapView(*this, 0, _r - 1, 0, _c - 1);
}
TileMapView TileMap::createView(){
    return TileMapView(*this,0, _r-1,0,_c-1);
}

TileMapView TileMap::createView(int s_r, int s_c, int f_r, int f_c) {
    return TileMapView(*this, s_r, f_r, s_c, f_c);
}