import tkinter as tk
from tkinter import messagebox

import cv2
import numpy as np
import imutils
import math

x1 = 0
y1 = 0
old_x = 0
old_y = 0
varlist  = []

#step 1: take picture :)
#step 2: click two dots--find distance :-)
#step 3: step 2 again
#step 4: math

#magical picture stuffs
vid = cv2.VideoCapture(0)

def popup(message):

    import tkinter as tk
    from tkinter import messagebox

    # Initialize Tkinter root
    root = tk.Tk()
    root.withdraw()  # Hide the main window

    # Show the popup message
    messagebox.showinfo("Information", message)

    root.destroy()  # Close the hidden main window

text0 = "Initializing..."
popup(text0)

while True:
    ret, frame, = vid.read()

    cv2.imshow('frame', frame)

    if cv2.waitKey(1) & 0xFF == ord('p'):
        cv2.imwrite('/Users/sofia/Downloads/pic.jpeg',frame)
        img=cv2.imread('/Users/sofia/Downloads/pic.jpeg')
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

vid.release()
cv2.destroyAllWindows()
def draw_circle(event, x, y, flags, param): 
      
    if event == cv2.EVENT_LBUTTONDOWN: 
        print("u maed a corcle!1!1!11") 
        cv2.circle(img, (x, y), 5, (0, 255, 0), -1) 
        global x1
        global y1
        global old_x
        global old_y
        x1 = x
        y1 = y
        global varlist
        if x1 != old_x or y1 != old_y:
            varlist.append(x1)
            varlist.append(y1)
        old_x = x
        old_y = y
          
cv2.namedWindow(winname = "Title of Popup Window") 
cv2.setMouseCallback("Title of Popup Window", draw_circle) 

while True:
    cv2.imshow("Title of Popup Window", img) 
    print(varlist)
    if cv2.waitKey(1) & 0xFF == 'q': 
        break
    if cv2.waitKey(1) & len(varlist) == 8:
        break

cv2.destroyAllWindows()

d1 = math.sqrt(((varlist[0]-varlist[2])**2)+((varlist[1]-varlist[3])**2))
d2 = math.sqrt(((varlist[4]-varlist[6])**2)+((varlist[5]-varlist[7])**2))
text = (d1/d2)*2.54
print(text)

popup(text)