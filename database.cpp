#include "database.h"
DataBase::DataBase()
{

}

bool DataBase::createConnection()
{
    //以后就可以用"sqlite1"与数据库进行连接了
       QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "sqlite1");
       db.setDatabaseName(".//qtDb.db");
       if( !db.open())
       {
           qDebug() << "无法建立数据库连接";
           return false;
       }
       return true;

}

bool DataBase::createTable()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
      QSqlQuery query(db);
      bool success = query.exec("create table automobil(id int primary key,name varchar,"
                                "password varchar,mode1 int,mode2 int,mode3 int)");
      if(success)
      {
          qDebug() << QObject::tr("数据库表创建成功！");
          return true;
      }
      else
      {
          qDebug() << QObject::tr("数据库表创建失败！\n");
          return false;
      }

}

bool DataBase::insert(QString a, QString b)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QSqlRecord rec = query.record();

    query.prepare("insert into automobil values(?, ?, ?, ?, ?, ?)");
    query.bindValue(0,num());
    query.bindValue(1, a);
    query.bindValue(2, b);
    query.bindValue(3,0);
    query.bindValue(4, 0);
    query.bindValue(5, 0);
    bool success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }

    return true;
}

bool DataBase::queryAll()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QSqlQuery my_query(db);
    my_query.prepare("select*from automobil");
    if(!my_query.exec()){
        qDebug() << "radioForm sqlQuery error";
    }
    else{
        while (my_query.next()) {
            qDebug()<<my_query.value(1).toString()<<" "<<my_query.value(2).toString()
                      <<" "<<my_query.value(3).toInt()<<" "<<my_query.value(4).toInt()
                        <<" "<<my_query.value(5).toInt();
        }
    }
    return true;
}

int DataBase::score(int a, QString b)
{
    if(a==1){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        QSqlQuery my_query(db);
        QString select_sql = QString("select* from automobil where name='%1'").arg(b);
        if(!my_query.exec(select_sql))
        {
            qDebug()<<my_query.lastError();
        }
        else
        {
            while(my_query.next())
            {
                int temp=  my_query.value(3).toInt();
                return temp;
            }
        }
    }
    if(a==2){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        QSqlQuery my_query(db);
        QString select_sql = QString("select* from automobil where name='%1'").arg(b);
        if(!my_query.exec(select_sql))
        {
            qDebug()<<my_query.lastError();
        }
        else
        {
            while(my_query.next())
            {
                int temp=  my_query.value(4).toInt();
                return temp;
            }
        }
    }
    if(a==3){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        QSqlQuery my_query(db);
        QString select_sql = QString("select* from automobil where name='%1'").arg(b);
        if(!my_query.exec(select_sql))
        {
            qDebug()<<my_query.lastError();
        }
        else
        {
            while(my_query.next())
            {
                int temp=  my_query.value(5).toInt();
                return temp;
            }
        }
    }
}


bool DataBase::find(QString a)
{

    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QSqlQuery my_query(db);
    my_query.prepare("select*from automobil");
    if(!my_query.exec()){
        qDebug() << "radioForm sqlQuery error";
        return false;
    }
    else{
        while (my_query.next()) {
            if (a==my_query.value(1).toString()){
                 return true;
            }
        }
        return false;
    }
}

