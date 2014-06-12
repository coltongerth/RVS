#include "BiomassDIO.h"

RVS::Biomass::BiomassDIO::BiomassDIO(void) : RVS::DataManagement::DIO()
{
	this->create_output_table();
	this->create_intermediate_table();
}

RVS::Biomass::BiomassDIO::~BiomassDIO(void)
{

}

int* RVS::Biomass::BiomassDIO::create_output_table()
{
	std::stringstream sqlstream;
	sqlstream << "CREATE TABLE " << BIOMASS_OUTPUT_TABLE << "(" << \
		PLOT_NUM_FIELD << " INTEGER NOT NULL, " << \
		YEAR_OUT_FIELD << " INTEGER NOT NULL, " << \
		EVT_NUM_FIELD << " INTEGER NOT NULL, " << \
		BPS_NUM_FIELD << " INTEGER NOT NULL, " << \
		BIOMASS_SHRUB_OUT_FIELD << " REAL, " << \
		BIOMASS_HERB_OUT_FIELD << " REAL, " << \
		BIOMASS_TOTAL_OUT_FIELD << " REAL);";

	char* sql = new char;
	sql = streamToCharPtr(&sqlstream);
	RC = create_table(sql);
	delete[] sql;

	return RC;
}

int* RVS::Biomass::BiomassDIO::write_biomass_output_record(int* plot_num, int* year, int* evt_num, int* bps, double* totalBiomass, double* herbBiomass, double* shrubBiomass)
{
	std::stringstream sqlstream;
	sqlstream << "INSERT INTO " << BIOMASS_OUTPUT_TABLE << " (" << \
		PLOT_NUM_FIELD << ", " << YEAR_OUT_FIELD << ", " << EVT_NUM_FIELD << ", " << BPS_NUM_FIELD << ", " << \
		BIOMASS_TOTAL_OUT_FIELD << ", " << BIOMASS_SHRUB_OUT_FIELD << ", " << BIOMASS_HERB_OUT_FIELD << ") " << \
		"VALUES (" << *plot_num << "," << *year << "," << *evt_num << "," << *bps << "," << \
		*totalBiomass << "," << *shrubBiomass << "," << *herbBiomass << ");";

	char* sql = new char;
	sql = streamToCharPtr(&sqlstream);
	RC = exec_sql(sql);
	delete[] sql;
	return RC;
}

int* RVS::Biomass::BiomassDIO::create_intermediate_table()
{
	std::stringstream sqlstream;
	sqlstream << "CREATE TABLE " << BIOMASS_INTERMEDIATE_TABLE << " (" << \
		PLOT_NUM_FIELD << " INTEGER NOT NULL, " << \
		YEAR_OUT_FIELD << " INTEGER NOT NULL, " << \
		EVT_NUM_FIELD << " INTEGER NOT NULL, " << \
		BPS_NUM_FIELD << " INTEGER NOT NULL, " << \
		DOM_SPP_FIELD << " char(255), " << \
		SPP_CODE_FIELD << " char(8), " << \
		BIOMASS_SHRUB_OUT_FIELD << " REAL);";

	char* sql = new char; 
	sql = streamToCharPtr(&sqlstream);
	RC = create_table(sql);
	delete[] sql;
	return RC;
}

int* RVS::Biomass::BiomassDIO::write_biomass_intermediate_record(RVS::DataManagement::AnalysisPlot* ap, RVS::DataManagement::SppRecord* record, int* plot_num, int* year, double* shrubBiomass)
{
	std::stringstream sqlstream;
	sqlstream << "INSERT INTO " << BIOMASS_INTERMEDIATE_TABLE << " (" << \
		PLOT_NUM_FIELD << ", " << YEAR_OUT_FIELD << ", " << EVT_NUM_FIELD << ", " << BPS_NUM_FIELD << " ," << \
		DOM_SPP_FIELD << ", " << SPP_CODE_FIELD << ", " << BIOMASS_SHRUB_OUT_FIELD << ") " << \
		"VALUES (" << *plot_num << "," << *year << "," << ap->EVT_NUM() << "," << ap->BPS_NUM() << ",\"" << \
		record->DOM_SPP() << "\",\"" << record->SPP_CODE() << "\"," << *shrubBiomass << ");";

	char* sql = new char;
	sql = streamToCharPtr(&sqlstream);
	RC = exec_sql(sql);
	delete[] sql;
	return RC;
}

int RVS::Biomass::BiomassDIO::query_biomass_crosswalk_table(std::string spp, std::string returnType)
{
	// Create the sqlite3 statment to query biomass crosswalk table on species
	sqlite3_stmt* stmt = query_base(BIOMASS_CROSSWALK_TABLE, SPP_CODE_FIELD, spp);
	int colNum = sqlite3_column_count(stmt);
	// Initiate the query
	*RC = sqlite3_step(stmt);
	// Step over the columns, looking for the requested return type
	int ret = 0;
	for (int i = 0; i < colNum; i++)
	{
		// If the column name matches the return type, return the equation number found there
		if (strcmp(sqlite3_column_name(stmt, i), returnType.c_str()) == 0)
		{
			ret = sqlite3_column_int(stmt, i);
		}
	}
	// Cleanup
	*RC = sqlite3_finalize(stmt);
	return ret;
}

