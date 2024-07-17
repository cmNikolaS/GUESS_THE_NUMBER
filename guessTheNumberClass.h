#pragma once

#include <cstdlib>
#include <ctime>

typedef int rNum_t;

class randomNumber
{
    private:
    rNum_t lowerBorder, higherBorder;

    public:
    randomNumber(rNum_t lB, rNum_t hB):lowerBorder(lB), higherBorder(hB)
    {
        srand(time(NULL));
    }

    inline rNum_t getRandomNumber()
    {
        return (lowerBorder + (rand() % (higherBorder - lowerBorder + 1)));
    }

    inline void changeLowerBorder(rNum_t newLowerBorder)
    {
        lowerBorder = newLowerBorder;
    }
    
    inline void changeHigherBorder(rNum_t newHigherBorder)
    {
        higherBorder = newHigherBorder;
    }

};