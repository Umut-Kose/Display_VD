#include "TreeManager.h"
#include "Header.h"
#include "Hits.h"


#include <iostream>
#include <stdlib.h>
#include <list>
//#include <array>

#if !defined (__CINT__) || defined (__MAKECINT__)
#include "Rtypes.h"
#endif
#ifdef __MAKECINT__
#pragma link off all class;
#pragma link C++ class Header+;
#pragma link C++ class Hits+;
#pragma link off all function;
#pragma link off all global;
#pragma link off all typedef;
#endif

using namespace std;

class Header;
class Hits;
class TObject;

TreeManager::TreeManager(std::string infilename){
	m_inFilename = infilename;
	cout << "Processing file: " << m_inFilename.c_str() << endl;
	init();
}

TreeManager::~TreeManager(){
	delete  m_treeRes;
	delete  m_treeHit;
	
	delete  m_inFile;
}



void TreeManager::nullify(){
	m_treeRes  = NULL;
	m_treeHit  = NULL;
	Header::releaseThis();
	Hits::releaseThis();
}

void TreeManager::init(){
	nullify();
	m_inFile = new TFile(m_inFilename.c_str(), "READ");
	if( m_inFile->IsOpen() == kFALSE ) return;
	cout << "File opened!" << endl;

	m_treeRes = (TTree*) m_inFile->FindObjectAny("HeaderTree");
	if( m_treeRes != NULL ) {
		cout << "m_treeRes found!" << endl;
		m_tres = Header::giveThis(m_treeRes,"read");
		if( m_tres != NULL ) {
			cerr << " [0] it is ok!!" << endl;
		}
	}

	m_treeHit = (TTree*) m_inFile->FindObjectAny("HitsTree");
	if( m_treeHit != NULL ) {
		cout << "m_treeHit found!" << endl;
		m_thit = Hits::giveThis(m_treeHit,"read");
		if( m_thit != NULL ) {
			cerr << " [1] it is ok!!" << endl;
		}
	}

}

