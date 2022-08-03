import cv2, serial,time
face_cascade= cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
cap=cv2.VideoCapture(0)
ArduinoSerial=serial.Serial('com7',9600,timeout=0.1)
time.sleep(1)

while cap.isOpened():
    ret, frame= cap.read()
    frame=cv2.flip(frame,1)  #mirror the image
    frame=cv2.flip(frame,0)  #verticle flip
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    faces= face_cascade.detectMultiScale(gray,1.1,6)  #detect face
    for x,y,w,h in faces:
        #sending coordinates to Arduino
        coordinates='X{0:d}Y{1:d}'.format((x+w//2),(y+h//2))
        print(coordinates)
        ArduinoSerial.write(coordinates.encode('utf-8'))
        #center of the face
        cv2.circle(frame,(x+w//2,y+h//2),2,(0,255,0),2)
        #rectangle around face
        cv2.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),3)
    #tiny rectangle
    cv2.rectangle(frame,(640//2-30,480//2-30),
                 (640//2+30,480//2+30),
                  (255,255,255),3)
    cv2.imshow('img',frame)
    
    # press q to quit
    if cv2.waitKey(10)&0xFF== ord('q'):
        break
cap.release()
cv2.destroyAllWindows()