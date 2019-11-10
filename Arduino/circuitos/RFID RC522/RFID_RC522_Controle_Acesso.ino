// Programa : RFID - Controle de acess0
// Autor : Ismael Lopes

#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9

// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); 

// Indicação sonora de acesso liberado ou negado
const int buzzer = 4;

char st[20];

void sinal_beep(int frequencia,int duracao)
{   
  tone(buzzer,frequencia);
  delay(duracao);
  noTone(buzzer);
  delay(duracao);
}

void setup() 
{
  pinMode(buzzer, OUTPUT);
  // Inicia a serial
  Serial.begin(9600);
  // Inicia SPI bus
  SPI.begin();
  // Inicia MFRC522
  mfrc522.PCD_Init(); 
  // Mensagens iniciais no serial monitor
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
}

void loop() 
{
  // Aguarda a aproximacao do cartao
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      return;
    }
  // Seleciona um dos cartoes
  if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      return;
    }
  // Mostra UID na serial
  sinal_beep(1000,200);
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  
  // Testa se um determinado cartao foi lido
  if (conteudo.substring(1) == "53 8E 90 55")
  {
    // Acende o led verde
    sinal_beep(2500,100);
    sinal_beep(2000,100);
    Serial.println("Cartao - Acesso liberado !");
  }
}

