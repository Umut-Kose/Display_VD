
#ifndef Hits_h
#define Hits_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <TTreePerfStats.h>
#include <TLorentzVector.h>

using namespace std;

class Hits : public TObject {
	public :

	static const Int_t   kMaxSeg = 4000;
   // Declaration of leaf types
   Int_t           RunNum;
   Int_t           EveNum;
   Int_t           NIncHits;
   Int_t           IdInc[1];   //[NIncHits]
   Int_t           IdParInc[1];   //[NIncHits]
   Int_t           TrInc[1];   //[NIncHits]
   Int_t           ParTrInc[1];   //[NIncHits]
   Int_t           IntParInc[1];   //[NIncHits]
   Int_t           RegInc[1];   //[NIncHits]
   Float_t         PosInc[1][3];   //[NIncHits]
   Float_t         PInc[1][5];   //[NIncHits]
   Float_t         TimeInc[1];   //[NIncHits]
   Int_t           NCalHits;
   Int_t           WhCal[1];   //[NCalHits]
   Float_t         PosCal[1][3];   //[NCalHits]
   Float_t         EneCal[1];   //[NCalHits]
   Float_t         EqCal[1];   //[NCalHits]
   Int_t           NCHitPiz;
   Int_t           WhCPiz[1];   //[NCHitPiz]
   Float_t         PosCPiz[1][3];   //[NCHitPiz]
   Float_t         EneCPiz[1];   //[NCHitPiz]
   Float_t         EqCPiz[1];   //[NCHitPiz]
   Int_t           NIneHits;
   Int_t           TypeIne[18];   //[NIneHits]
   Int_t           IdIne[18];   //[NIneHits]
   Int_t           TrIne[18];   //[NIneHits]
   Int_t           IdParIne[18];   //[NIneHits]
   Int_t           IntParIne[1];   //[NIncHits]
   Float_t         PIne[18][5];   //[NIneHits]
   Float_t         PosIne[18][3];   //[NIneHits]
   Float_t         TimeIne[18];   //[NIneHits]
   Int_t           NSecIne[18];   //[NIneHits]
   Int_t           FirstSec[18];   //[NIneHits]
   Int_t           NTIneSec;
   Int_t           HitSecIne[52];   //[NTIneSec]
   Int_t           IdSecIne[52];   //[NTIneSec]
   Int_t           TrSecIne[52];   //[NTIneSec]
   Float_t         PSec[52][5];   //[NTIneSec]

   // List of branches
   TBranch        *b_RunNum;   //!
   TBranch        *b_EveNum;   //!
   TBranch        *b_NIncHits;   //!
   TBranch        *b_IdInc;   //!
   TBranch        *b_IdParInc;   //!
   TBranch        *b_TrInc;   //!
   TBranch        *b_ParTrInc;   //!
   TBranch        *b_IntParInc;   //!
   TBranch        *b_RegInc;   //!
   TBranch        *b_PosInc;   //!
   TBranch        *b_PInc;   //!
   TBranch        *b_TimeInc;   //!
   TBranch        *b_NCalHits;   //!
   TBranch        *b_WhCal;   //!
   TBranch        *b_PosCal;   //!
   TBranch        *b_EneCal;   //!
   TBranch        *b_EqCal;   //!
   TBranch        *b_NCHitPiz;   //!
   TBranch        *b_WhCPiz;   //!
   TBranch        *b_PosCPiz;   //!
   TBranch        *b_EneCPiz;   //!
   TBranch        *b_EqCPiz;   //!
   TBranch        *b_NIneHits;   //!
   TBranch        *b_TypeIne;   //!
   TBranch        *b_IdIne;   //!
   TBranch        *b_TrIne;   //!
   TBranch        *b_IdParIne;   //!
   TBranch        *b_IntParIne;   //!
   TBranch        *b_PIne;   //!
   TBranch        *b_PosIne;   //!
   TBranch        *b_TimeIne;   //!
   TBranch        *b_NSecIne;   //!
   TBranch        *b_FirstSec;   //!
   TBranch        *b_NTIneSec;   //!
   TBranch        *b_HitSecIne;   //!
   TBranch        *b_IdSecIne;   //!
   TBranch        *b_TrSecIne;   //!
   TBranch        *b_PSec;   //!

