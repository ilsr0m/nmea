#include "nmeaparser.h"

NMEAParser::NMEAParser() { m_idList = new QStringList(); }

NMEAParser::NMEAParser(QString nmeaId) { m_idList = new QStringList(nmeaId); }

NMEAParser::NMEAParser(QStringList nmeaIdList) {
  m_idList = new QStringList(nmeaIdList);
}

NMEAParser::~NMEAParser() { delete m_idList; }

QString NMEAParser::parseId(QString sentence) { return sentence.mid(1, 5); }

QString NMEAParser::parseCheckSum(QString sentence) {
  QRegularExpression re("\\*[0-9ABCDEF]{2}");
  QRegularExpressionMatch match = re.match(sentence);
  if (match.hasMatch()) {
    // ignore symbol '*'
    return match.captured(0).right(2);
  }
  return NULL;
}

QString NMEAParser::parseSentence(QString sentence) {
  QRegularExpression re("^\\$[A-Z]{5},.*\\*");
  QRegularExpressionMatch match = re.match(sentence);
  if (match.hasMatch()) {
    // ignore $ and *
    QString subSentence = match.captured(0);
    return subSentence.mid(1, subSentence.length() - 2);
  }
  return NULL;
}

QString NMEAParser::getCheckSum(QString sentence) {
  // set as the first character of the sentence
  char result = sentence[0].cell();

  // XOR operation of characters one by one
  for (int i = 1; i < sentence.length(); ++i)
    result = result ^ sentence[i].cell();

  // result to hex
  QString hexResult = QString::number(result, 16).toUpper();

  return (hexResult.length() == 1) ? ("0" + hexResult) : hexResult;
}

void NMEAParser::registerParser(QString nmeaId) { m_idList->append(nmeaId); }

void NMEAParser::registerParser(QStringList nmeaIdList) {
  m_idList->append(nmeaIdList);
}

bool NMEAParser::unregisterParser(QString nmeaId) {
  return m_idList->removeOne(nmeaId);
}

QStringList NMEAParser::parse(QString sentence) {
  if (sentence.isEmpty())
    return QStringList();

  // get id
  QString id = parseId(sentence);
  // find ID
  if (m_idList->indexOf(id) == -1)
    return QStringList();

  // checksum and sentence's data
  QString ckSum = parseCheckSum(sentence);
  QString rawData = parseSentence(sentence);

  // compare check sums
  if (ckSum != getCheckSum(rawData)) {
    return QStringList();
  }

  return rawData.split(",");
}

QStringList NMEAParser::parse(NMEAParser *nmea, QString sentence) {
  return nmea->parse(sentence);
}
