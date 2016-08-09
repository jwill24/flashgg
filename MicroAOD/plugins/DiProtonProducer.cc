#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "flashgg/DataFormats/interface/DiProtonCandidate.h"

#include <map>

using namespace edm;
using namespace std;

namespace flashgg {

    class DiProtonProducer : public EDProducer
    {

    public:
        DiProtonProducer( const ParameterSet & );
    private:
        void produce( Event &, const EventSetup & ) override;
        EDGetTokenT<View<flashgg::Proton> > protonToken_;
        double sqrtS_;
    };

    DiProtonProducer::DiProtonProducer( const ParameterSet &iConfig ) :
        protonToken_( consumes<View<flashgg::Proton> >( iConfig.getParameter<InputTag> ( "ProtonTag" ) ) ),
        sqrtS_( iConfig.getParameter<double> ( "SqrtS" ) )
    {
        produces<vector<flashgg::DiProtonCandidate> >();
    }

    void DiProtonProducer::produce( Event &evt, const EventSetup & )
    {
        Handle<View<flashgg::Proton> > protons;
        evt.getByToken( protonToken_, protons );

        auto_ptr<vector<DiProtonCandidate> > diProtonColl( new vector<DiProtonCandidate> );

        for( unsigned int i = 0 ; i < protons->size() ; i++ ) {

            Ptr<flashgg::Proton> pp1 = protons->ptrAt( i );
            for( unsigned int j = i + 1 ; j < protons->size() ; j++ ) {
                Ptr<flashgg::Proton> pp2 = protons->ptrAt( j );

                DiProtonCandidate dipro( pp1, pp2 );

                const float rel_xi = std::sqrt( std::pow( pp1->deltaXi()/pp1->xi(), 2 ) + std::pow( pp2->deltaXi()/pp2->xi(), 2 ) );

                dipro.setM( sqrtS_*1.e3 * std::sqrt( pp1->xi() * pp2->xi() ) );
                dipro.setDeltaM( dipro.M()/2. * rel_xi );

                dipro.setRapidity( 0.5 * std::log( pp2->xi() / pp1->xi() ) );
                dipro.setDeltaRapidity( 0.5 * rel_xi );

                // store the diproton into the collection
                diProtonColl->push_back( dipro );
            }
        }
        // Sort the final collection (descending) and put it in the event
        std::sort( diProtonColl->begin(), diProtonColl->end(), greater<DiProtonCandidate>() );

        evt.put( diProtonColl );
    }
}

typedef flashgg::DiProtonProducer FlashggDiProtonProducer;
DEFINE_FWK_MODULE( FlashggDiProtonProducer );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

