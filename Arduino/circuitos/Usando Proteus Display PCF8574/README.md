# Proteus-Arduino-Display-PCF8574
Projeto Proteus com Arduino Display 16x2 comunicação I2C interfaceado pelo CI PCF8574 e Virtual Terminal.
Após a inicialização as duas linhas do Display são escritas e depois aguarda uma string entrada pelo
Virtual Terminal e escreve na segunda linha do Display. O endereço de comunicação I2C com o CI PCF8574
é #20 porque os pinos A0, A1 e A2 estão conectados no ground (GND), então, o dispositivo responde em #20.
