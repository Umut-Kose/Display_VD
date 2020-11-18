#include <list>
#include "TCanvas.h"
#include <TObjArray.h>
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TMatrix.h"
#include "TROOT.h"
#include "TMath.h"
#include "TString.h"
#include "TFile.h"
#include "TSpectrum.h"
#include "TH1D.h"
#include "TH2S.h"
#include "TH2I.h"
#include "TText.h"
#include "TBox.h"
#include "TEveManager.h"
#include "TEveEventManager.h"
#include "TGLUtil.h"
#include "TEveViewer.h"
#include "TGeoVolume.h"
#include "TGeoMedium.h"
#include "TGeoMaterial.h"
#include "TGeoManager.h"
#include "TSystem.h"
#include "TEveGeoNode.h"
//#include "TEveGeoTopNode.h"
#include "TEveBoxSet.h"
#include "TEveRGBAPalette.h"
#include "TGLViewer.h"
#include "TEveBrowser.h"
#include "TGTab.h"
#include "TColor.h"
#include "TKey.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TEveCompound.h" 
#include "TEveTrans.h"
#include "TEveWindowManager.h"
#include "TGLOrthoCamera.h"

#include "TEveText.h"
#include "TEveLine.h"
#include "TEveText.h"
#include "TGLClip.h"


#include "TStyle.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>


using namespace std;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Loading TreeManager in order to access TTree
// You just need to give the correct input file
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//root v6
R__LOAD_LIBRARY(TreeManager_C.so);
#include "TreeManager.h"
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//TFile *_file0;
TreeManager filereader(_file0->GetName());
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int GetCharged(int flkcode);
void DumpEvent(Long64_t ientry);
void ReadFile();
void Multiplicity();
void DrawEvent(Long64_t ientry);
void GetDistributions();
void SandrosHisto();

static TCanvas * CreateCanvas(const char *plot_name, int tb);
void CleanCanvas();

TCanvas * Canvas_1;

TEveCompound *cmp_text_mctrack = NULL;
TGFileBrowser *gbrowser;
TFolder* froi;
TEveRGBAPalette* pal;
TCanvas *gcanvas = 0;
TGFileBrowser *g_hlt_browser = 0;
TCanvas       *g_hlt_canvas  = 0;
TGCheckButton *eGCBAnimation;
TTimer * eTimer;
Int_t EventNumber =0;
Int_t CurrentEventNumber;
TGNumberEntry *fNumberEntry;
TGTextButton *fIsolate;
Bool_t ApplyIsolation;
TFolder* Filefolder = new TFolder("Analysis","Histograms");  

