#pragma once
#include "raylib.h"
#include <string>

class fruit
{
private:
    Texture2D texture;
    double points;
    bool empty;
    std::string name;
public:
    fruit(Texture2D texture, int points);
    fruit() { empty = true; }
    Texture2D getTexture();
    std::string getName();
    double getPoints();
    bool isEmpty();
    ~fruit();
};

fruit::fruit(Texture2D texture, int points)
{
    this->texture=texture;
    this->points = 1 + (double)(points)/100;
    switch (points)
    {
    case 10:
        this->name="golden apple";
        break;
    case 20:
        this->name="watermelon";
        break;
    case 30:
        this->name="bar";
        break;
    case 40:
        this->name="lemon";
        break;
    case 50:
        this->name="pink apple";
        break;
    case 60:
        this->name="golden star";
        break;
    case 70:
        this->name="golden horseshoe";
        break;
    case 80:
        this->name="golden dollar";
        break;
    case 90:
        this->name="purple grapes";
        break;
    case 100:
        this->name="blue diamond";
        break;
    default:
        break;
    }
}

Texture2D fruit::getTexture() {
    return texture;
}

std::string fruit::getName() {
    return name;
}

double fruit::getPoints() {
    return points;
}

bool fruit::isEmpty() {
    return empty;
}

fruit::~fruit()
{
}
