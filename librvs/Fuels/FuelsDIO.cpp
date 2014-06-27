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
		FUEL_100HR_OUT_FIELD << " REAL, " << \
		FUEL_1HRLIVE_OUT_FIELD << " REAL, " << \
		FUEL_10HRLIVE_OUT_FIELD << " REAL, " << \
		FUEL_100HRLIVE_OUT_FIELD << " REAL, " << \
		FUEL_1HRDEAD_OUT_FIELD << " REAL, " << \
		FUEL_10HRDEAD_OUT_FIELD << " REAL, " << \
		FUEL_100HRDEAD_OUT_FIELD << " REAL, " << \
		FC_FBFM_FIELD << " INTEGER); ";

	char* sql = new char;
	sql = streamToCharPtr(&sqlstream);
	queuedWrites.push_back(sql);

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
		FUEL_100HR_OUT_FIELD << " REAL, " << \
		FUEL_1HRLIVE_OUT_FIELD << " REAL, " << \
		FUEL_10HRLIVE_OUT_FIELD << " REAL, " << \
		FUEL_100HRLIVE_OUT_FIELD << " REAL, " << \
		FUEL_1HRDEAD_OUT_FIELD << " REAL, " << \
		FUEL_10HRDEAD_OUT_FIELD << " REAL, " << \
		FUEL_100HRDEAD_OUT_FIELD << " REAL); ";

	char* sql = new char;
	sql = streamToCharPtr(&sqlstream);
	queuedWrites.push_back(sql);

	return RC;
}

int* RVS::Fuels::FuelsDIO::write_output_record(int* year, RVS::DataManagement::AnalysisPlot* ap)
{
	std::stringstream sqlstream;
	sqlstream << "INSERT INTO " << FUELS_OUTPUT_TABLE << " (" << \
		PLOT_NUM_FIELD << ", " << YEAR_OUT_FIELD << ", " << EVT_NUM_FIELD << ", " << BPS_NUM_FIELD << ", " << \
		FUEL_1HR_OUT_FIELD << ", " << 	FUEL_10HR_OUT_FIELD << ", " << FUEL_100HR_OUT_FIELD << ", " << \
		FUEL_1HRLIVE_OUT_FIELD << ", " << FUEL_10HRLIVE_OUT_FIELD << ", " << FUEL_100HRLIVE_OUT_FIELD << ", " << \
		FUEL_1HRDEAD_OUT_FIELD << ", " << FUEL_10HRDEAD_OUT_FIELD << ", " << FUEL_100HRDEAD_OUT_FIELD << ", " <<
		FC_FBFM_FIELD << ") " << \
		"VALUES (" << ap->PLOT_ID() << "," << *year << "," << ap->EVT_NUM() << "," << ap->BPS_NUM() << "," << \
		ap->TOTALFUELSCOLLECTION()[FUEL_1HR_OUT_FIELD] / 2000 << "," << ap->TOTALFUELSCOLLECTION()[FUEL_10HR_OUT_FIELD] / 2000 << "," << ap->TOTALFUELSCOLLECTION()[FUEL_100HR_OUT_FIELD] / 2000 << "," << \
		ap->TOTALFUELSCOLLECTION()[FUEL_1HRLIVE_OUT_FIELD] / 2000 << "," << ap->TOTALFUELSCOLLECTION()[FUEL_10HRLIVE_OUT_FIELD] / 2000 << "," << ap->TOTALFUELSCOLLECTION()[FUEL_100HRLIVE_OUT_FIELD] / 2000 << "," << \
		ap->TOTALFUELSCOLLECTION()[FUEL_1HRDEAD_OUT_FIELD] / 2000 << "," << ap->TOTALFUELSCOLLECTION()[FUEL_10HRDEAD_OUT_FIELD] / 2000 << "," << ap->TOTALFUELSCOLLECTION()[FUEL_100HRDEAD_OUT_FIELD] / 2000 << "," << \
		ap->FBFM() << ");";

	char* sql = new char;
	sql = streamToCharPtr(&sqlstream);
	queuedWrites.push_back(sql);

	return RC;
}

