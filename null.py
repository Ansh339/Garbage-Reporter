import urllib.request
import time
import RPi.GPIO as GPIO
import json

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(4,GPIO.OUT)
GPIO.output(4,GPIO.LOW)

def ThingSpeakLinkRead(link):
    RspR=urllib.request.urlopen(link)
    response = RspR.read()
    data=json.loads(response)
    Stats=data['feeds'][1]['field1']
    RspR.close()
    return Stats



while True:
    LinkR="https://api.thingspeak.com/channels/1578083/feeds.json?api_key=WAD8F0B69WMGHDSH&results=2"
    Stats=ThingSpeakLinkRead(LinkR)
    if str(Stats)!='None':
        print("Dustbin Status: "+Stats)
        if int(Stats)>90:
            GPIO.output(4,GPIO.HIGH)
            time.sleep(0.5)
            GPIO.output(4,GPIO.LOW)
            time.sleep(0.5)
            GPIO.output(4,GPIO.HIGH)
            time.sleep(0.5)
            GPIO.output(4,GPIO.LOW)
            time.sleep(0.5)
            GPIO.output(4,GPIO.HIGH)
            time.sleep(0.5)
            GPIO.output(4,GPIO.LOW)
    time.sleep(5)    
