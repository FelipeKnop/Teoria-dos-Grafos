#ifndef NO_H
#define NO_H
#include "Adjacencia.h"

class No
{
    public:
        No(int id,int  dado);
        ~No();
        int getId();
        int getDado();
        No* getProx();
        void setProx(No* no);

    protected:

    private:
        Adjacencia* adjRaiz;
        int id;
        int dado;
        No* prox;
};

#endif // NO_H