   Hits();
   ~Hits(){};
	static Hits* giveThis();
	static Hits* giveThis(TTree* aTree, const std::string& option);
	static void releaseThis();
	void setupRead(const std::string& option = "");
	bool SetBranchAddresses();
	Hits(TTree* aTree, const std::string& option);
	TTree* GetInputTree();
	void GetHits(Long64_t entry);
	Int_t       GetRunNumber()               { return m_run;           };
	Int_t       GetEventNumber()             { return m_event;         };
	//
	// inelastic and decays
	Int_t       GetNumberOfDecay()           { return m_numdcy;        };
	Int_t       GetType(Int_t index)         { return m_typ[index];    };
	Int_t       GetId(Int_t index)           { return m_id[index];     };
	Int_t       GetDauNumber(Int_t index)    { return m_trk[index];    };
	Int_t       GetDauParent(Int_t index)    { return m_prnt[index];   };
	TLorentzVector *GetDau4Mom(Int_t index)  { return m_dau4mom[index];};
	Float_t     GetDauPos(Int_t index)       { return m_posdau[index]; };
	// 
	// secondaries
	Int_t       GetNumberOfSecondaries()     { return m_num2nd;        };
	Int_t       GetId2nd(Int_t index)        { return m_id2nd[index];  };
	Int_t       Get2ndNumber(Int_t index)    { return m_2nd[index];    };
	TLorentzVector *GetSec4Mom(Int_t index)  { return m_sec4mom[index];};
	private:
		TTree* m_treeIn;
		Int_t 	m_run, m_event, m_numdcy, m_num2nd; 
		Int_t  m_id[kMaxSeg],m_trk[kMaxSeg],m_typ[kMaxSeg],m_prnt[kMaxSeg];
		Int_t  m_id2nd[kMaxSeg],m_2nd[kMaxSeg];
		TLorentzVector *m_dau4mom[kMaxSeg];
		TLorentzVector *m_sec4mom[kMaxSeg];
		Float_t m_posdau[3];
		
