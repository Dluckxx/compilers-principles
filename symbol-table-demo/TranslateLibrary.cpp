//
// Created by dutiesheng on 3/21/2022.
//

#include <iostream>
#include "TranslateLibrary.h"

namespace Translate {

    void program() {
        top = nullptr;
        block();
    }

    void block() {
        // '{'
        match("{");

        std::cout << "block start" << std::endl;

        // { saved = top; top = new Env(top); print("{ ") }
        saved = top;
        top = new Env(top);
        output("{ ");

        // decls stmts
        decls();
        stmts();

        // '}'
        std::cout << "block end" << std::endl;
        match("}");

        // { top = saved; print("} "); }
        top = saved;
        output("} ");
    }

    void Initialize(const std::string &src) {
        source = src;
        pointer = 0;
    }

    void output(const std::string &s) {
        cache += s;
    }

    void decls() {
        // decls -> decl decls
        auto it = source.cbegin();
        if (
                std::string(it + pointer, it + pointer + 3) == "int" ||
                std::string(it + pointer, it + pointer + 4) == "bool" ||
                std::string(it + pointer, it + pointer + 4) == "char"
                ) {
            decl();
            decls();
        }
        // decls -> ε
    }

    void decl() {
        // decl -> type id
        type();
        id();

        // { s = new Symbol; s.type = type.lexeme; top.put(id.lexeme, s); }
        auto *s = new Symbol();
        s->type = type_lexeme;
        top->put(id_lexeme, s);
        std::cout << "put symbol: " << type_lexeme << " " << id_lexeme << std::endl;
    }

    void stmts() {
        int count = 0;
        while (pointer + count < source.size() &&
               source.at(pointer + count) != ';' && source.at(pointer + count) != '}' &&
               source.at(pointer + count) != ' ' && source.at(pointer + count) != '\n' &&
               source.at(pointer + count) != '\t' && source.at(pointer + count) != '\r'

                ) {
            count++;
        }
        std::string next(source.cbegin() + pointer, source.cbegin() + pointer + count);

        // stmts -> stmt stmts
        if (source.at(pointer) == '{' || top->get(next) != nullptr) {
            stmt();
            stmts();
        }
        // ε
    }

    void stmt() {
        // stmt -> block | factor
        if (source.at(pointer) == '{') {
            block();
        } else {
            factor();
            // { print("; "); }
            output("; ");
        }
    }

    void factor() {
        // factor -> id
        id();

        std::cout << "call facter: " << id_lexeme << std::endl;

        // { s = top.get(id.lexeme); print(id.lexeme); print(":"); print("s.type"); }
        auto s = top->get(id_lexeme);
        output(id_lexeme);
        output(":");
        output(s->type);
    }

    bool match(const std::string &m) {
        auto it = source.cbegin();
        std::string temp(it + pointer, it + pointer + m.size());
        if (temp == m) {
            pointer += m.size();
            if (pointer >= source.size()) return true;
            while (source.at(pointer) == ' ' || source.at(pointer) == '\n' ||
                   source.at(pointer) == '\t' || source.at(pointer) == '\r') {
                pointer++;
            }
            std::cout << "match: " << m << std::endl;
            return true;
        } else {
            return false;
        }
    }

    void id() {
        auto it = source.cbegin() + pointer;
        std::string id_str;
        while (*it != ';') {
            id_str.push_back(*it);
            it++;
        }
        match(id_str);
        match(";");
        id_lexeme = id_str;
    }

    void type() {
        if (match("int")) {
            type_lexeme = "int";
        } else if (match("bool")) {
            type_lexeme = "bool";
        } else if (match("char")) {
            type_lexeme = "char";
        } else {
            std::cout << "compile error: " << "not supported type at " << pointer << std::endl;
            exit(1);
        }
    }

    void output_cache() {
        std::cout << "Result: " << cache << std::endl;
    }
}





