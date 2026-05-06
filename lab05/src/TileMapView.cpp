#include "TileMapView.h"
#include "TileMap.h"

Tile& TileMapView::operator()(int r, int c) {
    return map(s_r + r, s_c + c);
}

const Tile& TileMapView::operator()(int r, int c) const {
    return map(s_r + r, s_c + c);
}

Tile& TileMapView::operator[](int index) {
    int width = e_c - s_c + 1;
    return (*this)(index / width, index % width);
}

const Tile& TileMapView::operator[](int index) const {
    int width = e_c - s_c + 1;
    return (*this)(index / width, index % width);
}

Tile& TileMapView::Iterator::operator*() {
    return view[index];
}

TileMapView::Iterator& TileMapView::Iterator::operator++() {
    index++;
    return *this;
}

TileMapView::Iterator& TileMapView::Iterator::operator--() {
    index--;
    return *this;
}
bool TileMapView::Iterator::operator!=(const Iterator& other) const {
    return index != other.index;
}

TileMapView::Iterator TileMapView::begin() {
    return Iterator(*this, 0);
}

TileMapView::Iterator TileMapView::end() {
    int width = e_c - s_c + 1;
    int height = e_r - s_r + 1;
    return Iterator(*this, width * height);
}
