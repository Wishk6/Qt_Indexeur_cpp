#ifndef LEXER_H
#define LEXER_H

#include "fsm.h"
#include <QObject>
#include <QMap>

class Lexer
{
    //Q_OBJECT
    QString m_prompt;
    QStringList m_tokens;
    QString m_currentToken;
    QMap<QString,QStringList> m_dialectMap;
    Fsm *fsm;
public:
    Lexer(Fsm *fsm);
    QString prompt() const;
    void setPrompt(const QString &newPrompt);
    static QStringList stringToList(QString line);
    static bool isStringInList(const QStringList &list,const QString &str);
    QString currentToken() const;
    void setCurrentToken(const QString &newCurrentToken);
    QMap<QString, QStringList> dialectMap() const;
    QStringList dialectMap(const QString &str) const;
    void setDialectMap(const QMap<QString, QStringList> &newDialectMap);
    void compute();

};

#endif // LEXER_H
