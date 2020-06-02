linux-oe-g++ {
LIBS += -L$$PWD/arm -lassimp
} else {
LIBS += -L$$PWD/x86 -lassimp
}
