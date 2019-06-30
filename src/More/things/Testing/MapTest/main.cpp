#include <map>
#include <string>
#include <vector>
#include <cfloat>
#include <cmath>
#include <stdio.h>

enum {
    eINT_LON = 0,
    eINT_LAT,
    eINT_VERT,
    eINT_PAR1,
    eINT_PAR2,
    eINT_MAX_PAR // no params beyond this
  };

  enum {
    eMAP_PROFILE = 0,
    eMAP_TBL_X,
    eMAP_TBL_Y,
    eMAP_TBL_Z,
    eMAP_PAR_1,
    eMAP_PAR_2,
    eMAP_MAX_PAR
  };

	  const int gProfilesTotal2 = 45;

	    std::string
    g_Data_File_Descriptor2[gProfilesTotal2][eMAP_MAX_PAR]
  // -------                                       -------   -------    -------   ------- ------- 
  // Profile                                        LONG      LAT        VERT      First   Second
  // name                                           table     table      table     param   param
  // -------                                       -------   -------    -------   ------- ------- 
  = {
      {"WSHR_PROF_MOD1_VR",                       "FLONG1",  "FLAT1",   "FVSHR1",  "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD1_3DEGPITCH",                "FLONG1",  "FLAT1",   "FVSHR1",  "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD3_100FT",                    "FLONG3",  "FLAT3",   "FVSHR3",  "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD2_200FT",                    "FLONG2",  "FLAT2",   "FVSHR2",  "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD1_300FT",                    "FLONG1",  "FLAT1",   "FVSHR1",  "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD4_1200FT",                   "FLONG4",  "FLAT4",   "FVSHR4",  "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD7_NEUTRAL_SRI1",             "FLONG7",  "FLAT7",   "FVSHR7",  "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD8_FRONTAL1TOKYO_SRI2",       "FLONG8",  "FLAT8",   "FVSHR8",  "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD9_TSTORM1FAA_SRI3",          "FLONG9",  "FLAT9",   "FVSHR9",  "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD10_TSTORM2PHIL_SRI4",        "FLONG10", "FLAT10",  "FVSHR10", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD11_FRONTAL2BOSTON_SRI5",     "FLONG11", "FLAT11",  "FVSHR11", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD12_TSTORM3_SRI6",            "FLONG12", "FLAT12",  "FVSHR12", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD13_TSTORM4_SRI7",            "FLONG13", "FLAT13",  "FVSHR13", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD14_TSTORM5_SRI8",            "FLONG14", "FLAT14",  "FVSHR14", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD15_FRONTAL3_SRI9",           "FLONG15", "FLAT15",  "FVSHR15", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD16_TSTORM6_SRI10",           "FLONG16", "FLAT16",  "FVSHR16", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD17_DELTA191_560FT",          "FLONG25", "FLAT25",  "FVSHR25", "WSHR XREF",  ""   },
      {"WSHR_PROF_DALLAS_TFUJITA",                "FNSHR18", "FESHR18", "FVSHR18", "WSHR XREF", "ALTITUDE AGL" },
      {"WSHR_PROF_MOD4_FAA120_41",                "FLONG19", "FLAT19",  "FVSHR19", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_MOD6_FAA120_41",                "FLONG20", "FLAT20",  "FVSHR20", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_MOD7_FAA120_41",                "FLONG21", "FLAT21",  "FVSHR21", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_MOD8_FAA120_41",                "FLONG22", "FLAT22",  "FVSHR22", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_MOD9_FAA120_41",                "FLONG23", "FLAT23",  "FVSHR23", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_MOD10_FAA120_41",               "FLONG24", "FLAT24",  "FVSHR24", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_MOD7_DELTA191_2200FT",          "FLONG25", "FLAT25",  "FVSHR25", "WSHR XREF",   ""  },
      {"WSHR_PROF_NEWORLEANS_TFUJITA",            "FNSHR26", "FESHR26", "FVSHR26", "WSHR XREF", "ALTITUDE AGL" },
      {"WSHR_PROF_JFK_SUNDSTRAND",                "FNSHR27", "FESHR27", "FVSHR27", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_PHIL_23JUN76",                  "FNSHR28", "FESHR28", "FVSHR28", "WSHR XREF",   ""  },
      {"WSHR_PROF_DENVER_SUNDSTRAND",             "FNSHR29", "FESHR29", "FVSHR29", "WSHR XREF",   ""  },
      {"WSHR_PROF_MOD2_SUNDSTRAND",               "FLONG2",  "FLAT2",   "FVSHR2",  "WSHR XREF",   ""  },
      {"WSHR_PROF_JETLDG1",                       "FNSHR31", "FESHR31", "FVSHR31", "ALTITUDE AGL",    ""  },
      {"WSHR_PROF_JETLDG2",                       "FNSHR32", "FESHR32", "FVSHR32", "ALTITUDE AGL",    ""  },
      {"WSHR_PROF_JETLDG3",                       "FNSHR33", "FESHR33", "FVSHR33", "ALTITUDE AGL",    ""  },
      {"WSHR_PROF_DOUGLAS6395A",                  "FNSHR34", "FESHR34", "FVSHR34", "ALTITUDE AGL",    ""  },
      {"WSHR_PROF_CEDARHILL",                     "FNSHR35", "FESHR35", "FVSHR35", "ALTITUDE AGL",    ""  },
      {"WSHR_PROF_CHARLOTTE",                     "FNSHR36", "FESHR36", "FVSHR36", "WSHR XREF",   ""  },
      {"WSHR_PROF_DELTA_500FT",                   "FLONG1",  "FLAT1",   "FVSHR1",  "WSHR XREF",   ""  },
      {"WSHR_PROF_JET_UPSET",                     "FNSHR37", "FESHR37", "FVSHR37", "UPSET DISTANCE",   "ALTITUDE AGL"  },
      {"WSHR_PROF_A350_OVERSPD_DEMO",                "",        "",        "",       "",     ""  },
      {"WSHR_PROF_MOD1_HELO_60KTS",               "FLONG41", "FLAT41",  "FVSHR41", "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD1_HELO_30KTS",               "FLONG41", "FLAT41",  "FVSHR41", "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD2_HELO_50FT",                "FLONG42", "FLAT42",  "FVSHR42", "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD3_HELO_100FT",               "FLONG43", "FLAT43",  "FVSHR43", "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD1_HELO_150FT",               "FLONG41", "FLAT41",  "FVSHR41", "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD4_HELO_300FT",               "FLONG44", "FLAT44",  "FVSHR44", "WSHR XREF",  ""   },
    };

char * dataFileChar[gProfilesTotal2][eMAP_MAX_PAR]
  = {
      {"WSHR_PROF_MOD1_VR",                       "FLONG1",  "FLAT1",   "FVSHR1",  "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD1_3DEGPITCH",                "FLONG1",  "FLAT1",   "FVSHR1",  "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD3_100FT",                    "FLONG3",  "FLAT3",   "FVSHR3",  "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD2_200FT",                    "FLONG2",  "FLAT2",   "FVSHR2",  "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD1_300FT",                    "FLONG1",  "FLAT1",   "FVSHR1",  "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD4_1200FT",                   "FLONG4",  "FLAT4",   "FVSHR4",  "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD7_NEUTRAL_SRI1",             "FLONG7",  "FLAT7",   "FVSHR7",  "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD8_FRONTAL1TOKYO_SRI2",       "FLONG8",  "FLAT8",   "FVSHR8",  "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD9_TSTORM1FAA_SRI3",          "FLONG9",  "FLAT9",   "FVSHR9",  "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD10_TSTORM2PHIL_SRI4",        "FLONG10", "FLAT10",  "FVSHR10", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD11_FRONTAL2BOSTON_SRI5",     "FLONG11", "FLAT11",  "FVSHR11", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD12_TSTORM3_SRI6",            "FLONG12", "FLAT12",  "FVSHR12", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD13_TSTORM4_SRI7",            "FLONG13", "FLAT13",  "FVSHR13", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD14_TSTORM5_SRI8",            "FLONG14", "FLAT14",  "FVSHR14", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD15_FRONTAL3_SRI9",           "FLONG15", "FLAT15",  "FVSHR15", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD16_TSTORM6_SRI10",           "FLONG16", "FLAT16",  "FVSHR16", "ALTITUDE AGL",   ""   },
      {"WSHR_PROF_MOD17_DELTA191_560FT",          "FLONG25", "FLAT25",  "FVSHR25", "WSHR XREF",  ""   },
      {"WSHR_PROF_DALLAS_TFUJITA",                "FNSHR18", "FESHR18", "FVSHR18", "WSHR XREF", "ALTITUDE AGL" },
      {"WSHR_PROF_MOD4_FAA120_41",                "FLONG19", "FLAT19",  "FVSHR19", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_MOD6_FAA120_41",                "FLONG20", "FLAT20",  "FVSHR20", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_MOD7_FAA120_41",                "FLONG21", "FLAT21",  "FVSHR21", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_MOD8_FAA120_41",                "FLONG22", "FLAT22",  "FVSHR22", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_MOD9_FAA120_41",                "FLONG23", "FLAT23",  "FVSHR23", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_MOD10_FAA120_41",               "FLONG24", "FLAT24",  "FVSHR24", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_MOD7_DELTA191_2200FT",          "FLONG25", "FLAT25",  "FVSHR25", "WSHR XREF",   ""  },
      {"WSHR_PROF_NEWORLEANS_TFUJITA",            "FNSHR26", "FESHR26", "FVSHR26", "WSHR XREF", "ALTITUDE AGL" },
      {"WSHR_PROF_JFK_SUNDSTRAND",                "FNSHR27", "FESHR27", "FVSHR27", "ALTITUDE AGL",  "WSHR XREF"},
      {"WSHR_PROF_PHIL_23JUN76",                  "FNSHR28", "FESHR28", "FVSHR28", "WSHR XREF",   ""  },
      {"WSHR_PROF_DENVER_SUNDSTRAND",             "FNSHR29", "FESHR29", "FVSHR29", "WSHR XREF",   ""  },
      {"WSHR_PROF_MOD2_SUNDSTRAND",               "FLONG2",  "FLAT2",   "FVSHR2",  "WSHR XREF",   ""  },
      {"WSHR_PROF_JETLDG1",                       "FNSHR31", "FESHR31", "FVSHR31", "ALTITUDE AGL",    ""  },
      {"WSHR_PROF_JETLDG2",                       "FNSHR32", "FESHR32", "FVSHR32", "ALTITUDE AGL",    ""  },
      {"WSHR_PROF_JETLDG3",                       "FNSHR33", "FESHR33", "FVSHR33", "ALTITUDE AGL",    ""  },
      {"WSHR_PROF_DOUGLAS6395A",                  "FNSHR34", "FESHR34", "FVSHR34", "ALTITUDE AGL",    ""  },
      {"WSHR_PROF_CEDARHILL",                     "FNSHR35", "FESHR35", "FVSHR35", "ALTITUDE AGL",    ""  },
      {"WSHR_PROF_CHARLOTTE",                     "FNSHR36", "FESHR36", "FVSHR36", "WSHR XREF",   ""  },
      {"WSHR_PROF_DELTA_500FT",                   "FLONG1",  "FLAT1",   "FVSHR1",  "WSHR XREF",   ""  },
      {"WSHR_PROF_JET_UPSET",                     "FNSHR37", "FESHR37", "FVSHR37", "UPSET DISTANCE",   "ALTITUDE AGL"  },
      {"WSHR_PROF_A350_OVERSPD_DEMO",                "",        "",        "",       "",     ""  },
      {"WSHR_PROF_MOD1_HELO_60KTS",               "FLONG41", "FLAT41",  "FVSHR41", "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD1_HELO_30KTS",               "FLONG41", "FLAT41",  "FVSHR41", "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD2_HELO_50FT",                "FLONG42", "FLAT42",  "FVSHR42", "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD3_HELO_100FT",               "FLONG43", "FLAT43",  "FVSHR43", "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD1_HELO_150FT",               "FLONG41", "FLAT41",  "FVSHR41", "WSHR XREF",  ""   },
      {"WSHR_PROF_MOD4_HELO_300FT",               "FLONG44", "FLAT44",  "FVSHR44", "WSHR XREF",  ""   },
    };

int main(int argc, char** argv){

	printf("%s\n", argv[0]);
	char* text = "LMAO GOTEM";
	typedef std::vector<std::string> DATA_TABLE_INFO;
  typedef std::map<std::string, DATA_TABLE_INFO> DATA_TABLE_INFO_MAP;
  typedef std::vector<double*> DATA;
	//
	
	DATA_TABLE_INFO_MAP mProfileMap;
  std::map<std::string, std::vector<std::string>> thisShouldntWork;
  std::map<char*, std::vector<char*>> mapWithChar;



  std::pair<std::string, std::vector<std::string>> wPair("totally a string", std::vector<std::string>(5, "also a string"));
  thisShouldntWork["test"] = std::vector<std::string>();
  thisShouldntWork["brackets"] = std::vector<std::string>(5, "idk");
  thisShouldntWork.insert(make_pair("wow", std::vector<std::string>(5, "double wow")));

  thisShouldntWork.insert(wPair);
	thisShouldntWork.empty();



	mProfileMap.clear();
  //mProfileMap.insert(wPair);
  for(int idx = 0; idx < gProfilesTotal2; ++idx)
  {
    // form profile descriptor
    std::vector<std::string> wVec(eINT_MAX_PAR);
		/*
    wVec[eINT_LON]=g_Data_File_Descriptor2[idx][eMAP_TBL_X];  // name of Longitudinal component table
    wVec[eINT_LAT]=g_Data_File_Descriptor2[idx][eMAP_TBL_Y];  // name of Lateral component table
    wVec[eINT_VERT]=g_Data_File_Descriptor2[idx][eMAP_TBL_Z]; // name of Vertical component table
    wVec[eINT_PAR1]=g_Data_File_Descriptor2[idx][eMAP_PAR_1]; // contains alias of first input parameter
    wVec[eINT_PAR2]=g_Data_File_Descriptor2[idx][eMAP_PAR_2]; // contains alias of second input parameter
    // associate this descriptor with profile name
		*/

		wVec[eINT_LON]=dataFileChar[idx][eMAP_TBL_X];  // name of Longitudinal component table
    wVec[eINT_LAT]=dataFileChar[idx][eMAP_TBL_Y];  // name of Lateral component table
    wVec[eINT_VERT]=dataFileChar[idx][eMAP_TBL_Z]; // name of Vertical component table
    wVec[eINT_PAR1]=dataFileChar[idx][eMAP_PAR_1]; // contains alias of first input parameter
    wVec[eINT_PAR2]=dataFileChar[idx][eMAP_PAR_2]; // contains alias of second input parameter
    std::string wProfileNamePtr(g_Data_File_Descriptor2[idx][eMAP_PROFILE]);

		mProfileMap.insert(std::pair<std::string, DATA_TABLE_INFO >(wProfileNamePtr, wVec));
		
		std::vector<char*> vec;
		vec.insert(vec.begin() + eINT_LON, dataFileChar[idx][eMAP_TBL_X]);
		vec.insert(vec.begin() + eINT_LAT, dataFileChar[idx][eMAP_TBL_Y]);
		vec.insert(vec.begin() + eINT_VERT, dataFileChar[idx][eMAP_TBL_Z]);
		vec.insert(vec.begin() + eINT_PAR1, dataFileChar[idx][eMAP_PAR_1]);
		vec.insert(vec.begin() + eINT_PAR2, dataFileChar[idx][eMAP_PAR_2]);
		//vec[eINT_LON]=dataFileChar[idx][eMAP_TBL_X];  // name of Longitudinal component table
    //vec[eINT_LAT]=dataFileChar[idx][eMAP_TBL_Y];  // name of Lateral component table
    //vec[eINT_VERT]=dataFileChar[idx][eMAP_TBL_Z]; // name of Vertical component table
    //vec[eINT_PAR1]=dataFileChar[idx][eMAP_PAR_1]; // contains alias of first input parameter
    //vec[eINT_PAR2]=dataFileChar[idx][eMAP_PAR_2]; // contains alias of second input parameter

		mapWithChar.insert(std::pair<char*, std::vector<char*>>(dataFileChar[idx][eMAP_PROFILE], vec));
		//mProfileMap.insert(std::pair<char*, std::vector<char*>>(dataFileChar[idx][eMAP_PROFILE], vec));
  }
	std::string s = "WSHR_PROF_MOD1_HELO_150FT";
	std::map<char*, std::vector<char*>>::iterator mapIt;
	//mapIt = mapWithChar.find("WSHR_PROF_MOD1_HELO_150FT");
	//mapIt = mapWithChar.find(s.c_str());
	mapIt = mapWithChar.find(dataFileChar[0][0]);
	if(mapIt == mapWithChar.end())
  {
    // profile not found
    printf("The key has not been found");
  }
	else{
		printf("Key: %s found!", mapIt->first);

	}
	//char* orig_text
	std::string new_s(text);
	int a = mProfileMap.max_size();
	a = mapWithChar.max_size();
	printf("This text - %s - \n", text);
	return 0;

}