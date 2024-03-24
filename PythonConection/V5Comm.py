import serial
from serial.tools.list_ports import comports

def encontrar_puerto_serial():
    try:
        # Buscar dispositivos serie disponibles
        dispositivos = comports()
        
        for puerto in dispositivos:
            # Verificar si el dispositivo tiene una descripción que contiene "V5" y "User"
            if "V5" in puerto.description and "User" in puerto.description:
                return puerto.device
        
        # Si no se encuentra ningún puerto, devuelve None
        print("No se encontró ningún puerto V5 Brain.")
        return None
    except Exception as e:
        print("Error al buscar el puerto serial:", e)
        return None

def establecer_conexion(puerto_serial, baudrate=115200, timeout=1):
    try:
        # Establecer la conexión serial
        conexion = serial.Serial(puerto_serial, baudrate, timeout=timeout)
        print("Conexión establecida en el puerto", puerto_serial)
        return conexion
    except serial.SerialException as e:
        print("Error al conectar al puerto", puerto_serial)
        print("Exception:", e)
        return None

def enviar_datos(conexion):
    try:
        # Enviar datos cuando se recibe el mensaje "AA55CC3301"
        while True:
            data = conexion.readline().strip()
            if data.decode("utf-8") == "AA55CC3301":
                print("Mensaje recibido:", data.decode("utf-8"))
                # Envía los datos que desees aquí
                conexion.write(b"Probando conexion desde RaspBerry\r\n")
    except KeyboardInterrupt:
        print("Deteniendo el envío de datos.")
        conexion.close()

def main():
    puerto = encontrar_puerto_serial()
    if puerto is None:
        return
    
    baudrate = 115200  # Puedes cambiar esto si necesitas otro baudrate
    timeout = 1  # Tiempo de espera para lectura

    # Establecer la conexión serial
    conexion = establecer_conexion(puerto, baudrate, timeout)
    
    if conexion is not None:
        enviar_datos(conexion)

if __name__ == "__main__":
    main()
