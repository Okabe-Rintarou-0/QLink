#ifndef QLINKSQUARE_H
#define QLINKSQUARE_H

#include <QPushButton>
#include <QImage>
#include <QLabel>

class QLinkSquare {
private:
    QWidget *widget;
    QLabel *bonusLabel;
    QImage icon;
    static const QColor DEFAULT_BORDER_COLOR;
    static const QColor DEFAULT_ACTIVATE_BORDER_COLORS[2];
    static const QColor DEFAULT_HIGHLIGHT_BORDER_COLOR;
    int bonus;
    int iconIndex;
    int w;
    int h;
    bool activated;
public:

    /****************************************************
     *                Getter and Setter                 *
     ****************************************************/
     /**
      * @brief 获取方块对应的奖励
      * @return 奖励
      */
    int getBonus() const;

    /**
     * @brief 获取组件，用于辅助其他函数使用。
     * @note 该方法主要给Gridlayout使用，考虑到作为父组件本身就应该有控制子组件的能力，故暴露此接口。
     * @return 组件指针
     */
    QWidget *getWidget();

    /**
     * @brief 设置奖励
     * @param bonus 奖励
     */
    void setBonus(int bonus);

    /**
     * @brief 设置大小
     * @param w 宽度
     * @param h 高度
     */
    void setSize(int w, int h);

    /**
     * @brief 设置图标
     * @param iconIndex 图标对应ID(1~40)
     */
    void setIcon(int iconIndex);

    /**
     * @brief 判断当前方块是否被激活
     * @return 如果被激活返回true；否则返回false
     */
    bool isActivated() const;

    /**
     * @brief 获取当前方块图标的ID
     * @return 方块的图标ID
     */
    int getIconIndex() const;

    /****************************************************
     *                     Action                       *
     ****************************************************/
    /**
     * @brief 渲染图标
     */
    void renderIcon();

    /**
     * @brief 设置并渲染图标
     * @param iconIndex 图标ID
     * @param bonus 奖励
     */
    void setAndRenderIcon(int iconIndex, int bonus);

    /**
     * @brief 激活当前方块
     * @param idx 对应于玩家编号，激活会有不同的表现
     */
    void activate(int idx);

    /**
     * @brief 高亮当前图标
     */
    void highlight();

    /**
     * @brief 重置当前图标，即恢复到刚渲染出来的初始状态（无高亮、无激活表现）
     */
    void reset();

    /**
     * @brief 判断是否当前方块和另一块方块相同
     * @param other 另一个方块
     * @return 如果相同返回true；否则返回false
     */
    bool equals(QLinkSquare *other) const;

    /**
     * @brief 清除当前方块，考虑到性能只是简单隐藏
     */
    void clear();

    QLinkSquare();

    ~QLinkSquare();
};

#endif // QLINKSQUARE_H
