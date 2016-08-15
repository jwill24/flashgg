#-----------J. Tao from IHEP-Beijing--------------

import FWCore.ParameterSet.Config as cms

from flashgg.Taggers.eegammaDumpConfig_cff import eeammaDumpConfig

eegammaDumper = cms.EDAnalyzer('CutBasedEEGammaDumper',
                                **eegammaDumpConfig.parameters_()
                                )


