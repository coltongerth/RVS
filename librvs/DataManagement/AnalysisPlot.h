/// ********************************************************** ///
/// Name: AnalysisPlot.h                                       ///
/// Desc: Holds a vector of all records in an analysis plot    ///
/// Base Class(es): none                                       ///
/// ********************************************************** ///

#pragma once

#ifndef ANALYSIS_PLOT_H
#define ANALYSIS_PLOT_H

#include <string>
#include <vector>

#include "DataTable.h"
#include "DIO.h"
#include "SppRecord.h"

namespace RVS
{
namespace DataManagement
{
	class AnalysisPlot
	{
	public:
		AnalysisPlot(RVS::DataManagement::DIO* dio, RVS::DataManagement::DataTable* dt);
		virtual ~AnalysisPlot(void);

		inline int PLOT_ID() { return plot_id; }
		inline int EVT_NUM() { return evt_num; }
		inline int BPS_NUM() { return bps_num; }

		inline std::vector<RVS::DataManagement::SppRecord*>* SHRUB_RECORDS() { return &shrubRecords; }

		inline double HERBBIOMASS() { return herbBiomass; }
		inline void SET_HERBBIOMASS(double biomass) { herbBiomass = biomass; }
		inline double TOTALBIOMASS() { return totalBiomass; }
		inline void SET_TOTALBIOMASS(double biomass) { totalBiomass = biomass; }
		
		double getNDVI(int year);
		double getPPT(int year);

	private:
		int plot_id;
		int evt_num;
		std::string evt_name;
		int bps_num;

		double totalBiomass;
		double herbBiomass;

		std::vector<RVS::DataManagement::SppRecord*> shrubRecords;   // List of shrub records
		std::vector<double> ndviValues;   // NDVI values for all years to be simulated
		std::vector<double> precipValues; // PPT values for all years to be simulated

		// Builds the AnalysisPlot by querying the appropriate tables(s) in the database
		void buildAnalysisPlot(RVS::DataManagement::DIO* dio, RVS::DataManagement::DataTable* dt);
		// Create shrub records
		void buildShrubRecords(RVS::DataManagement::DIO* dio, int plot_num);
	};
}
}

#endif