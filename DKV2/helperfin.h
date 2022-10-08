#ifndef HELPERFIN_H
#define HELPERFIN_H


#include "pch.h"
#include "helper.h"

inline double r2(const double d)
{
    return (qRound(d * 100.))/100.;
}

inline int ctFromEuro( const double d)
{
    return qRound( d * 100.);
}
inline double euroFromCt( const int i)
{
    return double (i)/100.;
}
inline double dbInterest2Interest(int p) {
    return r2(double(p)/100.);
}

inline QString i2s(int x)       {return QString::number(x);}

inline QString d2euro(double x) {
    static QLocale locale;
    return locale.toCurrencyString(x);
}

inline QString prozent2prozent_str(double x) {
    static QLocale locale;
    return qsl("%1 %").arg(locale.toString(x, 'f', 2));
};

inline auto dbInterest2_str(int p) {
    return prozent2prozent_str(dbInterest2Interest (p));
}

int TageZwischen_30_360(QDate von, QDate bis);

int TageBisJahresende_30_360(QDate d);
int TageBisJahresende_lookup(const QDate& d);
int TageSeitJahresAnfang_30_360(QDate d);
int TageSeitJahresAnfang_lookup(const QDate& d);

double ZinsesZins_30_360(const double zins, const double wert,const QDate von, const QDate bis, const bool thesa=true);
double ZinsesZins_act_act(const double zins, const double wert,const QDate von, const QDate bis, const bool thesa=true);

#endif // HELPERFIN_H
