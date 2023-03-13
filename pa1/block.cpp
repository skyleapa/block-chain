#include "block.h"
#include <cmath>
#include <iostream>

int Block::width() const
{
    return data[0].size();
}
int Block::height() const
{
    return data.size();
}

void Block::render(PNG &im, int column, int row) const
{
    for (int y = row; y < (row + height()); y++) {
        for (int x = column; x < (column + width()); x++) {
            RGBAPixel * pixel = im.getPixel(x, y);            
            *pixel = data[y - row][x - column];
        }
    }
}


void Block::build(PNG &im, int column, int row, int width, int height)
{
    for (int y = row; y < row + height; y++) {
        vector<RGBAPixel> v;
        for (int x = column; x < column + width; x++) {
            v.push_back(*im.getPixel(x, y));
        }
        data.push_back(v);
    }
}


void Block::flipVert()
{
    for (int y = 0; y < (height() / 2); y++) {
        for (int x = 0; x < width(); x++) {
            swap(data[y][x], data[height() - 1 - y][x]);
        }
    }
}


void Block::flipHoriz()
{
    for (int y = 0; y < height(); y++) {
        for (int x = 0; x < (width() / 2); x++) {
            swap(data[y][x], data[y][width() - 1 - x]);
        }
    }
}

void Block::rotateRight()
{
    int a = 0;
    int b = height()-1;
    while(a < b){
        for(int i = 0; i < (b - a); ++i){
            swap(data[a][a+i], data[a+i][b]);
            swap(data[a][a+i], data[b][b-i]);
            swap(data[a][a+i], data[b-i][a]);
        }
        ++a;
        --b;
    }

}
