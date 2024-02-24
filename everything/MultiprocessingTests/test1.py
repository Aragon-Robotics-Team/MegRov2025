import multiprocessing
from multiprocessing import Process, cpu_count
import time
import os
# from everything.imgProcTraining import basics


def worker1():
    print("ID of process running worker1: {}".format(os.getpid()))

def worker2():
    print("ID of process running worker2: {}".format(os.getpid()))

def colors():
    print("dumb")

# basics.stinky()


# if __name__ == "__main__":
#     print("ID of ma in process: {}".format(os.getpid()))

#     p1 = multiprocessing.Process(target=stinky)
#     p2 = multiprocessing.Process(target=worker2)

#     p1.start()
#     p2.start()

#     print("ID of process p1: {}".format(p1.pid))
#     print("ID of process p2: {}".format(p1.pid))

#     p1.join()
#     p2.join()

#     print("Done!")

#     print("Process 1 is alive: {}".format(p1.is_alive()))
#     print("Process 2 is alive: {}".format(p2.is_alive()))