bool DataBase::modify(int a, QString b,int c)
{
    if(a==1){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery my_query(db);
        QString update_sql = QString("update automobil set mode1 = :mode1 where name='%1'").arg(b);
        my_query.prepare(update_sql);
        my_query.bindValue(":mode1", c);
        if(!my_query.exec())
        {
            qDebug() << my_query.lastError();
            return false;
        }
        else
        {
            qDebug() << "updated!";
            return true;
        }
    }
    if(a==2){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery my_query(db);
        QString update_sql = QString("update automobil set mode2 = :mode2 where name='%1'").arg(b);
        my_query.prepare(update_sql);
        my_query.bindValue(":mode2", c);
        if(!my_query.exec())
        {
            qDebug() << my_query.lastError();
            return false;
        }
        else
        {
            qDebug() << "updated!";
            return true;
        }
    }
    if(a==3){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery my_query(db);
        QString update_sql = QString("update automobil set mode3 = :mode3 where name='%1'").arg(b);
        my_query.prepare(update_sql);
        my_query.bindValue(":mode3", c);
        if(!my_query.exec())
        {
            qDebug() << my_query.lastError();
            return false;
        }
        else
        {
            qDebug() << "updated!";
            return true;
        }
    }
}

int *DataBase::sort(int a)
{
    static int temp[10];
    if(a==1){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        QSqlQuery my_query(db);
        my_query.prepare("select*from automobil order by mode1 desc ");
        if(!my_query.exec()){
            qDebug() << "radioForm sqlQuery error";
        }
        else{
            int i=0;
        while (my_query.next()&&i<10) {
            temp[i]=my_query.value(3).toInt();
            i++;
        }
    }
        }
    if(a==2){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        QSqlQuery my_query(db);
        my_query.prepare("select*from automobil order by mode2 desc ");
        if(!my_query.exec()){
            qDebug() << "radioForm sqlQuery error";
        }
        else{
            int i=0;
        while (my_query.next()&&i<10) {
            temp[i]=my_query.value(4).toInt();
            i++;
        }
    }
        }
    if(a==3){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        QSqlQuery my_query(db);
        my_query.prepare("select*from automobil order by mode3 desc ");
        if(!my_query.exec()){
            qDebug() << "radioForm sqlQuery error";
        }
        else{
            int i=0;
        while (my_query.next()&&i<10) {
            temp[i]=my_query.value(5).toInt();
            i++;
        }
    }
}
return temp;

}

QString *DataBase::name_sort(int a)
{
    static QString temp[10];
    if(a==1){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        QSqlQuery my_query(db);
        my_query.prepare("select*from automobil order by mode1 desc ");
        if(!my_query.exec()){
            qDebug() << "radioForm sqlQuery error";
        }
        else{
            int i=0;
        while (my_query.next()&&i<10) {
            temp[i]=my_query.value(1).toString();
            i++;
        }
    }
        }
    if(a==2){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        QSqlQuery my_query(db);
        my_query.prepare("select*from automobil order by mode2 desc ");
        if(!my_query.exec()){
            qDebug() << "radioForm sqlQuery error";
        }
        else{
            int i=0;
        while (my_query.next()&&i<10) {
            temp[i]=my_query.value(1).toString();
            i++;
        }
    }
        }
    if(a==3){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        QSqlQuery my_query(db);
        my_query.prepare("select*from automobil order by mode3 desc ");
        if(!my_query.exec()){
            qDebug() << "radioForm sqlQuery error";
        }
        else{
            int i=0;
        while (my_query.next()&&i<10) {
            temp[i]=my_query.value(1).toString();
            i++;
        }
    }
}
return temp;

}

bool DataBase::check(QString a, QString b)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QSqlQuery my_query(db);
    my_query.prepare("select*from automobil");
    if(!my_query.exec()){
        qDebug() << "radioForm sqlQuery error";
        return false;
    }
    else{
        while (my_query.next()) {
            if (a==my_query.value(1).toString()&&b==my_query.value(2).toString()){
                 return true;
            }
        }
        return false;
    }
}

QString DataBase::log(QString a, QString b)
{
    if(check(a,b)){
        return a;
    }

}

int DataBase::num()
{   QSqlDatabase db = QSqlDatabase::database("sqlite1");
    QSqlQuery query = QSqlQuery(db);
    query.exec("SELECT * FROM automobil");
    QSqlQueryModel *queryModel = new QSqlQueryModel();
    queryModel->setQuery(query);
    return queryModel->rowCount();
}

