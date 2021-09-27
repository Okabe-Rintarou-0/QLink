#ifndef QCHARACTERMANAGER_H
#define QCHARACTERMANAGER_H
#include "QCharacterWidget.h"
#include "QLinkArchive.h"
#include "QLinkArchive.h"

class QCharacterManager: public QObject {
    Q_OBJECT
public:
    static QCharacterManager *getInstance();

    QCharacterWidget *getCharacter(int id);

    void addCharacter(QCharacterWidget *character);

    void frozenAll();

    void unfrozenAll();

    void loadFromArchive(const QPlayerInfo &playerInfo);

    QPlayerInfo getPlayerInfo() const;

private:
    static QCharacterManager *instance;
    QCharacterWidget **characters;

    QCharacterManager();

    QVector<QCharacterInfo> getCharacterInfos() const;

signals:
    void spawn(int id, const QPoint &pos, MoveMode moveMode);
};

#endif // QCHARACTERMANAGER_H
