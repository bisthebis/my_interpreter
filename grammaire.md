#Language specification 
The language supports basic artihmetic, immutable state and printing.
The only data type is double precision floating number.

##Rules
Every statement (*ie.* printing or assignment) starts with the according keyword and ends with a semicolon (;).
Assignment is of the form : 
*let var = expr;*
Printing is of the form : 
*print var;*

Expressions are composed of addtion, multiplication, substraction and division, with literals and previously defined constants.

##Syntax analysis

Formal rules :
 * Expr -> Number
 * Expr -> Variable
 * Expr -> Expr + Expr
 * Expr -> Expr - Expr
 * Expr -> Expr * Expr
 * Expr -> Expr / Expr
 * Expr -> (Expr)
 * Statement -> LetStatement
 * Statement -> PrintStatement
 * LetStatement -> let Variable = Expr;
 * PrintStatement -> print Variable;

 Terminal symbols are {Number, Variable, let, print, =, +, -, *, /, ;}
 Non-Terminal symbols are {Expr, Statement, LetStatement, PrintStatement}