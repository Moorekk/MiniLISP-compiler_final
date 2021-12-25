# MiniLISP
## Compile

> compile main  

```g++ -c main.cc```  
> compile bison  

```bison -d -o yacc.tab.c final_MiniLISP.y```  
```g++ -c -g -I.. yacc.tab.c```  
> compile flex  

```flex -o lex.yy.c final_MiniLISP.l```  
```g++ -c -g -I.. lex.yy.c```
> compile and link bison, flex and main  

```g++ -o final_MiniLISP yacc.tab.o lex.yy.o main.o -ll```  
> remove redundent files  

```rm lex.yy.c lex.yy.o yacc.tab.c yacc.tab.h yacc.tab.o main.o```  

## Operations
> Numerical Operators

|Name| Symbol| Example|
|-|-|-|
|Plus| +| (+ 1 2) => 3|
|Minus| -| (- 1 2) => -1|
|Multiply |*| (* 2 3) => 6|
|Divide |/| (/ 6 3) => 2|
|Modulus |mod| (mod 8 3) => 2|
|Greater |>| (> 1 2) => #f|
|Smaller |<| (< 1 2) => #t|
|Equal| =| (= 1 2) => #f|

> Logical Operators

|Name |Symbol| Example|
|-|-|-|
|And |and| (and #t #f) => #f|
|Or |or| (or #t #f) => #t|
|Not |not| (not #t) => #f|

## Grammer
```
program         : stmts
stmts           : stmt stmts
                | ε
stmt            : exp
                | def_stmt
                | print_stmt
print_stmt      : '(' PRINT_NUM exp ')'
                | '(' PRINT_BOOL exp ')'
exps            : exp exps
                | ε
exp             : BOOL
                | INT
                | get_variable
                | num_op
                | logical_op
                | fun_exp
                | fun_call
                | if_exp
num_op          : plus
                | minus
                | multiply
                | divide
                | modulus
                | greater
                | smaller
                | equal
        plus            : '(' ADD exp exps ')'
        minus           : '(' SUB exp exp ')'
        multiply        : '(' MUL exp exps ')'
        divide          : '(' DIV exp exp ')'
        modulus         : '(' MOD exp exp ')'
        greater         : '(' GRT exp exp ')'
        smaller         : '(' SML exp exp ')'
        equal           : '(' EQL exp exps ')'
logical_op      : and_op
                | or_op
                | not_op
        and_op          : '(' AND exp exps ')'
        or_op           : '(' OR exp exps ')'
        not_op          : '(' NOT exp ')'
def_stmt        : '(' DEF def_variable exp ')'
def_variable    : ID
get_variable    : ID
fun_exp         : '(' FUN fun_ids fun_body ')'
        fun_ids         : '(' ids ')'
        fun_body        : exp
fun_call        : '(' fun_exp params ')'
                | '(' fun_name params ')'
        params          : ε
                        | param params
        param           : exp
        fun_name        : ID
if_exp          : '(' IF test_exp if_act_exp ')'
        test_exp        : exp
        if_act_exp      : then_exp else_exp
        then_exp        : exp
        else_exp        : exp
ids             : 
                | ID ids
```
## Defined Classes Functions
**classes:**  

```Node``` node in abstract systax tree  
```Data``` data that passing while traversing AST  

**functions:**  

```printTree``` display AST structure  
```insertNode``` construct the AST  
```traverseTree``` traverse AST and perfom corresponding behaviors  

## Basic Features
> complete

|Feature| Description|
|-|-|
|1. Syntax Validation |Print “syntax error” when parsing invalid syntax |
|2. Print |Implement print-num statement|
|3. Numerical Operations| Implement all numerical operations|
|4. Logical Operations|Implement all logical operations|
|5. if Expression| Implement if expression |
|6. Variable |Definition Able to define a variable|
|7. Function |Able to declare and call an anonymous function (can't recursion) |
|8. Named Function| Able to declare and call a named function |

## Bonus Features
> not complete

|Feature| Description|
|-|-|
|1. Recursion| Support recursive function call|
|2. Type Checking| Print error messages for type errors |
|3. Nested Function |Nested function (static scope) |
|4. First-class Function| Able to pass functions, support closure |

## Type checking
> not complete

|Op| Parameter Type| Output Type|
|-|-|-|
|+, -, *, /, mod| Number(s)| Number|
|>, <, = |Number(s)| Boolean|
|and, or, not| Boolean(s)| Boolean|
|If| Boolean(s) for test-exp| Depend on then-exp and else-exp|
|Fun| Any| Function|
|Function call| Any| Depend on fun-body and parameters|
