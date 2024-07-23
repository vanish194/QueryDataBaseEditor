#include "databaseaction.h"

DataBaseAction::DataBaseAction()
{
    this->model1 = new CustomQueryModel;
    this->treemodel = new QStandardItemModel;
}
DataBaseAction::~DataBaseAction()
{
    delete model1;
    delete treemodel;
    if (true)
        DataBaseAction::database_commit();
    else
        DataBaseAction::database_rollback();
    database.close();
}
void DataBaseAction::database_connecting(const QString &fileName)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(fileName);
    database.open();
    QSqlQuery q;
    q.exec("PRAGMA foreign_keys = ON");

    database_refresh();

    //QSqlDatabase::database().transaction();
}

void DataBaseAction::tree_model_create()
{
    treemodel->clear();

    QSqlQuery query;
    query.prepare(QStringLiteral("SELECT\
                  tools.tool_name,\
                  sensors.sensor_name,\
                  main_mnemonics.main_mnemonic_name,\
                  additional_mnemonics.additional_mnemonic_name\
                  FROM\
                  sensors\
                  FULL JOIN tools ON (sensors.tool_id = tools.tool_id)\
                  FULL  JOIN main_mnemonics ON (sensors.sensor_id = main_mnemonics.sensor_id)\
                  FULL  JOIN additional_mnemonics ON (main_mnemonics.main_mnemonic_id = additional_mnemonics.main_mnemonic_id)"));
    if (!query.exec()) {
        qDebug() << "error executing the request treemodel create:" << query.lastError().text();
    }

    // QMap для хранения иерархии данных
    QMap<QString, QMap<QString, QMap<QString, QStringList>>> data_hierarchy;

    // Создание структуры иерархии на основе результата запроса
    while (query.next()) {
        QString tool_name = query.value(0).toString();
        QString sensor_name = query.value(1).toString();
        QString main_mnemonic_name = query.value(2).toString();
        QString additional_mnemonic_name = query.value(3).toString();

        // Добавление данных в QMap
        data_hierarchy[tool_name][sensor_name][main_mnemonic_name].append(additional_mnemonic_name);
    }

    // Добавление элементов в модель данных на основе данных иерархии
    for (auto tool_iter = data_hierarchy.begin(); tool_iter != data_hierarchy.end(); ++tool_iter) {
        QStandardItem *tool_item = new QStandardItem(tool_iter.key());
        treemodel->appendRow(tool_item);

        for (auto sensor_iter = tool_iter.value().begin(); sensor_iter != tool_iter.value().end();
             ++sensor_iter) {
            QStandardItem *sensor_item = new QStandardItem(sensor_iter.key());
            tool_item->appendRow(sensor_item);

            for (auto main_iter = sensor_iter.value().begin();
                 main_iter != sensor_iter.value().end();
                 ++main_iter) {
                QStandardItem *main_item = new QStandardItem(main_iter.key());
                sensor_item->appendRow(main_item);

                for (const QString &additional : main_iter.value()) {
                    QStandardItem *additional_item = new QStandardItem(additional);
                    main_item->appendRow(additional_item);
                }
            }
        }
    }
}

void DataBaseAction::insert_types_of_units(const int &type_id, const QString &type_name)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO types_of_units(type_id,type_name)"
                                 "VALUES(?,?)"));
    query.addBindValue(type_id);
    query.addBindValue(type_name);
    if (!query.exec()) {
        qDebug() << "error executing the request insert_types_of_units:"
                 << query.lastError().text();
    }
}
/*void DataBaseAction::insert_additional_mnemonic_units(const int& additional_mnemonic_unit_id,const QString &additional_mnemonic_name, const int &additional_mnemonic_id, const int &conversion_formula_id)
{

    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO additional_mnemonic_units (additional_mnemonic_unit_id, additional_mnemonic_unit_name, additional_mnemonic_id, conversion_formula_id) "
                                 "VALUES (?,?,?,?)"));
    query.addBindValue(additional_mnemonic_unit_id);
    query.addBindValue(additional_mnemonic_name);
    query.addBindValue(additional_mnemonic_id);
    query.addBindValue(conversion_formula_id);
    if(!query.exec()){
        qDebug() << "error executing the request insert_additional_mnemonic_units:" << query.lastError().text();
    }
}
*/
void DataBaseAction::insert_additional_mnemonics(const int &additional_mnemonic_id,
                                                 const QString &additional_mnemonic_name,
                                                 const int &company_id,
                                                 const int &main_mnemonic_id,
                                                 const int &unit_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO additional_mnemonics(additional_mnemonic_id, "
                                 "additional_mnemonic_name,company_id, main_mnemonic_id,unit_id)"
                                 "VALUES(?,?,?,?,?)"));
    query.addBindValue(additional_mnemonic_id);
    query.addBindValue(additional_mnemonic_name);
    query.addBindValue(company_id);
    query.addBindValue(main_mnemonic_id);
    query.addBindValue(unit_id);
    if (!query.exec()) {
        qDebug() << "error executing the request insert_additional_mnemonics:"
                 << query.lastError().text();
    }
}

