#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QModelIndex>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("rast123.sqlite");
    
    if(!db.open()) {
        qDebug() << db.lastError().text();
        return 0;
    }
    
    QSqlQuery q(db);
    if(!q.exec("create table if not exists \"rast123\" (id text not null, num text not null, primary key(id, num)) ;")) {
        qDebug() << "Create table" << q.lastError().text();
        return 0;
    }
    
    QSqlTableModel model(0, db);
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);
    model.setTable("rast123");
    model.select();
    
    model.database().transaction();
    
    int rowCount = model.rowCount();
    qDebug() << rowCount;
    if(!model.insertRows(rowCount, 4)) {
        qDebug() << "insertRows" << model.lastError().text();
        return 0;
    }
    
    /* id */
    model.setData(model.index(rowCount + 0,0), "0");
    model.setData(model.index(rowCount + 1,0), "1");
    model.setData(model.index(rowCount + 2,0), "2");
    model.setData(model.index(rowCount + 3,0), "3");

    /* num */
    model.setData(model.index(rowCount + 0,1), "0");
    model.setData(model.index(rowCount + 1,1), "1");
    model.setData(model.index(rowCount + 2,1), "2");
    model.setData(model.index(rowCount + 3,1), "3");
    
    rowCount = model.rowCount();
    if(!model.insertRow(rowCount)) {
        qDebug() << "insertRow" << model.lastError().text();
        return 0;
    }
    model.setData(model.index(rowCount,0), "4");
    model.setData(model.index(rowCount,1), "4");
    
    if(model.submitAll()) {
        model.database().commit();
    } else {
        model.database().rollback();
                qDebug() << "Database Write Error" <<
                     "The database reported an error: " <<
                       model.lastError().text();
    
    }
    
    return 0;
}