		static Hits* m_instance;
		ClassDef(Hits,0)
};
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// initialisation of the Hits pointer
Hits* Hits::m_instance = 0;
Hits::Hits(){	}
// to get a unique instance 
inline Hits* Hits::giveThis()
{
	cout << "debug::m_instance Hits 0 " << m_instance << endl;
	if (0 == m_instance){
		cout << "Hits::giveThis error not constructed properly " << endl;
	}
	return m_instance;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Open a TTree for reading (writing option not now)
inline Hits* Hits::giveThis(TTree* aTree, const std::string& option)
{
	cout << "debug::m_instance Hits " << m_instance << endl;
	if(m_instance != 00000000) m_instance = 0;
	if (0 == m_instance){
		m_instance = new Hits(aTree, option);
		cout << "umutumut" << endl;
	} else{
		cout << "Hits::giveThis Warning " << aTree->GetTitle() << " " << aTree->GetName() << endl;
	}
	return m_instance;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Delete unique instance
inline void Hits::releaseThis() {
	if ( m_instance != 0 ) {
		delete m_instance;
		m_instance = 0;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// constructor for one TTree with read/write option
Hits::Hits(TTree* aTree, const std::string& option){
	if(option=="read"){
		m_treeIn = aTree;
		setupRead();
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// setup the input tree for reading
void Hits::setupRead(const std::string& option){
	if(!m_treeIn){
		cout << "setupRead error: m_treeIn undefined " << endl;
		exit(1);
	}
	if(SetBranchAddresses()){}else{
		cerr << "TBranch error.."<< endl;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Setting up Branch content of input TTree
bool Hits::SetBranchAddresses()
{
//		if(DEBUG_rg) cout << " ....inside setbranchaddresses.... " << endl;
	m_treeIn->SetMakeClass(1);
	m_treeIn->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
	m_treeIn->SetBranchAddress("EveNum", &EveNum, &b_EveNum);
	m_treeIn->SetBranchAddress("NIncHits", &NIncHits, &b_NIncHits);
	m_treeIn->SetBranchAddress("IdInc", &IdInc, &b_IdInc);
	m_treeIn->SetBranchAddress("IdParInc", &IdParInc, &b_IdParInc);
	m_treeIn->SetBranchAddress("TrInc", &TrInc, &b_TrInc);
	m_treeIn->SetBranchAddress("ParTrInc", &ParTrInc, &b_ParTrInc);
	m_treeIn->SetBranchAddress("IntParInc", &IntParInc, &b_IntParInc);
	m_treeIn->SetBranchAddress("RegInc", &RegInc, &b_RegInc);
	m_treeIn->SetBranchAddress("PosInc", &PosInc, &b_PosInc);
	m_treeIn->SetBranchAddress("PInc", &PInc, &b_PInc);
	m_treeIn->SetBranchAddress("TimeInc", &TimeInc, &b_TimeInc);
	m_treeIn->SetBranchAddress("NCalHits", &NCalHits, &b_NCalHits);
	m_treeIn->SetBranchAddress("WhCal", &WhCal, &b_WhCal);
	m_treeIn->SetBranchAddress("PosCal", &PosCal, &b_PosCal);
	m_treeIn->SetBranchAddress("EneCal", &EneCal, &b_EneCal);
	m_treeIn->SetBranchAddress("EqCal", &EqCal, &b_EqCal);
	m_treeIn->SetBranchAddress("NCHitPiz", &NCHitPiz, &b_NCHitPiz);
	m_treeIn->SetBranchAddress("WhCPiz", &WhCPiz, &b_WhCPiz);
	m_treeIn->SetBranchAddress("PosCPiz", &PosCPiz, &b_PosCPiz);
	m_treeIn->SetBranchAddress("EneCPiz", &EneCPiz, &b_EneCPiz);
	m_treeIn->SetBranchAddress("EqCPiz", &EqCPiz, &b_EqCPiz);
	m_treeIn->SetBranchAddress("NIneHits", &NIneHits, &b_NIneHits);
	m_treeIn->SetBranchAddress("TypeIne", TypeIne, &b_TypeIne);
	m_treeIn->SetBranchAddress("IdIne", IdIne, &b_IdIne);
	m_treeIn->SetBranchAddress("TrIne", TrIne, &b_TrIne);
	m_treeIn->SetBranchAddress("IdParIne", IdParIne, &b_IdParIne);
	m_treeIn->SetBranchAddress("IntParIne", &IntParIne, &b_IntParIne);
	m_treeIn->SetBranchAddress("PIne", PIne, &b_PIne);
	m_treeIn->SetBranchAddress("PosIne", PosIne, &b_PosIne);
	m_treeIn->SetBranchAddress("TimeIne", TimeIne, &b_TimeIne);
	m_treeIn->SetBranchAddress("NSecIne", NSecIne, &b_NSecIne);
	m_treeIn->SetBranchAddress("FirstSec", FirstSec, &b_FirstSec);
	m_treeIn->SetBranchAddress("NTIneSec", &NTIneSec, &b_NTIneSec);
	m_treeIn->SetBranchAddress("HitSecIne", HitSecIne, &b_HitSecIne);
	m_treeIn->SetBranchAddress("IdSecIne", IdSecIne, &b_IdSecIne);
	m_treeIn->SetBranchAddress("TrSecIne", TrSecIne, &b_TrSecIne);
	m_treeIn->SetBranchAddress("PSec", PSec, &b_PSec);
   return true;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// accessors for the input TTree
TTree* Hits::GetInputTree() {return m_treeIn;};
// get all branch contents of input TTree for entry i
void Hits::GetHits(Long64_t entry)
{
	if (!m_treeIn) {
		cout << "Hits::getEntry error" << endl;
		exit(1);
	}
	//
	// Turn on ALL branches                                                      
	m_treeIn->SetBranchStatus("*", 1);
	m_treeIn->GetEntry(entry);
	m_run          = RunNum; 
	m_event        = EveNum; 
	m_numdcy       = NIneHits;
	m_num2nd       = NTIneSec;
	//
	for(int i=0; i< NIneHits; i++)
	{
		// inelastic or decay
		m_id[i]  = IdIne[i];
		m_trk[i] = TrIne[i];
		m_prnt[i] = IdParIne[i];
		m_typ[i] = TypeIne[i];
		m_dau4mom[i] = new TLorentzVector();
		m_dau4mom[i]->SetPxPyPzE(PIne[i][0],PIne[i][1],PIne[i][2],PIne[i][3]);
		for(int j=0; j<3; j++)
			m_posdau[j] = PosIne[i][j];
		// secondaries
		m_id2nd[i]   = IdSecIne[i];
		m_2nd[i]     = TrSecIne[i];
		m_sec4mom[i] = new TLorentzVector();
		m_sec4mom[i]->SetPxPyPzE(PSec[i][0],PSec[i][1],PSec[i][2],PSec[i][3]);
	}
	
}


#endif
