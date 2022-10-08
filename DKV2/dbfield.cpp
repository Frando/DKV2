#include <iso646.h>

#include "helper.h"
#include "helpersql.h"

#include "dbfield.h"

/* static */ bool dbfield::isSupportedDBType(QVariant::Type t)
{
    if(t == QVariant::LongLong) return true; // index col
    if(t == QVariant::Int)      return true; // money in ct
    if(t == QVariant::Date)     return true;
    if(t == QVariant::DateTime) return true; // booking date & time
    if(t == QVariant::String)   return true;
    if(t == QVariant::Bool)     return true;
    if(t == QVariant::Double)   return true;
    Q_ASSERT_X(true, "isSupportedType: ", "unsupported database data type");
    return false;
}

bool dbfield::operator ==(const dbfield &b) const
{
    return ((tableName() == b.tableName())
            and (name()  == b.name())
            and (type()  == b.type()));
}

QString dbfield::get_CreateSqlSnippet() const
{
    return name()
            + qsl(" ") + dbCreatetable_type(type())
            + (primaryKey ? qsl(" PRIMARY KEY") : "")
            + (isAutoValue()? qsl(" AUTOINCREMENT") : "")
            + ((requiredStatus()==Required)? qsl(" NOT NULL") : "")
            + ((unique ? qsl(" UNIQUE") : "" ))
            + (defaultValue().isValid()
               ? qsl(" DEFAULT ")+ DbInsertableString(defaultValue())
               : (timeStamp ? qsl( " DEFAULT CURRENT_TIMESTAMP") : ""));
}

//////////////////////
/// dbForeignKey
//////////////////////

const QVector<QString> dbForeignKey::ODOU_Actions ={
    qsl("NO ACTION"),
    qsl("RESTRICT"),
    qsl("SET NULL"),
    qsl("SET DEFAULT"),
    qsl("CASCADE")};

QString dbForeignKey::get_CreateSqlSnippet()
{
    Q_ASSERT_X( (not refTable.isEmpty()) && (not refField.isEmpty()), "creating foreignKey sql", "table and name must not be empty");
    return qsl("FOREIGN KEY (%1) REFERENCES %2 (%3) %4 %5").arg(field, refTable, refField, onDelete, onUpdate);
}

QString dbForeignKey::get_SelectSqlWhereClause()
{   // todo: is this function really used?
    Q_ASSERT_X( (not refTable.isEmpty()) && (not refField.isEmpty()), "creating foreignKey select sql", "table and name must not be empty");
    QString sql;
    if( table.size()) sql = table + qsl(".");
    sql += field + qsl("=") + refTable + qsl(".") + refField;
    return sql;
}
