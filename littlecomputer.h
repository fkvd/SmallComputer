#ifndef LITTLECOMPUTER_H
#define LITTLECOMPUTER_H
#include <QThread>
#include <QObject>
#include <QStringList>
#include <QString>
#include <QRegularExpression>
#include <QDebug>
#include <QMap>
#include <QScrollBar>
#include <QTextCursor>

/***
 * ADD A B/5/$10
 * SUB A B/5/$10
 * MUL A B/5/$10
 * DIV A B/5/$10
 *
 * CPY A B/$3/2
 *
 * MOV $2 3
 *
 * _LABEL_          **
 *
 * NOP
 *
 * JMP  _LABEL_     **
 * JAEZ _LABEL_
 * JBBZ _LABEL_
 *
 * PRINT A/$10/5/"hello"
 *
 */

class LittleComputer : public QThread
{
    Q_OBJECT
private:
    static const int MEMORY_SIZE = 10;
    long * memory;
    long registerA;
    long registerB;
    long currentLine;
    QStringList code;
    QMap<QString, int> labels;

public:
    LittleComputer(QString);
    ~LittleComputer();
    bool isMemory(QString);
    int getMemory(QString);
    bool isString(QString);
    QString getString(QString);
    bool isNumber(QString);
    long getNumber(QString);
    bool isLabel(QString);
    QString getLabel(QString);
    int getLabelNumber(QString);
    bool isInLabels(QString);
    void scanLabels();
    QStringList parseLine(QString);
    void processLine(QString);
    void processCode();
    void run() override;

signals:
    void printConsol(QString);
    void clearConsol();
};

#endif // LITTLECOMPUTER_H
