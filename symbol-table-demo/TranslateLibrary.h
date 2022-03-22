//
// Created by dutiesheng on 3/21/2022.
//

#ifndef COMPILER_DEMO_TRANSLATELIBRARY_H
#define COMPILER_DEMO_TRANSLATELIBRARY_H

#include "Symbol.h"
#include "Env.h"

namespace Translate {

    // Variables
    static int pointer;
    static Env *top;
    static Env *saved;
    static std::string source;
    static std::string cache;
    static std::string type_lexeme;
    static std::string id_lexeme;

    // Tool function
    void Initialize(const std::string &src);

    void output(const std::string &s);

    void output_cache();

    // production function

    /**
     * program -> { top = null } block
     */
    void program();

    /**
     *  block -> '{'
     *      { saved = top; top = new Env(top); print("{ ") }
     *      decls stmts
     *  '}'
     *  { top = saved; print("} "); }
     */
    void block();

    /**
     * decls -> decls decl | ε
     */
    void decls();

    /**
     * decl -> type id { s = new Symbol; s.type = type.lexeme; top.put(id.lexeme, s); }
     */
    void decl();

    /**
     * stmts -> stmts stmt | ε
     */
    void stmts();

    /**
     * stmt -> block | factor; { print("; "); }
     */
    void stmt();

    /**
     * factor -> id { s = top.get(id.lexeme); print(id.lexeme); print(":"); print("s.type"); }
     */
    void factor();

    // Type of variables
    void type();

    // Variable name
    void id();

    // Match a sting
    bool match(const std::string& m);
}

#endif //COMPILER_DEMO_TRANSLATELIBRARY_H
