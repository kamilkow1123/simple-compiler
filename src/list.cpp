#include <stdlib.h>
#include "include/list.h"

List::List(size_t item_size)
{
    this->size = 0;
    this->item_size = item_size;
    this->items = 0;
}

void List::list_push(void* item)
{
    this->size += 1;
    // cout << "JESTEM TU KURWA\n";
    if(this->items == nullptr)
        this->items = new void*;
    else
    {
        this->items = (void**)realloc(this->items, (this->size * this->item_size));
    }

    this->items[this->size] = item;
}