int* RVS::Fuels::FuelsDIO::write_intermediate_record(int* year, RVS::DataManagement::AnalysisPlot* ap, RVS::DataManagement::SppRecord* spp)
{
	std::stringstream sqlstream;
	sqlstream << "INSERT INTO " << FUELS_INTERMEDIATE_TABLE << " (" << \
		PLOT_NUM_FIELD << ", " << YEAR_OUT_FIELD << ", " << EVT_NUM_FIELD << ", " << \
		BPS_NUM_FIELD << ", " << DOM_SPP_FIELD << ", " << SPP_CODE_FIELD << ", " << \
		FUEL_1HR_OUT_FIELD << ", " << FUEL_10HR_OUT_FIELD << ", " << FUEL_100HR_OUT_FIELD << ", " << \
		FUEL_1HRLIVE_OUT_FIELD << ", " << FUEL_10HRLIVE_OUT_FIELD << ", " << FUEL_100HRLIVE_OUT_FIELD << ", " << \
		FUEL_1HRDEAD_OUT_FIELD << ", " << FUEL_10HRDEAD_OUT_FIELD << ", " << FUEL_100HRDEAD_OUT_FIELD << ") " << \
		"VALUES (" << ap->PLOT_ID() << "," << *year << "," << ap->EVT_NUM() << "," << ap->BPS_NUM() << ",\"" << \
		spp->DOM_SPP() << "\", \"" << spp->SPP_CODE() << "\", " << \
		spp->FUELS()[FUEL_1HR_OUT_FIELD] / 2000 << "," << spp->FUELS()[FUEL_10HR_OUT_FIELD] / 2000 << "," << spp->FUELS()[FUEL_100HR_OUT_FIELD] / 2000 << "," << \
		spp->FUELS()[FUEL_1HRLIVE_OUT_FIELD] / 2000 << "," << spp->FUELS()[FUEL_10HRLIVE_OUT_FIELD] / 2000 << "," << spp->FUELS()[FUEL_100HRLIVE_OUT_FIELD] / 2000 << "," << \
		spp->FUELS()[FUEL_1HRDEAD_OUT_FIELD] / 2000 << "," << spp->FUELS()[FUEL_10HRDEAD_OUT_FIELD] / 2000 << "," << spp->FUELS()[FUEL_100HRDEAD_OUT_FIELD] / 2000 << ");";

	char* sql = new char;
	sql = streamToCharPtr(&sqlstream);
	queuedWrites.push_back(sql);

	return RC;
}

std::map<std::string, int> RVS::Fuels::FuelsDIO::query_crosswalk_table(std::string spp)
{
	std::map<std::string, int> equationNumbers = std::map<std::string, int>();
	// Create the sqlite3 statment to query biomass crosswalk table on species
	const char* sql = query_base(FUEL_CROSSWALK_TABLE, SPP_CODE_FIELD, spp);
	RVS::DataManagement::DataTable* dt = prep_datatable(sql, rvsdb);

	int colNum = dt->numCols();
	// Step over the columns, looking for the requested return type
	int val = 0;
	for (int i = 0; i < colNum; i++)
	{
		const char* colName = sqlite3_column_name(dt->getStmt(), i);
		std::string colStr = std::string(colName);
		// If the column name matches the return type, return the equation number found there
		if (colName[0] == 'F')
		{
			getVal(dt->getStmt(), i, &val);
			equationNumbers[colStr] = val;
		}
	}

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
	RVS::DataManagement::DataTable* dt = prep_datatable(sql, rvsdb);
	return dt;
}

RVS::DataManagement::DataTable* RVS::Fuels::FuelsDIO::query_equation_table(int equationNumber)
{
	const char* sql = query_base(FUEL_EQUATION_TABLE, EQUATION_NUMBER_FIELD, equationNumber);
	DataManagement::DataTable* dt = prep_datatable(sql, rvsdb);
	return dt;
}

RVS::DataManagement::DataTable* RVS::Fuels::FuelsDIO::query_fbfm_rules_selector(void)
{
	std::stringstream ss;
	ss << "SELECT * FROM " << FUEL_CLASSRULES_TABLE << ";";
	char* sql = streamToCharPtr(&ss);
	RVS::DataManagement::DataTable* dt = prep_datatable(sql, rvsdb);
	return dt;
}

RVS::DataManagement::DataTable* RVS::Fuels::FuelsDIO::query_fbfm_rules(std::string classTable)
{
	std::stringstream ss;
	ss << "SELECT * FROM " << classTable << ";";
	char* sql = streamToCharPtr(&ss);
	RVS::DataManagement::DataTable* dt = prep_datatable(sql, rvsdb);
	return dt;
}