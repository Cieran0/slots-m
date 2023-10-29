#pragma once
#include "fruit.hpp"
#include <vector>
#include <random>
#include <iostream>
class slot
{
private:
    fruit fruitInSlot[10];
    int indexOfFirstVisibleFruit;
public:
    void setFruitAtIndex(fruit f, int index);
    void setRandomIndex(fruit f);
    fruit at(int index);
    void moveAllDown();
    slot() {}
    ~slot() {}
};

void slot::setRandomIndex(fruit f) {
    int i = rand() % 10;
    while (!fruitInSlot[i].isEmpty())
    {
        i = rand() % 10;
    }
    fruitInSlot[i] = f;
}

void slot::setFruitAtIndex(fruit f, int index) { 
    fruitInSlot[index]=f;
}

fruit slot::at(int index) {
    return fruitInSlot[index];
}

void slot::moveAllDown() {
    fruit buff = fruitInSlot[9];
    for (int i = 9; i >= 1; i--)
    {
        fruitInSlot[i] = fruitInSlot[i-1];
    }
    fruitInSlot[0] = buff;
    
}

