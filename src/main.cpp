#include <SFML/Graphics.hpp>
#include <iostream>
#include "globals.hpp"
#include "agent.hpp"
using namespace std;
extern double grid[N][N];
bool check(int x, int y);
int main(){
    sf::RenderWindow win;
    win.create(sf::VideoMode(N, N), "s l i m e");
    sf::Event ev;
    sf::Image buffer;
    buffer.create(N, N);
    sf::Texture bufferTexture;
    sf::Sprite bufferSprite;
    Agent agents[NA];
    double b[N][N];
    double s;
    while(win.isOpen()){
        while(win.pollEvent(ev)){
            if(ev.type == sf::Event::Closed) win.close();
        }
        win.clear();
        for(int i = 0;i < NA;i++) agents[i].update();
        for(int i = 0;i < N;i++) for(int j = 0;j < N;j++) b[i][j] = grid[i][j] * DR;
        for(int i = 0;i < N;i++) for(int j = 0;j < N;j++) {
            s = 0;
            for(int l = -1; l < 2;l++) for(int k = -1;k < 2;k++) if(check(i+l, j+k)) s += b[i+l][j+k];
            grid[i][j] = b[i][j] * (1 - DS) + (s / 9) * DS;
            buffer.setPixel(i, j, sf::Color(grid[i][j] * 255, grid[i][j] * 255, grid[i][j] * 255));
        }
        bufferTexture.loadFromImage(buffer);
        bufferSprite.setTexture(bufferTexture);
        win.draw(bufferSprite);
        win.display();
    }
}