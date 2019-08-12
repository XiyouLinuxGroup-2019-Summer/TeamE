#ifndef MODEL_H
#define MODEL_H
#include<QString>
//num1  num2

class model
{
public:
    model();
    // she zhi san ge fang fa
    void setNum1(int num);
    void setNum2(int num);
    void setFlag(QString flag);
    QString doExpr();


private:
    int num1;
    int num2;
    QString flag;
 //   int result;
};

#endif // MODEL_H
