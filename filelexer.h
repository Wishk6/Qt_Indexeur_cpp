#ifndef FILELEXER_H
#define FILELEXER_H

#include <QString>
#include "lexer.h"

class FileLexer : public Lexer
{
    //Q_OBJECT
    QString m_pronoun;
    QString m_verb;
    QString m_determinant;
    QString m_animal;


public:
    FileLexer(Fsm *fsm);
    bool isPronoun();
    bool isVerb();
    bool isDeterminant();
    bool isAnimal();
    QString getPronoun() const;
    QString getVerb() const;
    QString getDeterminant() const;
    QString getAnimal() const;
    void setPronoun(const QString &newPronoun);
    void setVerb(const QString &newVerb);
    void setDeterminant(const QString &newDeterminant);
    void setAnimal(const QString &newAnimal);
};

#endif // FILELEXER_H
