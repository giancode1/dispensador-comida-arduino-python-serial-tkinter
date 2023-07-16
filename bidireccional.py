import serial
import time

serial_port = serial.Serial('COM3', 9600)
print("Estableciendo conexión con Arduino", serial_port)

time.sleep(2)

# Variables para el seguimiento del tiempo
intervalo_envio = 1  # Intervalo de tiempo en segundos
ultimo_envio = 0     # Tiempo del último envío

arr = ["vacio", 12.67, 0, 1]
try:
    while True:
        # Enviar datos cada segundo
        tiempo_actual = time.time()
        if tiempo_actual - ultimo_envio >= intervalo_envio:
            ultimo_envio = tiempo_actual

            #envio:
            arr[1] += 2.4
            arr[1] = round(arr[1], 1)

            arr_str = ','.join(map(str, arr)) + '\n'
            print(f"Enviado: {arr_str}")
            serial_port.write(arr_str.encode())


        
        #recibir:
        rawString = serial_port.readline().decode('utf-8').strip()
        print("recibido, rawString: ", rawString)
        time.sleep(0.1)
        if rawString:
            data = rawString.split(',')
            data.pop()  # ''
            print("recibido, data: ", data)




        # time.sleep(0.1)

except KeyboardInterrupt:
    # Cerrar el puerto serial
    serial_port.close()
    print("Conexión serial cerrada")
