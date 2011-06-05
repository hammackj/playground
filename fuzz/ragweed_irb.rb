#!/usr/bin/env ruby

require 'irb'
require 'ragweed'
include Ragweed

def consolize &block
	yield

	IRB.setup(nil)
	IRB.conf[:USE_READLINE] = true
	IRB.conf[:PROMPT_MODE] = :SIMPLE

	irb = IRB::Irb.new
	IRB.conf[:MAIN_CONTEXT] = irb.context

	irb.context.evaluate("require 'irb/completion'", 0)

	trap("SIGINT") do
   		irb.signal_handle
 	end
 	catch(:IRB_EXIT) do
  		irb.eval_input
  	end
end

consolize do
	puts "RagWeed Console"
end

