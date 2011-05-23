#!/usr/bin/env ruby

require 'ragweed'
include Ragweed

class DebugVulnC < Debuggerosx

	# print the registers every time the process stops
	def on_stop(signal)
		puts "Stopped with signal #{signal}"
		self.threads.each {|t| self.get_registers(t).dump}
	end
end

puts "[!] Attaching to PID #{ARGV[0]}"
d = DebugVulnC.new(ARGV[0].to_i)
d.attach

puts "[*] Attached"

# set breakpoint for lpwd
#d.breakpoint_set(0x420f,‘lpwd’, (bpl = lambda do | t, r, s | puts "#{ s.breakpoints[r.eip].first.function } hit in thread #{ t }\n"; end))
#d.install_breakpoints
d.continue
d.loop #loop until child exits

# now go do stuff in in your other terminal window running ftp
d.region_info(0x0,:basic).dump
