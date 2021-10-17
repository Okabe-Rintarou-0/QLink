#ifndef QSTYLESHEETBUILDER_H
#define QSTYLESHEETBUILDER_H

#include <QString>

/**
 * @brief 用于生成stylesheet字符串的辅助类
 * @note 考虑到本质上和java中的StringBuilder是很类似的，所以也采用建造者模式。
 */
class QStyleSheetBuilder {
private:
    QString styleSheet;
public:
    QStyleSheetBuilder();

    QStyleSheetBuilder *setBackgroundColor(const QString &color);

    QStyleSheetBuilder *setBorderColor(const QString &color);

    QStyleSheetBuilder *setBorderRadis(int radis);

    QStyleSheetBuilder *setBorder(int width, const QString &form, const QString &color);

    QStyleSheetBuilder *setColor(const QString &color);

    QString build();
};

#endif // QSTYLESHEETBUILDER_H