void DataBaseAction::insert_companies(const int &company_id, const QString &company_name)
{
    //+
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO companies(company_id,company_name)"
                                 "VALUES(?,?)"));
    query.addBindValue(company_id);
    query.addBindValue(company_name);
    if (!query.exec()) {
        qDebug() << "error executing the request insert_companies:" << query.lastError().text();
    }
}

void DataBaseAction::insert_conversion_formulas(const int &coversion_formula_id,
                                                const QString &formula,
                                                const int &inital_unit_id,
                                                const int &derived_unit_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral(
        "INSERT INTO conversion_formulas(formula_id, formula, inital_unit_id, derived_unit_id)"
        "VALUES(?,?,?,?)"));
    query.addBindValue(coversion_formula_id);
    query.addBindValue(formula);
    query.addBindValue(inital_unit_id);
    query.addBindValue(derived_unit_id);
    if (!query.exec()) {
        qDebug() << "error executing the request insert_conversion_formulas:"
                 << query.lastError().text();
    }
}

/*void DataBaseAction::insert_main_mnemonic_units(const int& main_mnemonic_unit_id,const QString &main_mnemonic_unit_name, const QString &main_mnemonic_unit_description, const int &main_mnemonic_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO main_mnemonic_units(main_mnemonic_unit_id, main_mnemonic_unit_name,main_mnemonic_unit_description,main_mnemonic_id)"
                                 "VALUES(?,?,?,?)"));
    query.addBindValue(main_mnemonic_unit_id);
    query.addBindValue(main_mnemonic_unit_name);
    query.addBindValue(main_mnemonic_unit_description);
    query.addBindValue(main_mnemonic_id);
    if(!query.exec()){
        qDebug() << "error executing the request insert_main_mnemonic_units:" << query.lastError().text();
    }
}*/

void DataBaseAction::insert_main_mnemonics(const int &main_mnemonic_id,
                                           const QString &main_mnemonic_name,
                                           const QString &main_mnemonic_description,
                                           const int &sensor_id,
                                           const int &unit_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO main_mnemonics(main_mnemonic_id, "
                                 "main_mnemonic_name,main_mnemonic_description,sensor_id,unit_id)"
                                 "VALUES(?,?,?,?,?)"));
    query.addBindValue(main_mnemonic_id);
    query.addBindValue(main_mnemonic_name);
    query.addBindValue(main_mnemonic_description);
    query.addBindValue(sensor_id);
    query.addBindValue(unit_id);
    if (!query.exec()) {
        qDebug() << "error executing the request insert_main_mnemonics:"
                 << query.lastError().text();
    }
}

void DataBaseAction::insert_methods(const int &method_id, const QString &method_name)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO methods(method_id, method_name)"
                                 "VALUES(?,?)"));
    query.addBindValue(method_id);
    query.addBindValue(method_name);
    if (!query.exec()) {
        qDebug() << "error executing the request insert_methods:" << query.lastError().text();
    }
}

void DataBaseAction::insert_produsers(const int &produser_id, const QString &produser_name)
{ //+
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO produsers(produser_id,produser_name)"
                                 "VALUES(?,?)"));
    query.addBindValue(produser_id);
    query.addBindValue(produser_name);
    if (!query.exec()) {
        qDebug() << "error executing the request insert_produsers:" << query.lastError().text();
    }
}

