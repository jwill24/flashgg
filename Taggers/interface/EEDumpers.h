#ifndef flashgg_EEDumpers_h
#define flashgg_EEDumpers_h

#include "flashgg/DataFormats/interface/DiElectronCandidate.h"
#include "flashgg/DataFormats/interface/EEGammaCandidate.h"

#include "flashgg/Taggers/interface/CollectionDumper.h"

namespace flashgg {

    typedef CollectionDumper<std::vector<DiElectronCandidate> > DiElectronDumper;
    typedef CollectionDumper<std::vector<DiElectronCandidate>,
            DiElectronCandidate,
            CutBasedClassifier<DiElectronCandidate> > CutBasedDiElectronDumper;

    typedef CollectionDumper<std::vector<EEGammaCandidate> > EEGammaDumper;
    typedef CollectionDumper<std::vector<EEGammaCandidate>,
            EEGammaCandidate,
            CutBasedClassifier<EEGammaCandidate> > CutBasedEEGammaDumper;

}

#endif

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
