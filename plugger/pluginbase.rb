class PluginBase
  @possible_plugins = []
  class << self
    attr_reader :possible_plugins 
  end
    
  def self.inherited(child)
      possible_plugins << child
  end
end



