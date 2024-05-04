import cv2 
from time import sleep
  
vid = cv2.VideoCapture(0) 
i = 0 
while True: 
      
    ret, frame = vid.read() 
  
    cv2.imshow('frame', frame) 
    
    if cv2.waitKey(1) == ord('s'):
        cv2.imwrite(f'C://Users//alexa//OneDrive//Desktop//Photogrammetry{i}.jpg', frame)

        if not cv2.imwrite(f'C://Users//alexa//OneDrive//Desktop//Photogrammetry{i}.jpg', frame):
            raise Exception("Could not write image")
        
        cv2.imshow(f'C://Users//alexa//OneDrive//Desktop//Photogrammetry{i}.jpg', frame)
        cv2.waitKey(0)
        print('taken')
        print(i)
        i += 1  
        

    if cv2.waitKey(1) & 0xFF == ord('q'): 
        vid.release()
        cv2.destroyAllWindows()
        break