void DataBaseAction::insert_sensor_descriptions(const int &sensor_description_id,
                                                const QString &sensor_description,
                                                const QString &offset)
{
    QSqlQuery query;
    query.prepare(QStringLiteral(
        "INSERT INTO sensor_descriptions(sensor_description_id, sensor_description, offset)"
        "VALUES(?,?,?)"));
    query.addBindValue(sensor_description_id);
    query.addBindValue(sensor_description);
    query.addBindValue(offset);
    if (!query.exec()) {
        qDebug() << "error executing the request insert_sensor_descriptions:"
                 << query.lastError().text();
    }
}

void DataBaseAction::insert_sensors(const int &sensor_id,
                                    const QString &sensor_name,
                                    const int &tool_id,
                                    const int &method_id,
                                    const int &sensor_description_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral(
        "INSERT INTO sensors(sensor_id, sensor_name,tool_id,method_id,sensor_description_id)"
        "VALUES(?,?,?,?,?)"));
    query.addBindValue(sensor_id);
    query.addBindValue(sensor_name);
    query.addBindValue(tool_id);
    query.addBindValue(method_id);
    query.addBindValue(sensor_description_id);
    if (!query.exec()) {
        qDebug() << "error executing the request insert_sensors:" << query.lastError().text();
    }
}

void DataBaseAction::insert_tool_descriptions(const int &tool_description_id,
                                              const QString &description,
                                              const QString &length,
                                              const QString &outer_diameter,
                                              const QString &inner_diameter,
                                              const QByteArray &image,
                                              const int &produser_id)
{
    QSqlQuery query;
    query.prepare(
        QStringLiteral("INSERT INTO tool_descriptions(tool_description_id, "
                       "description,length,outer_diameter,inner_diameter,image,produser_id)"
                       "VALUES(?,?,?,?,?,?,?)"));
    query.addBindValue(tool_description_id);
    query.addBindValue(description);
    query.addBindValue(length);
    query.addBindValue(outer_diameter);
    query.addBindValue(inner_diameter);
    query.addBindValue(image);
    query.addBindValue(produser_id);
    if (!query.exec()) {
        qDebug() << "error executing the request insert_tool_descriptions:"
                 << query.lastError().text();
    }
}

void DataBaseAction::insert_tools(const int &tool_id,
                                  const QString &tool_name,
                                  const int &tool_description_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO tools(tool_id,tool_name,tool_description_id)"
                                 "VALUES(?,?,?)"));
    query.addBindValue(tool_id);
    query.addBindValue(tool_name);
    query.addBindValue(tool_description_id);
    if (!query.exec()) {
        qDebug() << "error executing the request insert_tools:" << query.lastError().text();
    }
}

void DataBaseAction::insert_units(const int &unit_id, const QString &unit_name, const int &type_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO units(unit_id,unit_name,type_id)"
                                 "VALUES(?,?,?)"));
    query.addBindValue(unit_id);
    query.addBindValue(unit_name);
    query.addBindValue(type_id);
    if (!query.exec()) {
        qDebug() << "error executing the request insert_units:" << query.lastError().text();
    }
}

void DataBaseAction::remove_units(const int &unit_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM units\
        WHERE unit_id=?"));
    query.addBindValue(unit_id);
    if (!query.exec()) {
        qDebug() << "error executing the request remove_units:" << query.lastError().text();
    }
}

void DataBaseAction::remove_additional_mnemonic_units(const int &additional_mnemonic_unit_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM additional_mnemonic_units\
        WHERE additional_mnemonic_unit_id=?"));
    query.addBindValue(additional_mnemonic_unit_id);
    if (!query.exec()) {
        qDebug() << "error executing the request remove_additional_mnemonic_units:"
                 << query.lastError().text();
    }
}

void DataBaseAction::remove_additional_mnemonics(const int &additional_mnemonic_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM additional_mnemonics\
        WHERE additional_mnemonic_id=?"));
    query.addBindValue(additional_mnemonic_id);
    if (!query.exec()) {
        qDebug() << "error executing the request remove_additional_mnemonics:"
                 << query.lastError().text();
    }
}

