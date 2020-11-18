
#ifndef Header_h
#define Header_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <TTreePerfStats.h>
#include <TLorentzVector.h>


using namespace std;

class Header : public TObject {
	  public :

static const Int_t   kMaxSeg = 4000;
   // Declaration of leaf types
   Int_t           RunNum;
   Int_t           EveNum;
   Int_t           ReacType;
   Int_t           IntType;
   Float_t         Vertex[3];
   Int_t           TargZ;
   Int_t           TargA;
   Int_t           Target;
   Int_t           Primary;
   Float_t         P_Primary[5];
   Float_t         Weight;
   Int_t           NumLep;
   Int_t           IdLep[3];   //[NumLep]
   Int_t           TrLep[3];   //[NumLep]
   Float_t         P_Lep[3][5];   //[NumLep]
   Float_t         EneDep_Lep[3];   //[NumLep]
   Float_t         EneDep1st_Lep[3];   //[NumLep]
   Float_t         EneOut_Lep[3];   //[NumLep]
   Int_t           NumHad;
   Int_t           IdHad[24];   //[NumHad]
   Int_t           TrHad[24];   //[NumHad]
   Float_t         P_Had[24][5];   //[NumHad]
   Float_t         EneDep_Had[24];   //[NumHad]
   Float_t         EneDep1st_Had[24];   //[NumHad]
   Float_t         EneOut_Had[24];   //[NumHad]
   Int_t           NumPhot;
   Int_t           IdPhot[8];   //[NumPhot]
   Int_t           TrPhot[8];   //[NumPhot]
   Float_t         P_Phot[8][5];   //[NumPhot]
   Float_t         EneDep_Phot[8];   //[NumPhot]
   Float_t         EneDep1st_Phot[8];   //[NumPhot]
   Float_t         EneOut_Phot[8];   //[NumPhot]
   Int_t           NumHeavy;
   Int_t           IdHeavy[14];   //[NumHeavy]
   Int_t           TrHeavy[14];   //[NumHeavy]
   Float_t         P_Heavy[14][5];   //[NumHeavy]
   Float_t         EneDep_Heavy[14];   //[NumHeavy]
   Float_t         EneDep1st_Heavy[14];   //[NumHeavy]
   Float_t         EneOut_Heavy[14];   //[NumHeavy]
   Int_t           NumTracks;
   Int_t           IdTrack[31];   //[NumTracks]
   Int_t           Int_Track[31];   //[NumTracks]
   Float_t         Vtx_Track[31][3];   //[NumTracks]
   Int_t           Nsec_Track[31];   //[NumTracks]
   Float_t         Esec_Track[31][3];   //[NumTracks]
   Float_t         Psec_Track[31][3][3];   //[NumTracks]

   // List of branches
   TBranch        *b_RunNum;   //!
   TBranch        *b_EveNum;   //!
   TBranch        *b_ReacType;   //!
   TBranch        *b_IntType;   //!
   TBranch        *b_Vertex;   //!
   TBranch        *b_TargZ;   //!
   TBranch        *b_TargA;   //!
   TBranch        *b_Target;   //!
   TBranch        *b_Primary;   //!
   TBranch        *b_P_Primary;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_NumLep;   //!
   TBranch        *b_IdLep;   //!
   TBranch        *b_TrLep;   //!
   TBranch        *b_P_Lep;   //!
   TBranch        *b_EneDep_Lep;   //!
   TBranch        *b_EneDep1st_Lep;   //!
   TBranch        *b_EneOut_Lep;   //!
   TBranch        *b_NumHad;   //!
   TBranch        *b_IdHad;   //!
   TBranch        *b_TrHad;   //!
   TBranch        *b_P_Had;   //!
   TBranch        *b_EneDep_Had;   //!
   TBranch        *b_EneDep1st_Had;   //!
   TBranch        *b_EneOut_Had;   //!
   TBranch        *b_NumPhot;   //!
   TBranch        *b_IdPhot;   //!
   TBranch        *b_TrPhot;   //!
   TBranch        *b_P_Phot;   //!
   TBranch        *b_EneDep_Phot;   //!
   TBranch        *b_EneDep1st_Phot;   //!
   TBranch        *b_EneOut_Phot;   //!
   TBranch        *b_NumHeavy;   //!
   TBranch        *b_IdHeavy;   //!
   TBranch        *b_TrHeavy;   //!
   TBranch        *b_P_Heavy;   //!
   TBranch        *b_EneDep_Heavy;   //!
   TBranch        *b_EneDep1st_Heavy;   //!
   TBranch        *b_EneOut_Heavy;   //!
   TBranch        *b_NumTracks;   //!
   TBranch        *b_IdTrack;   //!
   TBranch        *b_Int_Track;   //!
   TBranch        *b_Vtx_Track;   //!
   TBranch        *b_Nsec_Track;   //!
   TBranch        *b_Esec_Track;   //!
   TBranch        *b_Psec_Track;   //!

