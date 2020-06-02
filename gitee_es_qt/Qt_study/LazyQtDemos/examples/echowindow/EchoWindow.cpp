#include <QtWidgets>

#include "EchoWindow.h"

EchoWindow::EchoWindow(QWidget *parent)
    : QWidget(parent)
{
    createGUI();
    setLayout(layout);
    setWindowTitle("Echo Plugin Example");

    if (!loadPlugin()) {
        QMessageBox::information(this, "Error", "Could not load the plugin");
        lineEdit->setEnabled(false);
        button->setEnabled(false);
    }
}

EchoWindow::~EchoWindow()
{

}

void EchoWindow::sendEcho()
{
    QString text = echoInterface->echo(lineEdit->text());
    label->setText(text);
}

void EchoWindow::createGUI()
{
    lineEdit = new QLineEdit;
    label = new QLabel;
    label->setFrameStyle(QFrame::Box | QFrame::Plain);
    button = new QPushButton(tr("Send Message"));

    connect(lineEdit, SIGNAL(editingFinished()),
            this, SLOT(sendEcho()));
    connect(button, SIGNAL(clicked()),
            this, SLOT(sendEcho()));

    layout = new QGridLayout;
    layout->addWidget(new QLabel(tr("Message:")), 0, 0);
    layout->addWidget(lineEdit, 0, 1);
    layout->addWidget(new QLabel(tr("Answer:")), 1, 0);
    layout->addWidget(label, 1, 1);
    layout->addWidget(button, 2, 1, Qt::AlignRight);
    layout->setSizeConstraint(QLayout::SetFixedSize);
}

bool EchoWindow::loadPlugin()
{
    const QByteArray lazySrcDirBytes = qgetenv("QT_LAZY_SRCDIR");
    QString pluginPath = "";
    if (!lazySrcDirBytes.isEmpty()) {
        pluginPath = QString::fromLocal8Bit(lazySrcDirBytes) + "/build_msvc2015/echoplugin";
    } else {
        pluginPath = qApp->applicationDirPath() + "/../../..";
    }

    QDir pluginsDir(pluginPath);
    // QDir pluginsDir(qApp->applicationDirPath());

//    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release") {
//        pluginsDir.cdUp();
//        pluginsDir.cdUp();
//        pluginsDir.cdUp();
//    }

    // 这个地方可能需要修改， 如何能够在其他地方合理的配置这个路径
//    pluginsDir.cd("plugins");
    // pluginsDir.cd("plugindist");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            echoInterface = qobject_cast<EchoInterface *>(plugin);
            if (echoInterface)
                return true;
        }
    }

    return false;
}
