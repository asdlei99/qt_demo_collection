#ifndef CALC_OPERANDS_H
#define CALC_OPERANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#define opr_stack_is_empty() (opr_top == 0)
extern float operands[];
extern int opr;

void opr_push(double opr);
double opr_pop(void);
void opr_clear(void);

#ifdef __cplusplus
}
#endif

#endif