TTree *HeaderTree;
TGStatusBar *fStatusBar;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void ReadFile()
{
	Header *data = filereader.tmCD(); 
	Long64_t entries = data->GetInputTree()->GetEntries();
	cout << "Reading all data " << entries << endl;
	for( Long64_t ientry=0; ientry<entries; ++ientry )
	{
		data->GetEvent(ientry);
		cout << "Data:: " << data->GetRunNumber() << " " <<  data->GetEventNumber() << " " << data->GetVertex(0) << " " << data->GetVertex(1) << " " <<data->GetVertex(2) << " " << endl;
	} // end_of_for_ientry_loop
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void DumpEvent(Long64_t ientry)
{
	Header *track = filereader.tmCD(); 
	Hits *hit = filereader.tmHits(); 
	//for( Long64_t ientry=0; ientry<entriesTrk; ++ientry )
	//{
		track->GetEvent(ientry);
		//if( ientry>20 ) break;
		cout << " vertex: " << track->GetVertex(0) << " " << track->GetVertex(1) << " " << track->GetVertex(2) << endl;
		
		Int_t lepnum = track->GetNumOfLepton();
		cout << "num of leptons " << lepnum << endl;
        for(Long64_t eve=0; eve<track->GetNumOfLepton(); ++eve)
        {
                cout << "leptons " << eve << " " << track->GetLeptonId(eve) << " " << track->GetLepton4Mom(eve)->Px() << " " << track->GetLepton4Mom(eve)->Py() << " " << track->GetLepton4Mom(eve)->Pz() << " " << track->GetLepton4Mom(eve)->E() << endl;
		cout << "  ---> Angle of Phi (in rad) " << track->GetLepton4Mom(eve)->Phi() << endl;
		cout << "  ---> Angle of Phi (in rad) " << track->GetLepton4Mom(eve)->Theta() << endl;
		cout << "  ---> Angle of Phi (in deg) " << 180*track->GetLepton4Mom(eve)->Phi()/TMath::Pi() << endl;
		cout << "  ---> Angle of Phi (in deg) " << 180*track->GetLepton4Mom(eve)->Theta()/TMath::Pi() << endl;
        }
		////////////
		Int_t hadnum = track->GetNumOfHadron();
		cout << "num of hadronss " << hadnum << endl;
        for(Long64_t eve=0; eve<track->GetNumOfHadron(); ++eve)
        {
                cout << "hadrons " << eve << " " << track->GetHadronId(eve) << " " << track->GetHadron4Mom(eve)->Px() << " " << track->GetHadron4Mom(eve)->Py() << " " << track->GetHadron4Mom(eve)->Pz() << " " << track->GetHadron4Mom(eve)->E() << endl;
		cout << "  ---> Angle of Phi (in rad) " << track->GetHadron4Mom(eve)->Phi() << endl;
		cout << "  ---> Angle of Phi (in rad) " << track->GetHadron4Mom(eve)->Theta() << endl;
		cout << "  ---> Angle of Phi (in deg) " << 180*track->GetHadron4Mom(eve)->Phi()/TMath::Pi() << endl;
		cout << "  ---> Angle of Phi (in deg) " << 180*track->GetHadron4Mom(eve)->Theta()/TMath::Pi() << endl;
        }
		////////////
		Int_t hvynum = track->GetNumOfHeavy();
		cout << "num of Heavys " << hvynum << endl;
        for(Long64_t eve=0; eve<track->GetNumOfHeavy(); ++eve)
        {
                cout << "Heavys " << eve << " " << track->GetHeavyId(eve) << " " << track->GetHeavy4Mom(eve)->Px() << " " << track->GetHeavy4Mom(eve)->Py() << " " << track->GetHeavy4Mom(eve)->Pz() << " " << track->GetHeavy4Mom(eve)->E() << endl;
		cout << "  ---> Angle of Phi (in rad) " << track->GetHeavy4Mom(eve)->Phi() << endl;
		cout << "  ---> Angle of Phi (in rad) " << track->GetHeavy4Mom(eve)->Theta() << endl;
		cout << "  ---> Angle of Phi (in deg) " << 180*track->GetHeavy4Mom(eve)->Phi()/TMath::Pi() << endl;
		cout << "  ---> Angle of Phi (in deg) " << 180*track->GetHeavy4Mom(eve)->Theta()/TMath::Pi() << endl;

        }
		////////////
		Int_t trknum = track->GetNumOfTrack();
		cout << "num of tracks " << trknum << endl;
		for(int i=0;i<trknum;i++)
		{
			cout << "--> " << track->GetTrack(i) << " " << track->GetTrackVertex(0) << " " << track->GetTrackVertex(1) << " " << track->GetTrackVertex(2) << endl;
		}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void GetPi0Rate()
{
	Header *track = filereader.tmCD(); 
	Double_t count_pi0 = 0;
	Double_t total = 0;
	Long64_t entries = track->GetInputTree()->GetEntries();
	for( Long64_t ientry=0; ientry<entries; ++ientry )
	{
	  track->GetEvent(ientry);
	  for(Long64_t eve=0; eve<track->GetNumOfHadron(); ++eve)
	    {
	      if(track->GetHadronId(eve) == 111)
		count_pi0++;
	    }
	  total++;
        }
	Double_t pi0rate = count_pi0/total;
	cout << "Pi0: " << count_pi0 << " in total number of events: " << total << " --->  " << pi0rate << endl;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void DrawEvent(Long64_t ientry)
{
	
	TEveEventManager* currEvent = gEve->GetCurrentEvent();
	if( currEvent ) currEvent->DestroyElements();
	TEveElement* top = gEve->GetCurrentEvent();
	//
	const TDatabasePDG *pdgDB = TDatabasePDG::Instance();
	//
	// Access header trees
	Header *track = filereader.tmCD(); 
	track->GetEvent(ientry);
	// Access Hits trees
	Hits *hit = filereader.tmHits(); 
	hit->GetHits(ientry);
	//
	cout << "Event #: " << track->GetEventNumber() << endl;
	cout << " vertex: " << track->GetVertex(0) << " " << track->GetVertex(1) << " " << track->GetVertex(2) << endl;
	//
	TEveVectorT<double> xp;
	int track_line_width = 4;
	char buf[256];
	//
	cmp_text_mctrack = new TEveCompound;
	cmp_text_mctrack->SetName("FLUKALeptons");
	gEve->AddElement(cmp_text_mctrack);
	cmp_text_mctrack->OpenCompound();
	//
	double posx, posy, posz;
	//////////////////////////////////////////////////////////////////////
	// Leptons
	//////////////////////////////////////////////////////////////////////
	for(Long64_t eve=0; eve<track->GetNumOfLepton(); ++eve)
	{
	        cout << "leptons " << eve << " " << track->GetLeptonId(eve) << " " << track->GetLepton4Mom(eve)->Px() << " " << track->GetLepton4Mom(eve)->Py() << " " << track->GetLepton4Mom(eve)->Pz() << " " << track->GetLepton4Mom(eve)->E() << endl;
		cout << "Pseudorapidity " << track->GetLepton4Mom(eve)->PseudoRapidity() << endl;
		cout << "Pseudorapidity22 " << track->GetLepton4Mom(eve)->Eta() << endl;
		cout << "phi " << track->GetLepton4Mom(eve)->Phi() << endl;
		cout << "theta " << track->GetLepton4Mom(eve)->Theta() << endl;
		//////////////////////////////////////////////////////////////////////
		// IDs seems given in PDG code, so use the following 
		const TParticlePDG* pdg = pdgDB->GetParticle(track->GetLeptonId(eve));
		double charge = pdg ? pdg->Charge() : 0.;
		//////////////////////////////////////////////////////////////////////
		// if the ID is given in FLUKA format, uncomment the following
		//int charge = GetCharged(track->GetLeptonId(eve));
		//////////////////////////////////////////////////////////////////////
		TEveText *tx = new TEveText();
		TEveLine *truthVtx = new TEveLine();
		cout << "Charged particle " << track->GetLeptonId(eve) << " " << pdg->GetName() << " " <<  charge << endl;
		double length = track->GetLepton4Mom(eve)->P()*100.;
		sprintf(buf,"%s",pdg->GetName());
		tx->SetText(buf);
		TVector3 particlePosition(track->GetVertex(0),track->GetVertex(1),track->GetVertex(2));
		xp.Set(track->GetVertex(0),track->GetVertex(1),track->GetVertex(2));
		posx = track->GetVertex(0) + length*track->GetLepton4Mom(eve)->Px()/track->GetLepton4Mom(eve)->P();
		posy = track->GetVertex(1) + length*track->GetLepton4Mom(eve)->Py()/track->GetLepton4Mom(eve)->P();
		posz = track->GetVertex(2) + length*track->GetLepton4Mom(eve)->Pz()/track->GetLepton4Mom(eve)->P();
		tx->PtrMainTrans()->SetPos(posx,posy,posz);
		tx->SetFontMode(TGLFont::kBitmap);
		tx->SetFontSize(18);
		cmp_text_mctrack->AddElement(tx);
		//Draw the line
		truthVtx->SetNextPoint(particlePosition.X(),particlePosition.Y(),particlePosition.Z());
		cout << "next positions " << particlePosition.X() << " " << particlePosition.Y() << " " << particlePosition.Z() << endl;
		truthVtx->SetNextPoint(posx,posy,posz);
		cout << "next positions2 " << posx << " " << posy << " " << posz << endl;
		truthVtx->SetLineColor(kGreen);// leptons in Green
		truthVtx->SetLineWidth(track_line_width);
		cmp_text_mctrack->AddElement(truthVtx);
		if(!charge)
		  {
		    truthVtx->SetLineStyle(10); // neutral leptons
		  }
	}
	//////////////////////////////////////////////////////////////////////
	// Hadrons
	//////////////////////////////////////////////////////////////////////
	for(Long64_t eve=0; eve<track->GetNumOfHadron(); ++eve)
	{
		cout << "Hadrons " << eve << " " << track->GetHadronId(eve) << " " << track->GetHadron4Mom(eve)->Px() << " " << track->GetHadron4Mom(eve)->Py() << " " << track->GetHadron4Mom(eve)->Pz() << " " << track->GetHadron4Mom(eve)->E() << endl;
		//////////////////////////////////////////////////////////////////////
		// IDs seems given in PDG code, so use the following 
		const TParticlePDG* pdg = pdgDB->GetParticle(track->GetHadronId(eve));
		double charge = pdg ? pdg->Charge() : 0.;
		//////////////////////////////////////////////////////////////////////
		// if the ID is given in FLUKA format, uncomment the following
		//int charge = GetCharged(track->GetHadronId(eve));
		//////////////////////////////////////////////////////////////////////
		cout << "Hadrons particle " << track->GetHadronId(eve) << " " << pdg->GetName() << " " << charge << endl;
		double length = track->GetHadron4Mom(eve)->P()*100.;
		TEveText *tx = new TEveText();
		TEveLine *truthVtx = new TEveLine();
		sprintf(buf,"%s",pdg->GetName());
		//cout << buf << endl;
		//truthVtx->SetName(buf);
		tx->SetText(buf);
		TVector3 particlePosition(track->GetVertex(0),track->GetVertex(1),track->GetVertex(2));
		xp.Set(track->GetVertex(0),track->GetVertex(1),track->GetVertex(2));
		posx = track->GetVertex(0) + length*track->GetHadron4Mom(eve)->Px()/track->GetHadron4Mom(eve)->P();
		posy = track->GetVertex(1) + length*track->GetHadron4Mom(eve)->Py()/track->GetHadron4Mom(eve)->P();
		posz = track->GetVertex(2) + length*track->GetHadron4Mom(eve)->Pz()/track->GetHadron4Mom(eve)->P();
		tx->PtrMainTrans()->SetPos(posx,posy,posz);
		tx->SetFontMode(TGLFont::kBitmap);
		tx->SetFontSize(18);
		cmp_text_mctrack->AddElement(tx);
		//Draw the line
		truthVtx->SetNextPoint(particlePosition.X(),particlePosition.Y(),particlePosition.Z());
		cout << "next positions " << particlePosition.X() << " " << particlePosition.Y() << " " << particlePosition.Z() << endl;
		truthVtx->SetNextPoint(posx,posy,posz);
		cout << "next positions2 " << posx << " " << posy << " " << posz << endl;
		truthVtx->SetLineColor(kYellow);
		truthVtx->SetLineWidth(track_line_width);
		if(!charge)
		  {
		    truthVtx->SetLineStyle(10);
		  }
		cmp_text_mctrack->AddElement(truthVtx);
		//}
	}
	//////////////////////////////////////////////////////////////////////
	// Hits for decay points
	//////////////////////////////////////////////////////////////////////
	cout << "Number of decays " << hit->GetNumberOfDecay() << endl;
	for(Long64_t eve=0; eve<hit->GetNumberOfDecay(); eve++)
	{
		//////////////////////////////////////////////////////////////////////
		// IDs seems given in PDG code, so use the following 
	        const TParticlePDG* pdg = pdgDB->GetParticle(hit->GetId(eve));
		double charge = pdg ? pdg->Charge() : 0.;
		cout << " --> " << eve << " " << hit->GetDau4Mom(eve)->P() << " " << hit->GetId(eve) << " " << hit->GetDauParent(eve) << " " << hit->GetDauNumber(eve )<<  endl;
		double length = hit->GetDau4Mom(eve)->P()*100.;
		TEveText *tx = new TEveText();
		TEveLine *truthVtx = new TEveLine();
		sprintf(buf,"%s",pdg->GetName());
		tx->SetText(buf);
		cout << buf << " " << hit->GetType(eve) << endl;
		truthVtx->SetName(buf);
		cout << "hits pos " << hit->GetDauPos(0) << " " << hit->GetDauPos(1) << " " << hit->GetDauPos(2) << endl;
		TVector3 particlePosition(hit->GetDauPos(0),hit->GetDauPos(1),hit->GetDauPos(2));
		xp.Set(hit->GetDauPos(0),hit->GetDauPos(1),hit->GetDauPos(2));
		//
		posx = hit->GetDauPos(0) + length*hit->GetDau4Mom(eve)->Px()/hit->GetDau4Mom(eve)->P();
		posy = hit->GetDauPos(1) + length*hit->GetDau4Mom(eve)->Py()/hit->GetDau4Mom(eve)->P();
		posz = hit->GetDauPos(2) + length*hit->GetDau4Mom(eve)->Pz()/hit->GetDau4Mom(eve)->P();
		//
		//Draw the line
		truthVtx->SetNextPoint(particlePosition.X(),particlePosition.Y(),particlePosition.Z());
		cout << "next positions " << particlePosition.X() << " " << particlePosition.Y() << " " << particlePosition.Z() << endl;
		truthVtx->SetNextPoint(posx,posy,posz);
		cout << "next positions2 " << posx << " " << posy << " " << posz << endl;
		tx->PtrMainTrans()->SetPos(posx,posy,posz);
		tx->SetFontMode(TGLFont::kBitmap);
		tx->SetFontSize(18);
		if(hit->GetId(eve)==111)// pi0 to gammas
		  continue;
		if(hit->GetType(eve)==217&&hit->GetId(eve)==22) // pair productions of gamma --> electron-positrons
		  {
			truthVtx->SetLineColor(kGreen+1);
			tx->SetText("e/p");		  
		  }
		if(hit->GetType(eve)==219) // compton
		  {
			truthVtx->SetLineColor(kGreen+1);
			tx->SetText("e-");		  
		  }
		if(hit->GetId(eve)!=22&&charge)//
			truthVtx->SetLineColor(kGray);

		if(hit->GetId(eve)!=22&&!charge)//
		  {
			truthVtx->SetLineColor(kGray);
			truthVtx->SetLineStyle(10);
		  }
		cmp_text_mctrack->AddElement(tx);
		truthVtx->SetLineWidth(track_line_width);
		cmp_text_mctrack->AddElement(truthVtx);
	}
	
	//
	cmp_text_mctrack->CloseCompound();
	gEve->AddElement(cmp_text_mctrack);
	//
	Int_t trknum = track->GetNumOfTrack();
	cout << "num of tracks " << trknum << endl;
	//for(int i=0;i<trknum;i++)
	//{
	  //	cout << "--> " << track->GetTrack(i) << " " << track->GetTrackVertex(0) << " " << track->GetTrackVertex(1) << " " << track->GetTrackVertex(2) << endl;
	//}
	//
	gEve->Redraw3D(kTRUE);

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// just an example
void GetDistributions()
{
	Header *track = filereader.tmCD(); 
	Long64_t entriesTrk = track->GetInputTree()->GetEntries();
	//
	//pseudorapidity:
	// eta = -ln(tan theta/2) // theta emission angle w.r.t neutrino directions
	//
	TH1F *henevis = new TH1F("VisEne","Visible Energy",100,0,2);
	TH1F *hpseudo = new TH1F("pseudo","PseudoRapidity (lepton angle wrt neutrino beam)",100,-10,10);
	TH1F *hpseudo2 = new TH1F("pseudo2","PseudoRapidity (hadron angle wrt neutrino beam)",100,-10,10);
	TH1F *hmultip = new TH1F("multip","Multiplicity [total]",30,-0.5,29.5);
	TH1F *hmultiph = new TH1F("multiph","Multiplicity [hadrons]",30,-0.5,29.5);
	TH1F *hmultiphvy = new TH1F("multiphvy","Multiplicity [heavy]",30,-0.5,29.5);
	TH1F *hmultipg = new TH1F("multipg","Multiplicity [photons]",30,-0.5,29.5);
	TH1F *hmultipl = new TH1F("multipl","Multiplicity [leptons]",30,-0.5,29.5);

	TH2F *hPseudoMulti = new TH2F("pseudo_vs_multip","PseudoRapidity vs multip",100,-10,10,100,-0.5,49.5);

	//
        Double_t pseudo, pseudo2;
	for( Long64_t ientry=0; ientry<entriesTrk; ++ientry )
	{
		track->GetEvent(ientry);
		hmultipl->Fill(track->GetNumOfLepton());
		hmultipg->Fill(track->GetNumOfPhoton());
		hmultiph->Fill(track->GetNumOfHadron());
		hmultiphvy->Fill(track->GetNumOfHeavy());
		int multip = track->GetNumOfLepton()+track->GetNumOfPhoton()+track->GetNumOfHadron();
		hmultip->Fill(multip);
		for(Long64_t eve=0; eve<track->GetNumOfLepton(); ++eve)
		{
		        pseudo = track->GetLepton4Mom(eve)->PseudoRapidity();
			hpseudo->Fill(pseudo);
			hPseudoMulti->Fill(pseudo,multip);
		}
		for(Long64_t eve=0; eve<track->GetNumOfHadron(); ++eve)
		{
			pseudo2 = track->GetHadron4Mom(eve)->PseudoRapidity();
			hpseudo2->Fill(pseudo2);
			hPseudoMulti->Fill(pseudo,multip);
		}
	}
	hpseudo->SetMarkerStyle(20);
	Filefolder->Add(hpseudo);
	Filefolder->Add(hpseudo2);
	Filefolder->Add(hmultip);
	Filefolder->Add(hmultipl);
	Filefolder->Add(hmultiph);
	Filefolder->Add(hmultiphvy);
	Filefolder->Add(hmultipg);
	Filefolder->Add(hPseudoMulti);
	
	g_hlt_browser->Add(Filefolder);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void SandrosHisto()
{
	// the following from Sandro's macro
	Float_t hadronP;
	Float_t hadronE;
	Float_t lepton_angle_x;
	Float_t lepton_angle_y;
	Float_t lepton_p_angle;
	Float_t hadron_angle_x;
	Float_t hadron_angle_y;
	Float_t leptonP;
	Float_t pi0E;
	// Float_t pi0_angle_x;
	Float_t gangle;
	Float_t Pratio;

	TH1D *h_lepton_angle_x = new TH1D("Lepton projected angle","Lepton projected angle",90,-90.,90.);
	TH1D *h_lepton_p_angle = new TH1D("Lepton polar angle","Lepton polar angle",90,0.,180.);
	TH1D *h_leptonP = new TH1D("Lepton momentum","Lepton momentum",50,0.,5.);
	TH1D *h_pi0_angle_x = new TH1D("pi0 projected angle","pi0 projected angle",90,-90.,90.);
	TH1D *h_pi0E = new TH1D("pi0 energy","pi0 energy",50,0.,5.);
	TH1D *h_gammaE = new TH1D("gamma energy","gamma energy",50,0.,5.);
	TH1D *h_gangle = new TH1D("gamma op angle","gamma op angle",90,0.,180.);
	TH2D *h_gamma_PRatio_OpA =  new TH2D("gamma P-r vs O_A","gamma P-R vs O-A",90,0.,180.,100,0.,1.);
	// Access header trees
	Header *data = filereader.tmCD(); 
	// Access Hits trees
	Hits *hit = filereader.tmHits(); 
	Long64_t entries = data->GetInputTree()->GetEntries();
	cout << "Reading all data " << entries << endl;
	for( Long64_t ientry=0; ientry<entries; ++ientry )
	{
		data->GetEvent(ientry);
		hit->GetHits(ientry);
		
		if(data->GetNumOfLepton()==1)
		{
			leptonP = data->GetLepton4Mom(0)->P();
			lepton_angle_x=TMath::ATan(data->GetLepton4Mom(0)->Px()/data->GetLepton4Mom(0)->Pz())*90/1.571;
			lepton_angle_y=TMath::ATan(data->GetLepton4Mom(0)->Py()/data->GetLepton4Mom(0)->Pz())*90/1.571;
			lepton_p_angle=TMath::ACos(data->GetLepton4Mom(0)->Pz()/data->GetLepton4Mom(0)->P())*90/1.571;
			h_lepton_p_angle->Fill(lepton_p_angle);
			if(abs(lepton_angle_y)<4)
			{
				h_leptonP->Fill(leptonP);
				h_lepton_angle_x->Fill(lepton_angle_x);
			}
		}
		for(Long64_t eve=0; eve<data->GetNumOfHadron(); ++eve)
		{
			if(data->GetHadronId(eve) == 111)
			{
				hadronP=data->GetHadron4Mom(eve)->P();
				hadronE=data->GetHadron4Mom(eve)->E();
				hadron_angle_x=TMath::ATan(data->GetHadron4Mom(eve)->Px()/data->GetHadron4Mom(eve)->Pz())*90/1.571;
				hadron_angle_y=TMath::ATan(data->GetHadron4Mom(eve)->Py()/data->GetHadron4Mom(eve)->Pz())*90/1.571;
				
				if(hit->GetNumberOfDecay()==3 && hit->GetId(0)==111 && hit->GetId(1)==22)
				{
					h_gammaE->Fill(hit->GetDau4Mom(1)->E());
					if(hit->GetId(2)==22)
					{
						h_gammaE->Fill(hit->GetDau4Mom(2)->E());
						gangle=TMath::ACos((hit->GetDau4Mom(1)->Px()*hit->GetDau4Mom(2)->Px()+hit->GetDau4Mom(1)->Py()*hit->GetDau4Mom(2)->Py()+hit->GetDau4Mom(1)->Pz()*hit->GetDau4Mom(2)->Pz())/(hit->GetDau4Mom(1)->E()*hit->GetDau4Mom(2)->E()))*90/1.571;
						h_gangle->Fill(gangle);
						Pratio= hit->GetDau4Mom(2)->E() / hit->GetDau4Mom(1)->E();
						if(Pratio > 1.) Pratio = 1/Pratio;
						h_gamma_PRatio_OpA->Fill(gangle,Pratio);
						if(Pratio<0.2 || gangle < 30.)
	       				{
							h_pi0E->Fill(hadronE);
							h_pi0_angle_x->Fill(hadron_angle_x);
						}
					}
				}
			}
		}
	}
	Filefolder->Add(h_leptonP);
	Filefolder->Add(h_lepton_p_angle);
	Filefolder->Add(h_lepton_angle_x);
	Filefolder->Add(h_pi0E);
	Filefolder->Add(h_pi0_angle_x);
	Filefolder->Add(h_gammaE);
	Filefolder->Add(h_gangle);
	Filefolder->Add(h_gamma_PRatio_OpA);
	g_hlt_browser->Add(Filefolder);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void SetEventNumber()
{
	EventNumber = fNumberEntry->GetNumber();
	fStatusBar->GetBarPart(0)->SetBackgroundColor(0xffffff);
	fStatusBar->SetText(Form("   Showing Event#: %i   ",EventNumber),0);
	cout << "Event Number is " << EventNumber << endl;
	//if(!ApplyIsolation) 
	DrawEvent(EventNumber);
	//if(ApplyIsolation) DrawIsolated(EventNumber);
	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void NextEvent()
{
	CurrentEventNumber = EventNumber;
	EventNumber = CurrentEventNumber + 1;
	fStatusBar->GetBarPart(0)->SetBackgroundColor(0xffffff);
	fStatusBar->SetText(Form("   Showing Event#: %i   ",EventNumber),0);
	cout<< "Next Event Number is " << EventNumber << endl;
	//if(!ApplyIsolation) 
	DrawEvent(EventNumber);
	//if(ApplyIsolation) DrawIsolated(EventNumber);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void PreviousEvent()
{
	CurrentEventNumber = EventNumber;
	EventNumber = CurrentEventNumber - 1;
	fStatusBar->GetBarPart(0)->SetBackgroundColor(0xffffff);
	fStatusBar->SetText(Form("   Showing Event#: %i   ",EventNumber),0);
	cout<< "Previous Event Number is " << EventNumber << endl;
	//if(!ApplyIsolation) 
	DrawEvent(EventNumber);
	//if(ApplyIsolation) DrawIsolated(EventNumber);
	
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
static TCanvas * CreateCanvas(const char *plot_name,int tb)
{
		// --- Create an embedded canvas
		
		TCanvas *c1;
		
		if(gEve==NULL) 
			c1 = new TCanvas();
		
		else {
			gEve->GetBrowser()->StartEmbedding(tb);
			//gROOT->ProcessLineFast("new TCanvas");
			//c1 = (TCanvas*) gPad;
			c1=new TCanvas;
			gEve->GetBrowser()->StopEmbedding(plot_name);
		}
		return c1;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*
void CleanCanvas()
{
	TSeqCollection* canvases = gROOT->GetListOfCanvases();
	TIter next(gROOT->GetListOfCanvases());
	while(c = (TCanvas*)next())
	{
		delete c;
	}
}
*/
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	TGLViewer *gv;
	TEveViewer            *T3DView;   
	TEveViewer            *TRPhiView; 
	TEveViewer            *TRhoZView; 
	TEveViewer            *MuonView; 
	TEveScene            *TRhoZGeomScene; 
void GetDisplay()
{
	// Event Display Manager
	TEveManager::Create(kTRUE,"V");
	TEveElementList *geometry = new TEveElementList("Geometry");
	TEveRGBAPalette* pal = new TEveRGBAPalette(0, 500);
	TEveViewer *ev;
	ev = gEve->GetDefaultViewer();
	gEve->GetWindowManager()->HideAllEveDecorations();
	gv = ev->GetGLViewer();
	gv->SetGuideState(TGLUtil::kAxesOrigin, kTRUE, kFALSE, 0);
	gv->SetClearColor(kBlack);

	T3DView = gEve->SpawnNewViewer("Projections", "");
	T3DView->GetGLViewer()->SetCurrentCamera(TGLViewer::kCameraOrthoZOY);
	//T3DView->GetGLViewer()->SetStyle(TGLRnrCtx::kWireFrame);
	T3DView->AddScene(gEve->GetGlobalScene());
	T3DView->AddScene(gEve->GetEventScene());
        // set camera parameters
        T3DView->GetGLViewer()->GetClipSet()->SetClipType(TGLClip::kClipBox);
        T3DView->GetGLViewer()->GetCameraOverlay()->SetOrthographicMode(TGLCameraOverlay::kAxis);
	T3DView->GetGLViewer()->GetCameraOverlay()->SetOrthographicMode(TGLCameraOverlay::kGridBack);
        T3DView->GetGLViewer()->GetCameraOverlay()->SetShowOrthographic(kTRUE);
	gv = T3DView->GetGLViewer();
	gv->SetGuideState(TGLUtil::kAxesOrigin, kTRUE, kFALSE, 0);
	gv->SetClearColor(kBlack);

	TEveBrowser * browser = gEve->GetBrowser();
	browser->StartEmbedding(TRootBrowser::kLeft);
	
	TGMainFrame* frmMain = new TGMainFrame(gClient->GetRoot(), 1000, 600);
	frmMain->SetWindowName("XX GUI");
	frmMain->SetCleanup(kDeepCleanup);
	
	//TGLabel *fLabel;
	TGTextButton *fb;
	int posy=0;
	TGVerticalFrame* hf = new TGVerticalFrame(frmMain);
	{
		TGGroupFrame *fGroupFrame2 = new TGGroupFrame(hf,"Event Display");
		fGroupFrame2->SetLayoutBroken(kTRUE);
		{
			posy = 20;
			fNumberEntry = new TGNumberEntry(fGroupFrame2, (Double_t) 0,6,-1,(TGNumberFormat::EStyle) 5,(TGNumberFormat::EAttribute) 1,(TGNumberFormat::ELimit) 2,0,10000);
			fGroupFrame2->AddFrame(fNumberEntry, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,62,2));
			fNumberEntry->MoveResize(20,posy,90,18);
			TGTextButton *b = new TGTextButton(fGroupFrame2, "Show Event#");
			b->SetCommand("SetEventNumber()");
			fGroupFrame2->AddFrame(b, new TGLayoutHints(kLHintsExpandX));
			b->MoveResize(120,posy,90,18);
			//
			posy+=28;
			fb = new TGTextButton(fGroupFrame2,"Next");
			fb->SetCommand("NextEvent()");
			fb->MoveResize(10,posy,95,18);
			fb->SetToolTipText("Show next event");
			//
			fb = new TGTextButton(fGroupFrame2,"Previous");
			fb->MoveResize(110,posy,95,18);
			fb->SetCommand("PreviousEvent()");
			fb->SetToolTipText("Show previous event");
		}
		hf->AddFrame(fGroupFrame2, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
		fGroupFrame2->MoveResize(0,200,240,105);
		// Group4
		TGGroupFrame *fGroupFrame4 = new TGGroupFrame(hf,"Display");
		fGroupFrame4->SetLayoutBroken(kTRUE);
		{
			int posy=15;
			TGLabel *fLabel = new TGLabel(fGroupFrame4,"Projections");
			fLabel->MoveResize(10,posy,50,20);

			TGTextButton *fb = new TGTextButton(fGroupFrame4,"Z-Y");
			fb->MoveResize(80,posy,20,18);
			fb->SetCommand("set_camera(CAMERA_X)");

			fb = new TGTextButton(fGroupFrame4,"X-Y");
			fb->MoveResize(105,posy,20,18);
			fb->SetCommand("set_camera(CAMERA_Y)");

			fb = new TGTextButton(fGroupFrame4,"X-Z");
			fb->MoveResize(130,posy,20,18);
			fb->SetCommand("set_camera(CAMERA_Z)");

			fb = new TGTextButton(fGroupFrame4,"U-view");
			fb->MoveResize(155,posy,50,18);
			fb->SetCommand("set_camera(CAMERA_B)");
			posy+=22;
			posy+=21;
			fb = new TGTextButton(fGroupFrame4,"Exit");
			fb->MoveResize(55,posy,100,20);
			fb->Connect("Clicked()",0,0, "DoExit()");
		}
		hf->AddFrame(fGroupFrame4, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
		fGroupFrame4->MoveResize(0,260,240,240);
	}

	// status bar
	Int_t parts[] = {45,20,20,15};
	fStatusBar = gEve->GetBrowser()->GetStatusBar();
	fStatusBar->SetParts(parts,4);
	fStatusBar->SetText("Welcome to V-D EventDisplay",0);

	frmMain->AddFrame(hf);
	frmMain->MapSubwindows();
	frmMain->Resize();
	frmMain->MapWindow();
	//
	browser->StopEmbedding();
	browser->SetTabTitle("Main", 0);
	gEve->GetBrowser()->StartEmbedding(0);   
	g_hlt_browser = gEve->GetBrowser()->MakeFileBrowser();   
	gEve->GetBrowser()->StopEmbedding("Files");	
	
	gDirectory = 0;
	//////////////////////////////////////////////////
	// if you want to get histograms linked to Event Display, uncomment below
	//GetDistributions();
	//SandrosHisto();
	
	gEve->GetBrowser()->StartEmbedding(1);   
	g_hlt_canvas = new TCanvas;   
	gEve->GetBrowser()->StopEmbedding("Histograms");
	gEve->GetBrowser()->GetTabRight()->SetTab(0);
	gEve->GetBrowser()->GetTabLeft()->SetTab(1);

	// Draw Display
	gEve->Redraw3D(kTRUE);	

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void DoExit()
{
	cout << "Exit application..." << endl;
	gROOT->Reset();
	gApplication->Terminate(0);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// particle charge --> Fluka code and particle names listed
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int GetCharged(int flkcode)
{
	int charge = 0;
	if ( flkcode ==  1 ) charge =  1; // Proton
	if ( flkcode ==  2 ) charge = -1; // Antiproton
	if ( flkcode ==  3 ) charge =  1; // Electron
	if ( flkcode ==  4 ) charge =  1; // Positron
	if ( flkcode ==  5 ) charge =  0; // Electron Neutrino
	if ( flkcode ==  6 ) charge =  0; // Electron Antineutrino
	if ( flkcode ==  7 ) charge =  0; // Photon
	if ( flkcode ==  8 ) charge =  0; // Neutron
	if ( flkcode ==  9 ) charge =  0; // Antineutron
	if ( flkcode == 10 ) charge =  1; // Positive Muon
	if ( flkcode == 11 ) charge = -1; // Negative Muon
	if ( flkcode == 12 ) charge =  0; // Kaon-zero long 
	if ( flkcode == 13 ) charge =  1; // Positive Pion
	if ( flkcode == 14 ) charge = -1; // Negative Pion
	if ( flkcode == 15 ) charge =  1; // Positive Kaon
	if ( flkcode == 16 ) charge = -1; // Negative Kaon
	if ( flkcode == 17 ) charge =  0; // Lambda
	if ( flkcode == 18 ) charge =  0; // Antilambda
	if ( flkcode == 19 ) charge =  0; // Kaon zero short
	if ( flkcode == 20 ) charge = -1; // Negative Sigma 
	if ( flkcode == 21 ) charge =  1; // Positive Sigma
	if ( flkcode == 22 ) charge =  0; // Sigma-zero
	if ( flkcode == 23 ) charge =  0; // Pion-zero
	if ( flkcode == 24 ) charge =  0; // Kaon-zero 
	if ( flkcode == 25 ) charge =  0; // Antikaon-zero
	if ( flkcode == 27 ) charge =  0; // Muon neutrino
	if ( flkcode == 28 ) charge =  0; // Muon antineutrino 
	if ( flkcode == 31 ) charge = -1; //AntiSigma_plus
	if ( flkcode == 32 ) charge =  0; // AntiSigma-zero  
	if ( flkcode == 33 ) charge =  1; // Antisigma-minus
	if ( flkcode == 34 ) charge =  0; // Xsi-zero
	if ( flkcode == 35 ) charge =  0; // AntiXsi-zero
	if ( flkcode == 36 ) charge =  0; //Sigma-zero
	if ( flkcode == 37 ) charge =  0; //AntiSigma-zero
	if ( flkcode == 38 ) charge = -1; // Omega-minus
	if ( flkcode == 39 ) charge =  1; // AntiOmega-minus
	if ( flkcode == 41 ) charge =  1; // Positive Tau
	if ( flkcode == 42 ) charge = -1; // Negative Tau
	if ( flkcode == 43 ) charge =  0; // Tau neutrino
	if ( flkcode == 44 ) charge =  0; // Tau antineutrino
	if ( flkcode == 45 ) charge =  1; // D-plus
	if ( flkcode == 46 ) charge = -1; // D-minus
	if ( flkcode == 47 ) charge =  0; // D-zero
	if ( flkcode == 48 ) charge =  0; // AntiD-zero 
	if ( flkcode == 49 ) charge =  1; // D_s-plus
	if ( flkcode == 50 ) charge = -1; // D_s-minus
	if ( flkcode == 51 ) charge =  1; // Lambda_c-plus
	if ( flkcode == 52 ) charge =  1; // Xsi_c-plus
	if ( flkcode == 53 ) charge =  0; // Sigma_c-zero
	if ( flkcode == 54 ) charge =  1; // Xsi_c_prime-plus
	if ( flkcode == 55 ) charge =  0; // Xsi_c_prime-zero
	if ( flkcode == 56 ) charge =  0; //Omega_c-zero
	if ( flkcode == 57 ) charge = -1; //Anti_Lambda_c
	if ( flkcode == 58 ) charge = -1; // Xsi_c-minus
	if ( flkcode== 59 ) charge =  0; // Anti_Xsi_c-zero
	if ( flkcode== 60 ) charge = -1; // Xsi_c_prime-minus
	if ( flkcode== 61 ) charge =  0; // AntiXsi_c_prime-zero
	if ( flkcode== 62 ) charge =  0; // Anti_Omega_c-zero
	return charge;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Fluka code to particle name
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void GetParticleName(int flkcode){
	std::string particle;
	if ( flkcode==  1 ) particle = "Proton";
	if ( flkcode==  2 ) particle = "Antiproton";
	if ( flkcode==  3 ) particle = "Electron";
	if ( flkcode==  4 ) particle = "Positron";
	if ( flkcode==  5 ) particle = "Electron Neutrino";
	if ( flkcode==  6 ) particle = "Electron Antineutrino";
	if ( flkcode==  7 ) particle = "Photon";
	if ( flkcode==  8 ) particle = "Neutron";
	if ( flkcode==  9 ) particle = "Antineutron";
	if ( flkcode== 10 ) particle = "Positive Muon";
	if ( flkcode== 11 ) particle = "Negative Muon";
	if ( flkcode== 12 ) particle = "Kaon-zero long ";
	if ( flkcode== 13 ) particle = "Positive Pion";
	if ( flkcode== 14 ) particle = "Negative Pion";
	if ( flkcode== 15 ) particle = "Positive Kaon";
	if ( flkcode== 16 ) particle = "Negative Kaon";
	if ( flkcode== 17 ) particle = "Lambda";
	if ( flkcode== 18 ) particle = "Antilambda";
	if ( flkcode== 19 ) particle = "Kaon zero short";
	if ( flkcode== 20 ) particle = "Negative Sigma ";
	if ( flkcode== 21 ) particle = "Positive Sigma";
	if ( flkcode== 22 ) particle = "Sigma-zero";
	if ( flkcode== 23 ) particle = "Pion-zero";
	if ( flkcode== 24 ) particle = "Kaon-zero ";
	if ( flkcode== 25 ) particle = "Antikaon-zero";
	if ( flkcode== 27 ) particle = "Muon neutrino";
	if ( flkcode== 28 ) particle = "Muon antineutrino ";
	if ( flkcode== 31 ) particle = "AntiSigma_plus";
	if ( flkcode== 32 ) particle = "AntiSigma-zero  ";
	if ( flkcode== 33 ) particle = "Antisigma-minus";
	if ( flkcode== 34 ) particle = "Xsi-zero";
	if ( flkcode== 35 ) particle = "AntiXsi-zero";
	if ( flkcode== 36 ) particle = "Sigma-zero";
	if ( flkcode== 37 ) particle = "AntiSigma-zero";
	if ( flkcode== 38 ) particle = "Omega-minus";
	if ( flkcode== 39 ) particle = "AntiOmega-minus";
	if ( flkcode== 41 ) particle = "Positive Tau";
	if ( flkcode== 42 ) particle = "Negative Tau";
	if ( flkcode== 43 ) particle = "Tau neutrino";
	if ( flkcode== 44 ) particle = "Tau antineutrino";
	if ( flkcode== 45 ) particle = "D-plus";
	if ( flkcode== 46 ) particle = "D-minus";
	if ( flkcode== 47 ) particle = "D-zero";
	if ( flkcode== 48 ) particle = "AntiD-zero ";
	if ( flkcode== 49 ) particle = "D_s-plus";
	if ( flkcode== 50 ) particle = "D_s-minus";
	if ( flkcode== 51 ) particle = "Lambda_c-plus";
	if ( flkcode== 52 ) particle = "Xsi_c-plus";
	if ( flkcode== 53 ) particle = "Sigma_c-zero";
	if ( flkcode== 54 ) particle = "Xsi_c_prime-plus";
	if ( flkcode== 55 ) particle = "Xsi_c_prime-zero";
	if ( flkcode== 56 ) particle = "Omega_c-zero";
	if ( flkcode== 57 ) particle = "Anti_Lambda_c";
	if ( flkcode== 58 ) particle = "Xsi_c-minus";
	if ( flkcode== 59 ) particle = "Anti_Xsi_c-zero";
	if ( flkcode== 60 ) particle = "Xsi_c_prime-minus";
	if ( flkcode== 61 ) particle = "AntiXsi_c_prime-zero";
	if ( flkcode== 62 ) particle = "Anti_Omega_c-zero";
	
	fprintf(stdout,"************************************************************************\n");
	fprintf(stdout, "    Fluka Code: %d --> Particle Name: %s\n",flkcode,particle.c_str());
	fprintf(stdout,"************************************************************************\n");
}

enum {
	CAMERA_X,
	CAMERA_Y,
	CAMERA_Z,
	CAMERA_B
};

void set_camera(int projection)
{
	if(projection==CAMERA_X) {
		(T3DView->GetGLViewer())->SetCurrentCamera(TGLViewer::kCameraOrthoZOY);
		TGLOrthoCamera& cam = (TGLOrthoCamera &)(T3DView->GetGLViewer())->CurrentCamera();
		cam.Reset();
		//cam.RotateRad( -3.14159*0.5, 0.0);
		//cam.SetEnableRotate(1);
	}
	if(projection==CAMERA_Y) {
		(T3DView->GetGLViewer())->SetCurrentCamera(TGLViewer::kCameraOrthoXOY);
		TGLOrthoCamera& cam = (TGLOrthoCamera &)(T3DView->GetGLViewer())->CurrentCamera();
		//cam.Reset();
		//cam.SetEnableRotate(1);
	}
	if(projection==CAMERA_Z) {
		(T3DView->GetGLViewer())->SetCurrentCamera(TGLViewer::kCameraOrthoXOZ);
		TGLOrthoCamera& cam = (TGLOrthoCamera &)(T3DView->GetGLViewer())->CurrentCamera();
		//cam.Reset();
		//cam.SetEnableRotate(1);
	}
	if(projection==CAMERA_B) {
		(T3DView->GetGLViewer())->SetCurrentCamera(TGLViewer::kCameraOrthoZOY);
		TGLOrthoCamera& cam = (TGLOrthoCamera &)(T3DView->GetGLViewer())->CurrentCamera();
		cam.Reset();
		cam.RotateRad(0.0,0.78);
		//cam.SetEnableRotate(1);
	}
	(T3DView->GetGLViewer())->DoDraw();
}

