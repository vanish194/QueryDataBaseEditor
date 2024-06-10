#include "databaseaction.h"

DataBaseAction::DataBaseAction()
{
    this->model1=new CustomQueryModel;

}
DataBaseAction::~DataBaseAction()
{
    if(true) DataBaseAction::database_commit();
    else DataBaseAction::database_rollback();
    database.close();
}
void DataBaseAction::database_connecting(const QString& fileName)
{
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(fileName);
    database.open();
    database_refresh();

    //QSqlDatabase::database().transaction();
}
void DataBaseAction::insert_additional_mnemonic_units(const QString &additional_mnemonic_name, const int &additional_mnemonic_id, const int &conversion_formula_id)
{

    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO additional_mnemonic_units (additional_mnemonic_unit_name, additional_mnemonic_id, conversion_formula_id) "
                                 "VALUES (?,?,?)"));
    query.addBindValue(additional_mnemonic_name);
    query.addBindValue(additional_mnemonic_id);
    query.addBindValue(conversion_formula_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса iamu:" << query.lastError().text();
    }
}

void DataBaseAction::insert_additional_mnemonics(const QString &additional_mnemonic_name, const int &company_id, const int &main_mnemonic_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO additional_mnemonics(additional_mnemonic_name,company_id,main_mnemonic_id)"
                                 "VALUES(?,?,?)"));
    query.addBindValue(additional_mnemonic_name);
    query.addBindValue(company_id);
    query.addBindValue(main_mnemonic_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса iam:" << query.lastError().text();
    }
}

void DataBaseAction::insert_companies(const QString &company_name)
{
    //+
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO companies(company_name)"
                                 "VALUES(?)"));
    query.addBindValue(company_name);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса ic:" << query.lastError().text();
    }
}

void DataBaseAction::insert_conversion_formaulas(const QString &conversion_formula)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO conversion_formaulas(conversion_formula)"
                                 "VALUES(?)"));
    query.addBindValue(conversion_formula);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса icf:" << query.lastError().text();
    }
}

void DataBaseAction::insert_main_mnemonic_units(const QString &main_mnemonic_unit_name, const QString &main_mnemonic_unit_description, const int &main_mnemonic_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO main_mnemonic_units(main_mnemonic_unit_name,main_mnemonic_unit_description,sensor_id)"
                                 "VALUES(?,?,?)"));
    query.addBindValue(main_mnemonic_unit_name);
    query.addBindValue(main_mnemonic_unit_description);
    query.addBindValue(main_mnemonic_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса immu:" << query.lastError().text();
    }
}

void DataBaseAction::insert_main_mnemonics(const QString &main_mnemonic_name, const QString &main_mnemonic_description, const int &sensor_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO main_mnemonics(main_mnemonic_name,main_mnemonic_description,sensor_id)"
                                 "VALUES(?,?,?)"));
    query.addBindValue(main_mnemonic_name);
    query.addBindValue(main_mnemonic_description);
    query.addBindValue(sensor_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса imm:" << query.lastError().text();
    }
}

void DataBaseAction::insert_methods(const QString &method_name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO methods()"
                  "VALUES(?)");
    query.addBindValue(method_name);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса im:" << query.lastError().text();
    }
}

void DataBaseAction::insert_produsers(const QString &produser_name)
{//+
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO produsers(produser_name)"
                                 "VALUES(?)"));
    query.addBindValue(produser_name);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса ip:" << query.lastError().text();
    }
}

void DataBaseAction::insert_sensor_descriptions(const QString &sensor_descriptions, const QString &offset)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO sensor_descriptions(sensor_description,offset)"
                                 "VALUES(?,?)"));
    query.addBindValue(sensor_descriptions);
    query.addBindValue(offset);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса isd:" << query.lastError().text();
    }
}

void DataBaseAction::insert_sensors(const QString &sensor_name, const int &tool_id, const int &method_id, const int &sensor_description_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO sensors(sensor_name,tool_id,method_id,sensor_description_id)"
                                 "VALUES(?,?,?,?)"));
    query.addBindValue(sensor_name);
    query.addBindValue(tool_id);
    query.addBindValue(method_id);
    query.addBindValue(sensor_description_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса is:" << query.lastError().text();
    }
}

void DataBaseAction::insert_tool_descriptions(const QString &description, const QString &length, const QString &outer_diameter,
                                              const QString &inner_diameter, const QByteArray  &image,const int produser_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO tool_descriptions(description,length,outer_diameter,inner_diameter,image,produser_id)"
                                 "VALUES(?,?,?,?,?,?)"));
    query.addBindValue(description);
    query.addBindValue(length);
    query.addBindValue(outer_diameter);
    query.addBindValue(inner_diameter);
    query.addBindValue(image);
    query.addBindValue(produser_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса itd:" << query.lastError().text();
    }
}

void DataBaseAction::insert_tools(const QString &tool_name, const int &tool_description_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO tools(tool_name,tool_description_id)"
                                 "VALUES(?,?)"));
    query.addBindValue(tool_name);
    query.addBindValue(tool_description_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса it:" << query.lastError().text();
    }
}

void DataBaseAction::remove_additional_mnemonic_units(const int& additional_mnemonic_unit_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM additional_mnemonic_units\
        WHERE additional_mnemonic_unit_id=?"));
    query.addBindValue(additional_mnemonic_unit_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса ramu:" << query.lastError().text();
    }
}

