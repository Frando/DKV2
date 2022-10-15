#ifndef DLGASKDATE_H
#define DLGASKDATE_H



class dlgAskDate : public QDialog
{
    Q_OBJECT
public:
    explicit dlgAskDate(QWidget *parent = nullptr);
    void setDate(QDate d) {dateEdit->setDate(d);}
    QDate date(void) {return dateEdit->date();}
    void setHeader(const QString &s) {header->setText(s);}
    void setMsg(const QString &s) {msg->setText(s);}
// signals:
private slots:
    void showEvent(QShowEvent*) override;
private:
    QLabel* header;
    QLabel* msg;
    QDateEdit* dateEdit;
    QDialogButtonBox* buttons;
};

#endif // DLGASKDATE_H
