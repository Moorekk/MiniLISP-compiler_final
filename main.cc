#include "main.hh"
using namespace std;

Node::Node() {}
Node::Node(token_type t, inData *in) { this->token = t;this->indata = in; }
Data::Data() {}
Data::Data(int a) {this->I = a;}
Data::Data(bool a) {this->B = a;}
Data::Data(string a) {this->S = a;}
Data::Data(type a) {this->N = a;}
Data::operator int() { return this->I; }
Data::operator bool() { return this->B; }
Data::operator string() { return this->S; }
Data::operator type() { return this->N; }
Data::operator vector<int>() { return this->vec_I; }
Data::operator vector<bool>() { return this->vec_B; }
Data::operator vector<string>() { return this->vec_S; }
Data::operator vector<type>() { return this->vec_N; }
// template <typename Enumeration>
// auto as_integer(Enumeration const value)
//     -> typename std::underlying_type<Enumeration>::type
// {
//     return static_cast<typename std::underlying_type<Enumeration>::type>(value);
// }
map<string, type> table;
map<string, type> fun_table;
bool tmptag; // for if else stmts
void printTree(Node *tree)
{
    if(tree == nullptr) {
        cout << "NULL tree";
        return ;
    }
    if (tree->left || tree->right) cout << "(";
    cout << " " << tree->token;
    if (tree->indata)
        printf(" [%d, %d, %s] ", tree->indata->I, tree->indata->B, tree->indata->S.c_str());
    if (tree->left) printTree(tree->left);
    if (tree->right) printTree(tree->right);
    if (tree->left || tree->right) cout << ")";
}
Node *insertNode(Node *l, Node *r, token_type t)
{
    Node *p = new Node();
    p->left = l;
    p->right = r;
    p->token = t;
    p->indata = nullptr;
    return p;
}

Data numOperation(Data data, token_type op){
    Data rst = Data();
    vector<int> vec_I = data;
    vector<bool> vec_B = data;
    int tmp;
    switch (op)
    {
    case _plus:
        rst.I = 0;
        for(auto i : vec_I)
            rst.I += i;
        break;
    case _multiply:
        rst.I = 1;
        for (auto i : vec_I)
            rst.I *= i;
        break;
    case _equal:
        tmp = vec_I[0];
        rst.B = true;
        for (auto i : vec_I)
            if(i != tmp)
                rst.B = false;
        break;
    case _and_op:
        rst.B = true;
        for (auto i : vec_B)
            rst.B &= i;
        break;
    case _or_op:
        rst.B = false;
        for (auto i : vec_B)
            rst.B |= i;
        break;
    }
    return rst;
}
Data traverseTree(Node *ptr)
{

    if (ptr == nullptr) return Data(0);

    Data l = traverseTree(ptr->left);
    Data r = traverseTree(ptr->right);
    switch (ptr->token)
    {
    case _program:
        return l;
    case _stmt:
        return l;
    case _stmts:
        return l;
    case _exp:
        return l;
    case _exps:
        // l: exp int/bool
        // r: exps vector<int/bool>
        r.vec_I.push_back(l.I);
        r.vec_B.push_back(l.B);
        return r;
    case _print_stmt:{
        if (l == _PRINT_NUM)
            cout << r.I << endl;
        else if (l == _PRINT_BOOL)
        {

            if((bool)r) cout << "#t" << endl;
            else cout << "#f" << endl;
        }
        return Data(1);
    }
    case _PRINT_NUM:
        return Data(_PRINT_NUM);
    case _PRINT_BOOL:
        return Data(_PRINT_BOOL);
    case _num_op:
        return l;
        case _minus:
            return Data(l - r);
        case _divide:
            if(r == 0) return Data(0);
            return Data(l / r);
        case _modulus:
            return Data(l % r);
        case _greater:
            return Data(l > r);
        case _smaller:
            return Data(l < r);
    case _logical_op:
        return l;
        case _not_op:
            return Data(!l);
    // for multiple operator
        case _plus:
        case _multiply:
        case _equal:
        case _and_op:
        case _or_op:
            r.vec_I.push_back(l.I);
            r.vec_B.push_back(l.B);
            r = numOperation(r, ptr->token);
            return r;
        case _def_stmt:
            table[(string)l].node = ptr->right;
            return Data(1);
        case _def_variable:
            return l;
        case _get_variable:
            if (fun_table.find((string)l) != fun_table.end()) // variable in function table
                return traverseTree(fun_table[(string)l].node);
            // if (table.find((string)l) == table.end()) // not in both table
            //     cout << "Variable not define!\n"; // error
            return traverseTree(table[(string)l].node);
        case _fun_exp: // r take by fun_call
            return r;
        case _fun_ids: // function input l: vector<string>
            return l;
        case _fun_body:
            return l;
        case _fun_call:{
            // l: _fun_name(string) or _fun_exp(int/bool)
            // r: vector<type>
            if (ptr->left->token == _fun_name)
            {
                if (fun_table.find((string)l) == table.end()){ // not in table
                    cout << "Variable not define!\n";         // error
                    return Data(0);
                }
                ptr->left = table[(string)l].node->left;
                // cout << "table[" << (string)l << "] = " << table[(string)l].node->token << endl;
                // printTree(ptr->left);
                // cout << endl;
            }
            vector<string> vec_vars = traverseTree(ptr->left->left);
            vector<type> vec_exp = r;
            // cout << "length: " << vec_vars.size() << ", " << vec_exp.size() << endl;
            for (int i = 0; i < vec_exp.size(); i++)
            {
                // cout<< "fun binding: " << vec_vars[i] <<", " << vec_exp[i].node->indata->I << endl;
                fun_table[vec_vars[i]] = vec_exp[i];
            }
            l = traverseTree(ptr->left->right);
            fun_table.clear();
            return l;
        }
        case _params:
            r.vec_N.push_back(l.N); //l: type r: vector<type>
            return r;
        case _param:
            return Data(type{ptr->left->left, nullptr}); //l: exp
        case _fun_name:                            //l: string
            // cout << "fun_name: " << (string)l << endl;
            return l;
        case _if_exp:{
            // l: bool
            // r: Data
            if((bool)l) r = traverseTree(ptr->right->left);
            else        r = traverseTree(ptr->right->right);
            return r;
        }
        case _test_exp:
            return l;
        case _if_act_exp: // not used
            return Data(0);
        case _then_exp:
            return l;
        case _else_exp:
            return l;
        case _ids: //l: string r: vector<string>
            r.vec_S.push_back(l.S);
            return r;
        case _INT:
            return Data(ptr->indata->I);
        case _BOOL:
            return Data(ptr->indata->B);
        case _ID:
            return Data(ptr->indata->S);
        case _IF:
        case _DEF:
        case _FUN:
            return Data(1);
        default:
            return Data(1);
    }
}