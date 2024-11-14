#include <QtTest/QTest>
class TestFileparcer : public QObject {
    Q_OBJECT

public:
    TestFileparcer(QObject *parent = 0);
    ~TestFileparcer();

private slots:
    void testParserDataLengh();
    void testParserError();
    void testDateTimeChange();
};
