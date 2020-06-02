#ifndef PROPERTY_DEF_H
#define PROPERTY_DEF_H

#include <QObject>
//带信号的宏
#define PropertyRW(Type, Name, ...)         \
    Q_PROPERTY(Type Name READ Name WRITE set##Name NOTIFY Name##Changed);\
    public:                                                        \
    Type m_ ## Name __VA_ARGS__;                                    \
    public:                                                         \
    Q_SIGNALS :                                                     \
    void Name ## Changed(Type a);                                   \
    public:                                                         \
    inline const Type &Name(void) const { return m_ ## Name; }      \
    inline void set ## Name(const Type &Name) { m_ ## Name = Name;      \
    Q_EMIT Name ## Changed(m_ ## Name); }


#define PropertyRO(Type, Name, ...)         \
    Q_PROPERTY(Type Name READ Name NOTIFY Name##Changed);\
    public:                                                        \
    Type m_ ## Name __VA_ARGS__;                                    \
    public:                                                         \
    Q_SIGNALS :                                                     \
    void Name ## Changed(Type a);                                   \
    public:                                                         \
    inline const Type &Name(void) const { return m_ ## Name; }      \
    private:                                                         \
    inline void set ## Name(const Type &Name) { m_ ## Name = Name;      \
    Q_EMIT Name ## Changed(m_ ## Name); }


#endif // PROPERTY_DEF_H
