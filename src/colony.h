#include <vector>

#include "resources.h"

class Colony
{
    private:
    int id;

    public:
    int owner;

    int structure[(int)Structures::indexLast] = {0};

    

    Colony(int id, int owner);
    ~Colony();
};