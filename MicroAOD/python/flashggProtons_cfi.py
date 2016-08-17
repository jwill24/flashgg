import FWCore.ParameterSet.Config as cms

flashggProtons = cms.EDProducer('FlashggProtonProducer',
    protonTag = cms.InputTag('totemRPLocalTrackFitter'),
    useXiInterpolation = cms.bool(True),
    xiInterpolationFile = cms.FileInPath('flashgg/MicroAOD/data/ctpps_optics_v1.root'),
)
