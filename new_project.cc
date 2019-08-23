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
    if(!q.exec("create table if not exists \"rast123\" (id integer primary key) without rowid;")) {
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
    
    model.setData(model.index(rowCount + 0,0), rowCount +0);
    model.setData(model.index(rowCount + 1,0), rowCount +1);
    model.setData(model.index(rowCount + 2,0), rowCount +2);
    model.setData(model.index(rowCount + 3,0), rowCount +3);
    
    rowCount = model.rowCount();
    if(!model.insertRow(rowCount)) {
        qDebug() << "insertRow" << model.lastError().text();
        return 0;
    }
    model.setData(model.index(rowCount,0), rowCount);
    
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
