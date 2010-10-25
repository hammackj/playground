require 'pluginbase'
class PluginManager
  def initialize()
    @registered_plugins = Array.new
  end
  
  def load_plugins(path)
    Dir["#{path}/*.rb"].each{|x| load x }
    
    PluginBase.possible_plugins.each { |p|
      if validate(p) ==  true
        registered_plugins << p
      end
    }

  end
  
  def validate(plugin)
    p = plugin.new
        
    if p == nil
      return false
    end

    if p.respond_to?(:run) == false
      return false
    end
          
    return true
  end
  
  attr_accessor :registered_plugins
end