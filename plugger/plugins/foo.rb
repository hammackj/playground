class FooPlugin < PluginBase
  def initialize()
    @plug_info = { :name => "Foo", :author => "Jacob", :version => "0.0.0"}   
  end

  def run 
    puts 1 
  end
  
  attr_accessor :plug_info
end
