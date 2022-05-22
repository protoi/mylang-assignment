#include <stdio.h>
#include "mylang.h"
#include "mylang.tab.h"
exReturn ex(nodeType *p)
{
    // printf("entered the ex function\n"); // debug
    exReturn x;
    x.iORf = NULL;
    x.inti = 0;
    if (!p)
    {
        exReturn temp;
        temp.iORf = NULL;
        temp.inti = 0;
        return temp;
    }
    switch (p->type)
    {
    case typeCon:
        printf("\tconstant block\n"); // debug
        exReturn temp;
        temp.iORf = p->con.iORf;
        if (p->con.iORf)
        {
            temp.inti = p->con.ival;
            printf("\t\t\tthe value of the IDENTIFIER: %d\n", p->con.ival);

        }
        else
        {
            temp.floatie = p->con.fval;
            printf("\t\t\tthe value of the IDENTIFIER: %lf\n", p->con.fval);
        }
        printf(temp.iORf ? "\tconstant type: integer\n" : "\tconstant type: floating point\n");

        return temp;

    case typeId:
        printf("\tidentifier block\n"); // debug
        temp.iORf = p->id.iORf;
        printf(temp.iORf ? "\t\t\tinteger Identifier\n" : "\t\t\tfloating point variable\n");
        if (temp.iORf)
        {
            temp.inti = symInt[p->id.iIndex];
            printf("\tthe value of the identifier was: %d", (symInt[p->id.iIndex]));
        }
        else
        {
            temp.floatie = symFloat[p->id.fIndex];
            printf("\tthe value of the identifier was: %lf", (symFloat[p->id.fIndex]));
        }
        // printf(temp.iORf ? "\tidentifier type: integer\n" : "\tidentifier type: floating point\n");
        return temp;

    case typeOpr:
        switch (p->opr.oper)
        {
        case WHILE:
            temp.iORf = NULL;
            temp.inti = 0;
            while (ex(p->opr.op[0]).inti)
                ex(p->opr.op[1]);
            return temp;

        case IF:
            temp.iORf = NULL;
            temp.inti = 0;
            if (ex(p->opr.op[0]).inti)
                ex(p->opr.op[1]);
            else if (p->opr.nops > 2)
                ex(p->opr.op[2]);
            return temp;

        case DISPLAY:
            //display a55;
            printf("\tdisplay block\n");
            temp = ex(p->opr.op[0]); //p->opr.op[0] stores pointer to a55;  
            printf(temp.iORf ? "\tinteger\n" : "\tfloating point\n");
            if (temp.iORf)
                printf("%d\n", temp.inti);
            else
                printf("%lf\n", temp.floatie);
            temp.iORf = NULL;
            temp.inti = 0;
            return temp;

        case ';':
            ex(p->opr.op[0]);
            return ex(p->opr.op[1]);
        case '=':                   // assigning shit to floating point numbers messes things up for some reason
            printf("\t= clause\n"); // debug
            temp = ex(p->opr.op[1]);
            printf(temp.iORf ? "\tvalue being assigned is an integer\n" : "\tvalue being assigned is an floating point\n");
            printf("\tvalue that is being assigned is %lf: \n", temp.floatie);
            bool temptemp = p->opr.op[0]->id.iORf;
            printf(temptemp ? "\t integer variable\n" : " floating point variable\n");
            if (p->opr.op[0]->id.iORf) // variable to which we are writing is integer
            {
                if (temp.iORf) // value we are writing is integer
                {
                    symInt[p->opr.op[0]->id.iIndex] = temp.inti;
                    printf("\tinteger value assigned to an integer variable\n");
                }
                else
                {
                    symInt[p->opr.op[0]->id.iIndex] = temp.floatie;
                    printf("\tfloating value assigned to an integer variable\n");
                }
            }
            else
            {
                if (temp.iORf)
                {
                    symFloat[p->opr.op[0]->id.fIndex] = temp.inti;
                    printf("\tinteger value assigned to an floating point variable\n\tVALUE BEING ASSIGNED is: %lf\n", (double)(temp.inti));
                }
                else
                {
                    symFloat[p->opr.op[0]->id.fIndex] = temp.floatie;
                    printf("\tfloating point value assigned to an floating point variable\n\tVALUE BEING ASSIGNED is: %lf\n", (temp.floatie));
                }
            }
            return temp;

        case UMINUS:
            temp;
            temp = ex(p->opr.op[0]);
            if (temp.iORf)
                temp.inti = temp.inti * -1;
            else
                temp.floatie = temp.floatie * -1;
            return temp;

        case '+':
            exReturn a, b;
            temp.iORf = a.iORf && b.iORf;
            printf("temp.iORf is supposed to be: ");
            printf(temp.iORf ? "true\n" : "false\n");
            a = ex(p->opr.op[0]);
            b = ex(p->opr.op[1]);

            if (a.iORf) // a contains integer variable
            {
                if (b.iORf) // b contains integer variable
                    temp.inti = a.inti + b.inti;
                else
                    temp.floatie = a.inti + b.floatie;
            }
            else
            {
                if (b.iORf) // b contains integer variable
                    temp.floatie = a.floatie + b.inti;
                else
                    temp.floatie = a.floatie + b.floatie;
            }
            return temp;

        case '-':
            temp.iORf = a.iORf && b.iORf;
            a = ex(p->opr.op[0]);
            b = ex(p->opr.op[1]);

            if (a.iORf) // a contains integer variable
            {
                if (b.iORf) // b contains integer variable
                    temp.inti = a.inti - b.inti;
                else
                    temp.floatie = a.inti - b.floatie;
            }
            else
            {
                if (b.iORf) // b contains integer variable
                    temp.floatie = a.floatie - b.inti;
                else
                    temp.floatie = a.floatie - b.floatie;
            }
            return temp;

        case '*':
            temp.iORf = a.iORf && b.iORf;
            a = ex(p->opr.op[0]);
            b = ex(p->opr.op[1]);

            if (a.iORf) // a contains integer variable
            {
                if (b.iORf) // b contains integer variable
                    temp.inti = a.inti * b.inti;
                else
                    temp.floatie = a.inti * b.floatie;
            }
            else
            {
                if (b.iORf) // b contains integer variable
                    temp.floatie = a.floatie * b.inti;
                else
                    temp.floatie = a.floatie * b.floatie;
            }
            return temp;

        case '/':
            temp.iORf = a.iORf && b.iORf;
            a = ex(p->opr.op[0]);
            b = ex(p->opr.op[1]);

            if (a.iORf) // a contains integer variable
            {
                if (b.iORf) // b contains integer variable
                    temp.inti = a.inti / b.inti;
                else
                    temp.floatie = a.inti / b.floatie;
            }
            else
            {
                if (b.iORf) // b contains integer variable
                    temp.floatie = a.floatie / b.inti;
                else
                    temp.floatie = a.floatie / b.floatie;
            }
            return temp;

        case '<':
            temp.iORf = NULL;
            a = ex(p->opr.op[0]);
            b = ex(p->opr.op[1]);

            if (a.iORf) // a contains integer variable
            {
                if (b.iORf) // b contains integer variable
                    temp.inti = a.inti < b.inti;
                else
                    temp.floatie = a.inti < b.floatie;
            }
            else
            {
                if (b.iORf) // b contains integer variable
                    temp.floatie = a.floatie < b.inti;
                else
                    temp.floatie = a.floatie < b.floatie;
            }
            return temp;
        case '>':
            temp.iORf = NULL;
            a = ex(p->opr.op[0]);
            b = ex(p->opr.op[1]);

            if (a.iORf) // a contains integer variable
            {
                if (b.iORf) // b contains integer variable
                    temp.inti = a.inti > b.inti;
                else
                    temp.floatie = a.inti > b.floatie;
            }
            else
            {
                if (b.iORf) // b contains integer variable
                    temp.floatie = a.floatie > b.inti;
                else
                    temp.floatie = a.floatie > b.floatie;
            }
            return temp;
        case GE:
            temp.iORf = NULL;
            a = ex(p->opr.op[0]);
            b = ex(p->opr.op[1]);

            if (a.iORf) // a contains integer variable
            {
                if (b.iORf) // b contains integer variable
                    temp.inti = a.inti >= b.inti;
                else
                    temp.floatie = a.inti >= b.floatie;
            }
            else
            {
                if (b.iORf) // b contains integer variable
                    temp.floatie = a.floatie >= b.inti;
                else
                    temp.floatie = a.floatie >= b.floatie;
            }
            return temp;
        case LE:
            temp.iORf = NULL;
            a = ex(p->opr.op[0]);
            b = ex(p->opr.op[1]);

            if (a.iORf) // a contains integer variable
            {
                if (b.iORf) // b contains integer variable
                    temp.inti = a.inti <= b.inti;
                else
                    temp.floatie = a.inti <= b.floatie;
            }
            else
            {
                if (b.iORf) // b contains integer variable
                    temp.floatie = a.floatie <= b.inti;
                else
                    temp.floatie = a.floatie <= b.floatie;
            }
            return temp;

        case NE:
            temp.iORf = NULL;
            a = ex(p->opr.op[0]);
            b = ex(p->opr.op[1]);

            if (a.iORf) // a contains integer variable
            {
                if (b.iORf) // b contains integer variable
                    temp.inti = a.inti != b.inti;
                else
                    temp.floatie = a.inti != b.floatie;
            }
            else
            {
                if (b.iORf) // b contains integer variable
                    temp.floatie = a.floatie != b.inti;
                else
                    temp.floatie = a.floatie != b.floatie;
            }
            return temp;
        case EQ:
            temp.iORf = NULL;
            a = ex(p->opr.op[0]);
            b = ex(p->opr.op[1]);

            if (a.iORf) // a contains integer variable
            {
                if (b.iORf) // b contains integer variable
                    temp.inti = a.inti == b.inti;
                else
                    temp.floatie = a.inti == b.floatie;
            }
            else
            {
                if (b.iORf) // b contains integer variable
                    temp.floatie = a.floatie == b.inti;
                else
                    temp.floatie = a.floatie == b.floatie;
            }
            return temp;
        }
    }
    return x;
}
