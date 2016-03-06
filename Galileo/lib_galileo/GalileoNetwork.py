from urllib2 import urlopen
import json

class GalileoNetwork:
    server_url = 'http://127.0.0.1'

    def __init__(self, server_url):
        self.server_url = server_url

    def __getJSON(self, url):
        data = urlopen(url).read()
        return json.loads(data)

    def __getURLContents(self, page):
        url = self.server_url + page
        response = urlopen(url)
        html = response.read()
        return html

    def askPermission(self, person_id):
        """Ask to webservice if the person_id is authorized to enter"""
        jsonResponse = self.__getJSON(self.server_url + 'access.php?user_id=' + person_id)
        permission = jsonResponse['access']
        if (permission == 'true'):
            return True
        else:
            return False

    def getFrame(self):
        """Receive image from webservice"""
        return self.__getURLContents('/frame.php')

    def getFaces(self):
        """Receives new xml from webservice"""
        return self.__getURLContents('/faces')
