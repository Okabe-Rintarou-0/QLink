#include "QStyleSheetBuilder.h"

QStyleSheetBuilder::QStyleSheetBuilder() {
    styleSheet.clear();
}

QStyleSheetBuilder *QStyleSheetBuilder::setBorderColor(QString color) {
    styleSheet.append(QString("border-color:%1;").arg(color));
    return this;
}

QStyleSheetBuilder *QStyleSheetBuilder::setBackgroundColor(QString color) {
    styleSheet.append(QString("background-color:%1;").arg(color));
    return this;
}

QString QStyleSheetBuilder::build() {
    return styleSheet;
}
