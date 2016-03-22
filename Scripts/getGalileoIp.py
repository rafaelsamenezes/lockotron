#!/usr/bin/python
# -*- coding: utf-8 -*-
import socket
from pprint import pprint

port = 1534
file_name = '../web/galileo_ip.php'

sock = socket.socket(type=socket.SOCK_DGRAM)
sock.bind(("", port))

msg = ""
print "Aguardando mensagem UDP na porta %d" % port
while True:
    try:
        msg, addr = sock.recvfrom(232)
        print "   Mensagem recebida:"
        print msg
        print
        if (msg[:4] == 'TCF2'):
            print "   VÁLIDA."
            break
        else:
            print " - INVÁLIDA."
    except KeyboardInterrupt as e:
        break

if (msg != ""):
    lines = msg.split('\x00')
    # Keep only lines with a '=' symbol
    lines = [x for x in lines if '=' in x]
    d = dict(x.split('=') for x in lines)

    print
    pprint(d, indent=2, width=1)

    if 'Linux' and 'yocto' in d.get('OSName'):
        print
        contents = '<?php $galileo_ip="%s";' % d.get('Host')
        php_file = file(file_name, 'w')
        php_file.write(contents)
        print '`%s` escrito no arquivo "%s"' % (contents, php_file.name)
else:
    print "\nCancelado."
