#ifndef TABLEDATAINSERTER_H
#define TABLEDATAINSERTER_H
#include <iso646.h>


#include "helpersql.h"
#include "dbtable.h"

struct TableDataInserter
{
    // constr. destrc. & access fu
    //TableDataInserter(){}
    TableDataInserter(const dbtable& t);
    TableDataInserter(const QString& tname, const QSqlRecord& rec) : tablename(tname), record(rec){};
    enum treatNull {allowNullValues, notAllowNullValues};
    bool setValue(const QString& field, const QVariant& v, treatNull allowNull =treatNull::notAllowNullValues);
    bool setValueToDefault(const QString& field);
    bool setValues(const QSqlRecord &rec);
    bool updateValue(const QString& n, const QVariant& v, qlonglong index);
    QVariant getValue(const QString& fieldName) const { return record.field(fieldName).value();}
    QSqlRecord getRecord() const {return record;}
    // interface
    tableindex_t InsertRecord(const QSqlDatabase &db = QSqlDatabase::database()) const;
    tableindex_t InsertData_noAuto(const QSqlDatabase &db = QSqlDatabase::database()) const;
    tableindex_t InsertOrReplaceData(const QSqlDatabase &db = QSqlDatabase::database()) const;
    tableindex_t UpdateRecord() const;
    void reset() {tablename =QString(); record =QSqlRecord();}
    void overrideTablename(const QString& tn) {tablename =tn;};
private:
    // data
    QString tablename;
    QSqlRecord record;
    //int lastRecord;
    // helper
    QString getInsertRecordSQL() const;
    QString getInsertOrReplaceRecordSQL() const;
    QString getInsert_noAuto_RecordSQL() const;
    QString getUpdateRecordSQL(tableindex_t &autovalue) const;

};



#endif // TABLEDATAINSERTER_H
