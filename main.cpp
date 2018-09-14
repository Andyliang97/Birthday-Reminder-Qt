#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QList>
#include <QStringList>
#include<QDate>
#include<QtAlgorithms>



struct record{
    QString name;
    QString date;
    QDate qdate;
};

bool comparename(const record &name1,const record &name2)
{
    return name1.name<name2.name;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filename;
    QTextStream out(stdout);
    QTextStream in(stdin);

    //out<<"please enter the path of your file"<<endl;

    //in>>filename;
    QFile file("birthday.dat");
    QTextStream outfile(&file);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        qDebug()<<"cant' open the file!"<<endl;
    }

    int NoLine=0;
    QTextStream input(&file);
    QString line;
    record container;
    QList<record> list;



    while(!input.atEnd()){
        line=input.readLine();
        container.name=line;
        line=input.readLine();
        container.date=line;
        //container.qdate=QDate::fromString(line,"ddd MM d yyyy");
        list.append(container);
        NoLine++;
    }

    //file.close();

    QDate current_date;
    current_date=QDate::currentDate();
    if(argc==1)
        {
            QDate thirdtydays;
            thirdtydays=current_date.addDays(30);
            QList<QDate>templist;
            QDate toDate;

            for(int i=0;i<list.size();i++)
            {

                toDate=QDate::fromString(list[i].date,"ddd MMM d yyyy");

                if((toDate>=current_date)&&(toDate<=thirdtydays))
                {

                    templist.append(toDate);
                }
            }
            if(templist.empty())
            {out<<"No birthdays found!"<<endl;}
            else{
                qSort(templist.begin(),templist.end());
                QString srtdate;
                out<<"\tName\t\t\tBirthday\n\t====\t\t\t======"<<endl;
                for(int j=0;j<templist.size();j++)
                {
                    srtdate=templist[j].toString();
                    for(int n=0;n<list.size();n++)
                    {
                        if(srtdate==list[n].date)
                        {
                            out<<list[n].name<<"\t\t\t"<<templist[j].toString("yyyy-MM-dd")<<"\n";
                            break;
                        }
                    }
                 }
            }
        }
    if(argc>1)
    {
        try{
        if(std::string(argv[1])=="-a")
        {
            QString adddate=argv[2];
            QString addname=argv[3];
            QDate tempdate=QDate::fromString(adddate,"yyyy-MM-dd");
            QString tempstr=tempdate.toString("ddd MMM d yyyy");
            if(!tempdate.isValid())
            {throw 1;}
            else
            {
                int i;
                bool isExist=false;
                for (i=0;i<list.size();i++)
                {
                    if (addname==list[i].name)
                    {
                        isExist=true;
                        break;
                    }
                }
                if(isExist==false)
                {
                    outfile<<addname<<"\n"<<tempstr<<endl;
                    file.close();
                    out<<"\tName\t\t\tBirthday\n\t====\t\t\t======"<<endl;
                    for(int m=0;m<list.size();m++)
                {
                    list[m].qdate=QDate::fromString(list[m].date,"ddd MMM d yyyy");
                    out<<list[m].name<<"\t\t\t"<<list[m].qdate.toString("yyyy-MM-dd")<<"\n";
                }
                    out<<addname<<"\t\t\t"<<tempdate.toString("yyyy-MM-dd")<<endl;
                }
                else
                {
                    list[i].date=tempstr;
                    file.resize(0);
                    for(int j=0;j<list.size();j++)
                {
                    outfile<<list[j].name<<"\n"<<list[j].date<<endl;
                }
                    out<<"\tName\t\t\tBirthday\n\t====\t\t\t======"<<endl;
                    for(int m=0;m<list.size();m++)
                {
                    list[m].qdate=QDate::fromString(list[m].date,"ddd MMM d yyyy");
                    out<<list[m].name<<"\t\t\t"<<list[m].qdate.toString("yyyy-MM-dd")<<"\n";
                }
                }
             }
        }
        if(std::string(argv[1])=="-n")
        {
            int adddate=atoi(argv[2]);
            QDate unknownadd=current_date.addDays(adddate);
            QList<QDate>templist;
            QDate toDate;
            for(int i=0;i<list.size();i++)
            {
                toDate=QDate::fromString(list[i].date,"ddd MMM d yyyy");
                if((toDate>=current_date)&&(toDate<=unknownadd))
                {
                    templist.append(toDate);
                }
             }
            if(templist.empty())
            {out<<"No birthdays found!"<<endl;}
            else{
                 qSort(templist.begin(),templist.end());
                 QString srtdate;
                 out<<"\tName\t\t\tBirthday\n\t====\t\t\t======"<<endl;
                 for(int j=0;j<templist.size();j++)
                 {
                    srtdate=templist[j].toString();
                    for(int n=0;n<list.size();n++)
                {
                    if(srtdate==list[n].date)
                    {
                        out<<list[n].name<<"\t\t\t"<<templist[j].toString("yyyy-MM-dd")<<"\n";
                        break;
                    }
                }
                 }
             }
         }
        if(std::string(argv[1])=="-d")
        {
            QDate checkdelete=QDate::fromString(argv[2],"yyyy-MM-dd");
            QString deleteitem=checkdelete.toString("ddd MMM d yyyy");
            file.resize(0);
            if(deleteitem.isEmpty())
            {
                QString deletename=argv[2];
                for(int i=0;i<list.size();i++)
                {
                    if(deletename==list[i].name)
                    {
                        list.removeAt(i);
                        break;
                    }
                }
                for(int j=0;j<list.size();j++)
                {
                    outfile<<list[j].name<<"\n"<<list[j].date<<endl;
                }
                out<<"\tName\t\t\tBirthday\n\t====\t\t\t======"<<endl;
                for(int m=0;m<list.size();m++)
                {
                    list[m].qdate=QDate::fromString(list[m].date,"ddd MMM d yyyy");
                    out<<list[m].name<<"\t\t\t"<<list[m].qdate.toString("yyyy-MM-dd")<<"\n";
                }
            }
            else
            {
                for(int i=0;i<list.size();i++)
                {
                    if(deleteitem==list[i].date)
                    {
                        list.removeAt(i);
                    }
                }
                for(int j=0;j<list.size();j++)
                {
                    outfile<<list[j].name<<"\n"<<list[j].date<<endl;
                }
                out<<"\tName\t\t\tBirthday\n\t====\t\t\t======"<<endl;
                for(int m=0;m<list.size();m++)
                {
                    list[m].qdate=QDate::fromString(list[m].date,"ddd MMM d yyyy");
                    out<<list[m].name<<"\t\t\t"<<list[m].qdate.toString("yyyy-MM-dd")<<"\n";
                }
            }
        }
        if(std::string(argv[1])=="-m")
        {
            QDate birthdaydate;
            for(int i=0;i<list.size();i++)
            {
                if(list[i].name==argv[2])
                {
                    birthdaydate=QDate::fromString(list[i].date,"ddd MMM d yyyy");
                break;
                }
            }
            if((birthdaydate.toString("yyyy-MM-dd")).isEmpty())
            {throw 2;}
            else{
            int adddate=atoi(argv[3]);
            QDate unknownadd=birthdaydate.addDays(adddate);
            QList<QDate>templist;
            QDate toDate;
            for(int i=0;i<list.size();i++)
            {
                toDate=QDate::fromString(list[i].date,"ddd MMM d yyyy");
                if((toDate>=birthdaydate)&&(toDate<=unknownadd))
                {
                    templist.append(toDate);
                }
             }
            qSort(templist.begin(),templist.end());
            QString srtdate;
            out<<"\tName\t\t\tBirthday\n\t====\t\t\t======"<<endl;
            for(int j=0;j<templist.size();j++)
            {
                srtdate=templist[j].toString();
                for(int n=0;n<list.size();n++)
                {
                    if(srtdate==list[n].date)
                    {
                        out<<list[n].name<<"\t\t\t"<<templist[j].toString("yyyy-MM-dd")<<"\n";
                        break;
                    }
                }
            }
            }
        }
        if(std::string(argv[1])=="-r")
        {
            QDate firstdate=QDate::fromString(argv[2],"yyyy-MM-dd");
            QDate lastdate=QDate::fromString(argv[3],"yyyy-MM-dd");
            if(!firstdate.isValid())
            {throw 1;}
            else if (!lastdate.isValid())
            {throw 1;}
            else
            {
                QList<QDate>templist;
                QDate toDate;
                for(int i=0;i<list.size();i++)
                {
                    toDate=QDate::fromString(list[i].date,"ddd MMM d yyyy");
                    if((toDate>=firstdate)&&(toDate<=lastdate))
                    {
                        templist.append(toDate);
                    }
                }
                qSort(templist.begin(),templist.end());
                QString srtdate;
                if(templist.empty())
                {out<<"No birthdays found!"<<endl;}
                else{
                    out<<"\tName\t\t\tBirthday\n\t====\t\t\t======"<<endl;
                    for(int j=0;j<templist.size();j++)
                    {
                        srtdate=templist[j].toString();
                        for(int n=0;n<list.size();n++)
                        {
                            if(srtdate==list[n].date)
                            {
                                out<<list[n].name<<"\t\t\t"<<templist[j].toString("yyyy-MM-dd")<<"\n";
                                break;
                            }
                        }
                    }
                }
            }
        }
        if(std::string(argv[1])=="-q")
        {
            record tempcontainer;
            QList<record>templist;
            QDate toDate;
            QDate birthdayfirst;
            QDate birthdaylast;
            for(int i=0;i<list.size();i++)
            {
                if(list[i].name==argv[2])
                {
                    birthdayfirst=QDate::fromString(list[i].date,"ddd MMM d yyyy");
                }
                if(list[i].name==argv[3])
                {
                    birthdaylast=QDate::fromString(list[i].date,"ddd MMM d yyyy");
                }
            }
            if((birthdayfirst.toString("yyyy-MM-dd")).isEmpty())
            {throw 2;}
            else if((birthdaylast.toString("yyyy-MM-dd")).isEmpty())
            {throw 2;}
            else{
            for(int i=0;i<list.size();i++)
            {
                toDate=QDate::fromString(list[i].date,"ddd MMM d yyyy");
                if((toDate>=birthdayfirst)&&(toDate<=birthdaylast))
                {
                    tempcontainer.qdate=toDate;
                    tempcontainer.name=list[i].name;
                    templist.append(tempcontainer);
                }
            }
            qSort(templist.begin(),templist.end(),comparename);
            out<<"\tName\t\t\tBirthday\n\t====\t\t\t======"<<endl;
            for(int j=0;j<templist.size();j++)
            {
                out<<templist[j].name<<"\t\t\t"<<templist[j].qdate.toString("yyyy-MM-dd")<<"\n";
            }
            }
        }
        QString str=argv[1];
        if(!str.contains("-"))
        {
            record tempcontainer;
            QList<record> templist;
            bool isContain=false;

            for(int i=0;i<list.size();i++)
            {
                if(list[i].name.contains(str,Qt::CaseInsensitive))
                {
                    isContain=true;
                    tempcontainer.name=list[i].name;
                    tempcontainer.qdate=QDate::fromString(list[i].date,"ddd MMM d yyyy");
                    templist.append(tempcontainer);
                }
            }
            qSort(templist.begin(),templist.end(),comparename);
            if(isContain){
                out<<"\tName\t\t\tBirthday\n\t====\t\t\t======"<<endl;
                for(int j=0;j<templist.size();j++)
                {
                    out<<templist[j].name<<"\t\t\t"<<templist[j].qdate.toString("yyyy-MM-dd")<<"\n";
                }
            }
            else
            {out<<"No Namesepc found!"<<endl;}
        }
        }
        catch(int error)
        {
            if(error==1)
            {qDebug()<<"Bad time input:"<<error<<"."<<endl;}
            else if(error==2)
            {qDebug()<<"Bad name input:"<<error<<"."<<endl;}
            exit(-1);
        }
    }
   return 0;
}

