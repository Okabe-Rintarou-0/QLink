#ifndef QCHARACTERMANAGER_H
#define QCHARACTERMANAGER_H
#include "QCharacterWidget.h"
#include "QLinkArchive.h"

class QCharacterManager
{
public:
    static QCharacterManager *getInstance();

    QCharacterWidget *getCharacter(int id);

    void addCharacter(QCharacterWidget *character);

    void frozenAll();

    void unfrozenAll();

    QPlayerInfo getPlayerInfo() const;

private:
    static QCharacterManager *instance;
    QCharacterWidget **characters;

    QCharacterManager();

    QVector<QCharacterInfo> getCharacterInfos() const;
};

#endif // QCHARACTERMANAGER_H
