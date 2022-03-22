//
// Created by dutiesheng on 3/21/2022.
//

#include "Env.h"

Env::Env(Env *prev) : prev(prev) {
    table = new std::unordered_map<std::string, Symbol *>();
}

void Env::put(const std::string &s, Symbol *sym) {
    table->insert({s, sym});
}

Symbol *Env::get(const std::string &s) {
    for (Env *e = this; e != nullptr; e = e->prev) {
        auto found = e->table->find(s);
        if (found != e->table->end()) {
            return found->second;
        }
    }
    return nullptr;
}
