%{
#include "main.hh"

extern "C"
{
        void yyerror(const char *s);
        extern int yylex(void);
}
Node *root;
%}
%type<node> program stmts stmt print_stmt exps exp
%type<node> num_op plus minus multiply divide modulus greater smaller equal
%type<node> logical_op and_op or_op not_op
%type<node> def_stmt def_variable get_variable
%type<node> fun_exp fun_ids fun_body fun_call params param fun_name
%type<node> if_exp test_exp if_act_exp then_exp else_exp
%type<node> ids

%token<indata> INT
%token<indata> BOOL
%token<indata> ID
%token PRINT_NUM PRINT_BOOL
%left ADD SUB MUL DIV MOD GRT SML EQL AND OR NOT IF DEF FUN '(' ')'

%%
program         : stmts         {$$ = insertNode($1, nullptr, _program);root = $$;}
                ;
stmts           : stmt stmts    {$$ = insertNode($1, $2, _stmts);}
                |               {$$ = nullptr;}
                ;
stmt            : exp           {$$ = insertNode($1, nullptr, _stmt);}
                | def_stmt      {$$ = insertNode($1, nullptr, _stmt);}
                | print_stmt    {$$ = insertNode($1, nullptr, _stmt);}
                ;
print_stmt      : '(' PRINT_NUM exp ')'         {$$ = insertNode(new Node(_PRINT_NUM, nullptr), $3, _print_stmt);}
                | '(' PRINT_BOOL exp ')'        {$$ = insertNode(new Node(_PRINT_BOOL, nullptr), $3, _print_stmt);}
                ;
exps            : exp exps      {$$ = insertNode($1, $2, _exps);}
                |               {$$ = nullptr;}
                ;
exp             : BOOL          {$$ = insertNode(new Node(_BOOL, $1), nullptr, _exp);}
                | INT           {$$ = insertNode(new Node(_INT, $1), nullptr, _exp);}
                | get_variable  {$$ = insertNode($1, nullptr, _exp);}
                | num_op        {$$ = insertNode($1, nullptr, _exp);}
                | logical_op    {$$ = insertNode($1, nullptr, _exp);}
                | fun_exp       {$$ = insertNode($1, nullptr, _exp);}
                | fun_call      {$$ = insertNode($1, nullptr, _exp);}
                | if_exp        {$$ = insertNode($1, nullptr, _exp);}
                ;
num_op          : plus          {$$ = insertNode($1, nullptr, _num_op);}
                | minus         {$$ = insertNode($1, nullptr, _num_op);}
                | multiply      {$$ = insertNode($1, nullptr, _num_op);}
                | divide        {$$ = insertNode($1, nullptr, _num_op);}
                | modulus       {$$ = insertNode($1, nullptr, _num_op);}
                | greater       {$$ = insertNode($1, nullptr, _num_op);}
                | smaller       {$$ = insertNode($1, nullptr, _num_op);}
                | equal         {$$ = insertNode($1, nullptr, _num_op);}
                ;
        plus            : '(' ADD exp exps ')'  {$$ = insertNode($3, $4, _plus);}
                        ;
        minus           : '(' SUB exp exp ')'   {$$ = insertNode($3, $4, _minus);}
                        ;
        multiply        : '(' MUL exp exps ')'  {$$ = insertNode($3, $4, _multiply);}
                        ;
        divide          : '(' DIV exp exp ')'   {$$ = insertNode($3, $4, _divide);}
                        ;
        modulus         : '(' MOD exp exp ')'   {$$ = insertNode($3, $4, _modulus);}
                        ;
        greater         : '(' GRT exp exp ')'   {$$ = insertNode($3, $4, _greater);}
                        ;
        smaller         : '(' SML exp exp ')'   {$$ = insertNode($3, $4, _smaller);}
                        ;
        equal           : '(' EQL exp exps ')'  {$$ = insertNode($3, $4, _equal);}
                        ;
logical_op      : and_op        {$$ = insertNode($1, nullptr, _logical_op);}
                | or_op         {$$ = insertNode($1, nullptr, _logical_op);}
                | not_op        {$$ = insertNode($1, nullptr, _logical_op);}
                ;
        and_op          : '(' AND exp exps ')'      {$$ = insertNode($3, $4, _and_op);}
                        ;
        or_op           : '(' OR exp exps ')'       {$$ = insertNode($3, $4, _or_op);}
                        ;
        not_op          : '(' NOT exp ')'           {$$ = insertNode($3, nullptr, _not_op);}
                        ;
def_stmt        : '(' DEF def_variable exp ')'  {$$ = insertNode($3, $4, _def_stmt);}
                ;
def_variable    : ID                            {$$ = insertNode(new Node(_ID, $1), nullptr, _def_variable);}
                ;
get_variable    : ID                            {$$ = insertNode(new Node(_ID, $1), nullptr, _get_variable);}
                ;
fun_exp         : '(' FUN fun_ids fun_body ')'  {$$ = insertNode($3, $4, _fun_exp);}
                ;
        fun_ids         : '(' ids ')'   {$$ = insertNode($2, nullptr, _fun_ids);}
                        ;
        fun_body        : exp           {$$ = insertNode($1, nullptr, _fun_body);}
                        ;
fun_call        : '(' fun_exp params ')'        {$$ = insertNode($2, $3, _fun_call);}
                | '(' fun_name params ')'       {$$ = insertNode($2, $3, _fun_call);}
        params          :               {$$ = nullptr;}
                        | param params  {$$ = insertNode($1, $2, _params);}
                        ;
        param           : exp   {$$ = insertNode($1, nullptr, _param);}
                        ;
        fun_name        : ID    {$$ = insertNode(new Node(_ID, $1), nullptr, _fun_name);}
                        ;
if_exp          : '(' IF test_exp if_act_exp ')' {$$ = insertNode($3, $4, _if_exp);}
                ;
        test_exp        : exp                   {$$ = insertNode($1, nullptr, _test_exp);}
                        ;
        if_act_exp      : then_exp else_exp     {$$ = insertNode($1, $2, _if_act_exp);}
                        ;
        then_exp        : exp                   {$$ = insertNode($1, nullptr, _then_exp);}
                        ;
        else_exp        : exp                   {$$ = insertNode($1, nullptr, _else_exp);}
                        ;
ids             :               {$$ = nullptr;}
                | ID ids        {$$ = insertNode(new Node(_ID, $1), $2, _ids);}
                ;
%%


void yyerror (const char *s)
{
        cerr << s << endl;
}

int main() {
        yyparse();
        printTree(root);
        cout << endl;
        traverseTree(root);
        return(0);
}
