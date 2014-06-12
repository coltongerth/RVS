#include "FuelsDIO.h"

RVS::Fuels::FuelsDIO::FuelsDIO(void) : RVS::DataManagement::DIO()
{
	this->create_output_table();
	this->create_intermediate_table();
}

RVS::Fuels::FuelsDIO::~FuelsDIO(void)
{

}

int* RVS::Fuels::FuelsDIO::create_output_table()
{
	std::stringstream sqlstream;
	sqlstream << "CREATE TABLE " << FUELS_OUTPUT_TABLE << "(" << \
		PLOT_NUM_FIELD << " INT NOT NULL," << \
		YEAR_OUT_FIELD << " INT NOT NULL," << \
		EVT_NUM_FIELD << " INT NOT NULL," << \
		BPS_NUM_FIELD << " INT NOT NULL," << \
		FUEL_1HR_OUT_FIELD << " REAL, " << \
		FUEL_10HR_OUT_FIELD << " REAL, " << \
		FUEL_100HR_OUT_FIELD << " REAL, " \
		FUEL_1HRLIVE_OUT_FIELD << " REAL, " \
		FUEL_10HRLIVE_OUT_FIELD << " REAL, " \
		FUEL_100HRLIVE_OUT_FIELD << " REAL, " \
		FUEL_1HRDEAD_OUT_FIELD << " REAL, " \
		FUEL_10HRDEAD_OUT_FIELD << " REAL, " \
		FUEL_100HRDEAD_OUT_FIELD << " REAL); ";

	char* sql = new char;
	sql = streamToCharPtr(&sqlstream);
	RC = create_table(sql);
	delete[] sql;

	return RC;
}

int* RVS::Fuels::FuelsDIO::create_intermediate_table()
{
	std::stringstream sqlstream;
	sqlstream << "CREATE TABLE " << FUELS_INTERMEDIATE_TABLE << "(" << \
		PLOT_NUM_FIELD << " INT NOT NULL, " << \
		YEAR_OUT_FIELD << " INT NOT NULL, " << \
		EVT_NUM_FIELD << " INT NOT NULL, " << \
		BPS_NUM_FIELD << " INT NOT NULL, " << \
		DOM_SPP_FIELD << " char(255), " << \
		SPP_CODE_FIELD << " char(8), " << \
		FUEL_1HR_OUT_FIELD << " REAL, " << \
		FUEL_10HR_OUT_FIELD << " REAL, " << \
		FUEL_100HR_OUT_FIELD << " REAL, " \
		FUEL_1HRLIVE_OUT_FIELD << " REAL, " \
		FUEL_10HRLIVE_OUT_FIELD << " REAL, " \
		FUEL_100HRLIVE_OUT_FIELD << " REAL, " \
		FUEL_1HRDEAD_OUT_FIELD << " REAL, " \
		FUEL_10HRDEAD_OUT_FIELD << " REAL, " \
		FUEL_100HRDEAD_OUT_FIELD << " REAL); ";

	char* sql = new char;
	sql = streamToCharPtr(&sqlstream);
	RC = create_table(sql);
	delete[] sql;

	return RC;
}

int* RVS::Fuels::FuelsDIO::write_fuel_output_record(int* plot_num, int* year, int* evt_num, int* bps, std::map<std::string, double> fuelsValues)
{
	std::stringstream sqlstream;
	sqlstream << "INSERT INTO " << FUELS_OUTPUT_TABLE << " (" << \
		PLOT_NUM_FIELD << ", " << YEAR_OUT_FIELD << ", " << EVT_NUM_FIELD << ", " << BPS_NUM_FIELD << ", " << \
		FUEL_1HR_OUT_FIELD << ", " << 	FUEL_10HR_OUT_FIELD << ", " << FUEL_100HR_OUT_FIELD << ", " << \
		FUEL_1HRLIVE_OUT_FIELD << ", " << FUEL_10HRLIVE_OUT_FIELD << ", " << FUEL_100HRLIVE_OUT_FIELD << ", " << \
		FUEL_1HRDEAD_OUT_FIELD << ", " << FUEL_10HRDEAD_OUT_FIELD << ", " << FUEL_100HRDEAD_OUT_FIELD << ") " << \
		"VALUES (" << *plot_num << "," << *year << "," << *evt_num << "," << *bps << "," << \
		fuelsValues[FUEL_1HR_OUT_FIELD] << "," << fuelsValues[FUEL_10HR_OUT_FIELD] << "," << fuelsValues[FUEL_100HR_OUT_FIELD] << "," << \
		fuelsValues[FUEL_1HRLIVE_OUT_FIELD] << "," << fuelsValues[FUEL_10HRLIVE_OUT_FIELD] << "," << fuelsValues[FUEL_100HRLIVE_OUT_FIELD] << "," << \
		fuelsValues[FUEL_1HRDEAD_OUT_FIELD] << "," << fuelsValues[FUEL_10HRDEAD_OUT_FIELD] << "," << fuelsValues[FUEL_100HRDEAD_OUT_FIELD] << ");";

	char* sql = new char;
	sql = streamToCharPtr(&sqlstream);
	RC = exec_sql(sql);
	delete[] sql;
	return RC;
}

