#include <stdio.h>

#include "mylang.h"

#include "mylang.tab.h"
#include <stdbool.h>

static int lbl;

char firstSymbol(int x)
{
    x=x/100;
    return (char) (x + 'a');
}
int return SandT(int x)
{
    return x%100;
}

/*
char * symbolTableEntry (int x)
{
    int secAndThir;
    char fir;
    char answer[3];
    if(x >= 0)
    {
        int temp = x;
        secAndThir = temp%100;
        temp=temp/100;
        fir = (char)('a' + temp);
    }
    else
    {
        int temp = x;
        temp = temp * -1;
        temp=temp+1;
        secAndThir = temp%100;
        temp=temp/100;
        fir = (char)('o' + temp);
    } 

    answer[0] = fir + 'a';
    answer[1] = (char)(secAndThir/10 + 48);
    answer[2] = (char)(secAndThir%10 + 48);
    return answer;

}
*/
int ex(nodeType * p) {
  int lbl1, lbl2;
  if (!p) return 0;
  switch (p -> type) {
  case typeCon:
    if(p->con.whichConst)
      printf("\tpush\t%d\n", p -> con.ival);
    else
      printf("\tpush\t%f\n", p -> con.fval);
    break;
  case typeId:
      printf("\tpush\t%c%d\n", firstSymbol(p->id.i), SandT(p->id.i));
    break;
  case typeOpr:
    switch (p -> opr.oper) {
    case WHILE:
      printf("L%03d:\n", lbl1 = lbl++);
      ex(p -> opr.op[0]);
      printf("\tjz\tL%03d\n", lbl2 = lbl++);
      ex(p -> opr.op[1]);
      printf("\tjmp\tL%03d\n", lbl1);
      printf("L%03d:\n", lbl2);
      break;
    case IF:
      ex(p -> opr.op[0]);
      if (p -> opr.nops > 2) {
        /* if else */
        printf("\tjz\tL%03d\n", lbl1 = lbl++);
        ex(p -> opr.op[1]);
        printf("\tjmp\tL%03d\n", lbl2 = lbl++);
        printf("L%03d:\n", lbl1);
        ex(p -> opr.op[2]);
        printf("L%03d:\n", lbl2);
      } else {
        /* if */
        printf("\tjz\tL%03d\n", lbl1 = lbl++);
        ex(p -> opr.op[1]);
        printf("L%03d:\n", lbl1);
      }
      break;

    case PRINT:
      ex(p -> opr.op[0]);
      printf("\tprint\n");
      break;

      29
    case '=':
      ex(p -> opr.op[1]);
      printf("\tpop\t%s\n", p -> opr.op[0] -> symbolTableEntry(p->id.i));
      break;
    case UMINUS:
      ex(p -> opr.op[0]);
      printf("\tneg\n");
      break;
    default:
      ex(p -> opr.op[0]);
      ex(p -> opr.op[1]);
      switch (p -> opr.oper) {
      case '+':
        printf("\tadd\n");
        break;
      case '-':
        printf("\tsub\n");
        break;
      case '*':
        printf("\tmul\n");
        break;
      case '/':
        printf("\tdiv\n");
        break;
      case '<':
        printf("\tcompLT\n");
        break;
      case '>':
        printf("\tcompGT\n");
        break;
      case GE:
        printf("\tcompGE\n");
        break;
      case LE:
        printf("\tcompLE\n");
        break;
      case NE:
        printf("\tcompNE\n");
        break;
      case EQ:
        printf("\tcompEQ\n");
        break;
      }
    }
  }
  return 0;
}