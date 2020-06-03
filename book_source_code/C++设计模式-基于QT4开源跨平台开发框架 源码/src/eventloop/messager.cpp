#include "messager.h"

Messager::Messager(QString msg, QWidget* parent)
        : m_Parent(parent) {
    m_Message = new QErrorMessage(parent);
    setObjectName(msg);
}

void Messager::shout() {
    m_Message->showMessage(objectName());
}

