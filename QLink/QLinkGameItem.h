#ifndef QLINKGAMEITEM_H
#define QLINKGAMEITEM_H

#include <QWidget>
#include <QApplication>
#include "FileConstants.h"
#include "QCharacterWidget.h"

class QLinkGameItem : public QWidget {
    Q_OBJECT
public:
    enum JewelType {
        UNDEFINED = -1, TIME, SHUFFLE, HINT, FLASH
    };

    QLinkGameItem(const QString &imgPath);

    virtual ~QLinkGameItem() = default;

    /**
     * @brief 执行一些信号函数和槽函数的连接工作
     * @param character 需要建立连接关系的角色
     */
    virtual void connect(QCharacterWidget *character);

    /**
     * @brief 游戏物品生效
     * @param picker 拾取者，有些道具对拾取者有效果
     */
    virtual void takeEffect(int picker);

    /**
     * @brief 物品的类型
     * @return 返回物品类型
     */
    JewelType getJewelType() const;

private:

    /**
     * @brief 被拾取后触发的回调
     * @param picker 拾取者
     */
    void onPick(int picker);

    static constexpr int PICK_THRESH = 50;

    static constexpr int DEFAULT_H = 50;

    static constexpr int DEFAULT_W = 50;

protected:
    JewelType jewelType = UNDEFINED;

    signals:
            void picked(int
    picker);

public
slots:
    void tryPick(int picker, const QPoint &pickerPos);
};

#endif // QLINKGAMEITEM_H
