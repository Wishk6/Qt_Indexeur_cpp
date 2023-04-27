//#include <QDebug>


//QStringList stringToList(QString line) {
//    QStringList list;
//    QRegExp     rx("\"([^\"]*)\"");
//    int         pos = 0;
//    while ((pos = rx.indexIn(line, pos)) != -1) {
//        list << rx.cap(0);
//        pos += rx.matchedLength();
//    }
//    for (auto l : qAsConst(list)) {
//        QString ol = l;
//        l.replace(" ", "<SPC>");
//        line.replace(ol, l);
//    }

//    list.clear();
//    QStringList tmp = line.split(' ');
//    for (auto l : qAsConst(tmp)) {
//        if (l.isEmpty())
//            continue;

//        list << l.replace("<SPC>", " ");
//    }

//    return list;
//}


// pour test :
//QStringList l;
//l << "helo"
//  << "réda"
//  << "multi word"
//  << "\\plok\\"
//  << "\"plok is my name\\"
//  << "SEARCH \"testme please\" LAST_MODIFIED:2 days CREATED:31/12/2020 MAX_SIZE:1M EXT:txt,doc,xlsx TYPE:image OR "
//     "text"

//    ;
//for (const auto &i : qAsConst(l)) {
//    qDebug() << stringToList(i);
//    qDebug() << QUrl::toPercentEncoding(i);
//}
