#include "roshambo.h"
#include <cstdlib>

#define RAND_ROSHAMBO (rand()%3)

roshambo::roshambo()
{
    me = -1;
    opposite = -1;
    if_win = 0;
    me_score = 0;
    opposite_score = 0;
}

int roshambo::__set_me__(int op)
{
    switch (op)
    {
    case 0:
        me = 0;
        return 0;
    case 1:
        me = 1;
        return 0;
    case 2:
        me = 2;
        return 0;
    default:
        me = -1;
        return -1;
    }
}

int roshambo::__set_opposite__(int op)
{
    if (op < 0)
    {
        opposite = RAND_ROSHAMBO;
        return 1;
    }
    switch(op)
    {
    case 0:
        opposite = 0;
        return 0;
    case 1:
        opposite = 1;
        return 0;
    case 2:
       opposite = 2;
        return 0;
    default:
        opposite = -1;
        return -1;
    }
}

int roshambo::__comp__()
{
    switch(me)
    {
    case 0:
        switch(opposite)
        {
        case 0:
            if_win = 0;
            return 0;
        case 1:
            if_win = 1;
            me_score += 1;
            return 0;
        case 2:
            if_win = -1;
            opposite_score += 1;
            return 0;
        default:
            if_win = 0;
            return -1;
        }
    case 1:
        switch(opposite)
        {
        case 0:
            if_win = -1;
            opposite_score += 1;
            return 0;
        case 1:
            if_win = 0;
            return 0;
        case 2:
            if_win = 1;
            me_score += 1;
            return 0;
        default:
            if_win = 0;
            return -1;
        }
    case 2:
        switch(opposite)
        {
        case 0:
            if_win = 1;
            me_score += 1;
            return 0;
        case 1:
            if_win = -1;
            opposite_score += 1;
            return 0;
        case 2:
            if_win = 0;
            return 0;
        default:
            if_win = 0;
            return -1;
        }
    default:
        if_win = 0;
        return -1;
    }
}

bool roshambo::set_me(int op)
{
    if(__set_me__(op) < 0)
        return false;
    return true;
}

bool roshambo::set_opposite(int op)
{
    if(__set_opposite__(op) < 0)
        return false;
    return true;
}

bool roshambo::comp()
{
    if(__comp__()<0)
        return false;
    return true;
}

int roshambo::get_me()
{
    return me;
}

int roshambo::get_opposite()
{
    return opposite;
}

int roshambo::get_if_win()
{
    return if_win;
}

int roshambo::get_me_score()
{
    return me_score;
}

int roshambo::get_opposite_score()
{
    return opposite_score;
}

void roshambo::reset()
{
    me = -1;
    opposite = -1;
    if_win = 0;
    me_score = 0;
    opposite_score = 0;
}
