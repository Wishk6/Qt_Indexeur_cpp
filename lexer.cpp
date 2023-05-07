#include "lexer.h"
#include <QRegularExpression>

QString Lexer::prompt() const
{
    return m_prompt;
}

void Lexer::setPrompt(const QString &newPrompt)
{
    m_prompt = newPrompt;
    m_tokens = stringToList(m_prompt);

}

QString Lexer::currentToken() const
{
    return m_currentToken;
}

void Lexer::setCurrentToken(const QString &newCurrentToken)
{
    m_currentToken = newCurrentToken;
}

QMap<QString, QStringList> Lexer::dialectMap() const
{
    return m_dialectMap;
}

QStringList Lexer::dialectMap(const QString &str) const
{
    return m_dialectMap[str];
}

void Lexer::setDialectMap(const QMap<QString, QStringList> &newDialectMap)
{
    m_dialectMap = newDialectMap;
}

void Lexer::compute()
{
    fsm->run();

}

Lexer::Lexer(Fsm *fsm):fsm(fsm)
{

}

/**
 * @brief stringToList
 * @abstract split a string as list with double quotes (") handling
 * @param line
 * @return QStringList
 */

QStringList Lexer::stringToList(QString line) {
//        QStringList list;
//        QRegExp     rx("\"([^\"]*)\"");
//        int         pos = 0;
//        while ((pos = rx.indexIn(line, pos)) != -1) {
//            list << rx.cap(0);
//            pos += rx.matchedLength();
//        }
//        for (auto l : qAsConst(list)) {
//            QString ol = l;
//            l.replace(" ", "<SPC>");
//            line.replace(ol, l);
//        }

//        list.clear();
//        QStringList tmp = line.split(' ');
//        for (auto l : qAsConst(tmp)) {
//            if (l.isEmpty())
//                continue;

//            list << l.replace("<SPC>", " ");
//        }

//        return list;
}

bool Lexer::isStringInList(const QStringList &list,const QString &str)
{
    QStringList tmpList;
    for(const auto &elem : qAsConst(list)){
        tmpList << elem.toLower();
    }
    auto str2 = str.toLower();
    return tmpList.contains(str2);
}