void DataBaseAction::remove_additional_mnemonics(const int& addtitonal_mnemonic_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM addtitonal_mnemonics\
        WHERE addtitonal_mnemonic_id=?"));
    query.addBindValue(addtitonal_mnemonic_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса ram:" << query.lastError().text();
    }
}

void DataBaseAction::remove_companies(const int& company_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM companies\
        WHERE company_id=?"));
    query.addBindValue(company_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса rc:" << query.lastError().text();
    }
}

void DataBaseAction::remove_conversion_formaulas(const int& conversion_formula_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM conversion_formulas\
        WHERE conversion_formula_id=?"));
    query.addBindValue(conversion_formula_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса rcf:" << query.lastError().text();
    }
}

void DataBaseAction::remove_main_mnemonic_units(const int& main_mnemonic_unit_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM main_mnemonic_units\
        WHERE main_mnemonic_unit_id=?"));
    query.addBindValue(main_mnemonic_unit_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса rmmu:" << query.lastError().text();
    }
}

void DataBaseAction::remove_main_mnemonics(const int& main_mnemonic_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM main_mnemonics\
        WHERE main_mnemonic_id=?"));
    query.addBindValue(main_mnemonic_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса rmm:" << query.lastError().text();
    }
}

void DataBaseAction::remove_methods(const int& method_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM methods\
        WHERE method_id=?"));
    query.addBindValue(method_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса rm:" << query.lastError().text();
    }
}

void DataBaseAction::remove_produsers(const int& produser_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM produsers\
        WHERE produser_id=?"));
    query.addBindValue(produser_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса rp:" << query.lastError().text();
    }
}

void DataBaseAction::remove_sensor_descriptions(const int& sensor_description_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM sensor_descriptions\
        WHERE sensor_description_id=?"));
    query.addBindValue(sensor_description_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса rsd:" << query.lastError().text();
    }
}

void DataBaseAction::remove_sensors(const int& sensor_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM sensors\
        WHERE sensor_id=?"));
    query.addBindValue(sensor_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса rs:" << query.lastError().text();
    }
}

void DataBaseAction::remove_tool_descriptions(const int& tool_description_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM tool_descriptions\
        WHERE tool_description_id=?"));
    query.addBindValue(tool_description_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса rtd:" << query.lastError().text();
    }
}

void DataBaseAction::remove_tools(const int& tool_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM tools\
        WHERE tool_id=?"));
    query.addBindValue(tool_id);
    if(!query.exec()){
        qDebug() << "Ошибка выполнения запроса rt:" << query.lastError().text();
    }
}

void DataBaseAction::database_commit()
{
    QSqlDatabase::database().commit();
}
void DataBaseAction::database_transaction()
{
    QSqlDatabase::database().transaction();
}
void DataBaseAction::database_rollback()
{
    QSqlDatabase::database().rollback();
}

void DataBaseAction::database_refresh()
{
    model1->setQuery("SELECT *\
FROM\
  additional_mnemonic_units\
  FULL JOIN additional_mnemonics ON (additional_mnemonic_units.additional_mnemonic_id = additional_mnemonics.additional_mnemonic_id)\
  FULL JOIN companies ON (additional_mnemonics.company_id = companies.company_id)\
  FULL JOIN conversion_formulas ON (additional_mnemonic_units.conversion_formula_id = conversion_formulas.conversion_formula_id)\
  FULL JOIN main_mnemonics ON (additional_mnemonics.main_mnemonic_id = main_mnemonics.main_mnemonics_id)\
  FULL JOIN sensors ON (main_mnemonics.sensor_id = sensors.sensor_id)\
  FULL JOIN tools ON (sensors.tool_id = tools.tool_id)\
  FULL JOIN tool_descriptions ON (tool_descriptions.tool_desciption_id = tools.tool_description_id)\
  FULL JOIN produsers ON (tool_descriptions.produser_id = produsers.produser_id)\
  FULL JOIN methods ON (sensors.method_id = methods.method_id)\
  FULL JOIN sensor_descriptions ON (sensors.sensor_description_id = sensor_descriptions.sensor_description_id)\
  FULL JOIN main_mnemonic_units ON (main_mnemonic_units.main_mnemonic_id = main_mnemonics.main_mnemonics_id)\
");
}

void DataBaseAction::database_upload()
{
    database_commit();
    database_refresh();
}

int DataBaseAction::find_id_where_condition(QString type_id, QString table_name, QString condition)
{
    QSqlQuery query;
    query.prepare("SELECT "+ type_id+" FROM "+table_name+" WHERE "+condition);
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса find_id_where_comdition:" << query.lastError().text();
    }
    QVariant q1;
    if (query.next()){
        q1=query.value(0);
    }
    return q1.toInt();
}

QVariantList DataBaseAction::get_unique_values(QString columnName, QString tableName)
{
    QVariantList unique_values;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT " + columnName + " FROM "+tableName);
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса get_unique_values:" << query.lastError().text();
        return unique_values;
    }

    // Извлекаем уникальные значения и сохраняем их в массиве
    while (query.next()) {
        unique_values.append(query.value(0)); // Предполагается, что значение находится в первом столбце
    }
    return unique_values;
}

