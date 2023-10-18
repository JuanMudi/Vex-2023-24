import cv2 as cv
import numpy as np
import os
from time import time
from auxiliarFunctions import WindowCapture



os.chdir(os.path.dirname(os.path.abspath(__file__)))    

WindowCapture.list_window_names()

# Initialize the WindowCapture class
wincap = WindowCapture('(1225) VEX Robotics Competition: Over Under | 2023 - 2024 Game - YouTube — Mozilla Firefox')


loop_time = time()
while(True):

    # Get an updated image of the game
    screenshot = wincap.get_screenshot()

    # Display the picture
    cv.imshow('Unprocessed', screenshot)

    # debug the loop rate
    print('FPS {}'.format(1 / (time() - loop_time)))
    loop_time = time()

    # Press "q" to quit
    # wait 1 ms every loop to process key presses

    key = cv.waitKey(1)
    if cv.waitKey(1) == ord('q'):
        cv.destroyAllWindows()
        break
    elif key == ord('p'):
        cv.imwrite('positive/{}.jpg'.format(loop_time), screenshot)
    elif key == ord('n'):
        cv.imwrite('negative/{}.jpg'.format(loop_time), screenshot)

    print('Done.')
