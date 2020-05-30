#include "helper.h"

#include "dbfield.h"
#include "dbtable.h"

bool dbfield::operator ==(const dbfield &b) const
{
    return ((tableName() == b.tableName())
            && (name() == b.name())
            && (type() == b.type()));
}

QString dbTypeFromVariant(QVariant::Type t)
{
    switch( t)
    {
    case QVariant::String:
        return "STRING";
    case QVariant::Int:
    case QVariant::LongLong:
        return "INTEGER";
    case QVariant::Double:
        return "REAL";
    case QVariant::Date:
        return "STRING"; // sadly ...
    case QVariant::Bool:
        return "INTEGER";
    default:
        Q_ASSERT(!bool("invalid database type"));
        return "INVALID";
    }
}

QString dbfield::getCreateSqlSnippet()
{   //LOG_CALL_W(name());
    qInfo() << "getCreateSqlSnippet(" << name() << ")";
    QString s( name() + " " + dbTypeFromVariant(type()) + " " +typeDetails());
    if( reference.name.isEmpty())
        return s;
    s += " REFERENCES " + reference.tablename +" (" + reference.name + ")";
    if( option)
    {
        if( option == refIntOption::onDeleteNull)
            s += " ON DELETE SET NULL";
        if( option == refIntOption::onDeleteCascade)
            s += " ON DELETE CASCADE";
    }
    return s;
}

refFieldInfo dbfield::getReferenzeInfo() const
{
    return refFieldInfo{reference.tablename, reference.name};
}
