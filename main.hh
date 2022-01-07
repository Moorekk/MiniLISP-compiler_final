#ifndef MAIN_HPP
#define MAIN_HPP
#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
using namespace std;
enum token_type
{
    _program, _stmts, _stmt, _print_stmt, _exps, _exp,
    _num_op, _plus, _minus, _multiply, _divide, _modulus, _greater, _smaller, _equal,
    _logical_op, _and_op, _or_op, _not_op,
    _def_stmt, _def_variable, _get_variable,
    _fun_exp, _fun_ids, _fun_body, _fun_call, _params, _param, _fun_name,
    _if_exp, _test_exp, _if_act_exp, _then_exp, _else_exp,
    _ids,

    _INT, _BOOL, _ID,
    _ADD, _SUB, _MUL, _DIV, _MOD, _GRT, _SML, _EQL, _AND, _OR, _NOT, _PRINT_NUM, _PRINT_BOOL, _IF, _DEF, _FUN
};

struct inData
{
    int I;
    bool B;
    string S;
};
class Node
{
public:
    Node *left;
    Node *right;
    token_type token;
    inData *indata;
    Node(token_type, inData *);
    Node();
};
struct type
{
    Node *node;
    inData *indata;
};
class Data
{
public:
    int I;
    bool B;
    string S;
    type N;
    vector<int> vec_I;
    vector<bool> vec_B;
    vector<string> vec_S;
    vector<type> vec_N;
    Data();
    Data(int);
    Data(bool);
    Data(string);
    Data(type);
    operator int();
    operator bool();
    operator string();
    operator type();
    operator vector<int>();
    operator vector<bool>();
    operator vector<string>();
    operator vector<type>();
};

void printTree(Node *);
Node *insertNode(Node *, Node *, token_type);
Data numOperation(Node *, token_type);
Data traverseTree(Node *);

#define YYSTYPE type

#endif