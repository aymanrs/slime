#ifndef __AGENT_HPP__
#define __AGENT_HPP__

class Agent{
public:
    Agent();
    void update();
private:
    double x, y;
    double ang;
};

#endif