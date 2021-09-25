#ifndef QLINKGAMEITEM_H
#define QLINKGAMEITEM_H
#include <QWidget>
#include <QApplication>
#include "FileConstants.h"
#include "QCharacterWidget.h"

class QLinkGameItem: public QWidget
{
    Q_OBJECT
public:
    enum JewelType { UNDEFINED, TIME, FLASH, SHUFFLE, HINT };

    QLinkGameItem(const QString &imgPath);

    virtual ~QLinkGameItem() = default;

    virtual void connect(QCharacterWidget *character);

    virtual void takeEffect(int picker);

    JewelType getJewelType() const;
private:

    void onPick(int picker);

    static constexpr int PICK_THRESH = 15;

    static constexpr int DEFAULT_H = 50;

    static constexpr int DEFUALT_W = 50;

protected:
    JewelType jewelType = UNDEFINED;
signals:
    void picked(int picker);

public slots:
    void tryPick(int picker, const QPoint &pickerPos);
};

#endif // QLINKGAMEITEM_H
