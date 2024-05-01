import cv2 
from time import sleep
  
vid = cv2.VideoCapture(0) 
i = 1
running = True  
while(True): 
      
    ret, frame = vid.read() 
  
    cv2.imshow('frame', frame) 
    
    while running:
        cv2.imwrite(r'C:\Users\dogei\python\MATE_ROV\CAMERA\mee' + str(i) + '.jpg', frame)
        print('taken')
        print(i)
        i += 1
        sleep(1)
        

    if cv2.waitKey(1) & 0xFF == ord('q'): 
        break
  
vid.release() 

cv2.destroyAllWindows() 