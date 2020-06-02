#include <QString>
#include <QtTest>

class TestQStringTest : public QObject
{
    Q_OBJECT

public:
    TestQStringTest();

private Q_SLOTS:
    void toUpper_data();
    void toUpper();
};

TestQStringTest::TestQStringTest()
{
}

void TestQStringTest::toUpper_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    QTest::newRow("all lower") << "hello" << "HELLO";
    QTest::newRow("mixed")     << "Hello" << "HELLO";
    QTest::newRow("all upper") << "HELLO" << "HELLO";
}

void TestQStringTest::toUpper()
{
    QFETCH(QString, string);
    QFETCH(QString, result);

    QCOMPARE(string.toUpper(), result);
//    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestQStringTest)

#include "TestQStringTest.moc"
