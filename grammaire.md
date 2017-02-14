#Language specification 
The language supports basic artihmetic, immutable state and printing.
The only data type is double precision floating number.

##Rules
Every statement (*ie.* printing or assignment) starts with the according keyword and ends with a semicolon (;).
Assignment is of the form : 
*let var = expr;*
Printing is of the form : 
*print var;*

Comments start by // and go until the end of the line. There are also multi-lines comment that start with /* and end with */. It is not allowed to nest them.

Expressions are composed of addtion, multiplication, substraction, division, and exponentiation with literals and previously defined constants.

Conditions are **expressions** in the form *if cond then x else y endif*, where cond is a number and is evaluated to True if it's not 0.

##Syntax analysis

Formal rules :
 * Atom -> Number
 * Atom -> Variable
 * Atom -> function (args)
 * Atom -> (Expr)
 * Atom -> Atom ^ Atom (Not implemented soon. Maybe one day ?)
 * Term -> Atom
 * Term -> Atom * Atom
 * Term -> Atom / Atom
 * Expr -> Term
 * Expr -> Term {+ Expr}
 * Expr -> Term {- Expr}
 * Expr -> if Bool then Expr else Expr endif
 * Bool -> (Expr (>|<|==|!=|<=|>=) Expr)
 * Bool -> Expr
 * Statement -> LetStatement
 * Statement -> PrintStatement
 * LetStatement -> let Variable = Expr;
 * PrintStatement -> print Variable;

 Terminal symbols are {Number, Variable, let, print, =, +, -, *, /, ^, ;}
 Non-Terminal symbols are {Expr, Statement, LetStatement, PrintStatement}