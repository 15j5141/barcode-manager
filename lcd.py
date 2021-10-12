import sensor, image, time, lcd

lcd.init(freq=15000000)
#sensor.reset()


from fpioa_manager import fm
from machine import UART
fm.register(35, fm.fpioa.UART2_TX, force=True)
fm.register(34, fm.fpioa.UART2_RX, force=True)


uart_Port = UART(UART.UART2, 115200,8,0,0, timeout=1000, read_buf_len= 4096)
data_packet = bytearray([0x00,0x00,0x00,0x00,0x00])

#uart_Port.write( data_packet )

def disp_lcd():
    line = uart_Port.readline()
    #lcd.display(img)                # Display on LCD
    if line==None:
        line = "                                                   "
    else:
        line = line.decode('utf8')
    lcd.draw_string(0, 0, "line:"+line, lcd.RED, lcd.BLACK)
    print(line)

x = 0

while(True):
    lcd.draw_string(100, 100, "count:"+str(x), lcd.RED, lcd.BLACK)
    disp_lcd()
    time.sleep(1.0)
    x+=1
