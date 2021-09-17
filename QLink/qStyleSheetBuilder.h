#ifndef QSTYLESHEETBUILDER_H
#define QSTYLESHEETBUILDER_H
#include <QString>

class QStyleSheetBuilder
{
private:
    QString styleSheet;
public:
    QStyleSheetBuilder();
    QStyleSheetBuilder *setBackgroudColor(QString color);
    QStyleSheetBuilder *setBorderColor(QString color);

    QString build();
};

#endif // QSTYLESHEETBUILDER_H
