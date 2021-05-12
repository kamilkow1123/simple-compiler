#ifndef SOWA_LIST_H
#define SOWA_LIST_H

class List
{
private:
    void **items;
    size_t size;
    size_t item_size;
public:
    List(size_t);
    void list_push(void*);
    void *getItems(int i) { return this->items[i]; }
    size_t getSize() { return this->size; }
};

#endif // SOWA_LIST_H