	Header();
	~Header(){};
	//virtual ~Header();
	static Header* giveThis();
	static Header* giveThis(TTree* aTree, const std::string& option);
	static void releaseThis();
	void setupRead(const std::string& option = "");
	bool SetBranchAddresses();
	Header(TTree* aTree, const std::string& option);
	TTree* GetInputTree();
	void GetEvent(Long64_t entry);
	Int_t       GetRunNumber()                  { return m_run;           };
	Int_t       GetEventNumber()                { return m_event;         };
	Float_t     GetVertex(Int_t index)          { return m_vtx[index];    };
	//
	Int_t   GetReacId()                         { return m_reacid;        };
	//
	Int_t   GetNumOfLepton()                    { return m_numlep;        };
	Int_t   GetLeptonId(Int_t index)            { return m_lepid[index];  };
	TLorentzVector *GetLepton4Mom(Int_t index)  { return m_lep4mom[index];};
	//
	Int_t   GetNumOfHadron()                    { return m_numhad;        };
	Int_t   GetHadronId(Int_t index)            { return m_hadid[index];  };
	TLorentzVector *GetHadron4Mom(Int_t index)  { return m_had4mom[index];};
	//
	Int_t   GetNumOfPhoton()                    { return m_numph;         };
	TLorentzVector *GetPhoton4Mom(Int_t index)  { return m_ph4mom[index]; };
	//
	Int_t   GetNumOfHeavy()                     { return m_numhvy;        };
	Int_t   GetHeavyId(Int_t index)             { return m_hvyid[index];  };
	TLorentzVector *GetHeavy4Mom(Int_t index)   { return m_hvy4mom[index];};
	//
	Int_t   GetNumOfTrack()                     { return m_numtrk;        };
	Int_t   GetTrackId(Int_t index)             { return m_trkid[index];  };
	Float_t GetTrackVertex(Int_t index)         { return m_trkvtx[index]; };
	Int_t GetTrack(Int_t index)                 { return m_trk[index];    };
	//
	private:
		TTree* m_treeIn;
		Int_t 	m_run, m_event, m_trk[kMaxSeg]; 
		Float_t m_vtx[3], m_ene, m_visene, m_trkvtx[3];
		Int_t m_numlep, m_lepid[kMaxSeg], m_numhad, m_hadid[kMaxSeg], m_numph, m_phid[kMaxSeg], m_numhvy, m_hvyid[kMaxSeg];
		Int_t m_numtrk, m_trkid[kMaxSeg];
		TLorentzVector *m_lep4mom[kMaxSeg],*m_had4mom[kMaxSeg],*m_ph4mom[kMaxSeg],*m_hvy4mom[kMaxSeg];
		Int_t m_seg0, m_seg1, m_pidin[kMaxSeg];
		Float_t m_xinx[kMaxSeg], m_xiny[kMaxSeg], m_xinz[kMaxSeg];
		Float_t m_xemcal[kMaxSeg], m_yemcal[kMaxSeg], m_zemcal[kMaxSeg];
		Int_t m_reacid, m_regin[kMaxSeg], m_whcalo[kMaxSeg];
		//
		static Header* m_instance;
		ClassDef(Header,0)
};
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// initialisation of the Header pointer
Header* Header::m_instance = 0;
Header::Header(){	}
// to get a unique instance 
inline Header* Header::giveThis()
{
	cout << "debug::m_instance Header 0 " << m_instance << endl;
	if (0 == m_instance){
		cout << "Header::giveThis error not constructed properly " << endl;
	}
	return m_instance;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Open a TTree for reading (writing option not now)
inline Header* Header::giveThis(TTree* aTree, const std::string& option)
{
	cout << "debug::m_instance Header " << m_instance << endl;
	if(m_instance != 00000000) m_instance = 0;
	if (0 == m_instance){
		m_instance = new Header(aTree, option);
		cout << "umutumut" << endl;
	} else{
		cout << "Header::giveThis Warning " << aTree->GetTitle() << " " << aTree->GetName() << endl;
	}
	return m_instance;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Delete unique instance
inline void Header::releaseThis() 
{
	if ( m_instance != 0 ) {
		delete m_instance;
		m_instance = 0;
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// constructor for one TTree with read/write option
Header::Header(TTree* aTree, const std::string& option)
{
	if(option=="read"){
		m_treeIn = aTree;
		setupRead();
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// setup the input tree for reading
void Header::setupRead(const std::string& option)
{
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
bool Header::SetBranchAddresses()
{
	//if(DEBUG_rg) cout << " ....inside setbranchaddresses.... " << endl;
	m_treeIn->SetMakeClass(1);
	m_treeIn->SetBranchAddress("RunNum",         &RunNum,        &b_RunNum         );
	m_treeIn->SetBranchAddress("EveNum",         &EveNum,        &b_EveNum         );
	m_treeIn->SetBranchAddress("ReacType",       &ReacType,      &b_ReacType       );
	m_treeIn->SetBranchAddress("IntType",        &IntType,       &b_IntType        );
	m_treeIn->SetBranchAddress("Vertex",         Vertex,         &b_Vertex         );
	m_treeIn->SetBranchAddress("TargZ",          &TargZ,         &b_TargZ          );
	m_treeIn->SetBranchAddress("TargA",          &TargA,         &b_TargA          );
	m_treeIn->SetBranchAddress("Target",         &Target,        &b_Target         );
	m_treeIn->SetBranchAddress("Primary",        &Primary,       &b_Primary        );
	m_treeIn->SetBranchAddress("P_Primary",      P_Primary,      &b_P_Primary      );
	m_treeIn->SetBranchAddress("Weight",         &Weight,        &b_Weight         );
	m_treeIn->SetBranchAddress("NumLep",         &NumLep,        &b_NumLep         );
	m_treeIn->SetBranchAddress("IdLep",          IdLep,          &b_IdLep          );
	m_treeIn->SetBranchAddress("TrLep",          TrLep,          &b_TrLep          );
	m_treeIn->SetBranchAddress("P_Lep",          P_Lep,          &b_P_Lep          );
	m_treeIn->SetBranchAddress("EneDep_Lep",     EneDep_Lep,     &b_EneDep_Lep     );
	m_treeIn->SetBranchAddress("EneDep1st_Lep",  EneDep1st_Lep,  &b_EneDep1st_Lep  );
	m_treeIn->SetBranchAddress("EneOut_Lep",     EneOut_Lep,     &b_EneOut_Lep     );
	m_treeIn->SetBranchAddress("NumHad",         &NumHad,        &b_NumHad         );
	m_treeIn->SetBranchAddress("IdHad",          IdHad,          &b_IdHad          );
	m_treeIn->SetBranchAddress("TrHad",          TrHad,          &b_TrHad          );
	m_treeIn->SetBranchAddress("P_Had",          P_Had,          &b_P_Had          );
	m_treeIn->SetBranchAddress("EneDep_Had",     EneDep_Had,     &b_EneDep_Had     );
	m_treeIn->SetBranchAddress("EneDep1st_Had",  EneDep1st_Had,  &b_EneDep1st_Had  );
	m_treeIn->SetBranchAddress("EneOut_Had",     EneOut_Had,     &b_EneOut_Had     );
	m_treeIn->SetBranchAddress("NumPhot",        &NumPhot,       &b_NumPhot        );
	m_treeIn->SetBranchAddress("IdPhot",         IdPhot,         &b_IdPhot         );
	m_treeIn->SetBranchAddress("TrPhot",         TrPhot,         &b_TrPhot         );
	m_treeIn->SetBranchAddress("P_Phot",         P_Phot,         &b_P_Phot         );
	m_treeIn->SetBranchAddress("EneDep_Phot",    EneDep_Phot,    &b_EneDep_Phot    );
	m_treeIn->SetBranchAddress("EneDep1st_Phot", EneDep1st_Phot, &b_EneDep1st_Phot );
	m_treeIn->SetBranchAddress("EneOut_Phot",    EneOut_Phot,    &b_EneOut_Phot    );
	m_treeIn->SetBranchAddress("NumHeavy",       &NumHeavy,      &b_NumHeavy       );
	m_treeIn->SetBranchAddress("IdHeavy",        IdHeavy,        &b_IdHeavy        );
	m_treeIn->SetBranchAddress("TrHeavy",        TrHeavy,        &b_TrHeavy        );
	m_treeIn->SetBranchAddress("P_Heavy",        P_Heavy,        &b_P_Heavy        );
	m_treeIn->SetBranchAddress("EneDep_Heavy",   EneDep_Heavy,   &b_EneDep_Heavy   );
	m_treeIn->SetBranchAddress("EneDep1st_Heavy",EneDep1st_Heavy,&b_EneDep1st_Heavy);
	m_treeIn->SetBranchAddress("EneOut_Heavy",   EneOut_Heavy,   &b_EneOut_Heavy   );
	m_treeIn->SetBranchAddress("NumTracks",      &NumTracks,     &b_NumTracks      );
	m_treeIn->SetBranchAddress("IdTrack",        IdTrack,        &b_IdTrack        );
	m_treeIn->SetBranchAddress("Int_Track",      Int_Track,      &b_Int_Track      );
	m_treeIn->SetBranchAddress("Vtx_Track",      Vtx_Track,      &b_Vtx_Track      );
	m_treeIn->SetBranchAddress("Nsec_Track",     Nsec_Track,     &b_Nsec_Track     );
	m_treeIn->SetBranchAddress("Esec_Track",     Esec_Track,     &b_Esec_Track     );
	m_treeIn->SetBranchAddress("Psec_Track",     Psec_Track,     &b_Psec_Track     );
	return true;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// accessors for the input TTree
TTree* Header::GetInputTree() {return m_treeIn;};
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// get all branch contents of input TTree for entry i
void Header::GetEvent(Long64_t entry)
{
	if (!m_treeIn) {
		cout << "Header::getEntry error" << endl;
		exit(1);
	}
	//
	// Turn on ALL branches                                                      
	m_treeIn->SetBranchStatus("*", 1);
	m_treeIn->GetEntry(entry);
	//if(DEBUG_rg) m_treeIn->Show(entry);
	m_run          = RunNum; 
	m_event        = EveNum; 
	m_reacid = ReacType;
	m_numlep = NumLep;
	m_numhad = NumHad;
	m_numph = NumPhot;
	m_numhvy = NumHeavy;
	m_numtrk = NumTracks;
	//
	for(int i=0; i<3; i++)
		m_vtx[i] = Vertex[i];
	
	for(int i=0; i<NumLep; i++)
	{
		m_lepid[i] = IdLep[i];
		m_lep4mom[i] = new TLorentzVector();
		m_lep4mom[i]->SetPxPyPzE(P_Lep[i][0],P_Lep[i][1],P_Lep[i][2],P_Lep[i][3]);
	}
	for(int i=0; i<NumHad; i++)
	{
		m_hadid[i] = IdHad[i];
		m_had4mom[i] = new TLorentzVector();
		m_had4mom[i]->SetPxPyPzE(P_Had[i][0],P_Had[i][1],P_Had[i][2],P_Had[i][3]);
	}
	for(int i=0; i<NumPhot; i++)
	{
		m_ph4mom[i] = new TLorentzVector();
		m_ph4mom[i]->SetPxPyPzE(P_Phot[i][0],P_Phot[i][1],P_Phot[i][2],P_Phot[i][3]);
	}
	for(int i=0; i<NumHeavy; i++)
	{
		m_hvyid[i] = IdHeavy[i];
		m_hvy4mom[i] = new TLorentzVector();
		m_hvy4mom[i]->SetPxPyPzE(P_Heavy[i][0],P_Heavy[i][1],P_Heavy[i][2],P_Heavy[i][3]);
	}
	for(int i=0; i<NumTracks; i++)
	{
		m_trkid[i] = IdTrack[i];
		m_trk[i] = Int_Track[i];
		for(int j=0; j<3; j++)
			m_trkvtx[j] = Vtx_Track[i][j];
		}
	}
#endif 