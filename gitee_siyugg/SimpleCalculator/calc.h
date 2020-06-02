#ifndef CALC_CALC_H
#define CALC_CALC_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 运算式最长为129 - 1 = 128字节
 */
#define MAX_LENGTH  129

/**
 * @brief The opt_prior 表示一个运算符及其优先级，运算符
 * 及其优先级的定义见calc.c
 */
struct opt_prior
{
	char opt;
	int prior;
};

/**
 * @brief check 检查运算表达式形式是否正确
 * @return 正确返回1，否则返回0
 */
int check(void);

/**
 * @brief get_prior 取得一个运算符的优先级
 * @param opt 运算符，用char表示
 * @return 运算符的优先级
 */
int get_prior(char opt);

/**
 * @brief cmp_prior 比较两个运算符的优先级
 * @param opt1 运算符1
 * @param opt2 运算符2
 * @return 两个运算符优先级的差值
 */
int cmp_prior(char opt1,char opt2);

/**
 * @brief get_float_from_str 从运算式字符串中解析出一个float数值
 * @return 解析出的float
 */
float get_double_from_str(void);

/**
 * @brief figure 对两个数进行计算
 * @param left_value 左计算数
 * @param rignt_value 右计算数
 * @param opt 运算符
 * @return 计算结果
 */
double figure(double left_value,double rignt_value,char opt);

/**
 * @brief parse 对运算式进行解析
 */
void parse(void);

/**
 * @brief get_expression 从键盘输入运算式
 */
void  get_expression(void);

/**
 * @brief expression 运算式
 */
extern char expression[MAX_LENGTH];

#ifdef __cplusplus
}
#endif

#endif
