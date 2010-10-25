#!/usr/bin/env ruby

require 'pluginmanager'

pm = PluginManager.new
pm.load_plugins("plugins")

pm.registered_plugins.each { |plugin|
  p = plugin.new
  puts p.mod_info[:name]
  
  p.run
}

