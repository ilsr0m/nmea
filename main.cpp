#include "nmeaparser.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  // reg in constructor
  NMEAParser nmea = NMEAParser({"GLGSV", "GLGLL", "GLRMC", "GPRMC"});
  // single reg
  nmea.registerParser("GLVTG");
  // multiple reg
  nmea.registerParser({"GNRMC", "GPGGA", "GPGSA"});

  // list of parsed sentences
  QList<QStringList> nmea_data = {
      // parse sentences
      nmea.parse(
          "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30"),
      nmea.parse("$GPRMC,172256.313,A,5607.264,N,05657.188,E,2592261.3,278.0,"
                 "010723,000.0,W*7A"),
      nmea.parse(
          "$GPGGA,172255.313,6045.550,N,06822.734,E,1,12,1.0,0.0,M,0.0,M,,*60"),
      nmea.parse(
          "$GLGSV,3,1,09,74,08,001,34,66,55,096,,82,69,318,21,73,25,326,,0*78"),
      nmea.parse("$GLRMC,102030.000,A,5546.95900,N,03740.69200,E,0.12,49.75,"
                 "200220,,,A,V*3C"),

      // parse through static function
      NMEAParser::parse(&nmea,
                        "$GLGLL,5501.76932,S,02740.69200,E,112229.000,A*3A"),
      NMEAParser::parse(&nmea, "$GLVTG,45.05,T,,M,0.8,N,0.12,K*43"),
      NMEAParser::parse(&nmea, "$GNRMC,042330.000,A,5000.90000,N,03740.69200,E,"
                               "0.2,15.15,010101,,*19")

  };

  // print result
  foreach (auto data, nmea_data) {
    if (!data.empty()) {
      foreach (auto i, data) { qDebug() << i; }
      qDebug("");
    }
  }

  return a.exec();
}
