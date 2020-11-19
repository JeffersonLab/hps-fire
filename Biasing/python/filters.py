
from HPS.SimCore import simcfg

class PairConvFilter(simcfg.UserAction): 
  def __init__(self):
    super().__init__("pair_conv_filter", "biasing::PairConvFilter")

