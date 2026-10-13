# 🌫️ Monitoramento da Qualidade do Ar com ESP8266 e Machine Learning

Projeto de estudo que integra Internet das Coisas (IoT), consumo de APIs e Machine Learning para classificar a qualidade do ar a partir da concentração de partículas finas (PM2.5).

O sistema utiliza um ESP8266 para consultar dados da qualidade do ar em Manaus por meio da API Open-Meteo. Em seguida, um modelo de Machine Learning treinado em Python e exportado para C++ realiza a classificação diretamente no microcontrolador.

## 📌 Objetivos

- Consultar dados de qualidade do ar por meio de uma API.
- Processar respostas JSON em um sistema embarcado.
- Treinar um modelo de classificação utilizando Python e Scikit-learn.
- Exportar o modelo para C++ com a biblioteca emlearn.
- Executar inferências em um ESP8266.

## ⚙️ Tecnologias utilizadas

| Tecnologia | Aplicação |
|---|---|
| ESP8266 | Execução do firmware e conexão Wi-Fi |
| C++ / Arduino | Desenvolvimento do firmware |
| PlatformIO | Compilação e gerenciamento do projeto embarcado |
| Python | Preparação dos dados e treinamento do modelo |
| NumPy e Pandas | Manipulação e organização dos dados |
| Scikit-learn | Treinamento e avaliação do modelo |
| emlearn | Conversão do modelo para C/C++ |
| ArduinoJson | Interpretação das respostas JSON |
| Open-Meteo API | Fonte dos dados de qualidade do ar |

## 📊 Dados utilizados

O firmware consulta a API Open-Meteo para obter os seguintes parâmetros:

| Parâmetro | Descrição | Unidade |
|---|---|---|
| PM2.5 | Concentração de partículas finas | µg/m³ |
| PM10 | Concentração de partículas inaláveis | µg/m³ |
| CO | Concentração de monóxido de carbono | µg/m³, conforme a API |

A consulta utiliza coordenadas da região de Manaus, Amazonas.

**Observação:** CO é monóxido de carbono, não dióxido de carbono (CO₂). Embora o firmware consulte os três parâmetros, atualmente o modelo utiliza apenas PM2.5 para realizar a predição.

## 🧠 Treinamento do modelo

O modelo é treinado em Python utilizando o `RandomForestClassifier`, da biblioteca Scikit-learn.

O script de treinamento é responsável por:

1. Gerar ou preparar os dados de PM2.5.
2. Definir os rótulos das categorias.
3. Separar os dados em conjuntos de treinamento e teste.
4. Treinar o classificador Random Forest.
5. Avaliar o resultado com métricas de classificação.
6. Exportar o modelo para C/C++ usando a biblioteca `emlearn`.

Os dados gerados artificialmente são úteis para testar o funcionamento do pipeline, mas não substituem um conjunto de medições reais e representativas. O desempenho obtido com dados simulados não garante o mesmo desempenho em condições reais.

### Estrutura da pasta de treinamento

```text
treinamento/
├── treinar_modelo.py
└── requirements.txt
```

### Instalação das dependências

Recomenda-se utilizar um ambiente virtual Python.

No terminal, entre na pasta de treinamento e crie o ambiente:

```bash
python -m venv .venv
```

Ative-o no Windows PowerShell:

```powershell
.\.venv\Scripts\Activate.ps1
```

Instale as dependências:

```bash
python -m pip install -r requirements.txt
```

O arquivo `requirements.txt` contém:

```text
numpy
pandas
scikit-learn
emlearn
```

### Executando o treinamento

Com o ambiente virtual ativado, execute:

```bash
python treinar_modelo.py
```

O script deve treinar e avaliar o modelo e, caso esteja configurado para isso, gerar o arquivo C/C++ necessário para a inferência no ESP8266.

> O nome e o caminho do arquivo exportado devem corresponder ao cabeçalho utilizado pelo firmware. Neste projeto, o firmware inclui `modelo_pm25.h`.

## 🔄 Funcionamento do sistema

1. O ESP8266 inicia e conecta-se à rede Wi-Fi.
2. O dispositivo realiza uma requisição HTTPS à API Open-Meteo.
3. A resposta recebida é interpretada como JSON.
4. O firmware extrai os valores de PM2.5, PM10 e CO.
5. O valor de PM2.5 é convertido para o formato de entrada esperado pelo modelo.
6. O Random Forest exportado realiza a inferência no próprio microcontrolador.
7. A classe prevista é apresentada no Monitor Serial.
8. O processo se repete a cada 30 segundos.

## 📁 Estrutura do projeto

```text
qualidade_do_ar_requisitando/
├── include/
│   └── modelo_pm25.h
├── src/
│   └── main.cpp
├── treinamento/
│   ├── treinar_modelo.py
│   └── requirements.txt
├── test/
├── .gitignore
├── platformio.ini
└── README.md
```

## 🛠️ Como executar o firmware

### Pré-requisitos

- Visual Studio Code
- Extensão PlatformIO IDE
- Placa ESP8266 compatível
- Rede Wi-Fi com acesso à internet
- Arquivo `modelo_pm25.h` gerado pelo processo de treinamento

### Configuração

1. Clone o repositório:

   ```bash
   git clone https://github.com/SEU-USUARIO/qualidade-do-ar-esp8266.git
   ```

2. Abra a pasta do projeto no Visual Studio Code.

3. Configure as credenciais Wi-Fi localmente, sem publicá-las no GitHub.

4. Confira as dependências e a placa configuradas em `platformio.ini`.

5. Conecte o ESP8266 ao computador.

6. Compile e envie o firmware usando o PlatformIO.

7. Abra o Monitor Serial na velocidade configurada no firmware para acompanhar as consultas e as predições.

## 🔐 Segurança

- Não publique senhas de Wi-Fi, tokens ou outras credenciais.
- Mantenha arquivos de configuração locais fora do controle de versão.
- Em aplicações reais, valide o certificado HTTPS do servidor.
- Evite desativar a verificação dos certificados TLS, como ocorre com `setInsecure()`.

## 🚀 Melhorias futuras

- Adicionar um display OLED para exibir a classificação.
- Criar um painel para acompanhar o histórico das medições.
- Utilizar conjuntos de dados reais para treinar e avaliar o modelo.
- Comparar as predições com as categorias oficiais do índice de qualidade do ar adotado.
- Adicionar tratamento de erros de conexão e respostas inválidas da API.
- Avaliar o consumo de memória e o tempo de inferência no ESP8266.

## 🎯 Aprendizados

O projeto explora a integração entre sistemas embarcados, comunicação HTTP/HTTPS, processamento de JSON, preparação de dados, treinamento de modelos e inferência de Machine Learning em dispositivos com recursos limitados.

---

**Projeto de estudo — IoT, Sistemas Embarcados e Machine Learning.**