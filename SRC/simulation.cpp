#include "simulation.h"
#include "ui_simulation.h"
#include <QFileDialog>
#include <QLabel>


simulation::simulation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::simulation)
{
    ui->setupUi(this);
    this->setWindowTitle("Simulation");
    connect(this,SIGNAL(senderror(QString)),this,SLOT(geterror(QString)));
    window = new graphwindowsimulation();
    container = QWidget::createWindowContainer(window);
    ui->gridLayout->addWidget(container);
    connect(this,SIGNAL(sendpath(const QString)),this,SLOT(getpath(const QString)));
    connect(this,SIGNAL(sendfinishload()),this,SLOT(getfinishload()));
    connect(window,SIGNAL(sendvalue(float,float,float)),this,SLOT(getvalue(float,float,float)));
}

simulation::~simulation()
{
    delete ui;
}

void simulation::getpath(const QString path)
{
    window->loading(path);
}

void simulation::getfinishload()
{
    window->setmpoint((maxpoints + minpoints)/2);
    SetTime *settime = new SetTime(this);
    connect(settime,SIGNAL(sendtime(float)),window,SLOT(gettime(float)));
    connect(settime,SIGNAL(sendcoef(float,int)),window,SLOT(getcoef(float,int)));
    connect(settime,SIGNAL(sendAxis(QVector3D)),window,SLOT(getAxis(QVector3D)));
    connect(settime,SIGNAL(sendangleactive(bool)),window,SLOT(getangleactive(bool)));
    connect(settime,SIGNAL(sendspeedactive(bool)),window,SLOT(getspeedactive(bool)));
    connect(settime,SIGNAL(sendaccelerationactive(bool)),window,SLOT(getaccelerationactive(bool)));
    settime->setWindowTitle("Set Time");
    settime->show();
    ui->actionTime_Coef->setEnabled(true);
}

void simulation::geterror(QString message)
{
    QMessageBox::warning(this,"Error",message,QMessageBox::Ok);
}
void simulation::on_actionAdd_file_triggered()
{
    QStringList path = (QFileDialog::getOpenFileNames(nullptr,"Choose folder with STL files","*.STL",""));
    if(path.isEmpty())
        return;
    future = QtConcurrent::run(this,&simulation::loading,path);
}

void simulation::loading(const QStringList path)
{
    for(int i = 0; i < path.length(); i++)
    {
        QFile STLfile(path[i]);
        if(!STLfile.exists() || !STLfile.open(QIODevice::ReadOnly))
        {
            emit senderror("File " + path[i] + " doesn't exist or couldn't be open!");
            return;
        }
        QTextStream stream(&STLfile);
        QString str = stream.readLine();
        if(!solidcheck(str))
        {
           emit senderror("File " + path[i] + "\nSolid was not found or gap character after that!");
           return;
        }
        str = str.mid(5,str.length() - 5);
        while(!stream.atEnd() && getmPoint(stream,str));
        emit sendpath(path[i]);
    }
    emit sendfinishload();
}

bool simulation::solidcheck(QString &str)
{
    if(str.mid(0,6) != "solid ")
        return false;
    return true;
}

bool simulation::getPoint(QString &st, QString &st1,QVector3D &A)
{
    if(!st.contains(st1))
    {
        emit senderror(st1 + " was not found!");
        return false;
    }
    QStringList CheckList = st.split(" ");
    if(CheckList.size() <= 1)
        return true;
    else if(CheckList.size() != 4)
        return false;
    A = QVector3D(CheckList[1].toFloat(),CheckList[2].toFloat(),CheckList[3].toFloat());
    return true;
}

bool simulation::getmPoint(QTextStream &stream,const QString &str)
{
    QString st[7]; // Будет содержать строки считаные из файла
    QString st1[7] = {"facet normal","outer loop","vertex","vertex","vertex","endloop","endfacet"};
    for(int i = 0; i < 7; i++)
    {
        st[i] = stream.readLine();
        if((st[i] == "endsolid") || (st[i] == "endsolid" + str))
            return false;
    }
    QVector3D P[4];
    int j = 0;
    for(int i = 0; i < 7; i++)
    {
        QVector3D A;
        if(!(getPoint(st[i],st1[i],A)))
        {
            return false;
        }
        if(A!=P[j] && j < 4)
           P[j++] = A;
    }
    if(minpoints.isNull() && maxpoints.isNull())
    {
        minpoints.setX(P[1].x());
        minpoints.setY(P[1].y());
        minpoints.setZ(P[1].z());
        maxpoints.setX(P[1].x());
        maxpoints.setY(P[1].y());
        maxpoints.setZ(P[1].z());
    }
    for(int i = 1; i < 4; i++)
    {
       if(P[i].x() < minpoints.x())
           minpoints.setX(P[i].x());
       if(P[i].y() < minpoints.y())
           minpoints.setY(P[i].y());
       if(P[i].z() < minpoints.z())
           minpoints.setZ(P[i].z());
       if(P[i].x() > maxpoints.x())
           maxpoints.setX(P[i].x());
       if(P[i].y() > maxpoints.y())
           maxpoints.setY(P[i].y());
       if(P[i].z() > maxpoints.z())
           maxpoints.setZ(P[i].z());
    }
    return true;
}

void simulation::on_actionClear_all_triggered()
{
    window->clear();
    minpoints = QVector3D(0,0,0);
    maxpoints  = QVector3D(0,0,0);
    ui->actionTime_Coef->setEnabled(false);
}

void simulation::getvalue(float anglevalue, float speedvalue, float accelerationvalue)
{
    ui->label->setText("Angle: " + QString::number(anglevalue));
    ui->label_2->setText("Speed: " + QString::number(speedvalue));
    ui->label_3->setText("Acceleration: " + QString::number(accelerationvalue));
}

void simulation::on_actionTime_Coef_triggered()
{
    SetTime *settime = new SetTime(this);
    connect(settime,SIGNAL(sendtime(float)),window,SLOT(gettime(float)));
    connect(settime,SIGNAL(sendcoef(float,int)),window,SLOT(getcoef(float,int)));
    connect(settime,SIGNAL(sendAxis(QVector3D)),window,SLOT(getAxis(QVector3D)));
    connect(settime,SIGNAL(sendangleactive(bool)),window,SLOT(getangleactive(bool)));
    connect(settime,SIGNAL(sendspeedactive(bool)),window,SLOT(getspeedactive(bool)));
    connect(settime,SIGNAL(sendaccelerationactive(bool)),window,SLOT(getaccelerationactive(bool)));
    settime->setWindowTitle("Set Time");
    settime->show();
}
