#include "FWCore/Framework/interface/MakerMacros.h"
#include "flashgg/Taggers/interface/EEDumpers.h"
#include "PhysicsTools/UtilAlgos/interface/EDAnalyzerWrapper.h"

//-----------J. Tao from IHEP-Beijing--------------

typedef edm::AnalyzerWrapper<flashgg::DiElectronDumper> DiElectronDumper;
typedef edm::AnalyzerWrapper<flashgg::CutBasedDiElectronDumper> CutBasedDiElectronDumper;
typedef edm::AnalyzerWrapper<flashgg::EEGammaDumper> EEGammaDumper;
typedef edm::AnalyzerWrapper<flashgg::CutBasedEEGammaDumper> CutBasedEEGammaDumper;

DEFINE_FWK_MODULE( DiElectronDumper );
DEFINE_FWK_MODULE( CutBasedDiElectronDumper );
DEFINE_FWK_MODULE( EEGammaDumper );
DEFINE_FWK_MODULE( CutBasedEEGammaDumper );


// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

