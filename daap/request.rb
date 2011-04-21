#!/usr/bin/env ruby -wKU

require 'socket'
require 'zlib'

def inflate str
  zstream = Zlib::Inflate.new(Zlib:: MAX_WBITS + 32)
  buf = zstream.inflate(str)
  zstream.finish
  zstream.close
	buf	
end

mdns = "\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x14\x68\x61\x6d\x6d\x61\x63\x6b\x6a\xe2\x80\x99\x73\x20\x4c\x69\x62\x72\x61\x72\x79\x05\x5f\x64\x61\x61\x70\x04\x5f\x74\x63\x70\x05\x6c\x6f\x63\x61\x6c\x00\x00\x21\x00\x01"

request = 
"GET daap://10.69.69.10:3689/server-info HTTP/1.1\r\n" +
"Accept: */*\r\n" +
#"User-Agent: iTunes/10.2.1 (Macintosh; Intel Mac OS X 10.6.7) AppleWebKit/533.21.1\r\n" +
"User-Agent: FCK" +
"Host: 10.69.69.10:3689\r\n" +
"Client-DAAP-Version: 3.11\r\n" +
"Client-DAAP-Access-Index: 2\r\n" +
"Accept-Encoding: gzip\r\n\r\n"

login = 
"GET /login HTTP/1.1\r\n" +
"Host: 10.69.69.10:3689\r\n" +
"Client-DAAP-Version: 3.11\r\n" +
"User-Agent: iTunes/10.2.1 (Macintosh; Intel Mac OS X 10.6.7) AppleWebKit/533.21.1\r\n" +
"ITSharing-Version: 3.6\r\n" +
"Accept-Language: en-us, en;q=0.50\r\n" +
"Accept-Encoding: gzip\r\n\r\n"

fpsetup =
"POST /fp-setup?session-id=1411101596 HTTP/1.1\r\n" +
"Host: 10.69.69.10:3689\r\n" +
"Client-DAAP-Version: 3.11\r\n" +
"User-Agent: iTunes/10.2.1 (Macintosh; Intel Mac OS X 10.6.7) AppleWebKit/533.21.1\r\n" +
"ITSharing-Version: 3.6\r\n" +
"Accept-Language: en-us, en;q=0.50\r\n" +
"Accept-Encoding: gzip\r\n" +
"Content-Length: 16\r\n" +
"Content-Type: application/octet-stream\r\n\r\n"

udp = UDPSocket.open
#udp.send(mdns, 0, "224.0.0.251", 5353)
#puts udp.recvfrom(65000)

tcp = TCPSocket.open("10.69.69.10", 3689)
tcp.write request
response = tcp.recv(1024)
puts response

if response =~ /200 OK/
	gzip = tcp.recv(1024)
	puts inflate(gzip)
end

tcp.write login
response = tcp.recv(1024)
puts response

if response =~ /200 OK/
	gzip = tcp.recv(1024)
	buf = inflate(gzip)
	buf = buf.split("mlid")[1]

	

	
end

tcp.write fpsetup
tcp.write "A" * 100

response = tcp.recv(1024)
puts response

tcp.close
