#!/usr/bin/env ruby

# #define IMAGE_DOS_SIGNATURE                 0x5A4D      // MZ
#struct DOS_Header
# {
#     char signature[2] = "MZ";
#     short lastsize;
#     short nblocks;
#     short nreloc;
#     short hdrsize;
#     short minalloc;
#     short maxalloc;
#     void *ss;
#     void *sp;
#     short checksum;
#     void *ip;
#     void *cs;
#     short relocpos;
#     short noverlay;
#     short reserved1[4];
#     short oem_id;
#     short oem_info;
#     short reserved2[10];
#     long e_lfanew;
# }

class DosHeader
	IMAGE_DOS_SIGNATURE = 0x5a4d
	attr_accessor :signature, :lastsize, :nblocks, :nreloc, :hdrsize, :minalloc
	attr_accessor :maxalloc, :ss, :checksum, :ip, :cs, :relocpos, :noverlay
	attr_accessor :reversed1, :oem_info, :reserved2, :e_lfanew

	def initialize(signature, lastsize, nblocks, nreloc, hdrsize, minalloc, maxalloc, ss, sp, checksum, ip, cs, relocpos, noverlay, reversed1, oem_id, oem_info, reserved2, e_lfanew)
		@signature = signature
		@lastsize = lastsize
		@nblocks = nblocks
		@nreloc = nreloc
		@hdrsize = hdrsize
		@minalloc = minalloc
		@maxalloc = maxalloc
		@ss = ss
		@sp = sp
		@checksum = checksum
		@ip = ip
		@cs = cs
		@relocpos = relocpos
		@noverlay = nooverlay
		@reversed1 = reversed1
		@oem_id = oem_id
		@oem_info = oem_info
		@reserved2 = reserved2
		@e_lfanew = e_lfanew
	end

	def parse_dos_header(file)
		
	end
	
end
