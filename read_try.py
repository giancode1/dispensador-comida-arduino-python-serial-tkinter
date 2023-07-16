import serial
import time

def establecer_conexion():
    while True:
        try:
            serial_port = serial.Serial('COM3', 9600)
            print("Estableciendo conexión con Arduino", serial_port)
            time.sleep(2)
            return serial_port
        except serial.SerialException:
            print("¡Error de conexión con Arduino!")
            respuesta = input("¿Deseas volver a intentar? (s/n): ")
            if respuesta.lower() == "n":
                return None
            elif respuesta.lower() == "s":
                continue

serial_port = establecer_conexion()

if serial_port is not None:
    try:
        while True:
            try:
                rawString = serial_port.readline().decode('utf-8')
                print(rawString)
                time.sleep(0.1)
            except serial.SerialException:
                print("¡Error de conexión con Arduino!")
                break

    except KeyboardInterrupt:
        # Cerrar el puerto serial
        serial_port.close()
        print("Conexión serial cerrada")
