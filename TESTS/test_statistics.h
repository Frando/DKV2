#ifndef TEST_STATISTICS_H
#define TEST_STATISTICS_H

#include <QObject>
#include <QSqlDatabase>

#include "../DKV2/contract.h"

#include "testhelper.h"

struct statSet {
    statSet(int co, int cre, double v, double i, double ai)
        : nbrContracts(co), nbrCreditors(cre), volume(v), interest(i), avgInterest(ai) {}
    statSet() {}
    bool operator ==(const statSet &b) const {
        QString msg;
        do {
            if( nbrContracts not_eq b.nbrContracts)
                msg +=qsl("\nNbr of contracts differ: %1 / %2").arg(QString::number(nbrContracts), QString::number(b.nbrContracts));
            if( nbrCreditors not_eq b.nbrCreditors)
                msg +=qsl("\nNbr of creditors differ: %1 / %2").arg(QString::number(nbrCreditors), QString::number(b.nbrCreditors));
            if( volume not_eq b.volume)
                msg +=qsl("\nCredit volumes differ: %1 / %2").arg(QString::number(volume), QString::number(b.volume));
            if( interest not_eq b.interest)
                msg +=qsl("\nInterest values differ: %1 / %2").arg(QString::number(interest), QString::number(b.interest));
            if( avgInterest not_eq b.avgInterest)
                msg +=qsl("\navgInterest values differ: %1 / %2").arg(QString::number(avgInterest), QString::number(b.avgInterest));
        } while(false);
        if( msg.isEmpty())
            return true;
        else {
            qInfo().noquote() << msg;
            return false;
        }
    }
    int           nbrContracts =0;
    int           nbrCreditors =0;
    double        volume =0.;
    double        interest =0.;
    double        avgInterest =0.;
};
typedef QMap<interestModel, statSet> stats;

class test_statistics : public QObject
{
    Q_OBJECT
public:
    explicit test_statistics(QObject *p =nullptr) : QObject(p){};
private:
    // helper functions
signals:
private slots:
    void init();
    void cleanup();
    // the actual tests
    void test_noContractsNoBookings();
    void test_randomContracts_50pActivated();
    void test_contracts_current_statistics();
};

#endif // TEST_STATISTICS_H
