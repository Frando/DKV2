#include <QStandardPaths>

#include "../DKV2/appconfig.h"
#include "../DKV2/dkdbhelper.h"
#include "testhelper.h"
#include "test_appconfig.h"

void test_appConfig::initTestCase()
{
    appConfig::setLastDb("c:/temp/data.dkdb");
    QVERIFY( ! appConfig::LastDb().isEmpty());
    appConfig::setOutDir("C:/temp/output");
    QVERIFY( ! appConfig::Outdir().isEmpty());
    initTestDb();
    init_DKDBStruct();
    create_DK_TablesAndContent();

}
void test_appConfig::cleanupTestCase()
{
    appConfig::delLastDb();
    appConfig::delOutDir();
    QVERIFY(appConfig::Outdir() == QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    cleanupTestDb();
}

void test_appConfig::test_initials()
{
    // initTastCase runs w/o error
}
void test_appConfig::test_overwrite_value()
{
    QString newValue= "newvalue";
    // overwrite value fro initTestCase
    appConfig::setLastDb(newValue +"ldb");
    QCOMPARE(appConfig::LastDb(), newValue +"ldb");
    appConfig::setOutDir(newValue +"od");
    QCOMPARE(appConfig::Outdir(), newValue +"od");
}

void test_appConfig::test_dbConfig_RuntimeData()
{
    dbConfig in; // init with default values
    QCOMPARE(in, in); // check comparison operator

    QString expectedString{qsl("gmbh adresse 1")};
    in.setValue(GMBH_ADDRESS1, expectedString);
    QCOMPARE(in.getValue(GMBH_ADDRESS1), expectedString);

    QVariant vInt{13};
    in.setValue(STARTINDEX, vInt);
    QCOMPARE(in.getValue(STARTINDEX), vInt);

    QVariant vDouble{42.24};
    in.setValue(MIN_AMOUNT, vInt);
    QCOMPARE(in.getValue(MIN_AMOUNT), vInt);
}

void test_appConfig::test_dbConfig_Db()
{
    // the "global" config data
    QString expectedString{qsl("original Db Value")};
    dbConfig::setValue(GMBH_ADDRESS1, expectedString);
    QCOMPARE(dbConfig::getValue(GMBH_ADDRESS1), expectedString);

    // now lets start a second db
    QString newDbFilename{qsl("../data/new.dkdb")};
    if( QFile::exists(newDbFilename)) QFile::remove(newDbFilename);
    QVERIFY( ! QFile::exists(newDbFilename));
    {
        QSqlDatabase newDb =QSqlDatabase::addDatabase(qsl("QSQLITE"), qsl("newdb"));
        newDb.setDatabaseName(newDbFilename);
        QVERIFY(newDb.open());
        create_DK_TablesAndContent(newDb);

        QString newValue{qsl("Value of new DB")};
        dbConfig::writeValue(GMBH_ADDRESS1, newValue, newDb);
        // the value in runtime and default db has to stay
        QCOMPARE(dbConfig::getValue(GMBH_ADDRESS1).toString(), expectedString);
        // the value in the newDB should be independent of the runtime value
        QCOMPARE(dbConfig::readValue(GMBH_ADDRESS1, newDb).toString(), newValue);
        newDb.close();
    }
    QSqlDatabase::removeDatabase(qsl("newdb"));
    QFile::remove(newDbFilename);
}
