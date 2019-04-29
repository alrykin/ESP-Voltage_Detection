# -*- coding: utf-8 -*-
from grab import Grab
import re
import time


URL_List = ['http://192.168.1.100/','http://172.20.10.2/']   #IP адреса ESP


def get_state(g, url):
    try :
        g.go(url)
        return g.doc.select('/html/body/h1').text()   
    except:
        return 'No connection'


def main():
    while(1):
        for URL in URL_List:
            g = Grab()
            g.setup(encoding='utf-8', connect_timeout=3, timeout=5)
            print("{0} state: {1}".format(URL,get_state(g, URL)))
            time.sleep(1)            

if __name__ == "__main__":
    main()
