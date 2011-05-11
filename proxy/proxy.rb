#!/usr/bin/env ruby -wKU
 
class SimpleProxy 
    def initialize
      require 'webrick/httpproxy'
      require 'webrick/httpauth/basicauth'
      require 'webrick/httpauth/userdb'

      @proxy_server = nil
    end

    def start_proxy
      # First work around WEBrick's braindead interrupt handling
      trap("INT") { @proxy_server.shutdown }

      # Set up the proxy itself
      @proxy_server = WEBrick::HTTPProxyServer.new(
          :LogFile => $stdout,
          :BindAddress => "0.0.0.0",
          :Port => '9415',
					#:RequestCallback => Proc.new { |req, res| puts req.request_line, req.raw_header })
					:RequestCallback => Proc.new { |req, res| call_back(req, res) })

      ## TODO - this is going to block - how to avoid this??      
      @proxy_server.start
    end

    def stop_proxy
      @proxy_server.shutdown
			exit
    end

		def call_back(req, res)
			puts "==="
			puts req.methods
			puts "==="
			#puts req.raw_header
			#puts res.body
		end
end

s = SimpleProxy.new
s.start_proxy

