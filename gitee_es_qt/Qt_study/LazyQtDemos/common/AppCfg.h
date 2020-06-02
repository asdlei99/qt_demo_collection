#ifndef APPCFG_H
#define APPCFG_H


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief cfgMessageOutput 设置 日子输出格式
 * @param type
 * @param context
 * @param msg
 */
void cfgMessageOutputToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#ifdef __cplusplus
}
#endif


#endif // APPCFG_H
