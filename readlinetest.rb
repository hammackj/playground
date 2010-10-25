#!/usr/bin/env ruby
require 'readline'

stty_save = `stty -g`.chomp

def process_cmd line
  case line
    when "help"
      puts CMDS
    when "clear"
      system('clear')
    when "quit"
      exit
  end
end



CMDS = ['help','clear', 'quit'].sort

comp = proc { |s| CMDS.grep(/^#{Regexp.escape(s)}/)}

Readline.completion_append_character = ""
Readline.completion_proc = comp

begin
  while line = Readline.readline('> ', true)
    process_cmd line
  end
rescue Interrupt => e
  system('stty', stty_save)
  exit
end