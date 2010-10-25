class MyPlugin < PluginBase
  def initialize()
    @plug_info = { :name => "My", :author => "Jacob", :version => "0.2.0"}   
  end

  def run 
    puts 1 
  end
  
  attr_accessor :plug_info
end
