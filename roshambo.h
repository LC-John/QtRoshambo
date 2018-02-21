#ifndef ROSHAMBO_H
#define ROSHAMBO_H

#include <string>
using namespace std;

class roshambo
{
public:
    roshambo();
    bool set_me(int op);
    bool set_opposite(int op);
    bool comp();
    int get_me();
    int get_opposite();
    int get_if_win();
    int get_me_score();
    int get_opposite_score();
    void reset();

private:
    int me, opposite;
    int me_score, opposite_score;
    int if_win;

    int __set_me__(int op);
    int __set_opposite__(int op);
    int __comp__();
};

#endif // ROSHAMBO_H
