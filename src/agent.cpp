#include <random>
#include <cmath>
#include <iostream>
#include "agent.hpp"
#include "globals.hpp"

using namespace std;

double grid[N][N] = {{0}};
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> rng(0., 1.);

Agent::Agent(){
    double dist = rng(gen) * N / 3.;
    double theta = rng(gen) * 2 * M_PI;
    x = cos(theta) * dist + N / 2.;
    y = sin(theta) * dist + N / 2.;
    //x = rng(gen) * N;
    //y = rng(gen) * N;
    //ang = rng(gen) * M_PI * 2;
    double dirx = N / 2. - x, diry = N / 2. - y;
    ang = atan2(diry, dirx);
}

bool check(int x, int y){
    return min(x,y) >= 0 && max(x,y) < N;
}

double sense(double x, double y, double ang){
    double dirx = cos(ang) * SD, diry = sin(ang) * SD;
    x += dirx;
    y += diry;
    double s = 0;
    for(int i = -SW;i <= SW;i++) for(int j = -SW;j <= SW;j++) if(check(x + i, y + j)){
        s += grid[int(x+i)][int(y+j)];
    }
    return s;
}

void Agent::update(){
    double newx = x, newy = y, newang = ang;
    double forward = sense(x, y, ang),
    left = sense(x, y, ang - SA),
    right = sense(x, y, ang + SA);
    if(forward > max(left, right)) {
        double dirx = cos(ang) * SS, diry = sin(ang) * SS;
        newx += dirx;
        newy += diry;
    } else if(forward < min(left, right)){
        if(rng(gen) < 0.5){
            newang -= RA;
            double dirx = cos(newang) * SS, diry = sin(newang) * SS;
            newx += dirx;
            newy += diry;
        } else {
            newang += RA;
            double dirx = cos(newang) * SS, diry = sin(newang) * SS;
            newx += dirx;
            newy += diry;
        }
    }
    else if(left < forward){
        newang += RA;
        double dirx = cos(newang) * SS, diry = sin(newang) * SS;
        newx += dirx;
        newy += diry;
    }
    else if(right < forward){
        newang -= RA;
        double dirx = cos(newang) * SS, diry = sin(newang) * SS;
        newx += dirx;
        newy += diry;
    } else {
        double dirx = cos(ang) * SS, diry = sin(ang) * SS;
        newx += dirx;
        newy += diry;
    }
    if(check(newx, newy)){
        x = newx;
        y = newy;
        ang = newang;
        grid[int(x)][int(y)] = 1;
    } else {
        ang = rng(gen) * M_PI * 2;
    }
}