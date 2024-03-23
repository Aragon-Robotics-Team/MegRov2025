import cv2
import sys
import pygame
import serial
from time import sleep
import multiprocessing
#threading not processing
from multiprocessing import Process, Queue
import tkinter as tk
import serial

sys.path.append("C:/Users/alexa/OneDrive/Documents/GitHub/mate-rov-2023-2024/Nav")
import Nav
import MathFunc

def navProcess():
    Nav.nav()

class GUIClass():
    def __init__(self):
        root = tk.Tk()
        root.title("ROV Control Panel")

        # Create a larger canvas
        canvas_width = 1200  # Adjust the width as needed
        canvas_height = 800  # Adjust the height as needed
        canvas = tk.Canvas(root, width=canvas_width, height=canvas_height, bg="white")
        canvas.pack()

        self.guiNav = multiprocessing.Queue()
        self.navGUI = multiprocessing.Queue()

        imgprog2 = tk.Button(root, text="img prog", command=lambda: move("FORWARD"))
        imgprog2.place(x=1, y=35)

        startNav = tk.Button(root, text="Start Nav", command=lambda: move("FORWARD"))
        startNav.place(x=100, y=35)

        stop_button = tk.Button(root, text="Stop Nav", command=lambda: send_command("STOP"))
        stop_button.place(x=300, y=5)

        depth_label = tk.Label(root, text="IMG PROG:")
        depth_label.place(x=1, y=5)

        depth_label = tk.Label(root, text="NAV:")
        depth_label.place(x=100, y=5)

        ##

        depth_label = tk.Label(root, text="Depth Control:")
        depth_label.place(x=1, y=200)
        depth_slider = tk.Scale(root, from_=0, to=100, orient=tk.HORIZONTAL, command=lambda value: depth_control(value))
        depth_slider.place(x=1, y=220)

        arm_button = tk.Button(root, text="Toggle Claw", command=toggle_arm)
        arm_button.place(x=525, y=5)


if __name__ == '__main__':
    q = Queue()
    p1 = Process(target=navProcess)
    p2 = Process(target=GUIClass)
    





