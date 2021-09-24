#include "qlinkgameitem.h"
#include <QDebug>

void QLinkGameItem::onPick(int picker) {
    takeEffect(picker);
    setParent(nullptr);
    delete this;
}

void QLinkGameItem::tryPick(int picker, const QPoint &pickerPos){
    QPoint center = QPoint(pos().x() + width() / 2, pos().y() + height() / 2);
    QPoint diff = pickerPos - center;
    int diffX = diff.x(), diffY = diff.y();
    if (diffX * diffX + diffY * diffY <= PICK_THRESH * PICK_THRESH) {
        qDebug() << "Pick success" << endl;
        onPick(picker);
    }
}

void QLinkGameItem::takeEffect(int picker) {
    emit picked(picker);
}

void QLinkGameItem::connect(QCharacterWidget *character) {
    QApplication::connect(character, &QCharacterWidget::moveTo, this, &QLinkGameItem::tryPick);
}

QLinkGameItem::QLinkGameItem(const QString &imgPath) {
    setGeometry(0, 0, 50, 50);
    setAutoFillBackground(true);
    QImage image;
    image.load(imgPath);
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(image.scaled(size())));
    setPalette(palette);
}
