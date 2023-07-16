import serial
import time

serial_port = serial.Serial('COM3', 9600)
print("Estableciendo conexión con Arduino", serial_port)

time.sleep(2)
arr = ["mitad", 12.67, 0, 1]

try:
    while True:
        #envio:
        arr[1] += 1.1
        arr[1] = round(arr[1],2)
        #arr[2] = not arr[2]
        
        print(f"arr: {arr}")
        arr_str = ','.join(map(str, arr)) + '\n'
        print(f"Enviado: {arr_str}")
        serial_port.write(arr_str.encode())

        time.sleep(1)

except KeyboardInterrupt:
    # Cerrar el puerto serial
    serial_port.close()
    print("Conexión serial cerrada")
