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

    void insert_types_of_units(const int& id, const QString& type_name);
  //  void insert_additional_mnemonic_units(const int& id,const QString& name,const int& additional_mnemonic_id,const int& conversion_formula_id);
    void insert_additional_mnemonics(const int& id,const QString& name,const int& company_id,const int& main_mnemonic_id,const int& unit_id);
    void insert_companies (const int& id,const QString& name);
    void insert_conversion_formulas(const int& id,const QString& formula,const int& inital_unit_id,const int& derived_unit_id);
 //   void insert_main_mnemonic_units(const int& id,const QString& name,const QString& description,const int& main_mnemonic_id);
    void insert_main_mnemonics(const int& id,const QString& name,const QString& description,const int& sensor_id,const int& unit_id);
    void insert_methods (const int& id,const QString& method_name);
    void insert_produsers(const int& id,const QString& name);
    void insert_sensor_descriptions(const int& id,const QString& description,const QString& offset);
    void insert_sensors(const int& id,const QString& name,const int& tool_id,const int& method_id,const int& sensor_description_id);
    void insert_tool_descriptions(const int& id,const QString& description,const QString& length,const QString& outer_diameter,
                                  const QString& inner_diameter, const QByteArray & image,const int &produser_id);
    void insert_tools(const int& id,const QString& name,const int& description_id);
    void insert_units(const int& unit_id,const QString& unit_name,const int& type_id);

    void remove_units(const int& id);
    void remove_additional_mnemonic_units(const int& id);
    void remove_additional_mnemonics(const int& id);
    void remove_companies(const int& id);
    void remove_conversion_formulas(const int& id);
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

    QString find_with_condition(const QString& column_name, const QString& table_name, const QString& condition);

    int id_minimal_for_input( const QString& column_name, const QString& table_name);
    int id_exist_data( const QString& column_name, const QString& table_name, const QString& condition);

    QList<QString> get_unique_values( const QString& column_name, const QString& table_name);
    QList<QString> get_unique_values_with_condition( const QString& column_name, const QString& table_name,const QString& condition);

    DataBaseAction();
    ~DataBaseAction();
};

#endif // DATABASEACTION_H
