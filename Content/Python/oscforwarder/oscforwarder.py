"""Small example OSC server

This program listens to several addresses, and prints some information about
received packets.
"""



"""


/fwd/<host>/<args>  


/fwd/gopher
/fwd/default
/fwd/muskrat
/fwd/localhost
/fwd/<ip>
/fwd/<fqdn>

args provides named args order, comma-delimited no spaces

/fwd/gopher/T,Seek

<host> and <args> are optional
if <args> is omitted, first arg is dropped






"""

# Assume python 3
import sys
if sys.version_info < (3, 0):
	print("Requires Python 3.") 
	sys.exit(0)

from datetime import datetime
import argparse
import math
import traceback,sys
import socket

from pythonosc import dispatcher
from pythonosc import osc_server
from pythonosc.udp_client import SimpleUDPClient




globalArgs = None
clients = {} 

# Simple OSC sender
# Avoids instantiating clients for host:port pairs we've seen before
#
def oscSend(host, port, addr, args):
	print("out---- %s:%i" % (host, port))
	print("        %s %s" % (addr, "" if len(args)==0 else " ".join(args)))	 # not showing the list explicitly makes it easier to cut and paste
	try:
		k = ":".join([host, str(port)])
		if not k in clients:
			client = SimpleUDPClient(host, port) 
			clients[k] = client
		else:
			client = clients[k]
		if not globalArgs.test:
			client.send_message(addr, args) 
	except socket.gaierror as e:
		print("UDP socket error", e)
		if e.args[0]==socket.EAI_NONAME:
			print("Bad host: ", host)
	except Exception:
		print("UDP client general error")
		traceback.print_exc(file=sys.stdout)

# Main handler
#
def fwd(addr, *args):
	print("\nin-----", datetime.today().strftime('%y-%m-%d %H:%M:%S'))
	print("       ", addr, " ".join([str(a) for a in args])) # makes it easier to cut and paste
	try:
		comps = addr.split()
		cmd = comps[0].split("/")[1:]    # forwarder command
		msg = " ".join(comps[1:])
		if cmd[0] != "fwd": 
			print ("\tUnrecognized command:", addr, args)
			return
	except:
		print("Command parsing error:", addr, args)
		return
	
	# <host:port> 
	targetHost = globalArgs.defaulthost
	targetPort = globalArgs.sendport	
	if len(cmd) > 1 and len(cmd[1])>0:   # host specified or blank?
		hostcomps=cmd[1].split(":")      # handle host:port format
		if len(hostcomps) > 1:
			try:
				targetPort=int(hostcomps[1])
			except:
				print("bad port number", hostcomps[1])
		if hostcomps[0]=="localhost":
			targetHost="127.0.0.1"			# is this not defined in /etc/hosts anymore?
		elif hostcomps[0]=="muskrat":      # show specific
			targetHost="muskrat.remap.ucla.edu"
		elif hostcomps[0]=="gopher":
			targetHost="gopher.remap.ucla.edu"
		else: 			
			targetHost = hostcomps[0]
	
	# third component: argmap (comma-delimited)	
	# build keyvalue abuse of OSC message name 
	argMap = []
	if len(cmd) > 2 and len(cmd[2])>0:
		try:
			argMap=cmd[2].split(",")
		except:
			print("Argmap parsing error:", addr, args)
			return
			
	argList = [arg for arg in args]
	print("\tCommand:", cmd[0])
	print("\tTarget:  %s:%i" % (targetHost, targetPort))
	print("\tArgmap: ", argMap)
	print("\tMessage:", msg)
	print("\tArgs:   ", argList)
	try:
		namedArgs=list(map(lambda a, b: "=".join([str(a),str(b)]), argMap, args))
	except:
		print("Problem building namedArgs")
		return
	oscSend(targetHost,targetPort, comps[1], comps[2:] + namedArgs)


if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument("--ip",
      default="", help="The ip to listen on. Default: all interfaces.")
  parser.add_argument("--listenport",
      type=int, default=8061, help="The port to listen on. Default: 8061")
  parser.add_argument("--sendport",
      type=int, default=8060, help="The port to send on.  Default: 8060")
  parser.add_argument("--defaulthost",
      type=str, default="localhost", help="The default host to send to. Default: localhost")
  parser.add_argument("--test", '-t',
      action='count', default=0, help="Print rewriting only, do not send")

  globalArgs = parser.parse_args()

  dispatcher = dispatcher.Dispatcher()
  dispatcher.map("*",fwd)

  if globalArgs.test: 
  	print("*** TEST MODE, NOT SENDING OSC OUT ***") 
  print("Default host:", globalArgs.defaulthost)
  print("Send port:", globalArgs.sendport)
  print("Recv port:", globalArgs.listenport)
  server = osc_server.ThreadingOSCUDPServer(
      (globalArgs.ip, globalArgs.listenport), dispatcher)
  print("Serving on {}".format(server.server_address))
  server.serve_forever()
  