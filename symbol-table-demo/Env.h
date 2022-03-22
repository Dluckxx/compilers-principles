//
// Created by dutiesheng on 3/21/2022.
//

#ifndef COMPILER_DEMO_ENV_H
#define COMPILER_DEMO_ENV_H

#include <unordered_map>
#include "Symbol.h"

class Env {

public:
    Env(Env *prev);

    void put(const std::string &s, Symbol *sym);

    Symbol *get(const std::string &s);

protected:
    Env *prev;

private:
    std::unordered_map<std::string, Symbol *> *table;
};


#endif //COMPILER_DEMO_ENV_H
