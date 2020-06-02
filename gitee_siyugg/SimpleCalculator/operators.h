#ifndef CALC_OPERATORS_H
#define CALC_OPERATORS_H

#ifdef __cplusplus
extern "C" {
#endif

#define opt_get_top() (operators[opt_top - 1])
#define opt_stack_is_empty() (opt_top == 0)
extern char operators[];
extern int opt_top;
extern void opt_push(char ch);
extern char opt_pop(void);
extern void opt_clear(void);

#ifdef __cplusplus
}
#endif

#endif
