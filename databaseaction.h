#ifndef DATABASEACTION_H
#define DATABASEACTION_H

#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QSqlDatabase>
#include <customquerymodel.h>
#include <QString>
#include <QVariantList>
#include <QByteArray>
class DataBaseAction
{

public:
    CustomQueryModel *model1;
    QSqlDatabase database;

    void database_connecting(const QString& fileName);


    void insert_additional_mnemonic_units(const QString& name,const int& additional_mnemonic_id,const int& conversion_formula_id);
    void insert_additional_mnemonics(const QString& name,const int& company_id,const int& main_mnemonic_id);
    void insert_companies (const QString& name);
    void insert_conversion_formaulas(const QString& name);
    void insert_main_mnemonic_units(const QString& name,const QString& description,const int& main_mnemonic_id);
    void insert_main_mnemonics(const QString& name,const QString& description,const int& sensor_id);
    void insert_methods (const QString& method_name);
    void insert_produsers(const QString& name);
    void insert_sensor_descriptions(const QString& description,const QString& offset);
    void insert_sensors(const QString& name,const int& tool_id,const int& method_id,const int& sensor_description_id);
    void insert_tool_descriptions(const QString& description,const QString& length,const QString& outer_diameter,
                                  const QString& inner_diameter, const QByteArray & image,const int produser_id);
    void insert_tools(const QString& name,const int& description_id);

    void remove_additional_mnemonic_units(const int& id);
    void remove_additional_mnemonics(const int& id);
    void remove_companies(const int& id);
    void remove_conversion_formaulas(const int& id);
    void remove_main_mnemonic_units(const int& id);
    void remove_main_mnemonics(const int& id);
    void remove_methods(const int& id);
    void remove_produsers(const int& id);
    void remove_sensor_descriptions(const int& id);
    void remove_sensors(const int& id);
    void remove_tool_descriptions(const int& id);
    void remove_tools(const int& id);

    void database_commit();
    void database_rollback();
    void database_transaction();

    void database_refresh();
    void database_upload();

    int find_id_where_condition(QString type_id,QString table_name,QString condition);

    QVariantList get_unique_values(QString columnName,QString tableName);

    DataBaseAction();
    ~DataBaseAction();
  };

#endif // DATABASEACTION_H
