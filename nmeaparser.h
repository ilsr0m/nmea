#ifndef NMEAPARSER_H
#define NMEAPARSER_H

#include <QRegularExpression>
#include <QString>
#include <QStringList>

/**
 * @brief The QNmea class provides parsing of NMEA sentences
 */
class NMEAParser {
private:
  /**
   * @brief The string list of NMEA indetificators
   */
  QStringList *m_idList;

  /**
   * @brief The function extracts the identificator from NMEA sentence
   * @param sentence The NMEA sentence
   * @return The identificator of NMEA sentence
   */
  inline QString parseId(QString sentence);

  /**
   * @brief The function extracts the check sum string from NMEA sentence
   * @param sentence The NMEA sentence
   * @return The check sum of NMEA sentence
   */
  QString parseCheckSum(QString sentence);

  /**
   * @brief The function provides parsing the basic data of NMEA sentence
   * @param sentence The NMEA sentence
   * @return The data string of NMEA sentence
   */
  QString parseSentence(QString sentence);

  /**
   * @brief The function computes the check sum of NMEA sentence
   * @param sentence The NMEA sentence
   * @return The check sum of given sentence
   */
  QString getCheckSum(QString sentence);

public:
  NMEAParser();

  /**
   * @brief The QNmea constructor provides appending a NMEA identificator
   * previously
   * @param nmeaId NMEA identificator
   */
  NMEAParser(QString nmeaId);

  /**
   * @brief The QNmea constructor provides appending various amount of NMEA
   * identificators
   * @param nmeaIdList A group of nmea identificators
   */
  NMEAParser(QStringList nmeaIdList);

  ~NMEAParser();

  /**
   * @brief The function provides appending a NMEA identificator
   * @param nmeaId NMEA identificator to register
   */
  void registerParser(QString nmeaId);

  /**
   * @brief The funtion provides appending various amount of NMEA
   * identificators
   * @param nmeaIdList A group of nmea identificators to register
   */
  void registerParser(QStringList nmeaIdList);

  /**
   * @brief The function provides removing given nmea identificator from ID
   * list
   * @param nmeaId The nmea indetificator to unregister
   * @return The boolean success/fail of operation
   */
  bool unregisterParser(QString nmeaId);

  /**
   * @brief The function of QNmea class provides parsing of single NMEA
   * sentence
   * @param sentence The NMEA sentence
   * @return The string list of parsed NMEA sentence's data
   */
  QStringList parse(QString sentence);

  /**
   * @brief The static function of QNmea class provides parsing of single NMEA
   * sentence
   * @param nmea The QNmea class
   * @param sentence The NMEA sentence
   * @return The string list of parsed NMEA sentence's data
   */
  static QStringList parse(NMEAParser *nmea, QString sentence);
};

#endif // NMEAPARSER_H
