import FWCore.ParameterSet.Config as cms

flashggDiElectrons = cms.EDProducer('FlashggDiElectronProducer',
                                  ElectronTag=cms.InputTag('flashggSelectedElectrons'),
                                  VertexTag=cms.InputTag('offlineSlimmedPrimaryVertices'), 
                                  ##Parameters                                                
                                  minElectronPT=cms.double(5.),
                                  maxElectronEta=cms.double(2.4)
                                  )
