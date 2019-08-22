This repository contains a series of experiments with Qt's QSqlTableModel class.
My objective for these experiments was to determine why this table structure causes issues with "No Fields"

```SQL
CREATE TABLE preferences(
    person TEXT NOT NULL,
    dish TEXT NOT NULL,
    inclination TEXT NOT NULL,
    PRIMARY KEY(person, dish)
    WITHOUT ROWID;
```

I'm using SQLite (3.28.0 2019-04-16 19:49:53 884b4b7e502b4e991677b53971277adfaf0a04a284f8e483e2553d0f83156b50) and qt 5.13.0.

I started with a working example from the [Qt Forum](https://forum.qt.io/topic/18097/insert-new-rows-into-database-using-qsqltablemodel/5).
This copy of this example resides in a [Git repository](https://github.com/bminard/qt_qsqltablemodel).

Each change to bring the table in the example closer to my ideal is on a separate branch.
This permits a simple diff between the master branch and the changed branch to determine the alterations I've made to the original example.

These branches as as follows.

- master: is functionally equivalent to the example downloaded from the Qt Forum.
