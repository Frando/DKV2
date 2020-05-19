#ifndef TEST_SQLHELPER_H
#define TEST_SQLHELPER_H

#include <QObject>
#include <QSqlQuery>

class test_sqlhelper : public QObject
{
    Q_OBJECT
public:
    explicit test_sqlhelper(QObject *parent = nullptr);

private:

signals:

private slots:
    void initTestCase();
    void cleanupTestCase();
    // void init();
    // void cleanup();
    void test_sqlValInt();
    void test_sqlValBool();
    void test_sqlValDouble();
    void test_sqlValString();
    void test_sqlValDate();
    void test_getFields();
    void test_tableExists();
};

#endif // TEST_SQLHELPER_H
