#ifndef FLASHgg_ProtonKinematicsUtils_h
#define FLASHgg_ProtonKinematicsUtils_h

#include "flashgg/DataFormats/interface/Proton.h"

namespace flashgg {

    float tracksDistance( const ProtonTrack& near_p, const ProtonTrack& far_p )
    {
        const float z_far = far_p.getZ0();
        const TVector2 far_xy_ext = near_p.getTrackPoint( z_far ), far_xy_obs = TVector2( far_p.getX0(), far_p.getY0() );
        return (far_xy_ext-far_xy_obs).Mod()/1.e3; // mm -> m
    }

    void computeXi( const Proton& prot, float* xi_, float* err_xi_ )
    {
        *xi_ = *err_xi_ = 0.;

        if ( !prot.isValid() ) return;

        float dx_n, dx_f;
        switch ( prot.side() ) {
            case ProtonTrack::LeftSide: {
                dx_n = 9.26e-2;
                dx_f = 9.22e-2;
            } break;
            case ProtonTrack::RightSide: {
                dx_n = 5.81e-2;
                dx_f = 5.16e-2;
            } break;
            default: return;
        }

        const float de_x = 0.2e-3/*m*/, de_rel_dx = 0.1;

        if ( prot.farTrack().isValid() ) {
            *xi_ = (prot.farTrack().getX0()*1.e-3) / dx_f;
            *err_xi_ = std::sqrt( std::pow( de_x/dx_f, 2 )
                                + std::pow( de_rel_dx * (*xi_), 2 ) );
            return;
        }
        if ( prot.nearTrack().isValid() ) {
            *xi_ = (prot.nearTrack().getX0()*1.e-3) / dx_n;
            *err_xi_ = std::sqrt( std::pow( de_x/dx_n, 2 )
                                + std::pow( de_rel_dx * (*xi_), 2 ) );
            return;
        }
    }

}

#endif
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
