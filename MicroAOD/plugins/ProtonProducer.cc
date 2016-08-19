// system include files
#include <memory>
// user include files
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/CTPPSReco/interface/TotemRPLocalTrack.h"
#include "flashgg/DataFormats/interface/Proton.h"
#include "flashgg/MicroAOD/interface/ProtonKinematicsUtils.h"

using namespace std;
using namespace edm;

#include <iostream>

namespace flashgg {

    class ProtonProducer : public edm::EDProducer
    {
    public:
        ProtonProducer( const edm::ParameterSet & );
        ~ProtonProducer();

    private:
        void produce( edm::Event &, const edm::EventSetup & );
        void reconstructOneArm( const vector<flashgg::ProtonTrack>&, const vector<flashgg::ProtonTrack>&, const flashgg::ProtonTrack::Side&, vector<flashgg::Proton>& );

        edm::EDGetTokenT<DetSetVector<TotemRPLocalTrack> > localTracksToken_;

        bool useXiInterp_;
        ProtonUtils::XiInterpolator* xiInterp_;

    };

    ProtonProducer::ProtonProducer( const ParameterSet &iConfig ):
        localTracksToken_( consumes<DetSetVector<TotemRPLocalTrack> >( iConfig.getParameter<InputTag>( "protonTag" ) ) ),
        useXiInterp_( iConfig.getParameter<bool>( "useXiInterpolation" ) ), xiInterp_( 0 )
    {
        produces<vector<flashgg::Proton> >();
        xiInterp_ = new ProtonUtils::XiInterpolator;
        if ( useXiInterp_ ) { xiInterp_->loadInterpolationGraphs( iConfig.getParameter<edm::FileInPath>( "xiInterpolationFile" ).fullPath().c_str() ); }
    }

    ProtonProducer::~ProtonProducer() {
        if ( xiInterp_ ) delete xiInterp_;
    }

    void ProtonProducer::produce( Event &evt, const EventSetup & )
    {
        Handle<DetSetVector<TotemRPLocalTrack> >  prptracks;
        evt.getByToken( localTracksToken_, prptracks );

        std::auto_ptr<vector<flashgg::Proton> > protonColl( new vector<flashgg::Proton> );

        xiInterp_->setAlignmentConstants( evt.id().run() ); // run-based alignment corrections

        vector<flashgg::ProtonTrack> fl_tracks, fr_tracks, nl_tracks, nr_tracks;
        for (edm::DetSetVector<TotemRPLocalTrack>::const_iterator rp=prptracks->begin(); rp!=prptracks->end(); rp++) {
            const unsigned int det_id = rp->detId();
            for (edm::DetSet<TotemRPLocalTrack>::const_iterator proton=rp->begin(); proton!=rp->end(); proton++) {
                if (!proton->isValid()) continue;

                flashgg::ProtonTrack frpp = flashgg::ProtonTrack( det_id, *proton );

std::cout << ">>> " << det_id << " ---> station:" << frpp.station() << " side:" << frpp.side() << std::endl;
std::cout << "     (" << frpp.decDetId() << ") >>>>>>>> " << frpp.detId() << std::endl;

                const flashgg::ProtonTrack::Station st = frpp.station();
                const flashgg::ProtonTrack::Side side = frpp.side();

                if      (st==ProtonTrack::FarStation  && side==ProtonTrack::LeftSide)  fl_tracks.push_back( frpp );
                else if (st==ProtonTrack::FarStation  && side==ProtonTrack::RightSide) fr_tracks.push_back( frpp );
                else if (st==ProtonTrack::NearStation && side==ProtonTrack::LeftSide)  nl_tracks.push_back( frpp );
                else if (st==ProtonTrack::NearStation && side==ProtonTrack::RightSide) nr_tracks.push_back( frpp );
            }
        }
        /*cerr << "number of tracks reconstructed:" << endl
             << "  left side:  near pot:" << nl_tracks.size() << ", far pot: " << fl_tracks.size() << endl
             << "  right side: near pot:" << nr_tracks.size() << ", far pot: " << fr_tracks.size() << endl;*/

        reconstructOneArm( nl_tracks, fl_tracks, flashgg::ProtonTrack::LeftSide, *protonColl );
        reconstructOneArm( nr_tracks, fr_tracks, flashgg::ProtonTrack::RightSide, *protonColl );

        evt.put( protonColl );
    }

    void ProtonProducer::reconstructOneArm( const vector<flashgg::ProtonTrack>& near_coll, const vector<flashgg::ProtonTrack>& far_coll, const flashgg::ProtonTrack::Side& side, vector<flashgg::Proton>& out_coll )
    {
        float min_distance = 999., xi = 0., err_xi = 0.;
        flashgg::Proton proton;

        if ( near_coll.size()==0 ) {
            for ( vector<flashgg::ProtonTrack>::const_iterator trk_f=far_coll.begin(); trk_f!=far_coll.end(); trk_f++ ) {
                proton = flashgg::Proton( *trk_f, side );

                if ( useXiInterp_ ) { xiInterp_->computeXiSpline( proton, &xi, &err_xi ); }
                else                { xiInterp_->computeXiLinear( proton, &xi, &err_xi ); }
                proton.setXi( xi, err_xi );

                if ( proton.isValid() ) out_coll.push_back( proton );
            }

            return;
        }

        for (vector<flashgg::ProtonTrack>::const_iterator trk_n=near_coll.begin(); trk_n!=near_coll.end(); trk_n++) {
            // checks if far pot tracks are reconstructed
            if ( far_coll.size()==0 ) {
                proton = flashgg::Proton( *trk_n, side );

                if ( useXiInterp_ ) { xiInterp_->computeXiSpline( proton, &xi, &err_xi ); }
                else                { xiInterp_->computeXiLinear( proton, &xi, &err_xi ); }
                proton.setXi( xi, err_xi );

                if ( proton.isValid() ) out_coll.push_back( proton );
                continue;
            }

            // associate a minimum-distance far pot track to this near pot track
            flashgg::ProtonTrack ft_sel;
            min_distance = 999.;
            for (vector<flashgg::ProtonTrack>::const_iterator trk_f=far_coll.begin(); trk_f!=far_coll.end(); trk_f++) {
                float dist = ProtonUtils::tracksDistance( *trk_n, *trk_f );
                if ( dist<min_distance ) {
                    ft_sel = *trk_f;
                    min_distance = dist;
                }
            }
            if ( !ft_sel.isValid() ) continue;

            proton = flashgg::Proton( *trk_n, ft_sel, side );

            if ( useXiInterp_ ) { xiInterp_->computeXiSpline( proton, &xi, &err_xi ); }
            else                { xiInterp_->computeXiLinear( proton, &xi, &err_xi ); }
            proton.setXi( xi, err_xi );

            if ( proton.isValid() ) out_coll.push_back( proton );
        }
    }
}

typedef flashgg::ProtonProducer FlashggProtonProducer;
DEFINE_FWK_MODULE( FlashggProtonProducer );

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