void DataBaseAction::remove_companies(const int &company_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM companies\
        WHERE company_id=?"));
    query.addBindValue(company_id);
    if (!query.exec()) {
        qDebug() << "error executing the request remove_companies:" << query.lastError().text();
    }
}

void DataBaseAction::remove_conversion_formulas(const int &conversion_formula_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM conversion_formulas\
        WHERE conversion_formula_id=?"));
    query.addBindValue(conversion_formula_id);
    if (!query.exec()) {
        qDebug() << "error executing the request remove_conversion_formulas:"
                 << query.lastError().text();
    }
}

void DataBaseAction::remove_main_mnemonic_units(const int &main_mnemonic_unit_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM main_mnemonic_units\
        WHERE main_mnemonic_unit_id=?"));
    query.addBindValue(main_mnemonic_unit_id);
    if (!query.exec()) {
        qDebug() << "error executing the request remove_main_mnemonic_units:"
                 << query.lastError().text();
    }
}

void DataBaseAction::remove_main_mnemonics(const int &main_mnemonic_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM main_mnemonics\
        WHERE main_mnemonic_id=?"));
    query.addBindValue(main_mnemonic_id);
    if (!query.exec()) {
        qDebug() << "error executing the request remove_main_mnemonics:"
                 << query.lastError().text();
    }
}

void DataBaseAction::remove_methods(const int &method_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM methods\
        WHERE method_id=?"));
    query.addBindValue(method_id);
    if (!query.exec()) {
        qDebug() << "error executing the request remove_methods:" << query.lastError().text();
    }
}

void DataBaseAction::remove_produsers(const int &produser_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM produsers\
        WHERE produser_id=?"));
    query.addBindValue(produser_id);
    if (!query.exec()) {
        qDebug() << "error executing the request remove_produsers:" << query.lastError().text();
    }
}

void DataBaseAction::remove_sensor_descriptions(const int &sensor_description_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM sensor_descriptions\
        WHERE sensor_description_id=?"));
    query.addBindValue(sensor_description_id);
    if (!query.exec()) {
        qDebug() << "error executing the request remove_sensor_descriptions:"
                 << query.lastError().text();
    }
}

void DataBaseAction::remove_sensors(const int &sensor_id)
{
    int sensor_description_id = -1;
    QString condition = " sensor_id =\"" + QString::number(sensor_id) + "\"";
    sensor_description_id = id_exist_data("sensor_description_id", "sensors", condition);
    remove_sensor_descriptions(sensor_description_id);
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM sensors\
        WHERE sensor_id=?"));
    query.addBindValue(sensor_id);
    if (!query.exec()) {
        qDebug() << "error executing the request remove_sensors:" << query.lastError().text();
    }
}

void DataBaseAction::remove_tool_descriptions(const int &tool_description_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM tool_descriptions\
        WHERE tool_description_id=?"));
    query.addBindValue(tool_description_id);
    if (!query.exec()) {
        qDebug() << "error executing the request remove_tool_descriptions:"
                 << query.lastError().text();
    }
}

void DataBaseAction::remove_tools(const int &tool_id)
{
    int tool_description_id = 0;
    QString condition = " tool_id =\"" + QString::number(tool_id) + "\"";
    tool_description_id = id_exist_data("tool_description_id", "tools", condition);
    remove_tool_descriptions(tool_description_id);
    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM tools\
        WHERE tool_id=?"));
    query.addBindValue(tool_id);
    if (!query.exec()) {
        qDebug() << "error executing the request remove_tools:" << query.lastError().text();
    }
}

