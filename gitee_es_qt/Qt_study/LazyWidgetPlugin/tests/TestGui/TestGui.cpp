#include <QString>
#include <QtTest>
#include <QLineEdit>
#include <QApplication>

class TestGui : public QObject
{
    Q_OBJECT

public:
    TestGui();

private Q_SLOTS:
    void testGui_data();
    void testGui();
};

TestGui::TestGui()
{
}

void TestGui::testGui_data()
{
    QTest::addColumn<QTestEventList>("events");
    QTest::addColumn<QString>("expected");

    QTestEventList list1;
    list1.addKeyClick('a');
    QTest::newRow("char") << list1 << "a";

    QTestEventList list2;
    list2.addKeyClick('a');
    list2.addKeyClick(Qt::Key_Backspace);
    QTest::newRow("there and back again") << list2 << "";
}

void TestGui::testGui()
{
//    QLineEdit lineEdit;
//    QTest::keyClicks(&lineEdit, "hello world");
//    QCOMPARE(lineEdit.text(), QString("hello world"));

    QFETCH(QTestEventList, events);
    QFETCH(QString, expected);

    QApplication app();
    QLineEdit lineEdit;
    app.exec();

    events.simulate(&lineEdit);

    QCOMPARE(lineEdit.text(), expected);
}

QTEST_APPLESS_MAIN(TestGui)

#include "TestGui.moc"
