#include "QStyleSheetBuilder.h"

QStyleSheetBuilder::QStyleSheetBuilder() {
    styleSheet.clear();
}

QStyleSheetBuilder *QStyleSheetBuilder::setBorderColor(const QString &color) {
    styleSheet.append(QString("border-color:%1;").arg(color));
    return this;
}

QStyleSheetBuilder *QStyleSheetBuilder::setBackgroundColor(const QString &color) {
    styleSheet.append(QString("background-color:%1;").arg(color));
    return this;
}

QStyleSheetBuilder *QStyleSheetBuilder::setBorderRadis(int radis) {
    styleSheet.append(QString("border-radius:%1px;").arg(radis));
    return this;
}

QStyleSheetBuilder *QStyleSheetBuilder::setBorder(int width, const QString &form, const QString &color) {
    styleSheet.append(QString("border:%1px %2 %3;").arg(QString::number(width), form, color));
    return this;
}

QStyleSheetBuilder *QStyleSheetBuilder::setColor(const QString &color) {
    styleSheet.append(QString("color:%1;").arg(color));
    return this;
}

QString QStyleSheetBuilder::build() {
    return styleSheet;
}
