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

QString QStyleSheetBuilder::build() {
    return styleSheet;
}