RVS::DataManagement::DataTable* RVS::Biomass::BiomassDIO::query_biomass_equation_table(int equation_number)
{
	sqlite3_stmt* stmt = query_base(BIOMASS_EQUATION_TABLE, EQUATION_NUMBER_FIELD, equation_number);
	DataManagement::DataTable* dt = new DataManagement::DataTable(stmt);
	return dt;
}

void RVS::Biomass::BiomassDIO::query_equation_coefficients(int equation_number, double* coefs)
{
	// Get the datatable object for the requested equation number
	RVS::DataManagement::DataTable* dt = query_biomass_equation_table(equation_number);
	// Initiate the query
	*RC = sqlite3_step(dt->getStmt());

	int column = 0;
	column = dt->Columns[EQN_COEF_1_FIELD];
	getVal(dt->getStmt(), column, &coefs[0]);
	column = dt->Columns[EQN_COEF_2_FIELD];
	getVal(dt->getStmt(), column, &coefs[1]);
	column = dt->Columns[EQN_COEF_3_FIELD];
	getVal(dt->getStmt(), column, &coefs[2]);
	column = dt->Columns[EQN_COEF_4_FIELD];
	getVal(dt->getStmt(), column, &coefs[3]);
	
	delete dt;
}

void RVS::Biomass::BiomassDIO::query_equation_parameters(int equation_number, std::string* params)
{
	// Get the datatable object for the requested equation number
	RVS::DataManagement::DataTable* dt = query_biomass_equation_table(equation_number);
	// Initiate the query
	*RC = sqlite3_step(dt->getStmt());

	int column = 0;
	column = dt->Columns[EQN_P1_FIELD];
	getVal(dt->getStmt(), column, &params[0]);
	column = dt->Columns[EQN_P2_FIELD];
	getVal(dt->getStmt(), column, &params[1]);
	column = dt->Columns[EQN_P3_FIELD];
	getVal(dt->getStmt(), column, &params[2]);

	delete dt;
}

double RVS::Biomass::BiomassDIO::query_biomass_pp_table(int baseBPS, char* level)
{
	// Get the datatable for the herb biomass
	sqlite3_stmt* stmt = query_base(BIOMASS_PRIMARYPRODUCTION_TABLE, BPS_NUM_FIELD, baseBPS);
	DataManagement::DataTable* dt = new DataManagement::DataTable(stmt);

	double biomass = 0;

	int colCount = sqlite3_column_count(dt->getStmt());
	*RC = sqlite3_step(dt->getStmt());

	// Step through the returned record set. Match the column name to the requested level
	for (int i = 0; i < colCount; i++)
	{
		// If the column name matches the requested return level, get the value
		// and stop iteration.
		const char* colName = sqlite3_column_name(dt->getStmt(), i);
		if (strcmp(colName, level) == 0)
		{
			biomass = sqlite3_column_int(dt->getStmt(), i);
			break;
		}
	}

	delete dt;
	return biomass;
}

void RVS::Biomass::BiomassDIO::query_biogroup_coefs(int bps, double* group_const, double* ndvi_grp_interact, double* ppt_grp_interact)
{
	sqlite3_stmt* stmt1 = query_base(BIOMASS_MACROGROUP_TABLE, BPS_NUM_FIELD, bps);

	int colCount = sqlite3_column_count(stmt1);
	*RC = sqlite3_step(stmt1);
	char* groupID = NULL;

	for (int i = 0; i < colCount; i++)
	{
		const char* colName = sqlite3_column_name(stmt1, i);
		if (strcmp(colName, GROUP_ID_FIELD) == 0)
		{
			groupID = (char*)sqlite3_column_text(stmt1, i);
		}
	}

	if (groupID == NULL)
	{
		//$$ Throw new DATANOTFOUND error here
	}

	
	std::stringstream sqlstream;
	sqlstream << "SELECT * FROM " << BIOMASS_GROUP_COEFS_TABLE << \
		" WHERE " << GROUP_ID_FIELD << "='" << groupID << "';";

	char* sql = new char;
	sql = streamToCharPtr(&sqlstream);
	sqlite3_stmt* stmt2 = query_base(sql);
	*RC = sqlite3_step(stmt2);
	colCount = sqlite3_column_count(stmt2);

	for (int i = 0; i < colCount; i++)
	{
		const char* colName = sqlite3_column_name(stmt2, i);
		if (strcmp(colName, GROUP_CONST_FIELD) == 0)
		{
			double GC = sqlite3_column_double(stmt2, i);
			*group_const = sqlite3_column_double(stmt2, i);
		}
		else if (strcmp(colName, NDVI_INTERACT_FIELD) == 0)
		{
			*ndvi_grp_interact = sqlite3_column_double(stmt2, i);
		}
		else if (strcmp(colName, PRCP_INTERACT_FIELD) == 0)
		{
			*ppt_grp_interact = sqlite3_column_double(stmt2, i);
		}
	}

	delete[] sql;
	*RC = sqlite3_finalize(stmt1);
	*RC = sqlite3_finalize(stmt2);
}