#include "raylib.h"
#include "fruit.hpp"
#include "slot.hpp"
#include <iostream>
#include <vector>
#include <string>

#define XPOS(x) (x*200)+525

slot slots[4];
int offset = 0;
int speed = 20;
bool stopped[4] = {0,0,0,0};
bool shouldStop[4] = {0,0,0,0};

int balance = 10000;
int bet = 5000;

Color colours_light[6] = {
    {255,0,0,255},
    {0,255,0,255},
    {0,0,255,255},
    {255,255,51,255},
    {255,51,255,255},
    {51,255,255,255}
};

Color colours_dark[6] = {
    {127,0,0,255},
    {0,127,0,255},
    {0,0,127,255},
    {127,127,25,255},
    {127,25,127,255},
    {25,127,127,255}
};

bool lit[6] = {0,0,0,0,0,0};

const int maxOffset = 150;

std::string shownBoardPoints[4][4];

void loadTextures() {

    Texture2D buff;
    for (int i = 1; i < 11; i++)
    {
        std::string s = "fruit/";
        s+=std::to_string(i);
        s+=".png";
        buff = LoadTexture(s.c_str());
        for(int j =0; j <4; j++) 
            slots[j].setRandomIndex(fruit(buff,i*10));
    }
}

inline int max(double one, double two, int* out) {
    bool firstSmaller = one < two;
    *out = (firstSmaller)? 1 : 0;
    return (firstSmaller)? two : one;
}

int countTheSame(double* points, int* index) {
    int theSame[2] = {0,0};
    for (int i = 0; i < 2; i++)
    {
        for (int j = i; j < 4; j++)
        {
            if(points[i] == points[j])
                theSame[i]++;
        }
    }
    double m = max(theSame[0],theSame[1],index);
    return m;
}

double lightUp() {
    double buff[4];
    double multipler = 0;
    for (int i = 0; i < 4; i++)
    {
        int index = -1;
        buff[0] = slots[0].at(i+1).getPoints();
        buff[1] = slots[1].at(i+1).getPoints();
        buff[2] = slots[2].at(i+1).getPoints();
        buff[3] = slots[3].at(i+1).getPoints();
        int count = countTheSame(buff,&index);
        if(count >= 3) {
            lit[i] = true;
            multipler += (count == 4)? (2*buff[index]) : buff[index]; 
        }
    }
    for (int i = 0; i < 4; i++)
    {
        buff[i] = slots[i].at(i+1).getPoints();
    }
    int index = -1;
    int count = countTheSame(buff,&index);
    if(count >= 3) {
            lit[5] = true;
            multipler += (count == 4)? (2*buff[index]) : buff[index]; 
    }
    index = -1;
    for (int i = 0; i < 4; i++)
    {
        buff[i] = slots[3-i].at(i+1).getPoints();
    }
    count = countTheSame(buff,&index);
    if(count >= 3) {
            lit[4] = true;
            multipler += (count == 4)? (2*buff[index]) : buff[index]; 
    }
    std::cout << multipler << std::endl;
    return multipler;
}

int main(void)
{
    const int screenWidth = 1800;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "Slots");
    SetTargetFPS(60);
    loadTextures();

    int current = 0;
    bool hasWon = false;
    int amountWon = 0;
    const char* YOU_WON = "You Won!";
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        std::string sbalance = "£" + std::to_string((int)(balance/100)) + "." + std::to_string(balance%100) + ((balance%100>=10)? "" : "0");
        std::string sbet = "£" + std::to_string((int)(bet/100)) + "." + std::to_string(bet%100) + ((bet%100>=10)? "" : "0");
        DrawText(sbalance.c_str(), 0,0,100,BLACK);
        DrawText(sbet.c_str(), 0,100,100,BLACK);
        if(amountWon > 0) {
            std::string sWon = "£" + std::to_string((int)(amountWon/100)) + "." + std::to_string(amountWon%100) + ((amountWon%100>=10)? "" : "0");
            DrawText(YOU_WON,0,200,100,BLACK);
            DrawText(sWon.c_str(),0,300,100,BLACK);
        }

        for(int x = 0; x < 4; x++) {
            DrawRectangle(XPOS(x),0,150,900,WHITE);
        }

        for (int i = 1; i < 5; i++)
        {
            DrawLineEx((Vector2){450,i*150+74},(Vector2){1350,i*150+74},10,(lit[i-1])? colours_light[i-1] :colours_dark[i-1]);
            DrawLineEx((Vector2){400,i*150+74},(Vector2){450,i*150+74},20,(lit[i-1])? colours_light[i-1] :colours_dark[i-1]);
            DrawLineEx((Vector2){1350,i*150+74},(Vector2){1400,i*150+74},20,(lit[i-1])? colours_light[i-1] :colours_dark[i-1]);
        }
        DrawLineEx((Vector2){450,5*150}, (Vector2){1350,150},10,(lit[4])? colours_light[4] : colours_dark[4]);
        DrawLineEx((Vector2){400,5*150+(50*2/3)}, (Vector2){450,5*150},20,(lit[4])? colours_light[4] : colours_dark[4]);
        DrawLineEx((Vector2){1350,150}, (Vector2){1400,150-(50*2/3)} ,20,(lit[4])? colours_light[4] : colours_dark[4]);

        DrawLineEx((Vector2){450,150},(Vector2){1350,5*150},10,(lit[5])? colours_light[5] : colours_dark[5]);
        DrawLineEx((Vector2){400,150-(50*2/3)},(Vector2){450,150},20,(lit[5])? colours_light[5] : colours_dark[5]);
        DrawLineEx((Vector2){1350,5*150},(Vector2){1400,5*150+(50*2/3)},20,(lit[5])? colours_light[5] : colours_dark[5]);

        for (int x = 0; x < 4; x++)
        {

            //DrawRectangleLines((x*250)+975/2,0,150,900,BLACK);
            for (int y = 0; y < 10; y++)
            {
                Texture2D texture = slots[x].at(y).getTexture();
                DrawTexture(texture, XPOS(x), y*150 + ((stopped[x])? 0 : offset), WHITE);
            }
            
            DrawRectangle(XPOS(x),0,150,150,WHITE);
            DrawRectangle(XPOS(x),750,150,150,WHITE);
        }



        if(IsKeyPressed(KEY_ENTER)) {
            shouldStop[current] = true;
        } 

        if (IsKeyPressed(KEY_SPACE)) {
            if(stopped[3]) {
                amountWon = 0;
                balance -= bet;
                hasWon = false;
                for (int i = 0; i < 4; i++)
                {
                    stopped[i] = false;
                    shouldStop[i] = false;
                    lit[i] = false;
                }
                lit[4] =false ; lit[5] = false;
                current = 0;
            }
        }

        if(shouldStop[current] && offset == 0) {
            stopped[current] = true;
            current = (current==3)? current : current+1;
        }

        offset = ((offset>=maxOffset)? 0 : offset+speed);
        for (int i = 0; i < 4; i++)
        {
            if(offset == 0 && !stopped[i]) {
                slots[i].moveAllDown();
            }
        }

        if(stopped[0] && stopped[1] && stopped[2] && stopped[3] && !hasWon) {
            hasWon = true;
            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {

                    std::cout << slots[x].at(y+1).getName() << " | ";
                }
                std::cout << std::endl;
            }
            amountWon = bet * lightUp();
            balance += amountWon;
        }    
        EndDrawing();
    }
    CloseWindow();
    return 0;
}