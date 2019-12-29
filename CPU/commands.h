#define POS (*pos_number)
#define NEXT_P ++(POS)
#define PREV_P --(POS)

#define START_COMMAND(status) \
   if (status == StartProgram) {

#define POP(EL) data_t EL = StackPop(stk)

#define PUSH(EL) StackPush(stk, EL)

#define END_COMMAND }

#define PUSH_CODE\
  START_COMMAND(*programme_status)\
  \
  NEXT_P;\
  PUSH(command[POS]);\
  \
  return 0;\
  END_COMMAND\

#define PUSH_REG_CODE\
  START_COMMAND(*programme_status)\
  \
  NEXT_P;\
  PUSH(reg[command[POS] - 1]);\
  \
  return 0;\
  END_COMMAND\

#define POP_CODE\
  START_COMMAND(*programme_status)\
  \
  POP(x);\
  \
  return 0;\
  END_COMMAND\

#define POP_REG_CODE\
  START_COMMAND(*programme_status)\
  \
  NEXT_P;\
  POP(x);\
  reg[command[POS] - 1] = x;\
  \
  return 0;\
  END_COMMAND\

#define IN_CODE\
  START_COMMAND(*programme_status)\
  \
  data_t el;\
  scanf("%d\n", &el);\
  PUSH(el);\
  \
  return 0;\
  END_COMMAND\

#define OUT_CODE\
  START_COMMAND(*programme_status)\
  \
  POP(x);\
  printf("%d\n", x);\
  \
  return 0;\
  END_COMMAND\

#define SUM_CODE\
  START_COMMAND(*programme_status)\
  \
  POP(x);\
  POP(y);\
  PUSH(x + y);\
  \
  return 0;\
  END_COMMAND\

#define SUB_CODE\
  START_COMMAND(*programme_status)\
  \
  POP(x);\
  POP(y);\
  PUSH(x - y);\
  \
  return 0;\
  END_COMMAND\

#define MUL_CODE\
  START_COMMAND(*programme_status)\
  \
  POP(x);\
  POP(y);\
  PUSH(x * y);\
  \
  return 0;\
  END_COMMAND\

#define DIV_CODE\
  START_COMMAND(*programme_status)\
  \
  POP(x);\
  POP(y);\
  PUSH(x / y);\
  \
  return 0;\
  END_COMMAND\

#define SQRT_CODE\
  START_COMMAND(*programme_status)\
  \
  POP(x);\
  if(x >= 0) PUSH(sqrt(x));\
  \
  return 0;\
  END_COMMAND\

#define JMP_CODE\
  START_COMMAND(*programme_status)\
  \
  NEXT_P;\
  POS = command[POS];\
  PREV_P;\
  \
  return 0;\
  END_COMMAND\

#define JA_CODE\
  START_COMMAND(*programme_status)\
  \
  NEXT_P;\
  POP(x);\
  POP(y);\
  if(x < y) POS = command[POS];\
  PREV_P;\
  \
  return 0;\
  END_COMMAND\

#define JB_CODE\
  START_COMMAND(*programme_status)\
  \
  NEXT_P;\
  POP(x);\
  POP(y);\
  if(x > y) POS = command[POS];\
  PREV_P;\
  \
  return 0;\
  END_COMMAND\

#define JAE_CODE\
  START_COMMAND(*programme_status)\
  \
  NEXT_P;\
  POP(x);\
  POP(y);\
  if(x <= y) POS = command[POS];\
  PREV_P;\
  \
  return 0;\
  END_COMMAND\

#define JBE_CODE\
  START_COMMAND(*programme_status)\
  \
  NEXT_P;\
  POP(x);\
  POP(y);\
  if(x >= y) POS = command[POS];\
  PREV_P;\
  \
  return 0;\
  END_COMMAND\

#define JE_CODE\
  START_COMMAND(*programme_status)\
  \
  NEXT_P;\
  POP(x);\
  POP(y);\
  if(x == y) POS = command[POS];\
  PREV_P;\
  \
  return 0;\
  END_COMMAND\

#define JNE_CODE\
  START_COMMAND(*programme_status)\
  \
  NEXT_P;\
  POP(x);\
  POP(y);\
  if(x != y) POS = command[POS];\
  PREV_P;\
  \
  return 0;\
  END_COMMAND\

#define CALL_CODE
#define RETURN_CODE

#define END_CODE\
  START_COMMAND(*programme_status)\
  \
    *programme_status = EndProgram;\
  \
  return EndProgram;\
  END_COMMAND\

DEF_CMD( push, 1, SPEC(2), PUSH_CODE)
DEF_CMD( push, 2, , PUSH_REG_CODE)
DEF_CMD( pop, 3, SPEC(4), POP_CODE)
DEF_CMD( pop, 4, , POP_REG_CODE)
DEF_CMD( in, 5, , IN_CODE)
DEF_CMD( out, 6, , OUT_CODE)
DEF_CMD( sum, 7, , SUM_CODE)
DEF_CMD( sub, 8, , SUB_CODE)
DEF_CMD( mul, 9, , MUL_CODE)
DEF_CMD( div, 10, , DIV_CODE)
DEF_CMD( sqrt, 11, , SQRT_CODE)
DEF_CMD( jmp, 12, , JMP_CODE)
DEF_CMD( ja, 13, , JA_CODE)
DEF_CMD( jb, 14, , JB_CODE)
DEF_CMD( jae, 15, , JAE_CODE)
DEF_CMD( jbe, 16, , JBE_CODE)
DEF_CMD( je, 17, , JE_CODE)
DEF_CMD( jne, 18, , JNE_CODE)
DEF_CMD( call, 19, , CALL_CODE)
DEF_CMD( ret, 20, , RETURN_CODE)
DEF_CMD( end, 21, , END_CODE)
DEF_LABEL