void DataBaseAction::update_tool(const int &tool_id,
                                 const QString &name,
                                 const int &description_id,
                                 QString &description,
                                 const QString &length,
                                 const QString &outer_diameter,
                                 const QString &inner_diameter,
                                 const QByteArray &image,
                                 const int &produser_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("UPDATE tools      SET tool_name =?        WHERE tool_id=?"));
    query.addBindValue(name);
    query.addBindValue(tool_id);
    if (!query.exec()) {
        qDebug() << "error executing the request UPDATE update_tool:" << query.lastError().text();
    }
    query.prepare(QStringLiteral(
        "UPDATE tool_descriptions      SET description =?,length=?,outer_diameter=?,inner_diameter=?,\
                                 image=?,produser_id=?           WHERE tool_description_id=?"));
    query.addBindValue(description);
    query.addBindValue(length);
    query.addBindValue(outer_diameter);
    query.addBindValue(inner_diameter);
    query.addBindValue(image);
    query.addBindValue(produser_id);
    query.addBindValue(description_id);

    if (!query.exec()) {
        qDebug() << "error executing the request UPDATE tool_description:"
                 << query.lastError().text();
    }
}

void DataBaseAction::update_sensor(const int &sensor_id,
                                   const QString &name,
                                   const int &tool_id,
                                   const int &method_id,
                                   const int &sensor_description_id,
                                   const QString &description,
                                   const QString &offset)
{
    QSqlQuery query;
    query.prepare(QStringLiteral(
        "UPDATE sensors      SET sensor_name =?,tool_id=?,method_id=?,sensor_description_id=?\
                                  WHERE sensor_id=?"));
    query.addBindValue(name);
    query.addBindValue(tool_id);
    query.addBindValue(method_id);
    query.addBindValue(sensor_description_id);
    query.addBindValue(sensor_id);
    if (!query.exec()) {
        qDebug() << "error executing the request UPDATE sensors:" << query.lastError().text();
    }
    query.prepare(
        QStringLiteral("UPDATE sensor_descriptions      SET sensor_description =?,offset=?        \
                                 WHERE sensor_description_id=?"));
    query.addBindValue(description);
    query.addBindValue(offset);
    query.addBindValue(sensor_description_id);
    if (!query.exec()) {
        qDebug() << "error executing the request UPDATE sensor_descriptions:"
                 << query.lastError().text();
    }
}

void DataBaseAction::update_main_mnemonic(const int &id,
                                          const QString &name,
                                          const QString &description,
                                          const int &sensor_id,
                                          const int &unit_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral(
        "UPDATE main_mnemonics      SET main_mnemonic_name =?, main_mnemonic_description=?,\
                                  sensor_id=?, unit_id=?\
                                  WHERE main_mnemonic_id=?"));
    query.addBindValue(name);
    query.addBindValue(description);
    query.addBindValue(sensor_id);
    query.addBindValue(unit_id);
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug() << "error executing the request UPDATE main_mnemonics:"
                 << query.lastError().text();
    }
}

