#ifndef TREEMANAGER_h
#define TREEMANAGER_h

#include "Header.h"
#include "Hits.h"
#include "TTree.h"
#include "TFile.h"
#include "TVectorD.h"
#include <string>
class TreeManager {
	public :
		TreeManager(std::string infilename);
		virtual ~TreeManager();
		
		Header *tmCD()      { return m_tres;  };
		Hits   *tmHits()    { return m_thit;  };
        protected:
		void          init();
		void          nullify();
		
	private:
		std::string   m_inFilename;
		
		TFile         *m_inFile;
		
		TTree         *m_treeRes;
		TTree         *m_treeHit;
		
		Header        *m_tres;
		Hits          *m_thit;
};
#endif //TreeManager_h


