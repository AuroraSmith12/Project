import sensor, image, lcd, time
import KPU as kpu
from fpioa_manager import fm
from machine import UART
from fpioa_manager import fm
import time

fm.register(15, fm.fpioa.UART1_TX, force=True)#IO15--TX
fm.register(16, fm.fpioa.UART1_RX, force=True)#IO16--RX

uart_A = UART(UART.UART1, 9600, 8, 0, 0, timeout=1000, read_buf_len=4096)

color_R = (255, 0, 0)
color_G = (0, 255, 0)
color_B = (0, 0, 255)


class_IDs = ['no_mask', 'mask']


def drawConfidenceText(image, rol, classid, value):
    text = ""
    _confidence = int(value * 100)

    if classid == 1:
        text = 'mask: ' + str(_confidence) + '%'
        color_text=color_G
    else:
        text = 'no_mask: ' + str(_confidence) + '%'
        color_text=color_R
    image.draw_string(rol[0], rol[1], text, color=color_text, scale=2.5)



lcd.init()
sensor.reset(dual_buff=True)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_hmirror(0)
sensor.run(1)


task = kpu.load(0x300000)


anchor = (0.1606, 0.3562, 0.4712, 0.9568, 0.9877, 1.9108, 1.8761, 3.5310, 3.4423, 5.6823)
_ = kpu.init_yolo2(task, 0.5, 0.3, 5, anchor)
img_lcd = image.Image()

clock = time.clock()
while (True):
    clock.tick()
    img = sensor.snapshot()
    code = kpu.run_yolo2(task, img)
    if code:
        totalRes = len(code)

        for item in code:
            confidence = float(item.value())
            itemROL = item.rect()
            classID = int(item.classid())

            if confidence < 0.52:
                _ = img.draw_rectangle(itemROL, color=color_B, tickness=5)
                uart_A.write("1")
                continue

            if classID == 1 and confidence > 0.65:
                _ = img.draw_rectangle(itemROL, color_G, tickness=5)
                uart_A.write("2")
                if totalRes == 1:
                    drawConfidenceText(img, (0, 0), 1, confidence)
            else:
                _ = img.draw_rectangle(itemROL, color=color_R, tickness=5)
                if totalRes == 1:
                    drawConfidenceText(img, (0, 0), 0, confidence)

    _ = lcd.display(img)

    print(clock.fps())

_ = kpu.deinit(task)
