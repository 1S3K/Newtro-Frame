import os
from PIL import Image, ImageOps
import cv2
import serial
import time
import json, os, requests
from dotenv import load_dotenv
load_dotenv()

cap = cv2.VideoCapture(0)
cap.set(3, 640)
cap.set(4, 480)

subscription_key = os.environ['FACE_SUBSCRIPTION_KEY']
assert subscription_key

face_api_url = os.environ['FACE_ENDPOINT'] + '/v1.0/detect'
headers = {
    'Ocp-Apim-Subscription-Key': subscription_key,
    'Content-Type': 'application/octet-stream'
}
params = {
    'returnFaceId': 'true',
    'returnFaceAttributes': 'emotion'
}

arduino = serial.Serial('COM10', 9600)
def toArduino(emo_type):
    emo_type = emo_type.encode('utf-8')
    arduino.write(emo_type)

def recognition(emotion):
    anger = emotion['anger']
    contempt = emotion['contempt']
    disgust = emotion['disgust']
    fear = emotion['fear']
    happiness = emotion['happiness']
    neutral = emotion['neutral']
    sadness = emotion['sadness']
    surprise = emotion['surprise']

    if neutral >= 0.9:
        toArduino('a')
    elif happiness >= 0.75:
        toArduino('b')
    elif surprise >= 0.8:
        toArduino('c')
    else:
        toArduino('d')

while True:
    ret, frame = cap.read()
    
    frame = cv2.flip(frame,1) # 좌우 전환

    t = time.localtime()
    if (t.tm_sec % 5 == 0):
        cv2.imwrite('./img/capture.jpg',frame)
        pathToFileInDisk = './img/capture.jpg'
        with open( pathToFileInDisk, 'rb' ) as f:
            data = f.read()

        response = requests.post(face_api_url, data=data, params=params, headers=headers, json=None)
        result = response.json()
        if (result != []):
            emotion = result[0]['faceAttributes']['emotion']
            recognition(emotion)
            print(emotion)
    cv2.imshow("Camera", frame)
    if cv2.waitKey(1) > 0: break

cap.release()
cv2.destroyAllWindows()