#include "filelexer.h"
#include <QMap>

QString FileLexer::getPronoun() const
{
    return m_pronoun;
}
QString FileLexer::getVerb() const
{
    return m_verb;
}

QString FileLexer::getAnimal() const
{
    return m_animal;
}

QString FileLexer::getDeterminant() const
{
    return m_determinant;
}


void FileLexer::setPronoun(const QString &newPronoun)
{
    m_pronoun = newPronoun;
}

void FileLexer::setVerb(const QString &newVerb)
{
    m_verb = newVerb;
}

void FileLexer::setDeterminant(const QString &newDeterminant)
{
    m_determinant = newDeterminant;
}

void FileLexer::setAnimal(const QString &newAnimal)
{
    m_animal = newAnimal;
}

FileLexer::FileLexer(Fsm *fsm):Lexer(fsm)
{
    QMap<QString,QStringList> dialectMap;
    dialectMap["pronouns"] = {"I","you"};
    dialectMap["verbs"] = {"am","are","eat"};
    dialectMap["determinants"] = {"a","the"};
    dialectMap["animals"] = {"cat","bird"};
    setDialectMap(dialectMap);
}



bool FileLexer::isPronoun()
{
    return isStringInList(dialectMap("pronouns"),currentToken());
}

bool FileLexer::isVerb()
{
    return isStringInList(dialectMap("verbs"),currentToken());
}

bool FileLexer::isDeterminant()
{
    return isStringInList(dialectMap("determinants"),currentToken());
}

bool FileLexer::isAnimal()
{
    return isStringInList(dialectMap("animals"),currentToken());
}
