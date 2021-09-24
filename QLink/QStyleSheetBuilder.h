#ifndef QSTYLESHEETBUILDER_H
#define QSTYLESHEETBUILDER_H

#include <QString>

class QStyleSheetBuilder {
private:
    QString styleSheet;
public:
    QStyleSheetBuilder();

    QStyleSheetBuilder *setBackgroundColor(const QString &color);

    QStyleSheetBuilder *setBorderColor(const QString &color);

    QString build();
};

#endif // QSTYLESHEETBUILDER_H