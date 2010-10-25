#!/usr/bin/env ruby

strings = [ "This|is|fun|right?", "yes|this|is|fun."]

strings.each { |line|
  
  puts "line = " + line
  
  line.each("|"){ |one, two, three, four|
      puts one, two, three, four
    }
}