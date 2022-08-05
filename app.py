import cv2
import serial,time
face_cascade= cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
cap=cv2.VideoCapture(0)
fourcc= cv2.VideoWriter_fourcc(*'XVID')
ArduinoSerial=serial.Serial('/dev/cu.usbmodem11101',9600,timeout=0.1)
# out= cv2.VideoWriter('face detection4.avi',fourcc,20.0,(640,480))

while True:
    i = True
    ret, frame= cap.read()
    frame=cv2.flip(frame,0)  # verticle flip 
    # print(frame.shape)
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    faces= face_cascade.detectMultiScale(gray,1.1,8)  #detect the face
    for x,y,w,h in faces:
        # sending coordinates to Arduino
        string='X{0:d}Y{1:d}'.format((x+w//2),((y+h//2)))
        if i == True:
            print(string)
            ArduinoSerial.write(string.encode('utf-8'))
            i = False
        cv2.rectangle(frame,(x,y),(x+w,y+h),(100,255,255),1)
    # out.write(frame)
    cv2.imshow('img',frame)
    # press q to Quit
    if cv2.waitKey(10)&0xFF== ord('q'):
        break
cap.release()
cv2.destroyAllWindows()