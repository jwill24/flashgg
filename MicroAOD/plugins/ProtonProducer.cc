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
            const ProtonTrack::Arm  arm  = (det_id%100==2) ? ProtonTrack::NearArm  : ProtonTrack::FarArm;    // (003/103->F, 002/102->N)
            const ProtonTrack::Side side = (det_id/100==0) ? ProtonTrack::LeftSide : ProtonTrack::RightSide; // (002/003->L, 102/103->R)
            for (edm::DetSet<TotemRPLocalTrack>::const_iterator proton=rp->begin(); proton!=rp->end(); proton++) {
                if (!proton->isValid()) continue;
                flashgg::ProtonTrack frpp = flashgg::ProtonTrack( *proton );
                frpp.setArm( arm );
                frpp.setSide( side );
                frpp.setRPId( det_id );
                if      (arm==ProtonTrack::FarArm  && side==ProtonTrack::LeftSide)  fl_tracks.push_back( frpp );
                else if (arm==ProtonTrack::FarArm  && side==ProtonTrack::RightSide) fr_tracks.push_back( frpp );
                else if (arm==ProtonTrack::NearArm && side==ProtonTrack::LeftSide)  nl_tracks.push_back( frpp );
                else if (arm==ProtonTrack::NearArm && side==ProtonTrack::RightSide) nr_tracks.push_back( frpp );
            }
        }
        /*cerr << "number of tracks reconstructed:" << endl
             << "  left side:  near pot:" << nl_tracks.size() << ", far pot: " << fl_tracks.size() << endl
             << "  right side: near pot:" << nr_tracks.size() << ", far pot: " << fr_tracks.size() << endl;*/
        float min_distance = 999., xi = 0., err_xi = 0.;
        flashgg::Proton proton;
        {
            for (vector<flashgg::ProtonTrack>::const_iterator trk_n=nl_tracks.begin(); trk_n!=nl_tracks.end(); trk_n++) {
                if ( fr_tracks.size()==0 ) {
                    proton = flashgg::Proton( *trk_n, flashgg::ProtonTrack::LeftSide, flashgg::ProtonTrack::NearArm );

                    if ( useXiInterp_ ) { xiInterp_->computeXiSpline( proton, &xi, &err_xi ); }
                    else                { xiInterp_->computeXiLinear( proton, &xi, &err_xi ); }
                    proton.setXi( xi );
                    proton.setDeltaXi( err_xi );

                    continue;
                }
                min_distance = 999.;
                for (vector<flashgg::ProtonTrack>::const_iterator trk_f=fl_tracks.begin(); trk_f!=fl_tracks.end(); trk_f++) {
                    float dist = ProtonUtils::tracksDistance( *trk_n, *trk_f );
                    if ( dist<min_distance ) {
                        proton = flashgg::Proton( *trk_n, *trk_f, flashgg::ProtonTrack::LeftSide );

                        if ( useXiInterp_ ) { xiInterp_->computeXiSpline( proton, &xi, &err_xi ); }
                        else                { xiInterp_->computeXiLinear( proton, &xi, &err_xi ); }
                        proton.setXi( xi );
                        proton.setDeltaXi( err_xi );

                        min_distance = dist;
                    }
                }
                if ( proton.isValid() ) protonColl->push_back( proton );
            }
        }
        {
            for (vector<flashgg::ProtonTrack>::const_iterator trk_n=nr_tracks.begin(); trk_n!=nr_tracks.end(); trk_n++) {
                if ( fr_tracks.size()==0 ) {
                    proton = flashgg::Proton( *trk_n, flashgg::ProtonTrack::RightSide, flashgg::ProtonTrack::NearArm );

                    if ( useXiInterp_ ) { xiInterp_->computeXiSpline( proton, &xi, &err_xi ); }
                    else                { xiInterp_->computeXiLinear( proton, &xi, &err_xi ); }
                    proton.setXi( xi );
                    proton.setDeltaXi( err_xi );

                    continue;
                }
                min_distance = 999.;
                for (vector<flashgg::ProtonTrack>::const_iterator trk_f=fr_tracks.begin(); trk_f!=fr_tracks.end(); trk_f++) {
                    float dist = ProtonUtils::tracksDistance( *trk_n, *trk_f );
                    if ( dist<min_distance ) {
                        proton = flashgg::Proton( *trk_n, *trk_f, flashgg::ProtonTrack::RightSide );

                        if ( useXiInterp_ ) { xiInterp_->computeXiSpline( proton, &xi, &err_xi ); }
                        else                { xiInterp_->computeXiLinear( proton, &xi, &err_xi ); }
                        proton.setXi( xi );
                        proton.setDeltaXi( err_xi );

                        min_distance = dist;
                    }
                }
                if ( proton.isValid() ) protonColl->push_back( proton );
            }
        }
        evt.put( protonColl );
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

