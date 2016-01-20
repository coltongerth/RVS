/// ********************************************************** ///
/// Name: main.cpp                                             ///
/// Desc: (Test) driver for RVS. Build as execultable and      ///
/// this becomes the program entry point                       ///
/// Base Class(es): none                                       ///
/// Last Modified: 5 Aug 15                                    ///
/// ********************************************************** ///

/*
#include <ctime>
#include <fstream>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <boost/thread.hpp>
#include <boost/bind.hpp>
//#include <boost/exception/all.hpp>

#include "RVSDEF.h"
#include "DataManagement/DIO.h"
#include "DataManagement/AnalysisPlot.h"
#include "DataManagement/RVSException.h"
#include "Biomass/BiomassDIO.h"
#include "Biomass/BiomassDriver.h"
#include "Biomass/BiomassEqDriver.h"
#include "Fuels/FuelsDIO.h"
#include "Fuels/FuelsDriver.h"
#include "Succession/SuccessionDIO.h"
#include "Succession/SuccessionDriver.h"

using namespace std;
using namespace RVS;
using namespace RVS::DataManagement;

int* RC = new int(SQLITE_OK);
int* YEARS = new int(150);
bool* SUPPRESS_MSG = new bool(true);
const char* DEBUG_FILE = "RVS_Debug.txt";
bool* USE_MEM = new bool(true);

void simulate(int year, RVS::DataManagement::AnalysisPlot* currentPlot,
	Biomass::BiomassDriver* bd, Fuels::FuelsDriver* fd, Succession::SuccessionDriver* sd);

int main2(int argc, char* argv[])
{
	time_t t = time(NULL);
	unique_ptr<ofstream> dfile(new ofstream(DEBUG_FILE, ios::out));
	*dfile << ctime(&t) << "\n";
	dfile->close();

	///////////////////////////
	/// User execution args ///
	///////////////////////////

	/// Get DIO ready for queries
	Biomass::BiomassDIO* bdio = new Biomass::BiomassDIO();
	Fuels::FuelsDIO* fdio = new Fuels::FuelsDIO();
	Succession::SuccessionDIO* sdio = new Succession::SuccessionDIO();

	vector<int> plotcounts = bdio->query_analysis_plots();
	map<int, AnalysisPlot*> aps;

	///////////////////////////////////////////////////////////////////////
	/// Load analysis plots and shrub records into a map keyed by plot id
	///////////////////////////////////////////////////////////////////////

	std::cout << SQLITE_VERSION << std::endl << SQLITE_SOURCE_ID << std::endl;
	std::cout << "Loading records..." << std::endl;
	AnalysisPlot* currentPlot = NULL;

	RVS::DataManagement::DataTable* plots_dt = bdio->query_input_table();

	while (*RC == SQLITE_ROW)
	{
		currentPlot = new AnalysisPlot(fdio, plots_dt);
		aps.insert(pair<int, AnalysisPlot*>(currentPlot->PLOT_ID(), currentPlot));
		*RC = sqlite3_step(plots_dt->getStmt());
	}

	RVS::DataManagement::DataTable* shrub_dt = bdio->query_shrubs_table();

	int plot_id = 0;
	while (*RC == SQLITE_ROW)
	{
		bdio->getVal(shrub_dt->getStmt(), shrub_dt->Columns[PLOT_NUM_FIELD], &plot_id);
		currentPlot = aps[plot_id];
		currentPlot->push_shrub(bdio, shrub_dt);
		*RC = sqlite3_step(shrub_dt->getStmt());
	}

	std::cout << "Done." << std::endl;

	Biomass::BiomassEqDriver beqd = Biomass::BiomassEqDriver(bdio, *SUPPRESS_MSG);

	vector<int> testEquations = vector<int>();

	ifstream equationsFile;
	equationsFile.open("C:\\Users\\robblankston\\Documents\\GitHub\\RVS\\librvs\\biomass_text_equations.txt");
	string line;
	if (equationsFile.is_open())
	{
		while (getline(equationsFile, line))
		{
			line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
			int eqNum = std::stoi(line);
			testEquations.push_back(eqNum);
		}
		equationsFile.close();
	}

	for (vector<int>::iterator it = testEquations.begin(); it != testEquations.end(); ++it)
	{
		std::cout << "\n===================================" << std::endl;
		std::cout << "EQUATION " << *it << std::endl;
		std::cout << "===================================\n" << std::endl;

		for (int &p : plotcounts)
		{
			currentPlot = aps[p];
			RC = beqd.BioMain(*it, currentPlot);
		}

		stringstream ss;
		ss << "EQUATION " << *it << " finished";
		bdio->write_debug_msg(ss.str().c_str());
	}


	bdio->write_output();

	delete bdio;
	delete fdio;
	delete sdio;

	std::cout << std::endl << "Ran to completion." << std::endl;

	t = time(NULL);
	dfile = unique_ptr<ofstream>(new ofstream(DEBUG_FILE, ios::app));
	*dfile << ctime(&t) << "\n";
	dfile->close();



	return (*RC);
}

void simulate(int year, RVS::DataManagement::AnalysisPlot* currentPlot,
	Biomass::BiomassDriver* bd, Fuels::FuelsDriver* fd, Succession::SuccessionDriver* sd)
{
	if (!*SUPPRESS_MSG)
	{
		std::cout << std::endl;
		std::cout << "Results for plot " << currentPlot->PLOT_ID() << std::endl;
		std::cout << "====================" << std::endl;
	}

	double biomass = 0;
	double shrubBiomass = 0;
	double herbBiomass = 0;

	RC = bd->BioMain(year, currentPlot);

	//RC = sd->SuccessionMain(year, currentPlot);
}
*/