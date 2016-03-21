# -*- coding: utf-8 -*-
from urllib2 import urlopen
import json

class GalileoNetwork:
    server_url = 'http://127.0.0.1'

    def __init__(self):
        self.server_url = GalileoNetwork.server_url

    def __init__(self, server_url):
        self.server_url = server_url

    def __getJSON(self, url):
        data = urlopen(url).read()
        return json.loads(data)

    def __getURLContents(self, page):
        url = self.server_url + page
        try:
            response = urlopen(url)
            html = response.read()
        except Exception as e:
            print e
        return html

    def askPermission(self, person_id):
        """Ask to webservice if the person_id is authorized to enter"""
        print 'Getting authorization for id: %d' % person_id
        jsonResponse = self.__getJSON(self.server_url + 'access.php?user_id=' + str(person_id))
        permission = jsonResponse['data']['access']
        if (permission):
            return True
        else:
            return False

    def getFrame(self):
        """Receive image from webservice"""
        print 'Getting new frame from server'
        return self.__getURLContents('/frame.php')  # Problema de consumidor/produtor ao obter novo frame

    def getFaces(self):
        """Receives new xml from server"""
        print 'Updating faces.xml'
        return self.__getURLContents('/faces.php')