int* RVS::Fuels::FuelsDIO::write_fuel_intermediate_record(int* plot_num, int* year, int* evt_num, int* bps, std::string* dom_spp, std::string* spp_code, std::map<std::string, double> fuelsValues)
{
	std::stringstream sqlstream;
	sqlstream << "INSERT INTO " << FUELS_INTERMEDIATE_TABLE << " (" << \
		PLOT_NUM_FIELD << ", " << YEAR_OUT_FIELD << ", " << EVT_NUM_FIELD << ", " << \
		BPS_NUM_FIELD << ", " << DOM_SPP_FIELD << ", " << SPP_CODE_FIELD << ", " << \
		FUEL_1HR_OUT_FIELD << ", " << FUEL_10HR_OUT_FIELD << ", " << FUEL_100HR_OUT_FIELD << ", " << \
		FUEL_1HRLIVE_OUT_FIELD << ", " << FUEL_10HRLIVE_OUT_FIELD << ", " << FUEL_100HRLIVE_OUT_FIELD << ", " << \
		FUEL_1HRDEAD_OUT_FIELD << ", " << FUEL_10HRDEAD_OUT_FIELD << ", " << FUEL_100HRDEAD_OUT_FIELD << ") " << \
		"VALUES (" << *plot_num << "," << *year << "," << *evt_num << "," << *bps << ",\"" << \
		*dom_spp << "\", \"" << *spp_code << "\", " << \
		fuelsValues[FUEL_1HR_OUT_FIELD] << "," << fuelsValues[FUEL_10HR_OUT_FIELD] << "," << fuelsValues[FUEL_100HR_OUT_FIELD] << "," << \
		fuelsValues[FUEL_1HRLIVE_OUT_FIELD] << "," << fuelsValues[FUEL_10HRLIVE_OUT_FIELD] << "," << fuelsValues[FUEL_100HRLIVE_OUT_FIELD] << "," << \
		fuelsValues[FUEL_1HRDEAD_OUT_FIELD] << "," << fuelsValues[FUEL_10HRDEAD_OUT_FIELD] << "," << fuelsValues[FUEL_100HRDEAD_OUT_FIELD] << ");";

	char* sql = new char;
	sql = streamToCharPtr(&sqlstream);
	RC = exec_sql(sql);
	delete[] sql;
	return RC;
}

std::map<std::string, int> RVS::Fuels::FuelsDIO::query_crosswalk_table(std::string spp)
{
	std::map<std::string, int> equationNumbers = std::map<std::string, int>();
	// Create the sqlite3 statment to query biomass crosswalk table on species
	sqlite3_stmt* stmt = query_base(FUEL_CROSSWALK_TABLE, SPP_CODE_FIELD, spp);
	int colNum = sqlite3_column_count(stmt);
	// Initiate the query
	*RC = sqlite3_step(stmt);
	// Step over the columns, looking for the requested return type
	int val = 0;

	for (int i = 0; i < colNum; i++)
	{
		const char* colName = sqlite3_column_name(stmt, i);
		std::string colStr = std::string(colName);
		// If the column name matches the return type, return the equation number found there
		if (colName[0] == 'F')
		{
			val = sqlite3_column_int(stmt, i);
			equationNumbers[colStr] = val;
		}
	}
	// Cleanup
	*RC = sqlite3_finalize(stmt);
	return equationNumbers;
}

RVS::DataManagement::DataTable* RVS::Fuels::FuelsDIO::query_equation_table(std::map<std::string, int> equationNumbers)
{
	std::stringstream sqlstream;
	sqlstream << "SELECT * FROM " << FUEL_EQUATION_TABLE << " WHERE " << EQUATION_NUMBER_FIELD << " IN (";

	int count = 0;
	for (std::map<std::string, int>::iterator fit = equationNumbers.begin(); fit != equationNumbers.end(); fit++)
	{
		sqlstream << fit->second;
		if (count < equationNumbers.size() - 1)
		{
			sqlstream << ",";
		}
		else
		{
			sqlstream << ")";
		}
		count++;
	}

	char* sql = streamToCharPtr(&sqlstream);

	sqlite3_stmt* stmt = query_base(sql);
	RVS::DataManagement::DataTable* dt = new RVS::DataManagement::DataTable(stmt);
	return dt;
}

void RVS::Fuels::FuelsDIO::query_equation_coefficients(int equation_number, double* coefs)
{

}

void RVS::Fuels::FuelsDIO::query_equation_parameters(int equation_number, std::string* params)
{
	//getVal(dt->getStmt(), dt->Columns[EQN_P1_FIELD], &params[0]);
	//getVal(dt->getStmt(), dt->Columns[EQN_P2_FIELD], &params[1]);
	//getVal(dt->getStmt(), dt->Columns[EQN_P3_FIELD], &params[2]);
}