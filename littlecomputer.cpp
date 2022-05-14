#include "littlecomputer.h"

LittleComputer::LittleComputer(QString codeText)
{
    registerA = 0;
    registerB = 0;
    currentLine = 0;
    memory = new long[MEMORY_SIZE];
    code = codeText.split("\n");
}

LittleComputer::~LittleComputer()
{
    delete [] memory;
}

bool LittleComputer::isMemory(QString str)
{
    if(str[0] == "$")
    {
        QRegExp re("\\d*");
        QString numberStr = str.mid(1);
        if(re.exactMatch(numberStr))
        {
            bool checkConv = false;
            long number = numberStr.toLong(&checkConv);
            if(checkConv && number >= 0 && number < MEMORY_SIZE)
                return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

int LittleComputer::getMemory(QString str)
{
    return str.mid(1).toInt();
}

bool LittleComputer::isString(QString str)
{
    if(str.startsWith('"') && str.endsWith('"'))
    {
        return true;
    }

    return false;
}

QString LittleComputer::getString(QString str)
{
    return str.mid(1,str.size()-2);
}

bool LittleComputer::isNumber(QString str)
{
    bool checkConv = false;
    str.toLong(&checkConv);

    if(checkConv)
        return true;
    else
        return false;
}

long LittleComputer::getNumber(QString str)
{
    return str.toLong();
}

bool LittleComputer::isLabel(QString str)
{
    if(str.startsWith('_') && str.endsWith('_'))
        return true;
    else
        return false;
}

QString LittleComputer::getLabel(QString str)
{
    return str.mid(1,str.size()-2);
}

int LittleComputer::getLabelNumber(QString str)
{
    // Use if the str.isInLabels() == true
    return labels[str];
}

bool LittleComputer::isInLabels(QString str)
{
    return labels.contains(str);
}

void LittleComputer::scanLabels()
{
    int sizeOfCode = code.size();
    while(currentLine < sizeOfCode)
    {
        QStringList line = parseLine(code[currentLine]);
        if(line.size() == 1)
        {
            if(isLabel(line[0]))
            {
                labels.insert(getLabel(line[0]), currentLine);
            }
        }
        currentLine++;
    }
}

QStringList LittleComputer::parseLine(QString str)
{
    return str.trimmed().split(" ");
}

void LittleComputer::processLine(QString str)
{
    if(str.simplified().remove(' ')[0]=="#")
    {
        // It is a comment line
        currentLine++;
        return;
    }

    QStringList line = parseLine(str);
    if(line.size() == 0)
    {
        currentLine++;
        return;
    }
    else if(line.size() == 1)
    {
        if(line[0] == "NOP")
        {

        }
        else if(isLabel(line[0]))
        {

        }
        else if(line[0] == "SLEEP")
        {
            QThread::sleep(1);
        }
        else if(line[0] == "CLEAR")
        {
            emit clearConsol();
        }
        else
        {
            //qDebug() << "One parameter must be _LABEL_ or NOP";
        }
        currentLine++;
        return;
    }
    else if(line.size() == 2)
    {
        if(line[0] == "PRINT")          //todo:Clear ekle
        {
            if(line[1] == "A")
            {
                emit printConsol(QString::number(registerA));
            }
            else if(line[1] == "B")
            {
                emit printConsol(QString::number(registerB));
            }
            else if(isMemory(line[1]))
            {
                emit printConsol(QString::number(memory[getMemory(line[1])]));
            }
            else if(isString(line[1]))
            {
                emit printConsol(getString(line[1]));
            }
            else if(line[1]=="SPACE")
            {
                emit printConsol(QString(" "));
            }
            else if(line[1]=="LINE")
            {
                emit printConsol(QString("\n"));
            }
            currentLine++;
        }
        else if(line[0] == "JMP")
        {
            if(isInLabels(getLabel(line[1])))
            {
                currentLine = getLabelNumber(getLabel(line[1])) + 1;
            }
            else
            {
                qDebug() << line[1] << "is not in label list!";
                currentLine++;
            }

        }
        else if(line[0] == "JAGZ")
        {
            if(isInLabels(getLabel(line[1])))
            {
                if(registerA > 0)
                {
                    currentLine = getLabelNumber(getLabel(line[1])) + 1;
                }
                else
                {
                    currentLine++;
                }
            }
            else
            {
                qDebug() << line[1] << "is not in label list!";
                currentLine++;
            }
        }
        else if(line[0] == "JALZ")
        {
            if(isInLabels(getLabel(line[1])))
            {
                if(registerA < 0)
                {
                    currentLine = getLabelNumber(getLabel(line[1])) + 1;
                }
                else
                {
                    currentLine++;
                }
            }
            else
            {
                qDebug() << line[1] << "is not in label list!";
                currentLine++;
            }
        }
        else if(line[0] == "JAEZ")
        {
            if(isInLabels(getLabel(line[1])))
            {
                if(registerA == 0)
                {
                    currentLine = getLabelNumber(getLabel(line[1])) + 1;
                }
                else
                {
                    currentLine++;
                }
            }
            else
            {
                qDebug() << line[1] << "is not in label list!";
                currentLine++;
            }
        }
        else if(line[0] == "JBGZ")
        {
            if(isInLabels(getLabel(line[1])))
            {
                if(registerB > 0)
                {
                    currentLine = getLabelNumber(getLabel(line[1])) + 1;
                }
                else
                {
                    currentLine++;
                }
            }
            else
            {
                qDebug() << line[1] << "is not in label list!";
                currentLine++;
            }
        }
        else if(line[0] == "JBLZ")
        {
            if(isInLabels(getLabel(line[1])))
            {
                if(registerB < 0)
                {
                    currentLine = getLabelNumber(getLabel(line[1])) + 1;
                }
                else
                {
                    currentLine++;
                }
            }
            else
            {
                qDebug() << line[1] << "is not in label list!";
                currentLine++;
            }
        }
        else if(line[0] == "JBEZ")
        {
            if(isInLabels(getLabel(line[1])))
            {
                if(registerB == 0)
                {
                    currentLine = getLabelNumber(getLabel(line[1])) + 1;
                }
                else
                {
                    currentLine++;
                }
            }
            else
            {
                qDebug() << line[1] << "is not in label list!";
                currentLine++;
            }
        }
    }
    else if(line.size() == 3)
    {
        if(line[0] == "CPY")
        {
            if(line[1] == "A")
            {
                if(isMemory(line[2]))
                {
                    registerA = memory[getMemory(line[2])];
                }
                else if(isNumber(line[2]))
                {
                    registerA = getNumber(line[2]);
                }
                else if(line[2] == "B")
                {
                    registerA = registerB;
                }
                else
                {
                    qDebug() << "ERROR: CPY A ?";
                }
            }
            else if(line[1] == "B")
            {
                if(isMemory(line[2]))
                {
                    registerB = memory[getMemory(line[2])];
                }
                else if(isNumber(line[2]))
                {
                    registerB = getNumber(line[2]);
                }
                else if(line[2] == "A")
                {
                    registerB = registerA;
                }
                else
                {
                    qDebug() << "ERROR: CPY B ?";
                }
            }
            currentLine++;
        }
        else if(line[0] == "MOV")
        {
            if(isMemory(line[1]))
            {
                if(line[2] == "A")
                {
                    memory[getMemory(line[1])] = registerA;
                }
                else if(line[2] == "B")
                {
                    memory[getMemory(line[1])] = registerB;
                }
                else if(isMemory(line[2]))
                {
                    memory[getMemory(line[1])] = memory[getMemory(line[2])];
                }
                else if(isNumber(line[2]))
                {
                    memory[getMemory(line[1])] = getNumber(line[2]);
                }
                else
                {
                    qDebug() << "MOV $ADDRESS ?";
                }

            }
            else
            {
                qDebug() << "MOV ?";
            }
            currentLine++;
        }
        else if(line[0] == "ADD")
        {
            if(line[1] == "A")
            {
                if(line[2] == "B")
                {
                    registerA += registerB;
                }
                else if(isNumber(line[2]))
                {
                    registerA += getNumber(line[2]);
                }
                else if(isMemory(line[2]))
                {
                    registerA += getMemory(line[2]);
                }
                else
                {
                    qDebug() << "ADD A ?";
                }
            }
            else if(line[1] == "B")
            {
                if(line[2] == "A")
                {
                    registerB += registerA;
                }
                else if(isNumber(line[2]))
                {
                    registerB += getNumber(line[2]);
                }
                else if(isMemory(line[2]))
                {
                    registerB += getMemory(line[2]);
                }
                else
                {
                    qDebug() << "ADD B ?";
                }
            }
            else
            {
                qDebug() << "ADD ?";
            }
            currentLine++;
        }
        else if(line[0] == "SUB")
        {
            if(line[1] == "A")
            {
                if(line[2] == "B")
                {
                    registerA -= registerB;
                }
                else if(isNumber(line[2]))
                {
                    registerA -= getNumber(line[2]);
                }
                else if(isMemory(line[2]))
                {
                    registerA -= getMemory(line[2]);
                }
                else
                {
                    qDebug() << "SUB A ?";
                }
            }
            else if(line[1] == "B")
            {
                if(line[2] == "A")
                {
                    registerB -= registerA;
                }
                else if(isNumber(line[2]))
                {
                    registerB -= getNumber(line[2]);
                }
                else if(isMemory(line[2]))
                {
                    registerB -= getMemory(line[2]);
                }
                else
                {
                    qDebug() << "SUB B ?";
                }
            }
            else
            {
                qDebug() << "SUB ?";
            }
            currentLine++;
        }
        else if(line[0] == "MUL")
        {
            if(line[1] == "A")
            {
                if(line[2] == "B")
                {
                    registerA *= registerB;
                }
                else if(isNumber(line[2]))
                {
                    registerA *= getNumber(line[2]);
                }
                else if(isMemory(line[2]))
                {
                    registerA *= getMemory(line[2]);
                }
                else
                {
                    qDebug() << "MUL A ?";
                }
            }
            else if(line[1] == "B")
            {
                if(line[2] == "A")
                {
                    registerB *= registerA;
                }
                else if(isNumber(line[2]))
                {
                    registerB *= getNumber(line[2]);
                }
                else if(isMemory(line[2]))
                {
                    registerB *= getMemory(line[2]);
                }
                else
                {
                    qDebug() << "MUL B ?";
                }
            }
            else
            {
                qDebug() << "MUL ?";
            }
            currentLine++;
        }
        else if(line[0] == "DIV")
        {
            if(line[1] == "A")
            {
                if(line[2] == "B")
                {
                    registerA /= registerB;
                }
                else if(isNumber(line[2]))
                {
                    registerA /= getNumber(line[2]);
                }
                else if(isMemory(line[2]))
                {
                    registerA /= getMemory(line[2]);
                }
                else
                {
                    qDebug() << "DIV A ?";
                }
            }
            else if(line[1] == "B")
            {
                if(line[2] == "A")
                {
                    registerB /= registerA;
                }
                else if(isNumber(line[2]))
                {
                    registerB /= getNumber(line[2]);
                }
                else if(isMemory(line[2]))
                {
                    registerB /= getMemory(line[2]);
                }
                else
                {
                    qDebug() << "DIV B ?";
                }
            }
            else
            {
                qDebug() << "DIV ?";
            }
            currentLine++;
        }
    }
}

void LittleComputer::processCode()
{
    currentLine = 0;    // Since it increases in scanLabels function
    int sizeOfCode = code.size();
    while(currentLine < sizeOfCode)
    {
        processLine(code[currentLine]);
    }
}

void LittleComputer::run()
{
    scanLabels();
    processCode();
}
