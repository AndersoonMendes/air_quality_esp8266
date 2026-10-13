#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <modelo_pm25.h>

// configurações do wifi
const char* WIFI_SSID = "rede wifi";
const char* WIFI_PASS = "senha do wifi";

// url da api para pegar a qualidade do ar de manaus(pm10, pm2.5 e CO)
const char* API_URL = "https://air-quality-api.open-meteo.com/v1/air-quality?latitude=-3.1019&longitude=-60.025&current=pm10,pm2_5,carbon_monoxide";

void conectarWiFi(){
  Serial.println("Conectando ao Wifi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");  
  }
  Serial.println("\nWifi conectado!");
  Serial.print("IP`do ESP8266: ");
  Serial.println(WiFi.localIP());
}

void requisitarDados(){
  if(WiFi.status() == WL_CONNECTED){ // verifica se ta conectado ao wifi
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure); // necessario para lidar com requisições HTTPS
    client->setInsecure(); // abre a conexao evitando as validações dos certificados digitais(para evitar consumo de RAM)

    HTTPClient http;

    Serial.println("\nEnviando a requisição para a API...");
    if(http.begin(*client, API_URL)){
      int httpCode = http.GET(); // executa o GET, httpCode -> 200(ok), 404(nao encontrado) ou 500(erro interno no servidor) 

      if(httpCode == HTTP_CODE_OK){
        String payload = http.getString(); // receber o texto do JSON

        // processar o JSON recebido
        JsonDocument doc; // aloca uma estrutura na memória para o parser
        DeserializationError error = deserializeJson(doc, payload); // converte a string em objeto acessível - analisa a String do JSON e cria uma árvore sintática na memória chamada doc.

        if(!error){
            // extrair campos desejados do JSON
            float pm10 = doc["current"]["pm10"];
            float pm25 = doc["current"]["pm2_5"];
            float co = doc["current"]["carbon_monoxide"];

            // imprime os valores que foram puxados do JSON
            Serial.println("----------------------------------------");
            Serial.print("pm10: ");
            Serial.println(pm10);

            Serial.print("pm2.5: ");
            Serial.println(pm25);

            Serial.print("co2: ");
            Serial.println(co);

            // converter o valor float de pm25 em int16_t para a IA processar essa informação e realizar a predição
            int16_t dados[] = {
              static_cast<int16_t>(pm25)
            };
            int16_t predicao = modelo_pm25_predict(dados, 1); // chama o modelo de IA para fazer a predição e retorna um valor inteiro
            Serial.print("predição da ia: ");
            Serial.println(predicao);
            switch (predicao) {
              case 0:
                  Serial.println("Qualidade do ar: BOM");
                  break;

              case 1:
                  Serial.println("Qualidade do ar: MODERADO");
                  break;

              case 2:
                  Serial.println("Qualidade do ar: INSALUBRE PARA GRUPOS SENSÍVEIS");
                  break;

              case 3:
                  Serial.println("Qualidade do ar: INSALUBRE");
                  break;

              case 4:
                  Serial.println("Qualidade do ar: MUITO INSALUBRE");
                  break;

              default:
                  Serial.println("Classe de qualidade do ar desconhecida!");
                  break;
          }

          Serial.println("----------------------------------------");

        } else{
          Serial.print("Error ao interoretar JSON");
          Serial.print(error.c_str());
        }
      } else {
        Serial.printf("Falha na requisição HTTP, código de erro: %d\n", httpCode);
      }

      http.end();
    } else{
      Serial.println("Nao foi possivel conectar ao servidor");
    }
  } else{
    Serial.println("Wi-Fi Desconectado!");
  }

}

void setup(){
  Serial.begin(115200);
  conectarWiFi();
}

void loop(){
  requisitarDados();
  delay(30000);
}