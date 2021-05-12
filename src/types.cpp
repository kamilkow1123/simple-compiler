#include "include/types.h"

int typename_to_int(string name)
{
    int t = 0;
    size_t len = name.size();

    for (unsigned int i = 0; i < len; i++)
    {
        t += name[i];
    }

    return t;
}