#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QLineEdit>

#include "ColorProgressBar.h"

class TestColorProgressBar : public QObject
{
    Q_OBJECT

public:
    TestColorProgressBar();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase2();
};

TestColorProgressBar::TestColorProgressBar()
{
}

void TestColorProgressBar::initTestCase()
{
}

void TestColorProgressBar::cleanupTestCase()
{
}

void TestColorProgressBar::testCase1()
{
    QLineEdit lineEdit;
    QTest::keyClicks(&lineEdit, "hello world");
    QCOMPARE(lineEdit.text(), QString("hello world"));
}

void TestColorProgressBar::testCase2()
{
    ColorProg1ressBar bar;
    bar.setValue(90);
    QCOMPARE(bar.getValue(), 90.0);
}

QTEST_MAIN(TestColorProgressBar)

#include "TestColorProgressBar.moc"