void DataBaseAction::update_additional_mnemonic(const int &additional_mnemonic_id,
                                                const QString &name,
                                                const int &company_id,
                                                const int &main_mnemonic_id,
                                                const int &unit_id)
{
    QSqlQuery query;
    query.prepare(QStringLiteral(
        "UPDATE additional_mnemonics      SET additional_mnemonic_name =?, company_id=?,\
                                  main_mnemonic_id=?, unit_id=?\
                                  WHERE additional_mnemonic_id=?"));
    query.addBindValue(name);
    query.addBindValue(company_id);
    query.addBindValue(main_mnemonic_id);
    query.addBindValue(unit_id);
    query.addBindValue(additional_mnemonic_id);
    if (!query.exec()) {
        qDebug() << "error executing the request UPDATE additional_mnemonics:"
                 << query.lastError().text();
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
    model1->setQuery(QStringLiteral("SELECT\
  tools.tool_name,\
  tool_descriptions.description,\
  tool_descriptions.\"length\",\
  tool_descriptions.outer_diameter,\
  tool_descriptions.inner_diameter,\
  tool_descriptions.image,\
  produsers.produser_name,\
  sensors.sensor_name,\
  sensor_descriptions.sensor_description,\
  sensor_descriptions.offset,\
  methods.method_name,\
  main_mnemonics.main_mnemonic_name,\
  main_mnemonics.main_mnemonic_description,\
  types_of_units.type_name,\
  units.unit_name,\
  additional_mnemonics.additional_mnemonic_name,\
  companies.company_name,\
  conversion_formulas.formula\
 FROM \
  tools\
  LEFT JOIN sensors ON (sensors.tool_id = tools.tool_id) \
  LEFT JOIN main_mnemonics ON (main_mnemonics.sensor_id = sensors.sensor_id)\
  LEFT JOIN additional_mnemonics ON (additional_mnemonics.main_mnemonic_id= main_mnemonics.main_mnemonic_id)\
  LEFT JOIN conversion_formulas ON (main_mnemonics.unit_id = conversion_formulas.inital_unit_id AND additional_mnemonics.unit_id = conversion_formulas.derived_unit_id)\
  LEFT JOIN companies ON (additional_mnemonics.company_id = companies.company_id)\
  LEFT JOIN units ON (additional_mnemonics.unit_id = units.unit_id)\
  LEFT JOIN types_of_units ON (units.type_id = types_of_units.type_id)\
  LEFT JOIN tool_descriptions ON (tool_descriptions.tool_description_id = tools.tool_description_id)\
  LEFT JOIN produsers ON (tool_descriptions.produser_id = produsers.produser_id)\
  LEFT JOIN methods ON (sensors.method_id = methods.method_id)\
  LEFT JOIN sensor_descriptions ON (sensors.sensor_description_id = sensor_descriptions.sensor_description_id);\
"));
    tree_model_create();
}

void DataBaseAction::database_upload()
{
    database_commit();
    database_refresh();
}

QString DataBaseAction::find_with_condition(const QString &column_name,
                                            const QString &table_name,
                                            const QString &condition)
{
    QSqlQuery query;
    QString re_value;
    query.prepare("SELECT DISTINCT " + column_name + " FROM " + table_name + " WHERE " + condition);
    if (!query.exec()) {
        qDebug() << "error executing the request find_with_condition:" << query.lastError().text();
        return "-1";
    } //SELECT сам сортирует по возрастанию
    while (query.next()) {
        re_value = (query.value(0).toString());
    }
    return re_value;
}

int DataBaseAction::id_minimal_for_input(const QString &column_name, const QString &table_name)
{
    QList<int> sql_id_aray;
    QSqlQuery query;
    query.prepare("SELECT " + column_name + " FROM " + table_name);
    if (!query.exec()) {
        qDebug() << "error executing the request id_minimal_for_input:" << query.lastError().text();
        return -1;
    } //SELECT сам сортирует по возрастанию
    while (query.next()) {
        sql_id_aray.append(query.value(0).toInt());
    }
    if (!sql_id_aray.isEmpty()) {
        return sql_id_aray.last() + 1;
    } else {
        return 1;
    }
}

int DataBaseAction::id_exist_data(const QString &column_name,
                                  const QString &table_name,
                                  const QString &condition)
{
    int id1 = -1;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT " + column_name + " FROM " + table_name + " WHERE " + condition);
    if (!query.exec()) {
        qDebug() << " id_exist_data not exist. return id=-1:" << query.lastError().text();
        return -1;
    } //SELECT сам сортирует по возрастанию
    while (query.next()) {
        id1 = (query.value(0).toInt());
    }
    return id1;
}

QList<QString> DataBaseAction::get_unique_values(const QString &column_name,
                                                 const QString &table_name)
{
    QList<QString> unique_values;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT " + column_name + " FROM " + table_name);
    if (!query.exec()) {
        qDebug() << "error executing the request get_unique_values:" << query.lastError().text();
        return unique_values;
    }

    // Извлекаем уникальные значения и сохраняем их в массиве
    while (query.next()) {
        unique_values.append(
            query.value(0).toString()); // Предполагается, что значение находится в первом столбце
    }
    return unique_values;
}

QList<QString> DataBaseAction::get_unique_values_with_condition(const QString &column_name,
                                                                const QString &table_name,
                                                                const QString &condition)
{
    QList<QString> unique_values;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT " + column_name + " FROM " + table_name + " WHERE " + condition);
    if (!query.exec()) {
        qDebug() << "error executing the request get_unique_values:" << query.lastError().text();
        return unique_values;
    }

    // Извлекаем уникальные значения и сохраняем их в массиве
    while (query.next()) {
        unique_values.append(
            query.value(0).toString()); // Предполагается, что значение находится в первом столбце
    }
    return unique_values;
}
