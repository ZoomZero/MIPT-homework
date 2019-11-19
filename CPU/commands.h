//#ifndef COMMANDS_H
//#define COMMANDS_H

#define next_p (++(*position_number))
#define prev_p (--(*position_number))

#define DEF_LABEL(par) {\
  //int n = sizeof(label)/sizeof(label[0]);
  for(int j = 0; j < label_cnt; j++) {\
    if(strcmp(par, label[j].name) == 0)\
      return label[j].pos;\
  }\
}\

#define DEF_REG(name, number_reg, number) {\
  if(strcmp(#name, par) == 0) {\
      return number;\
  }\
}\

#define SPEC(number) {\
  DEF_REG(ax, 1, number)\
  DEF_REG(bx, 2, number)\
  DEF_REG(cx, 3, number)\
  DEF_REG(dx, 4, number)\
}\

#define PUSH_CODE
#define PUSH_REG_CODE
#define POP_CODE
#define POP_REG_CODE
#define IN_CODE
#define OUT_CODE
#define SUM_CODE
#define SUB_CODE
#define MUL_CODE
#define DIV_CODE
#define SQRT_CODE
#define JMP_CODE
#define JA_CODE
#define JB_CODE
#define JAE_CODE
#define JBE_CODE
#define JE_CODE
#define JNE_CODE
#define CALL_CODE
#define RETURN_CODE
#define END_CODE

DEF_CMD( push, 1, SPEC(2), PUSH_CODE)
DEF_CMD( push, 2,, PUSH_REG_CODE)
DEF_CMD( pop, 3, SPEC(4), POP_CODE)
DEF_CMD( pop, 4,, POP_REG_CODE)
DEF_CMD( in, 5,, IN_CODE)
DEF_CMD( out, 6,, OUT_CODE)
DEF_CMD( sum, 7,, SUM_CODE)
DEF_CMD( sub, 8,, SUB_CODE)
DEF_CMD( mul, 9,, MUL_CODE)
DEF_CMD( div, 10,, DIV_CODE)
DEF_CMD( sqrt, 11,, SQRT_CODE)
DEF_CMD( jmp, 12,, JMP_CODE)
DEF_CMD( ja, 13,, JA_CODE)
DEF_CMD( jb, 14,, JB_CODE)
DEF_CMD( jae, 15,, JAE_CODE)
DEF_CMD( jbe, 16,, JBE_CODE)
DEF_CMD( je, 17,, JE_CODE)
DEF_CMD( jne, 18,, JNE_CODE)
DEF_CMD( call, 19,, CALL_CODE)
DEF_CMD( return, 20,, RETURN_CODE)
DEF_CMD( end, 21,, END_CODE)
DEF_LABEL (par)

//#endif
