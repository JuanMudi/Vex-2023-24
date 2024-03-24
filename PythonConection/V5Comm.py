import serial
from serial.tools.list_ports import comports
import threading
from threading import Lock

class V5SerialComms:

    def __init__(self):
        self.__started = False
        self.__ser = None

    def start(self):
        self.__started = True
        self.__thread = threading.Thread(target=self.__run, args=())
        self.__thread.daemon = True
        self.__thread.start()

    def __run(self):
        count = 1
        while self.__started:  # Continue running while the thread is started
            port = None
            try:
                if not self.__ser:
                    devices = [dev for dev in comports() if "V5" in dev.description and "User" in dev.description]
                    if len(devices) == 0 and count <= 5:
                        print("No V5.")
                        time.sleep(1)
                        count += 1
                        continue
                    elif count > 5:
                        print("No V5 Brain detected after 5 attempts.")
                        return
                    else:
                        port = devices[0].device

                    print("Connecting to ", port)

                    self.__ser = serial.Serial(port, 115200, timeout=10)
                    self.__ser.flushInput()
                    self.__ser.flushOutput()

                data = self.__ser.readline()
                print("Bytes recibidos:", data)
                if data == "AA55CC3301":
                    data = "hola".to_Serial()
                    self.__ser.write(data)
                    print("Paquete de datos enviado correctamente.")

            except serial.SerialException as e:
                print("Could not connect to ", port, ". Exception: ", e)
                time.sleep(1)
        
            if self.__ser and self.__ser.isOpen():
                self.__ser.close()

        print("V5SerialComms thread stopped.")

    def __del__(self):
        self.stop()

if __name__ == "__main__":
    v5_serial = V5SerialComms()
    v5_serial.start()
