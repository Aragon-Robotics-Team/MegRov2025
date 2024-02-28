import tkinter as tk
import serial 
import sys
sys.path.append("C://Users//alexa//OneDrive//Documents//GitHub//mate-rov-2023-2024//Nav")
import Nav

def send_command(command):
    # Send the command to the ROV through the serial connection
    # ser.write(command.encode())
    print(f"Command sent: {command}")

# Create main window
root = tk.Tk()
root.title("ROV Control Panel")

# Create a larger canvas
canvas_width = 1200  # Adjust the width as needed
canvas_height = 800  # Adjust the height as needed
canvas = tk.Canvas(root, width=canvas_width, height=canvas_height, bg="white")
canvas.pack()


def checkButton(buttonPressed):
    print(buttonPressed)
    


# Create buttons for ROV movement

imgprog2 = tk.Button(root, text="img prog2", command=lambda: move("FORWARD"))
imgprog2.place(x=1, y=35)

imgprog3 = tk.Button(root, text="img prog3", command=lambda: move("FORWARD"))
imgprog3.place(x=1, y=65)




depth_label = tk.Label(root, text="IMG PROG:")
depth_label.place(x=1, y=5)

depth_label = tk.Label(root, text="NAV:")
depth_label.place(x=100, y=5)

# Start the main loop
root.mainloop()