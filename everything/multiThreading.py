import pygame
import cv2
import sys
import serial
from time import sleep
from threading import Thread
import tkinter as tk
import serial
import queue
import time

#

globalState = 0

# sys.path.append("C:/Users/alexa/OneDrive/Documents/GitHub/mate-rov-2023-2024/everything/nav/math_func.py")
# sys.path.append("C:/Users/alexa/OneDrive/Documents/GitHub/mate-rov-2023-2024/everything/nav/nav_main.py")
def Gui():
    root = tk.Tk()
    # root.title("ROV Control Panel")
    

    # # Create a larger canvas
    # canvas_width = 1200  # Adjust the width as needed
    # canvas_height = 800  # Adjust the height as needed
    # canvas = tk.Canvas(root, width=canvas_width, height=canvas_height, bg="white")
    # canvas.pack()


    # imgprog2 = tk.Button(root, text="img prog",)
    # imgprog2.place(x=1, y=35)

    startNav = tk.Button(root, text="Start Nav", command=lambda: globals().update(globalState = 1))
    startNav.place(x=100, y=35)

    stop_button = tk.Button(root, text="Stop Nav", command=lambda: globals().update(globalState = 0))
    stop_button.place(x=300, y=5)

    # depth_label = tk.Label(root, text="IMG PROG:")
    # depth_label.place(x=1, y=5)

    # depth_label = tk.Label(root, text="NAV:")
    # depth_label.place(x=100, y=5)
    root.mainloop()

def navLoop():
    while globalState == 0:
        sleep(1)
    pygame.init()
    print("nav loop started")
    while 1: 
        event = pygame.event.poll()
        if globalState == 1:
            if event.type == pygame.QUIT:
                break
        sleep(0.1)
    pygame.quit()
    


if __name__ == '__main__':
    navThread = Thread(target=Gui,)
    navThread.start()
    navLoop()
    

    





