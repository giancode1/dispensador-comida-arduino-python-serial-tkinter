import serial
import time

serial_port = serial.Serial('COM3', 9600)
print("Estableciendo conexión con Arduino", serial_port)

time.sleep(2)

try:
    while True:
        rawString = serial_port.readline().decode('utf-8')
        print(rawString)
        time.sleep(0.1)

except KeyboardInterrupt:
    # Cerrar el puerto serial
    serial_port.close()
    print("Conexión serial cerrada")
