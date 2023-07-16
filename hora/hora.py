import serial
import time

serial_port = serial.Serial('COM3', 9600)
print("Estableciendo conexión con Arduino", serial_port)


current_time = time.strftime('%H:%M:%S')
arr = [current_time, 12.67, 0, 1]

time.sleep(5) # 5 segundos

try:
    # while True:
    #enviar datos:
    arr_str = ','.join(map(str, arr)) + '\n'
    serial_port.write(arr_str.encode())
    print(f"Enviado: {arr_str}")


    time.sleep(10)
    arr[0] = '13:01:11'   #siempre longitud de 8
    arr_str = ','.join(map(str, arr)) + '\n'
    serial_port.write(arr_str.encode())
    print(f"Enviado: {arr_str}")
    
    
    time.sleep(10)
    arr[0] = '14:20:20'   #siempre longitud de 8
    arr_str = ','.join(map(str, arr)) + '\n'
    serial_port.write(arr_str.encode())
    print(f"Enviado: {arr_str}")


except KeyboardInterrupt:
    # Cerrar el puerto serial
    serial_port.close()
    print("Conexión serial cerrada")
